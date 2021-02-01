BCC - BPF (BSD Packet Filter) Complier Collection
---

# Tools
## Single Purpose Tools
1. opensnoop
```
[root@foss-ssc-7 /]# opensnoop -h
  -T, --timestamp       include timestamp on output
  -U, --print-uid       print UID column
  -x, --failed          only show failed opens
  -p PID, --pid PID     trace this PID only
  -t TID, --tid TID     trace this TID only
  --cgroupmap CGROUPMAP
                        trace cgroups in this BPF map only
  --mntnsmap MNTNSMAP   trace mount namespaces in this BPF map only
  -u UID, --uid UID     trace this UID only
  -d DURATION, --duration DURATION
                        total duration of trace in seconds
  -n NAME, --name NAME  only print process names containing this name
  -e, --extended_fields
                        show extended fields
  -f FLAG_FILTER, --flag_filter FLAG_FILTER
                        filter on flags argument (e.g., O_WRONLY)
```
Example:
```
C[root@foss-ssc-7 ~]# opensnoop -Ten sla-monitoring
libbpf: bpf_prog_put is not found in vmlinux BTF
TIME(s)       PID    COMM               FD ERR FLAGS    PATH
1.655291000   3099246 sla-monitoring     61   0 00100000 /proc/stat
1.655438000   3099246 sla-monitoring     61   0 00100000 /etc/exthostname
1.657243000   3099246 sla-monitoring     61   0 00100101 /iotests//testfile_0
1.660702000   3099246 sla-monitoring     62   0 00100000 /etc/exthostname
1.660913000   3099246 sla-monitoring     61   0 00100101 /iotests//testfile_1
1.661020000   3099246 sla-monitoring     62   0 00100000 /etc/exthostname
```

## Multiple Purposes Tools
1. funccount
Count on event or function call to answer:
* function is called or not
* How many call per second   
```
usage: funccount [-h] [-p PID] [-i INTERVAL] [-d DURATION] [-T] [-r] [-D]
                 pattern

Count functions, tracepoints, and USDT probes

positional arguments:
  pattern               search expression for events

  name or p:name: kernel function instrument
  lib:name or p:lib:name: User lib function instrument
  path:name: function in path file instrument
  t:system:name: tracepoint named system:name instrument
  u:lib:name: name located in lib USDT instrument
  *: all expression

optional arguments:
  -h, --help            show this help message and exit
  -p PID, --pid PID     trace this PID only
  -i INTERVAL, --interval INTERVAL
                        summary interval, seconds
  -d DURATION, --duration DURATION
                        total duration of trace, seconds
  -T, --timestamp       include timestamp on output
  -r, --regexp          use regular expressions. Default is "*" wildcards
                        only.
  -D, --debug           print BPF program before starting (for debugging
                        purposes)

```
```
[root@foss-ssc-7 tools]# funccount -Ti 1 't:syscalls:sys_enter_open'
Tracing 1 functions for "t:syscalls:sys_enter_open"... Hit Ctrl-C to end.

09:14:09
FUNC                                    COUNT
syscalls:sys_enter_open                    14

09:14:10
FUNC                                    COUNT
syscalls:sys_enter_open                    14
```
2. stackcount
   
3. trace

```
  -K, --kernel-stack    output kernel stack trace
  -U, --user-stack      output user stack trace
  -t, --timestamp       print timestamp column (offset from trace start)
  -u, --unix-timestamp  print UNIX timestamp instead of offset from trace
                        start, requires -t
  -T, --time            print time column
```

Trace the cfs scheduling runqueue remaining runtime
```
[root@foss-ssc-7 linux]# trace -n sla-monitoring -I 'kernel/sched/sched.h'       'p::__account_cfs_rq_runtime(struct cfs_rq *cfs_rq) "%d", cfs_rq->runtime_remaining'
PID     TID     COMM            FUNC             -
3099246 3099255 sla-monitoring  __account_cfs_rq_runtime 802625
3099246 3099255 sla-monitoring  __account_cfs_rq_runtime 802625
3099246 3099255 sla-monitoring  __account_cfs_rq_runtime 1000000
3099246 3099255 sla-monitoring  __account_cfs_rq_runtime 1000000
3099246 3099255 sla-monitoring  __account_cfs_rq_runtime 892669
3099246 3099255 sla-monitoring  __account_cfs_rq_runtime 892669
```

Trace tcp sendmsg calls only if socket's destination port is equal to 5473 (24853 in big endian order)
```
 trace -I 'net/sock.h' 'tcp_sendmsg(struct sock *sk, struct msghdr *msg, size_t size)(sk->sk_dport == 24853) "daddr %x buflen %d", sk->sk_daddr, size'
PID     TID     COMM            FUNC             -
6995    6995    calico-node     tcp_sendmsg      daddr f687fc87 buflen 108
6993    15873   calico-node     tcp_sendmsg      daddr 7f2a600a buflen 108
```

