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
	CPPFLAGS = $(PLAFG) \
		   $(VFLAG)
endif

ifeq ($(PLATFORM),KL25Z)
	CC = arm-none-eabi-gcc
	CPPFLAGS = $(PLAFG)
	LDFLAGS = ../platform/MKL25Z128xxx4_flash.ld
	ARCH = -mcpu = cortex-m0plus  \
	       -mthumb                \
	       -mfloat-abi = softfp   \
	       -mfpu = fpv4-sp-d16    \
	       --specs = nosys.specs    
endif

#Target rules
OBJECTS = $(SRCS:.c=.o)
ASM = $(SRCS:.c=.asm)
PPOUT = $(SRCS:.c=.i)
DEP = $(SRCS:.c=.dep)

#Preprocessor target rule
%.i : %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(CPPFLAGS) -E $< -o $@

#Assembly target rule
%.asm : %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(CPPFLAGS) -S $< -o $@

#Object file target rule
%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(CPPFLAGS) -c $^ -o $@

#compile_all target rule
.PHONY: compile-all
compile-all: $(OBJECTS)
$(OBJECTS): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(CPPFLAGS) -c $^

.PHONY: dependencies
dependencies: $(DEP)
main.dep: main.c 
	$(CC) $(CFLAGS) $(INCLUDES) $(CPPFLAGS) $(LDFLAGS) -M $< > $@
project1.dep: project1.c
	$(CC) $(CFLAGS) $(INCLUDES) $(CPPFLAGS) $(LDFLAGS) -M $< > $@
conversion.dep: conversion.c
	$(CC) $(CFLAGS) $(INCLUDES) $(CPPFLAGS) $(LDFLAGS) -M $< > $@
debug.dep: debug.c
	$(CC) $(CFLAGS) $(INCLUDES) $(CPPFLAGS) $(LDFLAGS) -M $< > $@
memory.dep: memory.c	
	$(CC) $(CFLAGS) $(INCLUDES) $(CPPFLAGS) $(LDFLAGS) -M $< > $@

#built target rule
.PHONY: build
build: project1.elf $(DEP)
project1.elf: $(OBJECTS) $(SRCS)
	$(CC) -o $@ $(OBJECTS) $(CFLAGS) -Wl,-Map=project1.map $(INCLUDES) -lm $(CPPFLAGS) $(LDFLAGS) 

#clean target rule
.PHONY: clean
clean:
	rm project1.map project1.elf $(OBJECTS) $(ASM) $(PPOUT) $(DEP)
