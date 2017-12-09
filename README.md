# ECEN_5813_Harlow_Tichkule

## WARNING

Do not call make clean. Project2.elf derived from KDS will be deleted. If you call make clean return to ```project_2_rel``` tag.  

## MAKEFILE

In order to build the project call the following commands:

Make build builds the full project1.elf file, size.txt file, and project1.map 

```
$ make build
```

This command can also be called with a PLATFORM=\<PLATFORMNAME\> command. 

```
$ make build PLATFORM=BBB
```

Make unittests builds the cmocka based unit tests for conversion.c, memory.c and circular\_buffer.c. The output is unittests.elf

```
$ make unittests
```

Make compile all compiles all files but does not link them. This command can also be called with a PLATFORM=\<PLATFORMNAME\> command.

```
$ make compile-all
```

Make dependencies builds a dependencies file for all c files. This command can also be called with a PLATFORM=\<PLATFORMNAME\> command.

```
$ make dependencies
```

Make can also be called to make preprocessor, assembly or .o files of any desired file. This command can also be called with a PLATFORM=\<PLATFORMNAME\> command.

```
$ make build <filename>.extension
```

Make clean removes all .o, .i, .asm, .map, .dep, .elf, files as well as size.txt. 

```
$ make clean
```

## Project 1

In project one we created several modules to help us manipulate memory, convert data, and disable certain operations for various platforms. 

### Memory

Memory includes several modules:

1. my_memmove
2. my_memcpy
3. my_memset
4. my_memzero
5. my_reverse
6. reserve_words
7. free_words

### Debug

Enables a print memory function

1. print_memory

### Conversion

Conversion includes several modules:

1. my_itoa
2. my_atoi
3. big_to_little32
4. little_to_big32

## Project 2

Project2 was mostly accomplished using the KDS software. After building and testing circular buffer on our host machines we built an initial uart.c file as well as a project2.c file. In KDS we renamed the project2.c file to be a main.c in order to eliminate overhead. We also made the ```project2()``` function into ```main()```. 

Main initialized two buffers by mallocing CB_t structs. It then enables interrupts globally and at the NVIC. Next it configures the UART from ```UART_config()``` by enabling clocks, ports, gates, and ```TCI``` and ```RI``` interupts. After this it enters a ```while(1)``` loop characteristic of embedded software. In this loop it enters another while loop that accepts receive interupts until the RX circular buffer is full. When this fills a global variable exits the internal while loop and calls our ```calculate_statistics()``` function which calculates the number of miscellaneous, numerical, alphabetical, and punction characters in the RX buffer. This function also empties the RX buffer in the process. Then ```calculate_statistics()``` populates the TX buffer with a formatted outup to display the relevant information. It ends by enabling TX interupts (```TCIE```). This causes our function to enter the transmit portion of the IRQ. It transmits the contents of the buffer, until there are no characters left in the buffer causing a ```CB_EMPTY``` return value. When ```CB_EMPTY``` is returned to ```UART_send()``` it disables the transmit interupts. All the while RX interupts are allowed. 

### Circular Buffer

Cirular buffer defines an error checking ```enum CB_status``` as well as the following modules

1. CB_init
2. CB_destroy
3. CB_is_full
4. CB_is_empty
5. CB_buffer_add_item
6. CB_buffer_remove_item
6. CB_peek

### UART

Uart defines an error checking ```enum UART_status``` as well as the following modules

1. UART_configure
2. UART_send
3. UART_send_n
4. UART_receive
5. UART_receive_n
6. UART0_IRQHandler

