/* This file is autogenerated by tracetool, do not edit. */

#ifndef TRACE_HW_NVRAM_GENERATED_TRACERS_H
#define TRACE_HW_NVRAM_GENERATED_TRACERS_H

#include "trace/control.h"

extern TraceEvent _TRACE_NVRAM_READ_EVENT;
extern TraceEvent _TRACE_NVRAM_WRITE_EVENT;
extern TraceEvent _TRACE_FW_CFG_SELECT_EVENT;
extern TraceEvent _TRACE_FW_CFG_READ_EVENT;
extern TraceEvent _TRACE_FW_CFG_ADD_BYTES_EVENT;
extern TraceEvent _TRACE_FW_CFG_ADD_FILE_EVENT;
extern TraceEvent _TRACE_FW_CFG_ADD_STRING_EVENT;
extern TraceEvent _TRACE_FW_CFG_ADD_I16_EVENT;
extern TraceEvent _TRACE_FW_CFG_ADD_I32_EVENT;
extern TraceEvent _TRACE_FW_CFG_ADD_I64_EVENT;
extern TraceEvent _TRACE_MACIO_NVRAM_READ_EVENT;
extern TraceEvent _TRACE_MACIO_NVRAM_WRITE_EVENT;
extern uint16_t _TRACE_NVRAM_READ_DSTATE;
extern uint16_t _TRACE_NVRAM_WRITE_DSTATE;
extern uint16_t _TRACE_FW_CFG_SELECT_DSTATE;
extern uint16_t _TRACE_FW_CFG_READ_DSTATE;
extern uint16_t _TRACE_FW_CFG_ADD_BYTES_DSTATE;
extern uint16_t _TRACE_FW_CFG_ADD_FILE_DSTATE;
extern uint16_t _TRACE_FW_CFG_ADD_STRING_DSTATE;
extern uint16_t _TRACE_FW_CFG_ADD_I16_DSTATE;
extern uint16_t _TRACE_FW_CFG_ADD_I32_DSTATE;
extern uint16_t _TRACE_FW_CFG_ADD_I64_DSTATE;
extern uint16_t _TRACE_MACIO_NVRAM_READ_DSTATE;
extern uint16_t _TRACE_MACIO_NVRAM_WRITE_DSTATE;
#define TRACE_NVRAM_READ_ENABLED 1
#define TRACE_NVRAM_WRITE_ENABLED 1
#define TRACE_FW_CFG_SELECT_ENABLED 1
#define TRACE_FW_CFG_READ_ENABLED 1
#define TRACE_FW_CFG_ADD_BYTES_ENABLED 1
#define TRACE_FW_CFG_ADD_FILE_ENABLED 1
#define TRACE_FW_CFG_ADD_STRING_ENABLED 1
#define TRACE_FW_CFG_ADD_I16_ENABLED 1
#define TRACE_FW_CFG_ADD_I32_ENABLED 1
#define TRACE_FW_CFG_ADD_I64_ENABLED 1
#define TRACE_MACIO_NVRAM_READ_ENABLED 1
#define TRACE_MACIO_NVRAM_WRITE_ENABLED 1
#include "qemu/log-for-trace.h"
#include "qemu/error-report.h"


#define TRACE_NVRAM_READ_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_NVRAM_READ) || \
    false)

static inline void _nocheck__trace_nvram_read(uint32_t addr, uint32_t ret)
{
    if (trace_event_get_state(TRACE_NVRAM_READ) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 4 "/home/zuherj/codehub/qemu_pv_device/hw/nvram/trace-events"
            qemu_log("%d@%zu.%06zu:nvram_read " "read addr %d: 0x%02x" "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , addr, ret);
#line 64 "trace/trace-hw_nvram.h"
        } else {
#line 4 "/home/zuherj/codehub/qemu_pv_device/hw/nvram/trace-events"
            qemu_log("nvram_read " "read addr %d: 0x%02x" "\n", addr, ret);
#line 68 "trace/trace-hw_nvram.h"
        }
    }
}

static inline void trace_nvram_read(uint32_t addr, uint32_t ret)
{
    if (true) {
        _nocheck__trace_nvram_read(addr, ret);
    }
}

#define TRACE_NVRAM_WRITE_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_NVRAM_WRITE) || \
    false)

