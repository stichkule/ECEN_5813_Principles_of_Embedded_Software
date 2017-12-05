# Copyright (C) 2017 by Kyle Harlow and Shiril Tichkule - University of Colorado
#
# Redistribution, modification or use of this software in source or binary
# forms is permitted as long as the files maintain this copyright. Users are
# permitted to modify this and use it to learn about the field of embedded
# software. Shiril Tichkule, Kyle Harlow, and the University of Colorado are
# not liable for any misuse of this material.

# Includes and Sources for Project 3
INCLUDES = -I ../include/common

ifeq ($(PLATFORM),HOST)
INCLUDES = -I ../include/common
endif

ifeq ($(PLATFORM),BBB)
INCLUDES = -I ../include/common
endif

ifeq ($(PLATFORM),KL25Z)
INCLUDES = \
	-I ../include/common \
	-I ../include/kl25z \
	-I ../include/CMSIS
endif
SRCS =	main.c		\
	memory.c	\
	conversion.c	\
	project3.c

ifeq ($(PLATFORM),KL25Z)
SRCS = main.c		\
	project1.c	\
	memory.c	\
	conversion.c	\
	debug.c\
	circular_buffer.c\
	system_MKL25Z4.c\
	uart.c\
	project2.c
endif
