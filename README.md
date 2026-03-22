```
██████╗ ██╗ ██████╗ ███████╗██╗     ██╗██████╗ 
██╔══██╗██║██╔═══██╗██╔════╝██║     ██║██╔══██╗
██████╔╝██║██║   ██║███████╗██║     ██║██████╔╝
██╔══██╗██║██║   ██║╚════██║██║     ██║██╔══██╗
██████╔╝██║╚██████╔╝███████║███████╗██║██████╔╝
╚═════╝ ╚═╝ ╚═════╝ ╚══════╝╚══════╝╚═╝╚═════╝ 
                                               
© Jeremy Simon Thornton 2024   v 0.4                                                                                              
```
A retro programming library to make life easier using the BIOS functions of PC, XT, AT, et al. (and their clones).

Inspired by David Jurgens' [HelpPC Reference Library](https://noami.us/helppc/index.html) and my desire to practice 8086 assembly language like it was 1986 :)

> [!TIP] Adding the Library
> 
> In your main project repository (the one using BIOSLIB):
> ```bash
> git submodule add https://github.com/cspjst/BIOSLIB.git bioslib
> ```

## Progress...

*N.B.* Implemented on an ad hoc basis as the need(s) arise:

- [ ] 0/1  INT 8 - System timer
- [ ] 0/27 INT 10 - Video BIOS Services
- [ ] 0/1  INT 11 - BIOS Equipment Determination / BIOS Equipment Flags
- [x] 1/1  INT 12 - Memory Size Determination
- [ ] 0/26 INT 13 - Diskette BIOS Services
- [ ] 0/5  INT 14 - BIOS Asynchronous Communications Services
- [ ] 0/30 INT 15 - System BIOS Services
- [x] 2/9  INT 16 - Keyboard BIOS Services
- [ ] 0/3  INT 17 - Printer BIOS Services
- [ ] 0/1  INT 19 - Bootstrap Loader
- [x] 2/13 INT 1A - System and Real Time Clock BIOS Services
- [ ] 0/1  INT 1B - BIOS Ctrl-Break Handler Address
- [ ] 0/1  INT 1C - System Timer Tick (User Routine)

## Interrupt Table as Implemented by System BIOS

| INT  | Source | Function                                |
| :--- | :----- | :-------------------------------------- |
| 00   | CPU    | Divide by zero                          |
| 01   | CPU    | Single step                             |
| 02   | CPU    | Non-maskable                            |
| 03   | CPU    | Breakpoint                              |
| 04   | CPU    | Overflow trap                           |
| 05   | BIOS   | Print screen                            |
| 06   | CPU    | Invalid opcode                          |
| 07   | CPU    | Coprocessor not available               |
| 08   | IRQ0   | Timer                                   |
| 09   | IRQ1   | Keyboard service required               |
| 0A   | IRQ2   | Slave 8259 or EGA/VGA vertical retrace  |
| 0B   | IRQ3   | COM2 service required                   |
| 0C   | IRQ4   | COM1 service required                   |
| 0D   | IRQ5   | Fixed disk or data request from LPT2    |
| 0E   | IRQ6   | Floppy disk service required            |
| 0F   | IRQ7   | Data request from LPT1                  |
| 10   | BIOS   | Video                                   |
| 11   | BIOS   | Equipment determination                 |
| 12   | BIOS   | Memory size                             |
| 13   | BIOS   | Disk I/O service                        |
| 14   | BIOS   | Serial communications                   |
| 15   | BIOS   | System services, cassette               |
| 16   | BIOS   | Keyboard services                       |
| 17   | BIOS   | Parallel printer                        |
| 18   | BIOS   | ROM BASIC loader                        |
| 19   | BIOS   | Bootstrap loader                        |
| 1A   | BIOS   | Time of day                             |
| 1B   | BIOS   | User defined ctrl-break handler         |
| 1C   | BIOS   | User defined clock tick handler         |
| 1D   | BIOS   | 6845 video parameter pointer            |
| 1E   | BIOS   | Diskette parameter pointer (base table) |
| 1F   | BIOS   | Graphics character table                |