static inline void _nocheck__trace_nvram_write(uint32_t addr, uint32_t old, uint32_t val)
{
    if (trace_event_get_state(TRACE_NVRAM_WRITE) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 5 "/home/zuherj/codehub/qemu_pv_device/hw/nvram/trace-events"
            qemu_log("%d@%zu.%06zu:nvram_write " "write addr %d: 0x%02x -> 0x%02x" "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , addr, old, val);
#line 95 "trace/trace-hw_nvram.h"
        } else {
#line 5 "/home/zuherj/codehub/qemu_pv_device/hw/nvram/trace-events"
            qemu_log("nvram_write " "write addr %d: 0x%02x -> 0x%02x" "\n", addr, old, val);
#line 99 "trace/trace-hw_nvram.h"
        }
    }
}

static inline void trace_nvram_write(uint32_t addr, uint32_t old, uint32_t val)
{
    if (true) {
        _nocheck__trace_nvram_write(addr, old, val);
    }
}

#define TRACE_FW_CFG_SELECT_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_FW_CFG_SELECT) || \
    false)

static inline void _nocheck__trace_fw_cfg_select(void * s, uint16_t key_value, const char * key_name, int ret)
{
    if (trace_event_get_state(TRACE_FW_CFG_SELECT) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 8 "/home/zuherj/codehub/qemu_pv_device/hw/nvram/trace-events"
            qemu_log("%d@%zu.%06zu:fw_cfg_select " "%p key 0x%04" PRIx16 " '%s', ret: %d" "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , s, key_value, key_name, ret);
#line 126 "trace/trace-hw_nvram.h"
        } else {
#line 8 "/home/zuherj/codehub/qemu_pv_device/hw/nvram/trace-events"
            qemu_log("fw_cfg_select " "%p key 0x%04" PRIx16 " '%s', ret: %d" "\n", s, key_value, key_name, ret);
#line 130 "trace/trace-hw_nvram.h"
        }
    }
}

static inline void trace_fw_cfg_select(void * s, uint16_t key_value, const char * key_name, int ret)
{
    if (true) {
        _nocheck__trace_fw_cfg_select(s, key_value, key_name, ret);
    }
}

#define TRACE_FW_CFG_READ_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_FW_CFG_READ) || \
    false)

static inline void _nocheck__trace_fw_cfg_read(void * s, uint64_t ret)
{
    if (trace_event_get_state(TRACE_FW_CFG_READ) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 9 "/home/zuherj/codehub/qemu_pv_device/hw/nvram/trace-events"
            qemu_log("%d@%zu.%06zu:fw_cfg_read " "%p = 0x%"PRIx64 "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , s, ret);
#line 157 "trace/trace-hw_nvram.h"
        } else {
#line 9 "/home/zuherj/codehub/qemu_pv_device/hw/nvram/trace-events"
            qemu_log("fw_cfg_read " "%p = 0x%"PRIx64 "\n", s, ret);
#line 161 "trace/trace-hw_nvram.h"
        }
    }
}

static inline void trace_fw_cfg_read(void * s, uint64_t ret)
{
    if (true) {
        _nocheck__trace_fw_cfg_read(s, ret);
    }
}

#define TRACE_FW_CFG_ADD_BYTES_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_FW_CFG_ADD_BYTES) || \
    false)

static inline void _nocheck__trace_fw_cfg_add_bytes(uint16_t key_value, const char * key_name, size_t len)
{
    if (trace_event_get_state(TRACE_FW_CFG_ADD_BYTES) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 10 "/home/zuherj/codehub/qemu_pv_device/hw/nvram/trace-events"
            qemu_log("%d@%zu.%06zu:fw_cfg_add_bytes " "key 0x%04" PRIx16 " '%s', %zu bytes" "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , key_value, key_name, len);
#line 188 "trace/trace-hw_nvram.h"
        } else {
#line 10 "/home/zuherj/codehub/qemu_pv_device/hw/nvram/trace-events"
            qemu_log("fw_cfg_add_bytes " "key 0x%04" PRIx16 " '%s', %zu bytes" "\n", key_value, key_name, len);
#line 192 "trace/trace-hw_nvram.h"
        }
    }
}

