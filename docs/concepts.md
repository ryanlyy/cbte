Concepts of Bpftrace and BCC
---
![image info](../pics/bcc_tracing_tools_2019.png)

# Instrumentation 
## Dynamic Instrumentation
* kprobes: p:name|name
  
  Kerenl function dynamic instrument

* kretprobe: r::name
  
  Kernel Function ret dynamic Instrument 

* uprobes: lib:name|p:lib:name|path:name|r:lib:name
  
  User function dynamic instrument

## Static Instrumentation
* tracepoint: t:system:name
  
  Kernel based static instrument

* USDT: u:lib:name
  
  User Level Static Defined Tracing

