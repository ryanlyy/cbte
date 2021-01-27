This Repos includes some dockerfiles which is used to build container image of bpftrace running environment 
---

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



