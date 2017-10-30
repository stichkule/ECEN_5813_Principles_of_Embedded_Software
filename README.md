# ECEN_5813_Harlow_Tichkule

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