static inline void trace_fw_cfg_add_bytes(uint16_t key_value, const char * key_name, size_t len)
{
    if (true) {
        _nocheck__trace_fw_cfg_add_bytes(key_value, key_name, len);
    }
}

#define TRACE_FW_CFG_ADD_FILE_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_FW_CFG_ADD_FILE) || \
    false)

static inline void _nocheck__trace_fw_cfg_add_file(void * s, int index, char * name, size_t len)
{
    if (trace_event_get_state(TRACE_FW_CFG_ADD_FILE) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 11 "/home/zuherj/codehub/qemu_pv_device/hw/nvram/trace-events"
            qemu_log("%d@%zu.%06zu:fw_cfg_add_file " "%p #%d: %s (%zd bytes)" "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , s, index, name, len);
#line 219 "trace/trace-hw_nvram.h"
        } else {
#line 11 "/home/zuherj/codehub/qemu_pv_device/hw/nvram/trace-events"
            qemu_log("fw_cfg_add_file " "%p #%d: %s (%zd bytes)" "\n", s, index, name, len);
#line 223 "trace/trace-hw_nvram.h"
        }
    }
}

static inline void trace_fw_cfg_add_file(void * s, int index, char * name, size_t len)
{
    if (true) {
        _nocheck__trace_fw_cfg_add_file(s, index, name, len);
    }
}

#define TRACE_FW_CFG_ADD_STRING_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_FW_CFG_ADD_STRING) || \
    false)

static inline void _nocheck__trace_fw_cfg_add_string(uint16_t key_value, const char * key_name, const char * value)
{
    if (trace_event_get_state(TRACE_FW_CFG_ADD_STRING) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 12 "/home/zuherj/codehub/qemu_pv_device/hw/nvram/trace-events"
            qemu_log("%d@%zu.%06zu:fw_cfg_add_string " "key 0x%04" PRIx16 " '%s', value '%s'" "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , key_value, key_name, value);
#line 250 "trace/trace-hw_nvram.h"
        } else {
#line 12 "/home/zuherj/codehub/qemu_pv_device/hw/nvram/trace-events"
            qemu_log("fw_cfg_add_string " "key 0x%04" PRIx16 " '%s', value '%s'" "\n", key_value, key_name, value);
#line 254 "trace/trace-hw_nvram.h"
        }
    }
}

static inline void trace_fw_cfg_add_string(uint16_t key_value, const char * key_name, const char * value)
{
    if (true) {
        _nocheck__trace_fw_cfg_add_string(key_value, key_name, value);
    }
}

#define TRACE_FW_CFG_ADD_I16_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_FW_CFG_ADD_I16) || \
    false)

static inline void _nocheck__trace_fw_cfg_add_i16(uint16_t key_value, const char * key_name, uint16_t value)
{
    if (trace_event_get_state(TRACE_FW_CFG_ADD_I16) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 13 "/home/zuherj/codehub/qemu_pv_device/hw/nvram/trace-events"
            qemu_log("%d@%zu.%06zu:fw_cfg_add_i16 " "key 0x%04" PRIx16 " '%s', value 0x%" PRIx16 "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , key_value, key_name, value);
#line 281 "trace/trace-hw_nvram.h"
        } else {
#line 13 "/home/zuherj/codehub/qemu_pv_device/hw/nvram/trace-events"
            qemu_log("fw_cfg_add_i16 " "key 0x%04" PRIx16 " '%s', value 0x%" PRIx16 "\n", key_value, key_name, value);
#line 285 "trace/trace-hw_nvram.h"
        }
    }
}

static inline void trace_fw_cfg_add_i16(uint16_t key_value, const char * key_name, uint16_t value)
{
    if (true) {
        _nocheck__trace_fw_cfg_add_i16(key_value, key_name, value);
    }
}

#define TRACE_FW_CFG_ADD_I32_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_FW_CFG_ADD_I32) || \
    false)

