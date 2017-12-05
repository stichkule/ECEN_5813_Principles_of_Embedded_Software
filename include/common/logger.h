#ifndef __LOGGER_H_
#define __LOGGER_H_

typedef struct logger{
  uint8_t log_id;
  time_t timestamp;
  size_t log_length;
  void * payload;
  uint32_t checksum;
}log_t;

typedef enum log_id{
  LOGGER_INITIALIZED;
  GPIO_INITIALIZED;
  SYSTEM_INITIALIZED;
  SYSTEM_HALTED;
  INFO;
  WARNING;
  ERROR;
  PROFILING_STARTED;
  PROFILING_RESULT;
  DATA_RECEIVED;
  DATA_ANALYSIS_STARTED;
  DATA_ALPHA_COUNT;
  DATA_NUMERIC_COUNT;
  DATA_ALPHA_COUNT;
  DATA_NUMERIC_COUNT;
  DATA_PUNCTUATION_COUNT;
  DATA_MISC_COUNT;
  DATA_ANALYSIS_COMPLETED;
}log_id_t;

typedef enum profiler_id{
  DMA_MOVE_10;
  DMA_MOVE_100;
  DMA_MOVE_1000;
  DMA_MOVE_5000;
  DMA_ZERO_10;
  DMA_ZERO_100;
  DMA_ZERO_1000;
  DMA_ZERO_5000;
  STD_MOVE_10;
  STD_MOVE_100;
  STD_MOVE_1000;
  STD_MOVE_5000;
  STD_ZERO_10;
  STD_ZERO_100;
  STD_ZERO_1000;
  STD_ZERO_5000;
  MY_MOVE_10;
  MY_MOVE_100;
  MY_MOVE_1000;
  MY_MOVE_5000;
  MY_ZERO_10;
  MY_ZERO_100;
  MY_ZERO_1000;
  MY_ZERO_5000;
}prof_id_t;

typedef struct prof_payload{
  uint8_t profiler_id;
  time_t profile_time;
}prof_t;

#endif /*__LOGGER_H_*/
