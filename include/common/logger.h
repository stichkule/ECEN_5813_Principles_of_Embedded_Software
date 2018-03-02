/******************************************************************************
 * Copyright (C) 2017 by Kyle Harlow and Shiril Tichkule - University of Colorado
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. The authors and the University of Colorado are not liable for any
 * misuse of this material.
 *
 *****************************************************************************/
/**
 * @file logger.h
 * @brief This file is to be used with ECEN 5813 -- Project 3.
 *
 * This header file contains function prototypes for the logger function wrappers
 * Definitions of the logger functions are contained in the file "logger.c".
 *
 * @author Kyle Harlow
 * @author Shiril Tichkule
 *
 * @date December 04, 2017
 *
 */

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdio.h>
#include <stddef.h>
#include "uart.h"

typedef struct{
  uint8_t log_id;
  time_t timestamp;
  size_t log_length;
  void * payload;
  uint32_t checksum;
}log_t;

typedef enum log_id{
  LOGGER_INITIALIZED,
  GPIO_INITIALIZED,
  SYSTEM_INITIALIZED,
  SYSTEM_HALTED,
  INFO,
  WARNING,
  ERROR,
  PROFILING_STARTED,
  PROFILING_RESULT,
  PROFILING_COMPLETED,
  DATA_RECEIVED,
  DATA_ANALYSIS_STARTED,
  DATA_ALPHA_COUNT,
  DATA_NUMERIC_COUNT,
  DATA_PUNCTUATION_COUNT,
  DATA_MISC_COUNT,
  DATA_ANALYSIS_COMPLETED,
  HEARTBEAT
}log_id_t;

typedef enum profiler_id{
  DMA_MOVE_10,
  DMA_MOVE_100,
  DMA_MOVE_1000,
  DMA_MOVE_5000,
  DMA_ZERO_10,
  DMA_ZERO_100,
  DMA_ZERO_1000,
  DMA_ZERO_5000,
  STD_MOVE_10,
  STD_MOVE_100,
  STD_MOVE_1000,
  STD_MOVE_5000,
  STD_ZERO_10,
  STD_ZERO_100,
  STD_ZERO_1000,
  STD_ZERO_5000,
  MY_MOVE_10,
  MY_MOVE_100,
  MY_MOVE_1000,
  MY_MOVE_5000,
  MY_ZERO_10,
  MY_ZERO_100,
  MY_ZERO_1000,
  MY_ZERO_5000,
}prof_id_t;

typedef struct{
  uint32_t profiler_id;
  uint32_t address;
  time_t profile_time;
}prof_t;

/**
 * @brief function to print log data
 *
 * This function prints data corresponding to a log to the terminal.
 *
 * @param log pointer, log id, profile id
 * @return none
 */
void print_log_item(log_t * log_ptr);

/**
 * @brief function to populate a log
 *
 * This function populates data elements of a log item.
 *
 * @param log pointer, log id, profile id
 * @return none
 */
void populate_log_item(log_t * log_ptr, uint8_t log_id, uint8_t profile_id, void * payload_info, size_t length);

/**
 * @brief function to log raw data
 *
 * This function logs a sequence of bytes to the terminal.
 *
 * @param byte pointer, no. of bytes to be logged
 * @return none
 */
void log_data (uint8_t * ptr, size_t length);

/**
 * @brief function to log strings
 *
 * This function logs a string to the terminal.
 *
 * @param string pointer
 * @return none
 */
void log_string (uint8_t * str);

/**
 * @brief function to log integers
 *
 * This function logs an integer to the terminal using the itoa() function.
 *
 * @param integer to be logged
 * @return none
 */
void log_integer (uint32_t integer);

/**
 * @brief function to initialize a log item
 *
 * This function initializes a log item
 *
 * @param none
 * @return none
 */
void log_init(log_t * log_ptr);

/**
 * @brief function to destroy a log item
 *
 * This function destroys a log item
 *
 * @param none
 * @return none
 */
void log_destroy(log_t * log_ptr);

/**
 * @brief function to configure RTC
 *
 * This function configures the clock source and pins for enabling the RTC.
 *
 * @param none
 * @return none
 */
void rtc_configure (void);

/**
 * @brief function to initialize RTC
 *
 * This function initializes the RTC according to configuration parameters in rtc_configuration()
 *
 * @param epoch
 * @return none
 */
void rtc_init(uint32_t epoch);

#ifdef VERBOSE
#ifdef BBB
#define LOG_RAW_DATA(A,B) log_data(A,B)
#endif /*BBB*/
#ifdef HOST
#define LOG_RAW_DATA(A,B) log_data(A,B)
#endif /*HOST*/
#ifdef KL25Z
#define LOG_RAW_DATA(A,B) UART_send_n((uint8_t*)A,(int16_t)B)
#endif /*KL25Z*/
#endif /*VERBOSE*/

#ifdef VERBOSE
#ifdef BBB
#define LOG_RAW_STRING(A) printf(A)
#endif /*BBB*/
#ifdef HOST
#define LOG_RAW_STRING(A) printf(A)
#endif /*HOST*/
#ifdef KL25Z
#define LOG_RAW_STRING(A) log_string((uint8_t*)A)
#endif /*KL25Z*/
#endif /*VERBOSE*/

#ifdef VERBOSE
#ifdef BBB
#define LOG_RAW_INT(A) printf("%d\n", A)
#endif /*BBB*/
#ifdef HOST
#define LOG_RAW_INT(A) printf("%d\n", A)
#endif /*HOST*/
#ifdef KL25Z
#define LOG_RAW_INT(A) log_integer((uint32_t)A)
#endif /*KL25Z*/
#endif /*VERBOSE*/

#endif /* __LOGGER_H__ */