static inline void _nocheck__trace_fw_cfg_add_i32(uint16_t key_value, const char * key_name, uint32_t value)
{
    if (trace_event_get_state(TRACE_FW_CFG_ADD_I32) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 14 "/home/zuherj/codehub/qemu_pv_device/hw/nvram/trace-events"
            qemu_log("%d@%zu.%06zu:fw_cfg_add_i32 " "key 0x%04" PRIx16 " '%s', value 0x%" PRIx32 "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , key_value, key_name, value);
#line 312 "trace/trace-hw_nvram.h"
        } else {
#line 14 "/home/zuherj/codehub/qemu_pv_device/hw/nvram/trace-events"
            qemu_log("fw_cfg_add_i32 " "key 0x%04" PRIx16 " '%s', value 0x%" PRIx32 "\n", key_value, key_name, value);
#line 316 "trace/trace-hw_nvram.h"
        }
    }
}

static inline void trace_fw_cfg_add_i32(uint16_t key_value, const char * key_name, uint32_t value)
{
    if (true) {
        _nocheck__trace_fw_cfg_add_i32(key_value, key_name, value);
    }
}

#define TRACE_FW_CFG_ADD_I64_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_FW_CFG_ADD_I64) || \
    false)

static inline void _nocheck__trace_fw_cfg_add_i64(uint16_t key_value, const char * key_name, uint64_t value)
{
    if (trace_event_get_state(TRACE_FW_CFG_ADD_I64) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 15 "/home/zuherj/codehub/qemu_pv_device/hw/nvram/trace-events"
            qemu_log("%d@%zu.%06zu:fw_cfg_add_i64 " "key 0x%04" PRIx16 " '%s', value 0x%" PRIx64 "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , key_value, key_name, value);
#line 343 "trace/trace-hw_nvram.h"
        } else {
#line 15 "/home/zuherj/codehub/qemu_pv_device/hw/nvram/trace-events"
            qemu_log("fw_cfg_add_i64 " "key 0x%04" PRIx16 " '%s', value 0x%" PRIx64 "\n", key_value, key_name, value);
#line 347 "trace/trace-hw_nvram.h"
        }
    }
}

static inline void trace_fw_cfg_add_i64(uint16_t key_value, const char * key_name, uint64_t value)
{
    if (true) {
        _nocheck__trace_fw_cfg_add_i64(key_value, key_name, value);
    }
}

#define TRACE_MACIO_NVRAM_READ_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_MACIO_NVRAM_READ) || \
    false)

static inline void _nocheck__trace_macio_nvram_read(uint32_t addr, uint8_t val)
{
    if (trace_event_get_state(TRACE_MACIO_NVRAM_READ) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 18 "/home/zuherj/codehub/qemu_pv_device/hw/nvram/trace-events"
            qemu_log("%d@%zu.%06zu:macio_nvram_read " "read addr=0x%04"PRIx32" val=0x%02x" "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , addr, val);
#line 374 "trace/trace-hw_nvram.h"
        } else {
#line 18 "/home/zuherj/codehub/qemu_pv_device/hw/nvram/trace-events"
            qemu_log("macio_nvram_read " "read addr=0x%04"PRIx32" val=0x%02x" "\n", addr, val);
#line 378 "trace/trace-hw_nvram.h"
        }
    }
}

static inline void trace_macio_nvram_read(uint32_t addr, uint8_t val)
{
    if (true) {
        _nocheck__trace_macio_nvram_read(addr, val);
    }
}

#define TRACE_MACIO_NVRAM_WRITE_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_MACIO_NVRAM_WRITE) || \
    false)

static inline void _nocheck__trace_macio_nvram_write(uint32_t addr, uint8_t val)
{
    if (trace_event_get_state(TRACE_MACIO_NVRAM_WRITE) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 19 "/home/zuherj/codehub/qemu_pv_device/hw/nvram/trace-events"
            qemu_log("%d@%zu.%06zu:macio_nvram_write " "write addr=0x%04"PRIx32" val=0x%02x" "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , addr, val);
#line 405 "trace/trace-hw_nvram.h"
        } else {
#line 19 "/home/zuherj/codehub/qemu_pv_device/hw/nvram/trace-events"
            qemu_log("macio_nvram_write " "write addr=0x%04"PRIx32" val=0x%02x" "\n", addr, val);
#line 409 "trace/trace-hw_nvram.h"
        }
    }
}

static inline void trace_macio_nvram_write(uint32_t addr, uint8_t val)
{
    if (true) {
        _nocheck__trace_macio_nvram_write(addr, val);
    }
}
#endif /* TRACE_HW_NVRAM_GENERATED_TRACERS_H */
