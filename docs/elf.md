GUN ELF Debugging Tools
---

- [objdump](#objdump)
  - [-a - archive header only for .a](#-a---archive-header-only-for-a)
- [readelf](#readelf)
- [strings](#strings)
- [addr2line](#addr2line)
- [nm](#nm)
- [ar](#ar)


# objdump
## -a - archive header only for .a
```
bash-4.2# objdump -a libDBtlv.a
In archive libDBtlv.a:

DBtlv_get_bufsize.c.o:     file format elf32-i386
rw-r--r-- 0/0   9076 Mar  1 05:54 2021 DBtlv_get_bufsize.c.o


DBtlv_reltotlv.c.o:     file format elf32-i386
rw-r--r-- 0/0  72648 Mar  1 05:54 2021 DBtlv_reltotlv.c.o


DBtlv_tlvtorel.c.o:     file format elf32-i386
rw-r--r-- 0/0  60280 Mar  1 05:54 2021 DBtlv_tlvtorel.c.o


DBtlv_interface.c.o:     file format elf32-i386
rw-r--r-- 0/0  11924 Mar  1 05:54 2021 DBtlv_interface.c.o
```

## -h: show section headers

```
bash-4.2# objdump -h mapsys

mapsys:     file format elf32-i386

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .interp       00000013  08048174  08048174  00000174  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  1 .note.ABI-tag 00000020  08048188  08048188  00000188  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  2 .note.gnu.build-id 00000024  080481a8  080481a8  000001a8  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  3 .gnu.hash     00002bd0  080481cc  080481cc  000001cc  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  4 .dynsym       00008370  0804ad9c  0804ad9c  00002d9c  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  5 .dynstr       0000e109  0805310c  0805310c  0000b10c  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  6 .gnu.version  0000106e  08061216  08061216  00019216  2**1
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  7 .gnu.version_r 00000310  08062284  08062284  0001a284  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  8 .rel.dyn      00000ea8  08062594  08062594  0001a594  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  9 .rel.plt      00001288  0806343c  0806343c  0001b43c  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 10 .init         00000023  080646c4  080646c4  0001c6c4  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 11 .plt          00002520  080646f0  080646f0  0001c6f0  2**4
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 12 .plt.got      00000028  08066c10  08066c10  0001ec10  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 13 .text         0098d090  08066c40  08066c40  0001ec40  2**4
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 14 .fini         00000014  089f3cd0  089f3cd0  009abcd0  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 15 .rodata       001634bc  089f3d00  089f3d00  009abd00  2**5
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 16 .eh_frame_hdr 00021444  08b571bc  08b571bc  00b0f1bc  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 17 .gcc_except_table 00008f10  08b78600  08b78600  00b30600  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 18 .eh_frame     000be2dc  08b829a4  08b829a4  00b399a4  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 19 .tdata        00000004  08c40c80  08c40c80  00bf7c80  2**2
                  CONTENTS, ALLOC, LOAD, DATA, THREAD_LOCAL
 20 .tbss         000000c0  08c40c84  08c40c84  00bf7c84  2**2
                  ALLOC, THREAD_LOCAL
 21 .init_array   00000114  08c40c84  08c40c84  00bf7c84  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 22 .fini_array   00000004  08c40d98  08c40d98  00bf7d98  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 23 .jcr          00000004  08c40d9c  08c40d9c  00bf7d9c  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 24 .data.rel.ro  0000291c  08c40da0  08c40da0  00bf7da0  2**5
                  CONTENTS, ALLOC, LOAD, DATA
 25 .dynamic      00000240  08c436bc  08c436bc  00bfa6bc  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 26 .got          000006f0  08c438fc  08c438fc  00bfa8fc  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 27 .got.plt      00000950  08c44000  08c44000  00bfb000  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 28 .data         000b43d8  08c44960  08c44960  00bfb960  2**5
                  CONTENTS, ALLOC, LOAD, DATA
 29 .bss          0c197568  08cf8d40  08cf8d40  00cafd38  2**6
                  ALLOC
 30 .comment      0000136f  00000000  00000000  00cafd38  2**0
                  CONTENTS, READONLY
 31 .note         000006e0  00000000  00000000  00cb10a7  2**0
                  CONTENTS, READONLY
 32 .debug_aranges 00005a38  00000000  00000000  00cb1787  2**0
                  CONTENTS, READONLY, DEBUGGING
 33 .debug_info   01de20a4  00000000  00000000  00cb71bf  2**0
                  CONTENTS, READONLY, DEBUGGING
 34 .debug_abbrev 00082c0c  00000000  00000000  02a99263  2**0
                  CONTENTS, READONLY, DEBUGGING
 35 .debug_line   00293da0  00000000  00000000  02b1be6f  2**0
                  CONTENTS, READONLY, DEBUGGING
 36 .debug_str    001c600d  00000000  00000000  02dafc0f  2**0
                  CONTENTS, READONLY, DEBUGGING
 37 .debug_loc    002ec0c8  00000000  00000000  02f75c1c  2**0
                  CONTENTS, READONLY, DEBUGGING
 38 .debug_ranges 0009d540  00000000  00000000  03261ce4  2**0
                  CONTENTS, READONLY, DEBUGGING
```

## -c - Decode (demangle) low-level symbol names into user-level names

# readelf
# strings
# addr2line
# nm
# ar
