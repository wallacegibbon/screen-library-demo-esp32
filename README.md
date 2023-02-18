## Introduction

This is a rewriting of [another project](https://github.com/wallacegibbon/esp32-screen-demo).
A mechanism like the *virtual function* in C++ is implemented in pure C.

## Comparing

The original C++ version:
(commit: 511d1defb014a6a1dafc4b27288a0094314c78e8)

```
Total sizes:
Used static IRAM:   59566 bytes ( 302674 remain, 16.4% used)
      .text size:   58539 bytes
   .vectors size:    1027 bytes
Used stat D/IRAM:   20640 bytes ( 152288 remain, 11.9% used)
      .data size:   11216 bytes
      .bss  size:    9424 bytes
Used Flash size :  404635 bytes
      .text     :  292499 bytes
      .rodata   :  111880 bytes
Total image size:  475417 bytes (.bin may be padded larger)
```

The current C version:
(commit: before the first commit)

```
Used static IRAM:   59182 bytes ( 303058 remain, 16.3% used)
      .text size:   58155 bytes
   .vectors size:    1027 bytes
Used stat D/IRAM:   13560 bytes ( 159368 remain, 7.8% used)
      .data size:   10960 bytes
      .bss  size:    2600 bytes
Used Flash size :  151819 bytes
      .text     :  112911 bytes
      .rodata   :   38652 bytes
Total image size:  221961 bytes (.bin may be padded larger)
```
