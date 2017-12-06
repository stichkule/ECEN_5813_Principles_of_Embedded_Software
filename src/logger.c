

void print_log_item(log_t * log_ptr, uint8_t log_id, uint8_t profile_id){

}

void log_item(log_t * log_ptr, log_q * log_queue){
  if(!log_ptr || !log_queue){return;}
  LQ_buffer_add_item(log_queue, log_ptr);
}

void populate_log_item(log_t * log_ptr, uint8_t log_id, uint8_t profile_id, void * payload_info, size_t length){
  switch(log_id){
    case INFO :
      log_ptr->log_id = log_id;
      log_ptr->timestamp = RTC_TSR;
      log_ptr->log_length = length;
      log_ptr->payload = (uint8_t *) payload_info;
      log_ptr->checksum = (uint32_t)log_id+(uint32_t)log_ptr->timestamp+(uint32_t)log_ptr->log_length
        +(uint32_t)log_ptr->payload;
      break;
    case WARNING :
      log_ptr->log_id = log_id;
      log_ptr->timestamp = RTC_TSR;
      log_ptr->log_length = length;
      log_ptr->payload = (uint8_t *) payload_info;
      log_ptr->checksum = (uint32_t)log_id+(uint32_t)log_ptr->timestamp+(uint32_t)log_ptr->log_length
        +(uint32_t)log_ptr->payload;
      break;
    case ERROR :
      log_ptr->log_id = log_id;
      log_ptr->timestamp = RTC_TSR;
      log_ptr->log_length = length;
      log_ptr->payload = (uint8_t *) payload_info;
      log_ptr->checksum = (uint32_t)log_id+(uint32_t)log_ptr->timestamp+(uint32_t)log_ptr->log_length
        +(uint32_t)log_ptr->payload;
      break;
    case PROFILING_STARTED :
      log_ptr->log_id = log_id;
      log_ptr->timestamp = RTC_TSR;
      log_ptr->log_length = length;
      log_ptr->payload = (uint8_t *) payload_info;
      log_ptr->checksum = (uint32_t)log_id+(uint32_t)log_ptr->timestamp+(uint32_t)log_ptr->log_length
        +(uint32_t)log_ptr->payload;
      break;
    case PROFILING_RESULT :
      log_ptr->log_id = log_id;
      log_ptr->timestamp = RTC_TSR;
      prof_t temp;
      prof_t * temp_ptr = &temp;
      log_ptr->log_length = sizeof(temp);
      temp_ptr->profile_id = profile_id;
      temp_ptr->profile_time = count_diff;
      log_ptr->payload = (prof_t *) temp_ptr;
      log_ptr->checksum = (uint32_t)log_id+(uint32_t)log_ptr->timestamp+(uint32_t)log_ptr->log_length
        +(uint32_t)log_ptr->payload;
      break;
    case PROFILING_COMPLETED :
      log_ptr->log_id = log_id;
      log_ptr->timestamp = RTC_TSR;
      log_ptr->log_length = length;
      log_ptr->payload = (uint8_t *) payload_info;
      log_ptr->checksum = (uint32_t)log_id+(uint32_t)log_ptr->timestamp+(uint32_t)log_ptr->log_length
        +(uint32_t)log_ptr->payload;
      break;
    case DATA_RECEIVED :
      log_ptr->log_id = log_id;
      log_ptr->timestamp = RTC_TSR;
      log_ptr->log_length = length;
      log_ptr->payload = (uint8_t *) payload_info;
      log_ptr->checksum = (uint32_t)log_id+(uint32_t)log_ptr->timestamp+(uint32_t)log_ptr->log_length
        +(uint32_t)log_ptr->payload;
      break;
    case DATA_ALPHA_COUNT :
      log_ptr->log_id = log_id;
      log_ptr->timestamp = RTC_TSR;
      log_ptr->log_length = length;
      log_ptr->payload = (uint8_t *) payload_info;
      log_ptr->checksum = (uint32_t)log_id+(uint32_t)log_ptr->timestamp+(uint32_t)log_ptr->log_length
        +(uint32_t)log_ptr->payload;
      break;
    case DATA_NUMERIC_COUNT :
      log_ptr->log_id = log_id;
      log_ptr->timestamp = RTC_TSR;
      log_ptr->log_length = length;
      log_ptr->payload = (uint8_t *) payload_info;
      log_ptr->checksum = (uint32_t)log_id+(uint32_t)log_ptr->timestamp+(uint32_t)log_ptr->log_length
        +(uint32_t)log_ptr->payload;
         break;
    case DATA_ALPHA_COUNT :
      log_ptr->log_id = log_id;
      log_ptr->timestamp = RTC_TSR;
      log_ptr->log_length = length;
      log_ptr->payload = (uint8_t *) payload_info;
      log_ptr->checksum = (uint32_t)log_id+(uint32_t)log_ptr->timestamp+(uint32_t)log_ptr->log_length
        +(uint32_t)log_ptr->payload;
    case DATA_NUMERIC_COUNT :
      log_ptr->log_id = log_id;
      log_ptr->timestamp = RTC_TSR;
      log_ptr->log_length = length;
      log_ptr->payload = (uint8_t *) payload_info;
      log_ptr->checksum = (uint32_t)log_id+(uint32_t)log_ptr->timestamp+(uint32_t)log_ptr->log_length
        +(uint32_t)log_ptr->payload;
         break;
    case DATA_PUNCTUATION_COUNT :
      log_ptr->log_id = log_id;
      log_ptr->timestamp = RTC_TSR;
      log_ptr->log_length = length;
      log_ptr->payload = (uint8_t *) payload_info;
      log_ptr->checksum = (uint32_t)log_id+(uint32_t)log_ptr->timestamp+(uint32_t)log_ptr->log_length
        +(uint32_t)log_ptr->payload;
         break;
    case DATA_MISC_COUNT :
      log_ptr->log_id = log_id;
      log_ptr->timestamp = RTC_TSR;
      log_ptr->log_length = length;
      log_ptr->payload = (uint8_t *) payload_info;
      log_ptr->checksum = (uint32_t)log_id+(uint32_t)log_ptr->timestamp+(uint32_t)log_ptr->log_length
        +(uint32_t)log_ptr->payload;
         break;
    default :
      log_ptr->log_id = log_id;
      log_ptr->timestamp = RTC_TSR;
      log_ptr->log_length = 0;
      log_ptr->payload = NULL;
      log_ptr->checksum = (uint32_t)log_id+(uint32_t)log_ptr->timestamp+(uint32_t)log_ptr->log_length;
      break;
  }
}
