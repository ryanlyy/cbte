Container Based Troubleshooting Environment
---

As you know following container widely usage and security concern that most of debugging tools are removed from container image. But debugging is always there because there is no software w/o bug in the world. And it is not allowed to install debugging tools into target machine. In order to solve this issue, this project help to build debugging environment w/o intall tools into target machine.

Now this project supports:
* BPF tool based debugging environment
* Network tool based debugging environment


# BPF tool based debugging environment
## Customize Bpf Container image
* Copy Config-* used by target host to this repos root directory
* Add New Dockerfile same like with Dockerfile.centos.7.6.1810.kernel.4.18.0 and then update COPY cmd
* And then update Kernel URL 
* Last run "docker build -t xxx:yyy -f ./Dockerfile.mmm ."

## Start bpf container
```
./bpfcli <imageid>

./bpfcli  bpftools:7.6.1810-4.18.0-210126
```

## Run Bpf tools
```
/usr/share/bpftrace/tools/killsnoop.bt
```

## NOTE
* kprobe: SyS_execve -- __64_sys_execve
```
/usr/share/bpftrace/tools/execsnoop.bt
/*kprobe:SyS_execve*/
kprobe:__x64_sys_execve
{
        printf("%-10u %-5d ", elapsed / 1e6, pid);
        join(arg1);
}
```

## Use Cases
1. List all instrument and arguments
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
2. Monitoring open file
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
3. 

# Network tool based debugging environment
## lsof
List open files

## strace
Trace system calls and signals

## tcpdump
Dump traffic on a network

## atop
Advanced System & Process Monitor

It shows the occupation of the most critical hardware resources (from a performance point of view) on system level, i.e. cpu, memory, disk and network. 
* CPU: sys, user, irq, idle, wait, steal, guest, ipc, cycl, curf curscal on each cpu
* MEM: tot, free, cache, dirty, buff, slab, slrec, shmem, shrss, shswp, vmbal, hptot, hpuse
* LVM: busy, read, write, avq, avio
* DSK: busy, read, write, avq, avio
* NET: Transport: tcpi, tcpo, udpi, udpo, tcpao, tcppo, tcprs, tcpie, tcpor, udpnp, udpie
* NET: network: ipi, ipo, ipfrw, deliv, icmpi, icmpo
* NET: dev: pcki, pcko, sp, si, so, coll, multi, erri, erro, drpi, drpo

It also shows which processes are responsible for the indicated load with respect to cpu and memory load on process level.  Disk load is shown per process if "storage accounting" is active in  the kernel.  
* PROC: pic, cid, syscpu, usrcpu, vgrow, rgrow, rddsk, wrdsk, ruid, euid, st, exc, thr, s cpunr, cpu, cmd


## iftop
Display bandwidth usage on an interface by host per ip

## htop
Interactive process viewer samilar with top

## iotop
Simple top-like I/O monitor

## nethogs
Net top tool grouping bandwidth per process
```
nethogs -d 1 -s 
```

## iperf3
Perform network throughput tests

## qperf
Measures bandwidth and latency between two nodes

## iproute/iproute-tc
ip and tc command line

## iputils
ping, arping, ping6, tracepath

## net-tools
netstat, arp, ifconfig, route

## traceroute
Print the route packets trace to network host

## bind-utils
dig, nslooup, nsupdate

## ethtool
Query or control network driver and hardware settings

## nmap/nmap-ncat
Network exploration tool and security / port scanner
nmap, nping, nc, ncat

## nmon
systems administrator, tuner, benchmark tool

# Tips
## Linux 60 seconds Analysis
1. uptime
2. dmesg | tail
3. vmstat 1
4. mpstat -P all 1
5 pidstat 1
* iostat -xz 1
* free -m
* sar -n DEV 1
* sar -n TCP,ETCP 1
* top



