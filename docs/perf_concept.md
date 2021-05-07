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
- [Application](#application)
  - [Appliction Performance Objective](#appliction-performance-objective)
  - [Application Methods and Analysis](#application-methods-and-analysis)
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

* CPU Scheduler Daly
* Block IO Delay
* Page Swapping Delay
* Memory Reclaim Delay

```
[root@foss-ssc-1 src]# ./getdelays -dp 3258789
print delayacct stats ON
PID     3258789


CPU             count     real total  virtual total    delay total  delay average
                   51       24290037       26014303        2015118          0.040ms
IO              count    delay total  delay average
                    0              0              0ms
SWAP            count    delay total  delay average
                    0              0              0ms
RECLAIM         count    delay total  delay average
                    0              0              0ms
[root@foss-ssc-1 src]#
```

```
/* Delay accounting fields start
	 *
	 * All values, until comment "Delay accounting fields end" are
	 * available only if delay accounting is enabled, even though the last
	 * few fields are not delays
	 *
	 * xxx_count is the number of delay values recorded
	 * xxx_delay_total is the corresponding cumulative delay in nanoseconds
	 *
	 * xxx_delay_total wraps around to zero on overflow
	 * xxx_count incremented regardless of overflow
	 */

	/* Delay waiting for cpu, while runnable
	 * count, delay_total NOT updated atomically
	 */
	__u64	cpu_count __attribute__((aligned(8)));
	__u64	cpu_delay_total;

	/* Following four fields atomically updated using task->delays->lock */

	/* Delay waiting for synchronous block I/O to complete
	 * does not account for delays in I/O submission
	 */
	__u64	blkio_count;
	__u64	blkio_delay_total;

	/* Delay waiting for page fault I/O (swap in only) */
	__u64	swapin_count;
	__u64	swapin_delay_total;

	/* cpu "wall-clock" running time
	 * On some architectures, value will adjust for cpu time stolen
	 * from the kernel in involuntary waits due to virtualization.
	 * Value is cumulative, in nanoseconds, without a corresponding count
	 * and wraps around to zero silently on overflow
	 */
	__u64	cpu_run_real_total;

	/* cpu "virtual" running time
	 * Uses time intervals seen by the kernel i.e. no adjustment
	 * for kernel's involuntary waits due to virtualization.
	 * Value is cumulative, in nanoseconds, without a corresponding count
	 * and wraps around to zero silently on overflow
	 */
	__u64	cpu_run_virtual_total;
	/* Delay accounting fields end */
```
# Application
* Operation
  * Network IO
  * Disk IO
  * CPU
* CPU model
  * User
  * Kernel
* Configuration
  * Performance Parameter (i.e: cache/buffer, threads etc.)
* PM or Counter
* Logging
## Appliction Performance Objective
* Low Delay: Quick Response
* Hight Throughput: Data transmission
* Low Resource Utilization

指标量化

IO开销包括：

  * 初始化缓冲区
  * 系统调用
  * 上下文切换
  * 分配内核元数据
  * 检查进程的权限和限制
  * 映射地址到设备
  * 执行内核和驱动
  * 释放元数据和缓冲区

## Application Methods and Analysis
* 线程状态分析
  
  其目的是分辨应用程序的时间用在了什么地方？

  六种状态：
  * 执行： on-CPU ---  top
  * 可运行：等待轮上CPU --- [latency.c](../src/latency.c) (/proc/pid/schedstat)
  * 匿名换页：可运行但因等待匿名换页而受阻 -- [getdelays.c](../src/getdelays-4.18.c) (netlink taskstat accounting -- SWAP)
  * 睡眠： 等待IO包括Network，Disk --- iotop/pidstat -d / getdelays.c (netlink taskstat IO) /pstack
  * 锁：等待获取同步锁 --- strace/ pstack etc.
  * 空闲：等待工作
* CPU刨析
* 系统调用分析 --- strace
* IO分析 --- strace
* 工作负载特征归纳
* dd

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