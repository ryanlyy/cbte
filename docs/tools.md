Tools used for debugging
---------------
- [procps-ng](#procps-ng)
- [util-linux](#util-linux)
- [coreuitls](#coreuitls)
- [sysstat](#sysstat)
- [sar](#sar)
- [perf](#perf)
- [systemtap](#systemtap)
- [dtrace](#dtrace)
- [stress-ng](#stress-ng)

# procps-ng
```
[root@foss-ssc-1 ~]# rpm -ql procps-ng-3.3.15-1.el8.x86_64 | grep bin
/usr/bin/free
/usr/bin/pgrep
/usr/bin/pidof
/usr/bin/pkill
/usr/bin/pmap
/usr/bin/ps
/usr/bin/pwdx
/usr/bin/skill
/usr/bin/slabtop
/usr/bin/snice
/usr/bin/tload
/usr/bin/top
/usr/bin/uptime
/usr/bin/vmstat
/usr/bin/w
/usr/bin/watch
/usr/sbin/pidof
/usr/sbin/sysctl
[root@foss-ssc-1 ~]#
```

# util-linux
```
[root@foss-ssc-1 ~]# rpm -ql util-linux | grep bin
/usr/bin/cal
/usr/bin/chmem
/usr/bin/chrt
/usr/bin/col
/usr/bin/colcrt
/usr/bin/colrm
/usr/bin/column
/usr/bin/dmesg
/usr/bin/eject
/usr/bin/fallocate
/usr/bin/fincore
/usr/bin/findmnt
/usr/bin/flock
/usr/bin/getopt
/usr/bin/hexdump
/usr/bin/i386
/usr/bin/ionice
/usr/bin/ipcmk
/usr/bin/ipcrm
/usr/bin/ipcs
/usr/bin/isosize
/usr/bin/kill
/usr/bin/last
/usr/bin/lastb
/usr/bin/linux32
/usr/bin/linux64
/usr/bin/logger
/usr/bin/login
/usr/bin/look
/usr/bin/lsblk
/usr/bin/lscpu
/usr/bin/lsipc
/usr/bin/lslocks
/usr/bin/lslogins
/usr/bin/lsmem
/usr/bin/lsns
/usr/bin/mcookie
/usr/bin/mesg
/usr/bin/more
/usr/bin/mount
/usr/bin/mountpoint
/usr/bin/namei
/usr/bin/nsenter
/usr/bin/prlimit
/usr/bin/raw
/usr/bin/rename
/usr/bin/renice
/usr/bin/rev
/usr/bin/script
/usr/bin/scriptreplay
/usr/bin/setarch
/usr/bin/setpriv
/usr/bin/setsid
/usr/bin/setterm
/usr/bin/su
/usr/bin/taskset
/usr/bin/ul
/usr/bin/umount
/usr/bin/uname26
/usr/bin/unshare
/usr/bin/utmpdump
/usr/bin/uuidgen
/usr/bin/uuidparse
/usr/bin/wall
/usr/bin/wdctl
/usr/bin/whereis
/usr/bin/write
/usr/bin/x86_64
/usr/sbin/addpart
/usr/sbin/agetty
/usr/sbin/blkdiscard
/usr/sbin/blkid
/usr/sbin/blkzone
/usr/sbin/blockdev
/usr/sbin/cfdisk
/usr/sbin/chcpu
/usr/sbin/clock
/usr/sbin/ctrlaltdel
/usr/sbin/delpart
/usr/sbin/fdformat
/usr/sbin/fdisk
/usr/sbin/findfs
/usr/sbin/fsck
/usr/sbin/fsck.cramfs
/usr/sbin/fsck.minix
/usr/sbin/fsfreeze
/usr/sbin/fstrim
/usr/sbin/hwclock
/usr/sbin/ldattach
/usr/sbin/losetup
/usr/sbin/mkfs
/usr/sbin/mkfs.cramfs
/usr/sbin/mkfs.minix
/usr/sbin/mkswap
/usr/sbin/nologin
/usr/sbin/partx
/usr/sbin/pivot_root
/usr/sbin/readprofile
/usr/sbin/resizepart
/usr/sbin/rfkill
/usr/sbin/rtcwake
/usr/sbin/runuser
/usr/sbin/sfdisk
/usr/sbin/sulogin
/usr/sbin/swaplabel
/usr/sbin/swapoff
/usr/sbin/swapon
/usr/sbin/switch_root
/usr/sbin/wipefs
/usr/sbin/zramctl
```
# coreuitls
```
[root@foss-ssc-1 ~]# rpm -ql coreutils | grep bin
/usr/bin/arch
/usr/bin/b2sum
/usr/bin/base32
/usr/bin/base64
/usr/bin/basename
/usr/bin/cat
/usr/bin/chcon
/usr/bin/chgrp
/usr/bin/chmod
/usr/bin/chown
/usr/bin/cksum
/usr/bin/comm
/usr/bin/cp
/usr/bin/csplit
/usr/bin/cut
/usr/bin/date
/usr/bin/dd
/usr/bin/df
/usr/bin/dir
/usr/bin/dircolors
/usr/bin/dirname
/usr/bin/du
/usr/bin/echo
/usr/bin/env
/usr/bin/expand
/usr/bin/expr
/usr/bin/factor
/usr/bin/false
/usr/bin/fmt
/usr/bin/fold
/usr/bin/groups
/usr/bin/head
/usr/bin/hostid
/usr/bin/id
/usr/bin/install
/usr/bin/join
/usr/bin/link
/usr/bin/ln
/usr/bin/logname
/usr/bin/ls
/usr/bin/md5sum
/usr/bin/mkdir
/usr/bin/mkfifo
/usr/bin/mknod
/usr/bin/mktemp
/usr/bin/mv
/usr/bin/nice
/usr/bin/nl
/usr/bin/nohup
/usr/bin/nproc
/usr/bin/numfmt
/usr/bin/od
/usr/bin/paste
/usr/bin/pathchk
/usr/bin/pinky
/usr/bin/pr
/usr/bin/printenv
/usr/bin/printf
/usr/bin/ptx
/usr/bin/pwd
/usr/bin/readlink
/usr/bin/realpath
/usr/bin/rm
/usr/bin/rmdir
/usr/bin/runcon
/usr/bin/seq
/usr/bin/sha1sum
/usr/bin/sha224sum
/usr/bin/sha256sum
/usr/bin/sha384sum
/usr/bin/sha512sum
/usr/bin/shred
/usr/bin/shuf
/usr/bin/sleep
/usr/bin/sort
/usr/bin/split
/usr/bin/stat
/usr/bin/stdbuf
/usr/bin/stty
/usr/bin/sum
/usr/bin/sync
/usr/bin/tac
/usr/bin/tail
/usr/bin/tee
/usr/bin/test
/usr/bin/timeout
/usr/bin/touch
/usr/bin/tr
/usr/bin/true
/usr/bin/truncate
/usr/bin/tsort
/usr/bin/tty
/usr/bin/uname
/usr/bin/unexpand
/usr/bin/uniq
/usr/bin/unlink
/usr/bin/users
/usr/bin/vdir
/usr/bin/wc
/usr/bin/who
/usr/bin/whoami
/usr/bin/yes
/usr/sbin/chroot
```

# sysstat

can copy iostat, mpstat, pidstat to target machine to run

sar depends on /usr/lib/systemd/system/sysstat.service inlcuded in sysstat rpm so can't copy it

https://github.com/sysstat/sysstat
```
[root@foss-ssc-1 ~]# rpm -ql sysstat | grep bin
/usr/bin/cifsiostat
/usr/bin/iostat
/usr/bin/mpstat
/usr/bin/pidstat
/usr/bin/sadf
/usr/bin/sar
/usr/bin/tapestat
```

# sar
# perf
# systemtap
# dtrace
# stress-ng

