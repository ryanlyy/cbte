Concepts of Bpftrace and BCC
---
![image info](../pics/bcc_tracing_tools_2019.png)

# Instrumentation 
## kprobes
  
* Kerenl function dynamic instrument
* p:name|name
* No need to restart os/kernel
* can instrument on any kernel function
* How:
  * Backup instrubment target address 
  * Replace target address with 单步终端指令 (int3指令行x86-64, if kprobe enable optimization, then jmp指令)
  * 当指令执行到断点时，断点处理函数会检查是否是kprobes注册，if yes, then execute kprobe处理函数
  * 原始指令接着执行


## kretprobe 

* Kernel Function ret dynamic Instrument 
* r::name
* when return then do instrument to get retvalue
* How:
  * do kproble in 函数入口
  * 当执行到函数入口时，将返回地址保存并替换为一个蹦床(trampoline)函数地址 (kretprobe_trampoline)
  * 当函数返会时（ret指令），CPU将控制交给蹦床函数处理
  * 当kretprobe处理完成后，CPU再执行返回地址继续

## uprobes
  
* User function dynamic instrument
* lib:name|p:lib:name|path:name|r:lib:name
* Instrument point:
  * 函数入口
  * 特定偏移处
  * 函数返回处
* HOW:
  * same with kprobe

## uretprobe
* HOW
  * same with kretprobe


## tracepoint
  
* Kernel based static instrument
* t:subsystem:eventname
* bpftrace -l 'tracepoint：*' to show all tracepoint
* Kernel Markers
  * Kernel developer setup tracepoints in special logical place
  * and thoese tracepoints is complied into kernel binary file
* HOW
  * Add 5 byters "nop" 指令 into tracepoints
  * at the end of tracepoints located function, add 蹦床函数
  * 执行时， when tracepoint enabled,
    * at the tracepoint callback function, add 跟踪器回调函数

## USDT: u:lib:name
  
* User Level Static Defined Tracing (用户态预定义静态跟踪)
* Following dtrace
  * Oracle Linux: https://blogs.oracle.com/d/adding-dtrace-probes-to-user-code
  * Redhat/Centos
    * systemtap-sdt-dev： https://github.com/iovisor/bcc/blob/master/examples/usdt_sample/
    * Facebook Folly C++ Library
* HOW
  * 当编译时，在USDT probe的位置放置一个 （no-operation)nop 指令，在插桩时，这个地址会由内核使用uprobe动态将其修改为一个断点指令(breakpoint instruct)

## dynamic USDT (JAVA)
## PMC
* Counting
* Overflow Sampling
## perf_events



