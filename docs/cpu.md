CPU Perforamnce Debugging
---

![image info](../pics/cpu_scheduler.jpg)

# CPU Basic
* CPU Running Mode
  * System Mode
    * Kernel
      * CPU 
      * all other kinds of resources
      * 系统内核一般按需运行
        * 系统调用
        * 处理中断
        * backend线程
  * User Mode
    * User App
      * Send Request to Kerenl to access all resoure
        * 显示请求
          * syscall
        * 隐式请求
          * 缺页中断(page fault)
* CPU Scheduler
  * Schedule Unit
    * thread/task
    * Interrupt Hander(hardware interrupt, softare interrupt)
  * Task Running State
    * ON-PROC: running on the cpu
    * RUNNABLE: waiting in run queue
    * SLEEP: waiting for other events including uninterruptable thread
  * Terms
    * VCX
      * Voluntary(自愿) Context Switch
      * wait for resource
    * ICX
      * Involuntary(强制) Context Switch
      * Preempt
    * Priority
      * Increase task running performance
    * Preempt
      * 触发抢占：对正在CPU上运行的线程设置请求重新调度的标志(TIF_NEED_RESCHED)
        * 周期性的时钟中断
          * timer interrupt handler call scheduler_tick to check if time slicing is over, if yes, set TIF_NEED_RESCHED
        * Thread Wakeup 
          * 当进程被唤醒时，如果进程的优先级高于CPU上的当前进程，then set TIF_NEED_RECHED
        * 进程修改nice值时
          * if new nice导致优先级高于CPU上的当前进程，then set TIF_NEED_RECHED
        * 进行负载均衡时
          * migration to another CPU
          * 
      * 执行抢占: when kernel found TIF_NEED_RESCHED flag is set then 执行抢占
        * 执行User Preempt(用户态抢占)时机
          * 系统调用(syscall)返回用户态时
          * 中断调用(Interrupt)返回用户态时
        * 执行Kernel Preempt(内核态抢占)时机
          * 
      * Reference
        * [Preempt Kernel Internal](preempt_internal.md)
        * http://linuxperf.com/?p=211


    * Linux CFS