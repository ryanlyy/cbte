Preempt Code Internal
---

```
#define TIF_NEED_RESCHED        3       /* rescheduling necessary */
```

# 触发抢占： 
## WakeUp New Task:
```
void wake_up_new_task(struct task_struct *p)
{
        struct rq_flags rf;
        struct rq *rq;

        raw_spin_lock_irqsave(&p->pi_lock, rf.flags);
        p->state = TASK_RUNNING;
#ifdef CONFIG_SMP
        /*
         * Fork balancing, do it here and not earlier because:
         *  - cpus_allowed can change in the fork path
         *  - any previously selected CPU might disappear through hotplug
         *
         * Use __set_task_cpu() to avoid calling sched_class::migrate_task_rq,
         * as we're not fully set-up yet.
         */
        p->recent_used_cpu = task_cpu(p);
        __set_task_cpu(p, select_task_rq(p, task_cpu(p), SD_BALANCE_FORK, 0));
#endif
        rq = __task_rq_lock(p, &rf);
        update_rq_clock(rq);
        post_init_entity_util_avg(p);

        activate_task(rq, p, ENQUEUE_NOCLOCK);
        p->on_rq = TASK_ON_RQ_QUEUED;
        trace_sched_wakeup_new(p);
        check_preempt_curr(rq, p, WF_FORK);
```
## Set nice:
```
                /*
                 * If the task increased its priority or is running and
                 * lowered its priority, then reschedule its CPU:
                 */
                if (delta < 0 || (delta > 0 && task_running(rq, p)))
                        resched_curr(rq);
```
## Migration CPU:
```
void resched_cpu(int cpu)
{
        struct rq *rq = cpu_rq(cpu);
        unsigned long flags;

        raw_spin_lock_irqsave(&rq->lock, flags);
        if (cpu_online(cpu) || cpu == smp_processor_id())
                resched_curr(rq);
}

#ifdef CONFIG_NUMA_BALANCING
static void __migrate_swap_task(struct task_struct *p, int cpu)
{
        if (task_on_rq_queued(p)) {
                struct rq *src_rq, *dst_rq;
                struct rq_flags srf, drf;

                src_rq = task_rq(p);
                dst_rq = cpu_rq(cpu);

                rq_pin_lock(src_rq, &srf);
                rq_pin_lock(dst_rq, &drf);

                p->on_rq = TASK_ON_RQ_MIGRATING;
                deactivate_task(src_rq, p, 0);
                set_task_cpu(p, cpu);
                activate_task(dst_rq, p, 0);
                p->on_rq = TASK_ON_RQ_QUEUED;
                check_preempt_curr(dst_rq, p, 0);

```

# 执行抢占: Kernel Internal
```
/*
 * __schedule() is the main scheduler function.
 *
 * The main means of driving the scheduler and thus entering this function are:
 *
 *   1. Explicit blocking: mutex, semaphore, waitqueue, etc.
 *
 *   2. TIF_NEED_RESCHED flag is checked on interrupt and userspace return
 *      paths. For example, see arch/x86/entry_64.S.
 *
 *      To drive preemption between tasks, the scheduler sets the flag in timer
 *      interrupt handler scheduler_tick().
 *
 *   3. Wakeups don't really cause entry into schedule(). They add a
 *      task to the run-queue and that's it.
 *
 *      Now, if the new task added to the run-queue preempts the current
 *      task, then the wakeup sets TIF_NEED_RESCHED and schedule() gets
 *      called on the nearest possible occasion:
 *
 *       - If the kernel is preemptible (CONFIG_PREEMPT=y):
 *
 *         - in syscall or exception context, at the next outmost
 *           preempt_enable(). (this might be as soon as the wake_up()'s
 *           spin_unlock()!)
 *
 *         - in IRQ context, return from interrupt-handler to
 *           preemptible context
 *
 *       - If the kernel is not preemptible (CONFIG_PREEMPT is not set)
 *         then at the next:
 *
 *          - cond_resched() call
 *          - explicit schedule() call
 *          - return from syscall or exception to user-space
 *          - return from interrupt-handler to user-space
 *
 * WARNING: must be called with preemption disabled!
 */
```
## syscall return user mode:
```
arch/x86/entry/entry_64.S:
ENTRY(entry_SYSCALL_64)
- do_syscall_64
-- syscall_return_slowpath
--- prepare_exit_to_usermode
----static void exit_to_usermode_loop(struct pt_regs *regs, u32 cached_flags)
{
        /*
         * In order to return to user mode, we need to have IRQs off with
         * none of EXIT_TO_USERMODE_LOOP_FLAGS set.  Several of these flags
         * can be set at any time on preemptible kernels if we have IRQs on,
         * so we need to loop.  Disabling preemption wouldn't help: doing the
         * work to clear some of the flags can sleep.
         */
        while (true) {
                /* We have work to do. */
                local_irq_enable();

                if (cached_flags & _TIF_NEED_RESCHED)
                        schedule();


```

## Interrupt return to user mode
```
arch/x86/entry/entry_64.S:
GLOBAL(retint_user)
    mov %rsp,%rdi
    call    prepare_exit_to_usermode
```

## Interrupt return to Kernel mode
```
arch/x86/entry/entry_64.S:
/* Returning to kernel space */
retint_kernel:
#ifdef CONFIG_PREEMPT
    /* Interrupts are off */
    /* Check if we need preemption */
    btl $9, EFLAGS(%rsp)        /* were interrupts off? */
    jnc 1f
0:  cmpl    $0, PER_CPU_VAR(__preempt_count)
    jnz 1f
    call    preempt_schedule_irq

/*
 * this is the entry point to schedule() from kernel preemption
 * off of irq context.
 * Note, that this is called and return with irqs disabled. This will
 * protect us against recursive calling from irq.
 */
asmlinkage __visible void __sched preempt_schedule_irq(void)
{
        enum ctx_state prev_state;

        /* Catch callers which need to be fixed */
        BUG_ON(preempt_count() || !irqs_disabled());

        prev_state = exception_enter();

        do {
                preempt_disable();
                local_irq_enable();
                __schedule(true);
                local_irq_disable();
                sched_preempt_enable_no_resched();
        } while (need_resched());

        exception_exit(prev_state);
}
```