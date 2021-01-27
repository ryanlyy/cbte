This Repos includes some dockerfiles which is used to build container image of bpftrace running environment 
---

# Customize Bpf Container image
* Copy Config-* used by target host to this repos root directory
* Add New Dockerfile same like with Dockerfile.centos.7.6.1810.kernel.4.18.0 and then update COPY cmd
* And then update Kernel URL 
* Last run "docker build -t xxx:yyy -f ./Dockerfile.mmm ."

# Start bpf container
```
./bpfcli <imageid>

./bpfcli  bpftools:7.6.1810-4.18.0-210126
```

# Run Bpf tools
```
/usr/share/bpftrace/tools/killsnoop.bt
```

# NOTE
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



