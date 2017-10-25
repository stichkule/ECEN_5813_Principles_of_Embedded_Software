# Copyright (C) 2017 by Kyle Harlow and Shiril Tichkule - University of Colorado
#
# Redistribution, modification or use of this software in source or binary
# forms is permitted as long as the files maintain this copyright. Users are
# permitted to modify this and use it to learn about the field of embedded
# software. Shiril Tichkule, Kyle Harlow, and the University of Colorado are
# not liable for any misuse of this material.
#
# Include file sources.mk
include sources.mk

# General flags (common to both platforms)
CFLAGS = -Wall	\
	 -Werror\
	 -g	\
	 -O0	\
	 -std=c99

PFLAG = -DPROJECT1
VFLAG = -DVERBOSE

ifeq ($(PLATFORM),HOST)
	CC = gcc
	CPPFLAGS = $(PFLAG) \
		   $(VFLAG)
endif

ifeq ($(PLATFORM),BBB)
	CC = arm-linux-gnueabihf-gcc
	CPPFLAGS = $(PFLAG) \
		   $(VFLAG)
endif

ifeq ($(PLATFORM),KL25Z)
	CC = arm-none-eabi-gcc
	CPPFLAGS = $(PFLAG)
	LDFLAGS = -Xlinker -T ../platform/MKL25Z128xxx4_flash.ld
	ARCH = -mcpu=cortex-m0  \
	       -mthumb\
	       -mfloat-abi=softfp   \
	       -mfpu=fpv4-sp-d16    \
	       --specs=nosys.specs    
endif

#Target rules
OBJECTS = $(SRCS:.c=.o)
ASM = $(SRCS:.c=.asm)
PPOUT = $(SRCS:.c=.i)
DEP = $(SRCS:.c=.dep)

#Preprocessor target rule
%.i : %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(CPPFLAGS) $(ARCH) -E $< -o $@

#Assembly target rule
%.asm : %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(CPPFLAGS) $(ARCH) -S $< -o $@

#Object file target rule
%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(CPPFLAGS) $(ARCH) -c $^ -o $@

#compile modules for unit tests
.PHONY: unittests
unittests: unittests.elf
unittests.elf: $(OBJECTS) unittests.c
  $(CC) $(CFLAGS) $(INCLUDES) $(CPPFLAGS) $(ARCH) -lm -lcmocka $^ -o $@

#compile_all target rule
.PHONY: compile-all
compile-all: $(OBJECTS)
$(OBJECTS): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(CPPFLAGS) $(ARCH) -c $^

.PHONY: dependencies
dependencies: $(DEP)
%.dep:%.c
	$(CC) $(CFLAGS) $(INCLUDES) $(CPPFLAGS) $(ARCH) -M $^ > $@	

#built target rule
.PHONY: build
build: project1.elf $(DEP) size.txt
project1.elf: $(OBJECTS) $(SRCS)
	$(CC) -o $@ $(OBJECTS) $(CFLAGS) -Wl,-Map=project1.map $(INCLUDES) -lm $(LDFLAGS) $(ARCH) $(CPPFLAGS)
size.txt: project1.elf
	size --format=SysV $< > size.txt 

#clean target rule
.PHONY: clean
clean:
	rm -rf *.o *.i *.asm *.s *.map *.dep project1.elf size.txt
