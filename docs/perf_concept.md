Performance Debugging Concept
---
- [Baisc Terms](#baisc-terms)
- [Methodologies](#methodologies)
  - [问题陈述](#问题陈述)
  - [工作负载特征归纳](#工作负载特征归纳)
  - [USE方法](#use方法)
  - [图表建模](#图表建模)
  - [深度挖掘分析](#深度挖掘分析)
- [Data Source](#data-source)
  - [/proc](#proc)
  - [/sys](#sys)
  - [Delay Accouting](#delay-accouting)
- [Tools](#tools)
  - [Counter](#counter)
  - [Tracing](#tracing)
  - [Profiling](#profiling)
  - [Monitoring](#monitoring)
- [Resource Check Lists](#resource-check-lists)



---------------------------------
https://www.kernel.org/doc/html/v5.12/

https://www.kernel.org/doc/Documentation/

---------------------------------

# Baisc Terms

# Methodologies
## 问题陈述
1. 是什么让你认为存在性能问题？
2. 系统之前运行的好吗？
3. 最近有什么改动？软件，硬件，负载？
4. 问题能用延时或者运行时间来表述吗？
5. 问题影响其他人或应用吗？
6. 环境是怎么样的？用了哪些软件硬件？版本号？配置
7. 其他同类型的系统有问题吗？不同点是什么？

## 工作负载特征归纳
1. 负载是谁产生的？进程ID，用户ID，远端的IP？
2. 负载为什么会被调用？代码路径，栈跟踪？
3. 负载的特征是什么？IOPS，throughput，read/write？
4. 负载变化趋势？有日常模式?

## USE方法

## 图表建模

## 深度挖掘分析

# Data Source
* Process Counter: /proc
* System Counter: /proc, /sys
* Device Driver Debugging: /sys
* Process Tracing: ptrace, uprobes
* Perf Counter: perf_event
* Network Tracing: tcpdump/libpcap
* Process Latency
* Sytem Tracing: tracepoints, kprobes, ftrace
## /proc
* Process Level Performence Data
  * limits - process level changed by rlimit
  * maps - Memory Layout
  * sched - CPU scheduler Statistics
  * schedstat - CPU runtime, latency and time slicing
  * smaps - Memory Statistics
  * stat- Prcess statu and statistics including total cpu and memory usage
  * statm - Memory Usage (paging units)
  * status - stat + statm
  * task -- all threads directory

* System Level Performence Data
  * cpuinfo - physical cpu information including cpu, mode, clock and cache
  * diskstats - Disk I/O Statistics
  * interrupts - CPU Interrupter Statistics
  * loadavg - Load Average
  * meminfo - memory usage statistics
  * net/dev - Network Interface Statistics
  * net/tcp - TCP Socket Information
  * net/udp - UDP socket information
  * schedstat - CPU Scheduler Statistics
  * slabinfo - kernel SLAP Allocation Statistics
  * stat - Kernel and System Resource Statistics including CPU, Disk, paging, swap and process
  * zoneinfo - Memory Information

## /sys
## Delay Accouting
https://elixir.bootlin.com/linux/v4.1/source/Documentation/accounting/getdelays.c
https://elixir.bootlin.com/linux/v5.12/source/tools/accounting/getdelays.c



# Tools
## Counter
* System Level
  * vmstat
  * mpstat
  * iostat
  * netstat
  * sar
* Process Level
  * ps
  * top
  * pmap

## Tracing
* System Level
  * tcpdump
  * blktrace
  * systemtap
  * perf
* Process Level
  * strace
  * gdb
## Profiling
* System and Process Level
  * oprofile
  * perf
  * systemTap
  * cachegrind
  
## Monitoring
* sar


# Resource Check Lists