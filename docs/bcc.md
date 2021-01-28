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
1. stackcount
2. trace
3. argdist