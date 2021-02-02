Generic Tips used by Linux Perforamnce Debugging
---

# List all kernel based program
```
ps --ppid 2 -p 2 -o uname,pid,ppid,cmd,cls
```
# List all instrument and arguments
```
[root@foss-ssc-7 /]# bpftrace -l 'tracepoint:*' | wc -l
1958
[root@foss-ssc-7 ~]# bpftrace -l 'kprobe:*' | wc -l
44472
[root@foss-ssc-7 ~]#
[root@foss-ssc-7 ~]# bpftrace -l 'kretprobe:*' | wc -l
44472
[root@foss-ssc-7 lib64]# bpftrace -l 'uprobe:./libpthread.so.0:*' |wc -l
556
[root@foss-ssc-7 lib64]
```
```
[root@foss-ssc-7 /]# bpftrace -v -l 'tracepoint:syscalls:sys_enter_open'
tracepoint:syscalls:sys_enter_open
    int __syscall_nr;
    const char * filename;
    int flags;
    umode_t mode;
```

# Linux 60 seconds Analysis
1. uptime
```
[root@foss-ssc-7 tools]# uptime
 07:42:10 up 59 days,  4:46,  0 users,  load average: 5.71, 3.74, 1.66
 
 load average: 1m, 5m, 15m
```

2. dmesg | tail
3. vmstat 1
```
[root@foss-ssc-7 tools]# vmstat 1
procs -----------memory----------          ---swap--    -io-     -system-    ---cpu---
 r  b     swpd   free      buff  cache     si   so    bi    bo   in   cs   us sy id wa st
 1  0      0    10886080   2252 50395900    0    0     0     3    0    0   1  0 99  0  0
 0  0      0    10884844   2252 50396064    0    0     0    20  4224 8918  1  0 99  0  0
 0  0      0    10884256   2252 50396432    0    0     0   540  2846 5823  0  0 100  0  0
 1  0      0    10884264   2252 50396528    0    0     0     0  6321 1234  1  1 99  0  0

r: The number of running + wait for running process, if count > cpu cores, then high load
b: The number of blocked process
free: (free -m check)
si/so: swap in/out, if not zero, then mem is not enough
us,sy,id,wa,st: cpu
```

4. mpstat -P all 1
```
[root@foss-ssc-7 tools]# mpstat -P ALL 1
Linux 4.18.0-193.el8.x86_64 (foss-ssc-7)        01/28/21        _x86_64_        (32 CPU)

07:56:18     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
07:56:19     all    0.31    0.00    0.16    0.00    0.06    0.06    0.00    0.00    0.00   99.40
07:56:19       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
07:56:19       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
...
```
5. pidstat 1
```
[root@foss-ssc-7 tools]# pidstat
Linux 4.18.0-193.el8.x86_64 (foss-ssc-7)        01/28/21        _x86_64_        (32 CPU)

07:57:15      UID       PID    %usr %system  %guest    %CPU   CPU  Command
07:57:15        0         1    0.46    0.55    0.00    1.01    30  systemd
07:57:15        0         2    0.00    0.00    0.00    0.00    17  kthreadd
07:57:15        0        10    0.00    0.00    0.00    0.00     0  ksoftirqd/0
07:57:15        0        11    0.00    0.11    0.00    0.11     9  rcu_sched
07:57:15        0        12    0.00    0.00    0.00    0.00     0  migration/0
```
6. iostat -xz 1
```
[root@foss-ssc-7 tools]# iostat -xz 1
Linux 4.18.0-193.el8.x86_64 (foss-ssc-7)        01/28/21        _x86_64_        (32 CPU)

avg-cpu:  %user   %nice %system %iowait  %steal   %idle
           0.67    0.00    0.36    0.01    0.00   98.96

Device:         rrqm/s   wrqm/s     r/s     w/s    rkB/s    wkB/s avgrq-sz avgqu-sz   await r_await w_await  svctm  %util
sda               0.00     0.21    0.02    0.90     0.77    83.35   183.85     0.03   31.56    4.81   32.06   1.16   0.11
dm-0              0.00     0.00    0.02    1.11     0.76    83.33   149.27     0.04   34.01    4.80   34.45   0.94   0.11
dm-1              0.00     0.00    0.00    0.00     0.00     0.00    42.42     0.00    7.51    7.51    0.00   0.64   0.00
dm-2              0.00     0.00    0.00    0.00     0.00     0.02    53.61     0.00   39.43    4.72   48.64   0.62   0.00

avg-cpu:  %user   %nice %system %iowait  %steal   %idle
           0.38    0.00    0.22    0.00    0.00   99.41

r/s,w/s,rkB/s,wkB/s: read/write times per second, read/write kb per second
await: IO average time (millsecond)
avgqu-sz: Request Query Average Length
%util: device usage
```
7. free -m
```
[root@foss-ssc-7 tools]# free -m
              total        used        free      shared  buff/cache   available
Mem:          64114        4271       10797        3973       49045       54721
Swap:             0           0           0
```
8. sar -n DEV 1
```
[root@foss-ssc-7 tools]# sar -n DEV 1
Linux 4.18.0-193.el8.x86_64 (foss-ssc-7)        01/28/21        _x86_64_        (32 CPU)

08:03:50        IFACE   rxpck/s   txpck/s    rxkB/s    txkB/s   rxcmp/s   txcmp/s  rxmcst/s
08:03:51         eno4      4.00      3.00      0.28      0.45      0.00      0.00      1.00
08:03:51    cali4772991997b      3.00      4.00      0.40      0.43      0.00      0.00      0.00
08:03:51    cali2b848086ba7     37.00     53.00      7.82    213.12      0.00      0.00      0.00
08:03:51         eno1     44.00     21.00     31.24      3.19      0.00      0.00      1.00
08:03:51         eno3      1.00      0.00      0.06      0.00      0.00      0.00      1.00
08:03:51           lo     12.00     12.00      0.86      0.86      0.00      0.00      0.00
```

9.  sar -n TCP,ETCP 1
```
[root@foss-ssc-7 tools]# sar -n TCP,ETCP 1
Linux 4.18.0-193.el8.x86_64 (foss-ssc-7)        01/28/21        _x86_64_        (32 CPU)

08:08:33     active/s passive/s    iseg/s    oseg/s
08:08:34         0.00      0.00     67.00   1096.00

08:08:33     atmptf/s  estres/s retrans/s isegerr/s   orsts/s
08:08:34         0.00      0.00      0.00      0.00     10.00

08:08:34     active/s passive/s    iseg/s    oseg/s
08:08:35         5.00      2.00     38.00     54.00

08:08:34     atmptf/s  estres/s retrans/s isegerr/s   orsts/s
08:08:35         2.00      0.00      0.00      0.00      2.00
```
10. top