### BBB Timings
| Test                       | Size (bytes) | stdlib.h vs. memory.h | Time1 (us) | Time2 (us) | Time3 (us) | Time4 (us) | Time5 (us) | TimeAvg (us) | 
|----------------------------|--------------|-----------------------|------------|------------|------------|------------|------------|--------------| 
| Memmove                    | 10           | stdlib.h              | 41         | 41         | 41         | 39         | 40         | 40.4         | 
|                            |              | memory.h              | 8          | 7          | 7          | 7          | 7          | 7.2          | 
|                            | 100          | stdlib.h              | 6          | 6          | 6          | 6          | 6          | 6            | 
|                            |              | memory.h              | 11         | 109        | 12         | 10         | 112        | 50.8         | 
|                            | 1000         | stdlib.h              | 9          | 9          | 9          | 9          | 10         | 9.2          | 
|                            |              | memory.h              | 167        | 68         | 68         | 172        | 68         | 108.6        | 
|                            | 5000         | stdlib.h              | 26         | 25         | 28         | 128        | 126        | 66.6         | 
|                            |              | memory.h              | 272        | 276        | 277        | 438        | 373        | 327.2        | 
| "Memset/                   |              |                       |            |            |            |            |            |              | 
| Memzero"                   | 10           | stdlib.h              | 4          | 3          | 5          | 4          | 4          | 4            | 
|                            |              | memory.h              | 5          | 5          | 4          | 5          | 5          | 4.8          | 
|                            | 100          | stdlib.h              | 33         | 101        | 35         | 35         | 35         | 47.8         | 
|                            |              | memory.h              | 8          | 9          | 8          | 9          | 8          | 8.4          | 
|                            | 1000         | stdlib.h              | 5          | 5          | 5          | 5          | 6          | 5.2          | 
|                            |              | memory.h              | 217        | 50         | 50         | 50         | 51         | 83.6         | 
|                            | 5000         | stdlib.h              | 107        | 9          | 9          | 10         | 9          | 28.8         | 
|                            |              | memory.h              | 237        | 237        | 238        | 237        | 237        | 237.2        | 
| Optimized Memmove          | 10           | stdlib.h              | 41         | 42         | 42         | 42         | 41         | 41.6         | 
|                            |              | memory.h              | 6          | 5          | 5          | 5          | 5          | 5.2          | 
|                            | 100          | stdlib.h              | 7          | 8          | 7          | 7          | 7          | 7.2          | 
|                            |              | memory.h              | 6          | 7          | 5          | 5          | 6          | 5.8          | 
|                            | 1000         | stdlib.h              | 8          | 9          | 10         | 9          | 9          | 9            | 
|                            |              | memory.h              | 18         | 18         | 18         | 17         | 17         | 17.6         | 
|                            | 5000         | stdlib.h              | 27         | 27         | 21         | 25         | 23         | 24.6         | 
|                            |              | memory.h              | 59         | 60         | 59         | 58         | 58         | 58.8         | 
| Optimized Memmove / Memset | 10           | stdlib.h              | 4          | 4          | 3          | 4          | 3          | 3.6          | 
|                            |              | memory.h              | 4          | 4          | 4          | 4          | 4          | 4            | 
|                            | 100          | stdlib.h              | 32         | 32         | 32         | 34         | 32         | 32.4         | 
|                            |              | memory.h              | 4          | 5          | 4          | 5          | 4          | 4.4          | 
|                            | 1000         | stdlib.h              | 4          | 4          | 4          | 5          | 5          | 4.4          | 
|                            |              | memory.h              | 13         | 14         | 14         | 14         | 14         | 13.8         | 
|                            | 5000         | stdlib.h              | 9          | 9          | 9          | 10         | 9          | 9.2          | 
|                            |              | memory.h              | 53         | 54         | 53         | 54         | 54         | 53.6         | 

### KL25Z Timings

| DMA Test                   | Size (bytes) | DMA 1  | DMA 2  | DMA 4  | stdlib.h | memory.h | 
|----------------------------|--------------|--------|--------|--------|----------|----------| 
| Memmove                    | 10           | 15.4   | 13.73  |        | 6.91     | 19.84    | 
|                            | 100          | 23.93  | 19.17  | 16.83  | 45.54    | 135.71   | 
|                            | 1000         | 109.82 | 62.08  | 38.24  | 431.78   | 1294.23  | 
|                            | 5000         | 490.04 | 251.63 | 132.42 | 2148.39  | 6444.79  | 
| Memset / Memzero           | 10           | 16.16  | 15.12  |        | 5.05     | 15.02    | 
|                            | 100          | 24.75  | 20.07  | 21.17  | 35.10    | 105.14   | 
|                            | 1000         | 110.63 | 63.18  | 74.86  | 335.50   | 1006.27  | 
|                            | 5000         | 490.52 | 252.29 | 311.71 | 1670.65  | 5012.46  | 
| Optimized Memmove          | 10           | 12.21  | 11.82  | 11.11  |          |          | 
|                            | 100          | 20.79  | 16.02  | 13.64  |          |          | 
|                            | 1000         | 106.61 | 11.25  | 35.09  |          |          | 
|                            | 5000         | 488.14 | 249.72 | 130.51 |          |          | 
| Optimized Memmove / Memset | 10           | 11.73  | 11.25  | 11.58  |          |          | 
|                            | 100          | 21.27  | 11.58  | 17.69  |          |          | 
|                            | 1000         | 107.05 | 11.54  | 71.29  |          |          | 
|                            | 5000         | 488.57 | 293.16 | 166.7  |          |          | 

### Timing comments

Overall the DMA significantly improved the timing for the KL25Z. Offloading the overhaed made improvements to both memset and memzero. However the benefits were relatively limited for the DMA4 on the 10 bit move, and was worse than standard lib for those functions at small memory as well. This is likely due to the overhead of setting up a dma transfer for such a small amount of memory. 

The BBB was faster than the KL25Z in almost all cases due to the significantly faster A8 architecture. It however, had more outliers. We predict that this is due to the operating system doing context switches or interupting the code in certain areas. Also the stdlib.h memove for 10 bytes was significanlty slower on the BBB, avering around 40us. We predict this is likely due to the architecture compiling in such a way that it used 32bit moves in most cases, which would be inefficent at moving 10 bytes due to the half word size. 

Finally, we noticed that optimization almost always improved the timing of the code. It was able to significanltly decrease the time used across both platforms. 

### Logging functionality

In project 3 we added logging functionality to our code. The logs are added by calling a function called populate_log_item(); Populate log item takes a log_t pointer, log id, profile id, payload pointer, and payload length. Each function can be called without those elements as the populate log checks the log id to determine which elements to use when populating the structure. After being populated the structure is added to a logger queue which is a circular buffer of log_t structures. In some cases, such as in the heartbeat we print immediately rather than adding to the queue. 
