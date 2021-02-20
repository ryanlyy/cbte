bpftrace = BPF + BCC
---

- [Monitoring Tools](#monitoring-tools)
- [bpftrace progrmaming](#bpftrace-progrmaming)
  - [Usage](#usage)
  - [Program Structure](#program-structure)
  - [comments](#comments)
  - [Probe Format](#probe-format)
    - [type:](#type)
    - [Identifiler (w/ expression like *)](#identifiler-w-expression-like-)
  - [Filter](#filter)
  - [Action](#action)
  - [Action Embedded Functions](#action-embedded-functions)
  - [Variable](#variable)
  - [Mapping functions](#mapping-functions)
  - [bpftrace control flow](#bpftrace-control-flow)
  - [Debugging](#debugging)

![image info](../pics/bpftrace.jpg)

# Monitoring Tools
* Perf

Script lanugage more complicated

* Ftrace

Less dependency w/ high performance

* bpftrace

4.9 and later 

* Systemtap

More dependency w/ kernel module

# bpftrace progrmaming
## Usage
```
bpftrace -e 'program'

bpftrace file.bt

./file.bit
if file includes "#!/usr/bin/bpftrace in first line
``` 

## Program Structure
```
probles /filter/ { actions }
```

## comments
```
// or /* */
```

## Probe Format
```
type:identifiler1[:identifer2[...]]
```
### type:
* kprobe:k
  * kprobe:function_name
* kretprobe:kr
  * kretprobe:function_name
* uprobe:u
  * uprobe:binary_path:function_name
  * uprobe:library_path:function_name
* uretprobe:ur
  * uretprobe:binary_path:function_name
  * uretprobe:library_path:function_name
* tracepoint:t
  * tracepoint: tracepoint_name
  * parameter: using embedded varialbe "args" to access parameter
    * for example: net:netif_rx parameter len: args->len
  * bpftrace -lv t:syscalls:sys_enter_read
* usdt:U
  * usdt:binary_path:probe_name
  * usdt:library_path:probe_name
  * usdt:binary_path:probe_namespace:probe_name
  * usdt:library_path:probe_namespace:probe_name
* BEGIN
* END
* software:s (software event)
  * software:event_name:count
  * software:event_name
  * software event:
    * cpu-clock/cpu
    * task-clock
    * page-faults/faults
    * context-switchs/cs
    * cpu-migrations
    * minor-faults
    * major-faults
    * alignment-faults
    * emulation-faults
    * dummy
    * bpf-output
* hardware:h (hardware event)
  * hardware:event_name:count
  * hardware:event_name
  * hardware event:
    * cpu-cycle/cycles
    * instructions
    * cache-references
    * cahce-misses
    * branch-instructions
    * bus-cycles
    * fronend-stalles
    * backend-stalles
    * ref-cycles
* profile:p
  * profile:hz:rate
  * profile:s:rate
  * profile:ms:rate
  * profile:us:rate
* interval:i
  * interval:s:rate
  * interval:ms:rate
  
### Identifiler (w/ expression like *)
* func name
* path/to/exec:name

```
bpftrace -l 'kprobe:*'
```

## Filter

```
/pid/

/pid == 124/
```

## Action

C Language format
```
{
    action;
}
}
```

## Action Embedded Functions
* printf
* time(char *fmt)
* join(char *arr[]): print 字符串数组
* exit()
* str(char *s [, int len]): convert buf s to string
* kstack(int limit): limit: 深度
* ustack(int limit)
* ksym(void *p): 返回该地址所代表的字符串
* usym(vopid *p)
* kaddr(char *name): convert name to kernel address
* uaddr(char *name)
* reg(char *name)：save name value to register
* ntop（[int af] int addr): retrun ip str
* system(format[,arguments ..]): run shell 
* cat(char *filename): print file content

## Variable
* Embedded
  1. pid
  2. tid
  3. uid
  4. username
  5. comm
  6. nsecs
  7. elapsed
  8. cpu
  9. kstack
  10. ustack
  11. arg0, ... , argN
  12. args
  13. retval
  14. func
  15. probe
  16. curtask
  17. cgroup
  18. $1, ..., $N: bpf程序的参数位置
* Temp
  1. $x = 1
  2. 
* Mapping table
  1. @name
  2. @start[tid] = nsecs
  3. @path[pid, $fd] = str(arg0)
  4. $name[k1,k2,k3...]

## Mapping functions
* count
* sum/avg/min/max(int n)
* stats(int n): return event count, avg and sum
* hist(int n): 
* 1hist(int n, int min, int max, int step)
* delete(@m[key])
* print(@m [, top [, div]])
* clear(@m)
* zero(@m)
* 

## bpftrace control flow
* bool testing
  * ==
  * !=
  * \>
  * <
  * \>=
  * <=
  * &&
  * ||
* filter
  * check if action shall be done by filter (true/false)
  * /pid==123/
* test ? true_statement : false_statement
  * $abs = $x >=0: $x : -$x
* if
  * if (test) {true_statement}
  * if (test) {true_statement} else {false_statement}
* loop
  * unroll (count) { statement }
  * count must be const values and less than 20
  * later: for/while
* op
  * =
  * +,-,*,/
  * ++,--
  * &, |, ^
  * !
  * << >>
  * +=, -= ....
  * 
## Debugging
* printf
* -d
* -v