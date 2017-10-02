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
CFLAGS = -Wall  \
         -Werr  \
         -g     \
         -O0    \
         -std = C99

ifeq($(PLATFORM),HOST)
  CC = gcc
  CPPFLAGS = -DPROJECT1
endif

ifeq($(PLATFORM),BBB)
  CC = arm-linux-gnueabihf
  CPPFLAGS = -DPROJECT1
endif

ifeq($(PLATFORM),KL25Z)
  CC = arm-linux-none-eabi-gcc 
  LDFLAGS = ../platform/MKL25Z128xxx4_flash.ld
  ARCH = -mcpu = cortex-m0plus  \
         -mthumb                \
         -mfloat-abi = softfp   \
         -mfpu = fpv4-sp-d16    \
         --specs = nosys.specs    
endif