Trace FD leak issue
(same to memory/file)
```
[root@foss-ssc-7 linux]# trace -n prometheus -tKU 'r::sock_alloc "open %llx", retval' '__sock_release "close %llx", arg1' |tee ~/prom.leak
TIME     PID     TID     COMM            FUNC             -
1.921802 6423    6568    prometheus      sock_alloc       open ffff9a1fc29caec0
        kretprobe_trampoline+0x0 [kernel]
        syscall.RawSyscall+0x2b [prometheus]
        syscall.Socket+0x52 [prometheus]
        net.sysSocket+0x57 [prometheus]
        net.socket+0x5a [prometheus]
        net.internetSocket+0x141 [prometheus]
        net.(*sysDialer).doDialTCP+0xc2 [prometheus]
        net.(*sysDialer).dialTCP+0xd7 [prometheus]
        net.(*sysDialer).dialSingle+0x36e [prometheus]
        net.(*sysDialer).dialSerial+0x221 [prometheus]
        net.(*Dialer).DialContext+0x666 [prometheus]
        net.(*Dialer).DialContext-fm+0x73 [prometheus]
        github.com/mwitkow/go-conntrack.dialClientConnTracker+0xaf [prometheus]
        github.com/mwitkow/go-conntrack.NewDialContextFunc.func1+0x12d [prometheus]
        net/http.(*Transport).dial+0x1f5 [prometheus]
        net/http.(*Transport).dialConn+0x193e [prometheus]
        net/http.(*Transport).dialConnFor+0xdc [prometheus]
        runtime.goexit+0x1 [prometheus]

1.923986 6423    7751    prometheus      __sock_release   close ffff9a1fc29caec0
        __sock_release+0x1 [kernel]
        sock_close+0x11 [kernel]
        __fput+0xb7 [kernel]
        task_work_run+0x8a [kernel]
        exit_to_usermode_loop+0xeb [kernel]
        do_syscall_64+0x198 [kernel]
        entry_SYSCALL_64_after_hwframe+0x65 [kernel]
        syscall.Syscall+0x30 [prometheus]
        internal/poll.(*FD).destroy+0x43 [prometheus]
        internal/poll.(*FD).decref+0x42 [prometheus]
        internal/poll.(*FD).Close+0x4f [prometheus]
        net.(*netFD).Close+0x4f [prometheus]
        net.(*conn).Close+0x4a [prometheus]
        github.com/mwitkow/go-conntrack.(*clientConnTracker).Close+0x37 [prometheus]
        net/http.(*persistConn).closeLocked+0x12e [prometheus]
        net/http.(*persistConn).readLoopPeekFailLocked+0x143 [prometheus]
        net/http.(*persistConn).readLoop+0x112b [prometheus]
        runtime.goexit+0x1 [prometheus]
```

4. argdist

Function Latency
```
[root@foss-ssc-7 linux]# argdist -H 'r::__tcp_select_window():int:$latency'
[05:01:23]
     $latency            : count     distribution
         0 -> 1          : 0        |                                        |
         2 -> 3          : 0        |                                        |
         4 -> 7          : 0        |                                        |
         8 -> 15         : 0        |                                        |
        16 -> 31         : 0        |                                        |
        32 -> 63         : 0        |                                        |
        64 -> 127        : 0        |                                        |
       128 -> 255        : 0        |                                        |
       256 -> 511        : 121      |****************************************|
       512 -> 1023       : 75       |************************                |
      1024 -> 2047       : 41       |*************                           |
      2048 -> 4095       : 10       |***                                     |
      4096 -> 8191       : 6        |*                                       |
      8192 -> 16383      : 2        |                                        |
     16384 -> 32767      : 1        |                                        |
```

Function Retval
```
[root@foss-ssc-7 linux]# argdist -H 'r::__tcp_select_window():int:$retval'
[05:02:33]
     $retval             : count     distribution
         0 -> 1          : 0        |                                        |
         2 -> 3          : 0        |                                        |
         4 -> 7          : 0        |                                        |
         8 -> 15         : 0        |                                        |
        16 -> 31         : 0        |                                        |
        32 -> 63         : 0        |                                        |
        64 -> 127        : 0        |                                        |
       128 -> 255        : 0        |                                        |
       256 -> 511        : 0        |                                        |
       512 -> 1023       : 0        |                                        |
      1024 -> 2047       : 0        |                                        |
      2048 -> 4095       : 0        |                                        |
      4096 -> 8191       : 0        |                                        |
      8192 -> 16383      : 0        |                                        |
     16384 -> 32767      : 39       |****************************************|
     32768 -> 65535      : 33       |*********************************       |
     65536 -> 131071     : 0        |                                        |
    131072 -> 262143     : 27       |***************************             |
    262144 -> 524287     : 0        |                                        |
    524288 -> 1048575    : 0        |                                        |
   1048576 -> 2097151    : 2        |**                                      |
   2097152 -> 4194303    : 23       |***********************                 |
```