/* This file is autogenerated by tracetool, do not edit. */

#ifndef TRACE_HW_RDMA_GENERATED_TRACERS_H
#define TRACE_HW_RDMA_GENERATED_TRACERS_H

#include "trace/control.h"

extern TraceEvent _TRACE_RDMA_CHECK_DEV_ATTR_EVENT;
extern TraceEvent _TRACE_RDMA_CREATE_AH_CACHE_HIT_EVENT;
extern TraceEvent _TRACE_RDMA_CREATE_AH_CACHE_MISS_EVENT;
extern TraceEvent _TRACE_RDMA_POLL_CQ_EVENT;
extern TraceEvent _TRACE_RDMACM_MUX_EVENT;
extern TraceEvent _TRACE_RDMACM_MUX_CHECK_OP_STATUS_EVENT;
extern TraceEvent _TRACE_RDMA_MAD_MESSAGE_EVENT;
extern TraceEvent _TRACE_RDMA_BACKEND_RC_QP_STATE_INIT_EVENT;
extern TraceEvent _TRACE_RDMA_BACKEND_UD_QP_STATE_INIT_EVENT;
extern TraceEvent _TRACE_RDMA_BACKEND_RC_QP_STATE_RTR_EVENT;
extern TraceEvent _TRACE_RDMA_BACKEND_UD_QP_STATE_RTR_EVENT;
extern TraceEvent _TRACE_RDMA_BACKEND_RC_QP_STATE_RTS_EVENT;
extern TraceEvent _TRACE_RDMA_BACKEND_UD_QP_STATE_RTS_EVENT;
extern TraceEvent _TRACE_RDMA_BACKEND_GET_GID_INDEX_EVENT;
extern TraceEvent _TRACE_RDMA_BACKEND_GID_CHANGE_EVENT;
extern TraceEvent _TRACE_RDMA_RES_TBL_GET_EVENT;
extern TraceEvent _TRACE_RDMA_RES_TBL_ALLOC_EVENT;
extern TraceEvent _TRACE_RDMA_RES_TBL_DEALLOC_EVENT;
extern TraceEvent _TRACE_RDMA_RM_ALLOC_MR_EVENT;
extern TraceEvent _TRACE_RDMA_RM_DEALLOC_MR_EVENT;
extern TraceEvent _TRACE_RDMA_RM_ALLOC_QP_EVENT;
extern TraceEvent _TRACE_RDMA_RM_MODIFY_QP_EVENT;
extern TraceEvent _TRACE_RDMA_PCI_DMA_MAP_EVENT;
extern TraceEvent _TRACE_RDMA_PCI_DMA_UNMAP_EVENT;
extern uint16_t _TRACE_RDMA_CHECK_DEV_ATTR_DSTATE;
extern uint16_t _TRACE_RDMA_CREATE_AH_CACHE_HIT_DSTATE;
extern uint16_t _TRACE_RDMA_CREATE_AH_CACHE_MISS_DSTATE;
extern uint16_t _TRACE_RDMA_POLL_CQ_DSTATE;
extern uint16_t _TRACE_RDMACM_MUX_DSTATE;
extern uint16_t _TRACE_RDMACM_MUX_CHECK_OP_STATUS_DSTATE;
extern uint16_t _TRACE_RDMA_MAD_MESSAGE_DSTATE;
extern uint16_t _TRACE_RDMA_BACKEND_RC_QP_STATE_INIT_DSTATE;
extern uint16_t _TRACE_RDMA_BACKEND_UD_QP_STATE_INIT_DSTATE;
extern uint16_t _TRACE_RDMA_BACKEND_RC_QP_STATE_RTR_DSTATE;
extern uint16_t _TRACE_RDMA_BACKEND_UD_QP_STATE_RTR_DSTATE;
extern uint16_t _TRACE_RDMA_BACKEND_RC_QP_STATE_RTS_DSTATE;
extern uint16_t _TRACE_RDMA_BACKEND_UD_QP_STATE_RTS_DSTATE;
extern uint16_t _TRACE_RDMA_BACKEND_GET_GID_INDEX_DSTATE;
extern uint16_t _TRACE_RDMA_BACKEND_GID_CHANGE_DSTATE;
extern uint16_t _TRACE_RDMA_RES_TBL_GET_DSTATE;
extern uint16_t _TRACE_RDMA_RES_TBL_ALLOC_DSTATE;
extern uint16_t _TRACE_RDMA_RES_TBL_DEALLOC_DSTATE;
extern uint16_t _TRACE_RDMA_RM_ALLOC_MR_DSTATE;
extern uint16_t _TRACE_RDMA_RM_DEALLOC_MR_DSTATE;
extern uint16_t _TRACE_RDMA_RM_ALLOC_QP_DSTATE;
extern uint16_t _TRACE_RDMA_RM_MODIFY_QP_DSTATE;
extern uint16_t _TRACE_RDMA_PCI_DMA_MAP_DSTATE;
extern uint16_t _TRACE_RDMA_PCI_DMA_UNMAP_DSTATE;
#define TRACE_RDMA_CHECK_DEV_ATTR_ENABLED 1
#define TRACE_RDMA_CREATE_AH_CACHE_HIT_ENABLED 1
#define TRACE_RDMA_CREATE_AH_CACHE_MISS_ENABLED 1
#define TRACE_RDMA_POLL_CQ_ENABLED 1
#define TRACE_RDMACM_MUX_ENABLED 1
#define TRACE_RDMACM_MUX_CHECK_OP_STATUS_ENABLED 1
#define TRACE_RDMA_MAD_MESSAGE_ENABLED 1
#define TRACE_RDMA_BACKEND_RC_QP_STATE_INIT_ENABLED 1
#define TRACE_RDMA_BACKEND_UD_QP_STATE_INIT_ENABLED 1
#define TRACE_RDMA_BACKEND_RC_QP_STATE_RTR_ENABLED 1
#define TRACE_RDMA_BACKEND_UD_QP_STATE_RTR_ENABLED 1
#define TRACE_RDMA_BACKEND_RC_QP_STATE_RTS_ENABLED 1
#define TRACE_RDMA_BACKEND_UD_QP_STATE_RTS_ENABLED 1
#define TRACE_RDMA_BACKEND_GET_GID_INDEX_ENABLED 1
#define TRACE_RDMA_BACKEND_GID_CHANGE_ENABLED 1
#define TRACE_RDMA_RES_TBL_GET_ENABLED 1
#define TRACE_RDMA_RES_TBL_ALLOC_ENABLED 1
#define TRACE_RDMA_RES_TBL_DEALLOC_ENABLED 1
#define TRACE_RDMA_RM_ALLOC_MR_ENABLED 1
#define TRACE_RDMA_RM_DEALLOC_MR_ENABLED 1
#define TRACE_RDMA_RM_ALLOC_QP_ENABLED 1
#define TRACE_RDMA_RM_MODIFY_QP_ENABLED 1
#define TRACE_RDMA_PCI_DMA_MAP_ENABLED 1
#define TRACE_RDMA_PCI_DMA_UNMAP_ENABLED 1
#include "qemu/log-for-trace.h"
#include "qemu/error-report.h"


#define TRACE_RDMA_CHECK_DEV_ATTR_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_RDMA_CHECK_DEV_ATTR) || \
    false)

static inline void _nocheck__trace_rdma_check_dev_attr(const char * name, int max_bk, int max_fe)
{
    if (trace_event_get_state(TRACE_RDMA_CHECK_DEV_ATTR) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 4 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("%d@%zu.%06zu:rdma_check_dev_attr " "%s: be=%d, fe=%d" "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , name, max_bk, max_fe);
#line 100 "trace/trace-hw_rdma.h"
        } else {
#line 4 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("rdma_check_dev_attr " "%s: be=%d, fe=%d" "\n", name, max_bk, max_fe);
#line 104 "trace/trace-hw_rdma.h"
        }
    }
}

static inline void trace_rdma_check_dev_attr(const char * name, int max_bk, int max_fe)
{
    if (true) {
        _nocheck__trace_rdma_check_dev_attr(name, max_bk, max_fe);
    }
}

#define TRACE_RDMA_CREATE_AH_CACHE_HIT_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_RDMA_CREATE_AH_CACHE_HIT) || \
    false)

static inline void _nocheck__trace_rdma_create_ah_cache_hit(uint64_t subnet, uint64_t if_id)
{
    if (trace_event_get_state(TRACE_RDMA_CREATE_AH_CACHE_HIT) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 5 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("%d@%zu.%06zu:rdma_create_ah_cache_hit " "subnet=0x%"PRIx64",if_id=0x%"PRIx64 "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , subnet, if_id);
#line 131 "trace/trace-hw_rdma.h"
        } else {
#line 5 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("rdma_create_ah_cache_hit " "subnet=0x%"PRIx64",if_id=0x%"PRIx64 "\n", subnet, if_id);
#line 135 "trace/trace-hw_rdma.h"
        }
    }
}

static inline void trace_rdma_create_ah_cache_hit(uint64_t subnet, uint64_t if_id)
{
    if (true) {
        _nocheck__trace_rdma_create_ah_cache_hit(subnet, if_id);
    }
}

#define TRACE_RDMA_CREATE_AH_CACHE_MISS_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_RDMA_CREATE_AH_CACHE_MISS) || \
    false)

static inline void _nocheck__trace_rdma_create_ah_cache_miss(uint64_t subnet, uint64_t if_id)
{
    if (trace_event_get_state(TRACE_RDMA_CREATE_AH_CACHE_MISS) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 6 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("%d@%zu.%06zu:rdma_create_ah_cache_miss " "subnet=0x%"PRIx64",if_id=0x%"PRIx64 "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , subnet, if_id);
#line 162 "trace/trace-hw_rdma.h"
        } else {
#line 6 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("rdma_create_ah_cache_miss " "subnet=0x%"PRIx64",if_id=0x%"PRIx64 "\n", subnet, if_id);
#line 166 "trace/trace-hw_rdma.h"
        }
    }
}

static inline void trace_rdma_create_ah_cache_miss(uint64_t subnet, uint64_t if_id)
{
    if (true) {
        _nocheck__trace_rdma_create_ah_cache_miss(subnet, if_id);
    }
}

#define TRACE_RDMA_POLL_CQ_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_RDMA_POLL_CQ) || \
    false)

static inline void _nocheck__trace_rdma_poll_cq(int ne, void * ibcq)
{
    if (trace_event_get_state(TRACE_RDMA_POLL_CQ) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 7 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("%d@%zu.%06zu:rdma_poll_cq " "Got %d completion(s) from cq %p" "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , ne, ibcq);
#line 193 "trace/trace-hw_rdma.h"
        } else {
#line 7 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("rdma_poll_cq " "Got %d completion(s) from cq %p" "\n", ne, ibcq);
#line 197 "trace/trace-hw_rdma.h"
        }
    }
}

static inline void trace_rdma_poll_cq(int ne, void * ibcq)
{
    if (true) {
        _nocheck__trace_rdma_poll_cq(ne, ibcq);
    }
}

#define TRACE_RDMACM_MUX_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_RDMACM_MUX) || \
    false)

static inline void _nocheck__trace_rdmacm_mux(const char * title, int msg_type, int op_code)
{
    if (trace_event_get_state(TRACE_RDMACM_MUX) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 8 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("%d@%zu.%06zu:rdmacm_mux " "%s: msg_type=%d, op_code=%d" "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , title, msg_type, op_code);
#line 224 "trace/trace-hw_rdma.h"
        } else {
#line 8 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("rdmacm_mux " "%s: msg_type=%d, op_code=%d" "\n", title, msg_type, op_code);
#line 228 "trace/trace-hw_rdma.h"
        }
    }
}

static inline void trace_rdmacm_mux(const char * title, int msg_type, int op_code)
{
    if (true) {
        _nocheck__trace_rdmacm_mux(title, msg_type, op_code);
    }
}

#define TRACE_RDMACM_MUX_CHECK_OP_STATUS_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_RDMACM_MUX_CHECK_OP_STATUS) || \
    false)

static inline void _nocheck__trace_rdmacm_mux_check_op_status(int msg_type, int op_code, int err_code)
{
    if (trace_event_get_state(TRACE_RDMACM_MUX_CHECK_OP_STATUS) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 9 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("%d@%zu.%06zu:rdmacm_mux_check_op_status " "resp: msg_type=%d, op_code=%d, err_code=%d" "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , msg_type, op_code, err_code);
#line 255 "trace/trace-hw_rdma.h"
        } else {
#line 9 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("rdmacm_mux_check_op_status " "resp: msg_type=%d, op_code=%d, err_code=%d" "\n", msg_type, op_code, err_code);
#line 259 "trace/trace-hw_rdma.h"
        }
    }
}

static inline void trace_rdmacm_mux_check_op_status(int msg_type, int op_code, int err_code)
{
    if (true) {
        _nocheck__trace_rdmacm_mux_check_op_status(msg_type, op_code, err_code);
    }
}

#define TRACE_RDMA_MAD_MESSAGE_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_RDMA_MAD_MESSAGE) || \
    false)

static inline void _nocheck__trace_rdma_mad_message(const char * title, int len, char * data)
{
    if (trace_event_get_state(TRACE_RDMA_MAD_MESSAGE) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 10 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("%d@%zu.%06zu:rdma_mad_message " "mad %s (%d): %s" "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , title, len, data);
#line 286 "trace/trace-hw_rdma.h"
        } else {
#line 10 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("rdma_mad_message " "mad %s (%d): %s" "\n", title, len, data);
#line 290 "trace/trace-hw_rdma.h"
        }
    }
}

static inline void trace_rdma_mad_message(const char * title, int len, char * data)
{
    if (true) {
        _nocheck__trace_rdma_mad_message(title, len, data);
    }
}

#define TRACE_RDMA_BACKEND_RC_QP_STATE_INIT_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_RDMA_BACKEND_RC_QP_STATE_INIT) || \
    false)

static inline void _nocheck__trace_rdma_backend_rc_qp_state_init(uint32_t qpn)
{
    if (trace_event_get_state(TRACE_RDMA_BACKEND_RC_QP_STATE_INIT) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 11 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("%d@%zu.%06zu:rdma_backend_rc_qp_state_init " "RC QP 0x%x switch to INIT" "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , qpn);
#line 317 "trace/trace-hw_rdma.h"
        } else {
#line 11 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("rdma_backend_rc_qp_state_init " "RC QP 0x%x switch to INIT" "\n", qpn);
#line 321 "trace/trace-hw_rdma.h"
        }
    }
}

static inline void trace_rdma_backend_rc_qp_state_init(uint32_t qpn)
{
    if (true) {
        _nocheck__trace_rdma_backend_rc_qp_state_init(qpn);
    }
}

#define TRACE_RDMA_BACKEND_UD_QP_STATE_INIT_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_RDMA_BACKEND_UD_QP_STATE_INIT) || \
    false)

static inline void _nocheck__trace_rdma_backend_ud_qp_state_init(uint32_t qpn, uint32_t qkey)
{
    if (trace_event_get_state(TRACE_RDMA_BACKEND_UD_QP_STATE_INIT) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 12 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("%d@%zu.%06zu:rdma_backend_ud_qp_state_init " "UD QP 0x%x switch to INIT, qkey=0x%x" "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , qpn, qkey);
#line 348 "trace/trace-hw_rdma.h"
        } else {
#line 12 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("rdma_backend_ud_qp_state_init " "UD QP 0x%x switch to INIT, qkey=0x%x" "\n", qpn, qkey);
#line 352 "trace/trace-hw_rdma.h"
        }
    }
}

static inline void trace_rdma_backend_ud_qp_state_init(uint32_t qpn, uint32_t qkey)
{
    if (true) {
        _nocheck__trace_rdma_backend_ud_qp_state_init(qpn, qkey);
    }
}

#define TRACE_RDMA_BACKEND_RC_QP_STATE_RTR_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_RDMA_BACKEND_RC_QP_STATE_RTR) || \
    false)

static inline void _nocheck__trace_rdma_backend_rc_qp_state_rtr(uint32_t qpn, uint64_t subnet, uint64_t ifid, uint8_t sgid_idx, uint32_t dqpn, uint32_t rq_psn)
{
    if (trace_event_get_state(TRACE_RDMA_BACKEND_RC_QP_STATE_RTR) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 13 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("%d@%zu.%06zu:rdma_backend_rc_qp_state_rtr " "RC QP 0x%x switch to RTR, subnet = 0x%"PRIx64", ifid = 0x%"PRIx64 ", sgid_idx=%d, dqpn=0x%x, rq_psn=0x%x" "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , qpn, subnet, ifid, sgid_idx, dqpn, rq_psn);
#line 379 "trace/trace-hw_rdma.h"
        } else {
#line 13 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("rdma_backend_rc_qp_state_rtr " "RC QP 0x%x switch to RTR, subnet = 0x%"PRIx64", ifid = 0x%"PRIx64 ", sgid_idx=%d, dqpn=0x%x, rq_psn=0x%x" "\n", qpn, subnet, ifid, sgid_idx, dqpn, rq_psn);
#line 383 "trace/trace-hw_rdma.h"
        }
    }
}

static inline void trace_rdma_backend_rc_qp_state_rtr(uint32_t qpn, uint64_t subnet, uint64_t ifid, uint8_t sgid_idx, uint32_t dqpn, uint32_t rq_psn)
{
    if (true) {
        _nocheck__trace_rdma_backend_rc_qp_state_rtr(qpn, subnet, ifid, sgid_idx, dqpn, rq_psn);
    }
}

#define TRACE_RDMA_BACKEND_UD_QP_STATE_RTR_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_RDMA_BACKEND_UD_QP_STATE_RTR) || \
    false)

static inline void _nocheck__trace_rdma_backend_ud_qp_state_rtr(uint32_t qpn, uint32_t qkey)
{
    if (trace_event_get_state(TRACE_RDMA_BACKEND_UD_QP_STATE_RTR) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 14 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("%d@%zu.%06zu:rdma_backend_ud_qp_state_rtr " "UD QP 0x%x switch to RTR, qkey=0x%x" "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , qpn, qkey);
#line 410 "trace/trace-hw_rdma.h"
        } else {
#line 14 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("rdma_backend_ud_qp_state_rtr " "UD QP 0x%x switch to RTR, qkey=0x%x" "\n", qpn, qkey);
#line 414 "trace/trace-hw_rdma.h"
        }
    }
}

static inline void trace_rdma_backend_ud_qp_state_rtr(uint32_t qpn, uint32_t qkey)
{
    if (true) {
        _nocheck__trace_rdma_backend_ud_qp_state_rtr(qpn, qkey);
    }
}

#define TRACE_RDMA_BACKEND_RC_QP_STATE_RTS_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_RDMA_BACKEND_RC_QP_STATE_RTS) || \
    false)

static inline void _nocheck__trace_rdma_backend_rc_qp_state_rts(uint32_t qpn, uint32_t sq_psn)
{
    if (trace_event_get_state(TRACE_RDMA_BACKEND_RC_QP_STATE_RTS) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 15 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("%d@%zu.%06zu:rdma_backend_rc_qp_state_rts " "RC QP 0x%x switch to RTS, sq_psn=0x%x, " "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , qpn, sq_psn);
#line 441 "trace/trace-hw_rdma.h"
        } else {
#line 15 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("rdma_backend_rc_qp_state_rts " "RC QP 0x%x switch to RTS, sq_psn=0x%x, " "\n", qpn, sq_psn);
#line 445 "trace/trace-hw_rdma.h"
        }
    }
}

static inline void trace_rdma_backend_rc_qp_state_rts(uint32_t qpn, uint32_t sq_psn)
{
    if (true) {
        _nocheck__trace_rdma_backend_rc_qp_state_rts(qpn, sq_psn);
    }
}

#define TRACE_RDMA_BACKEND_UD_QP_STATE_RTS_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_RDMA_BACKEND_UD_QP_STATE_RTS) || \
    false)

static inline void _nocheck__trace_rdma_backend_ud_qp_state_rts(uint32_t qpn, uint32_t sq_psn, uint32_t qkey)
{
    if (trace_event_get_state(TRACE_RDMA_BACKEND_UD_QP_STATE_RTS) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 16 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("%d@%zu.%06zu:rdma_backend_ud_qp_state_rts " "UD QP 0x%x switch to RTS, sq_psn=0x%x, qkey=0x%x" "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , qpn, sq_psn, qkey);
#line 472 "trace/trace-hw_rdma.h"
        } else {
#line 16 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("rdma_backend_ud_qp_state_rts " "UD QP 0x%x switch to RTS, sq_psn=0x%x, qkey=0x%x" "\n", qpn, sq_psn, qkey);
#line 476 "trace/trace-hw_rdma.h"
        }
    }
}

static inline void trace_rdma_backend_ud_qp_state_rts(uint32_t qpn, uint32_t sq_psn, uint32_t qkey)
{
    if (true) {
        _nocheck__trace_rdma_backend_ud_qp_state_rts(qpn, sq_psn, qkey);
    }
}

#define TRACE_RDMA_BACKEND_GET_GID_INDEX_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_RDMA_BACKEND_GET_GID_INDEX) || \
    false)

static inline void _nocheck__trace_rdma_backend_get_gid_index(uint64_t subnet, uint64_t ifid, int gid_idx)
{
    if (trace_event_get_state(TRACE_RDMA_BACKEND_GET_GID_INDEX) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 17 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("%d@%zu.%06zu:rdma_backend_get_gid_index " "subnet=0x%"PRIx64", ifid=0x%"PRIx64 ", gid_idx=%d" "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , subnet, ifid, gid_idx);
#line 503 "trace/trace-hw_rdma.h"
        } else {
#line 17 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("rdma_backend_get_gid_index " "subnet=0x%"PRIx64", ifid=0x%"PRIx64 ", gid_idx=%d" "\n", subnet, ifid, gid_idx);
#line 507 "trace/trace-hw_rdma.h"
        }
    }
}

static inline void trace_rdma_backend_get_gid_index(uint64_t subnet, uint64_t ifid, int gid_idx)
{
    if (true) {
        _nocheck__trace_rdma_backend_get_gid_index(subnet, ifid, gid_idx);
    }
}

#define TRACE_RDMA_BACKEND_GID_CHANGE_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_RDMA_BACKEND_GID_CHANGE) || \
    false)

static inline void _nocheck__trace_rdma_backend_gid_change(const char * op, uint64_t subnet, uint64_t ifid)
{
    if (trace_event_get_state(TRACE_RDMA_BACKEND_GID_CHANGE) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 18 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("%d@%zu.%06zu:rdma_backend_gid_change " "%s subnet=0x%"PRIx64", ifid=0x%"PRIx64 "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , op, subnet, ifid);
#line 534 "trace/trace-hw_rdma.h"
        } else {
#line 18 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("rdma_backend_gid_change " "%s subnet=0x%"PRIx64", ifid=0x%"PRIx64 "\n", op, subnet, ifid);
#line 538 "trace/trace-hw_rdma.h"
        }
    }
}

static inline void trace_rdma_backend_gid_change(const char * op, uint64_t subnet, uint64_t ifid)
{
    if (true) {
        _nocheck__trace_rdma_backend_gid_change(op, subnet, ifid);
    }
}

#define TRACE_RDMA_RES_TBL_GET_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_RDMA_RES_TBL_GET) || \
    false)

static inline void _nocheck__trace_rdma_res_tbl_get(char * name, uint32_t handle)
{
    if (trace_event_get_state(TRACE_RDMA_RES_TBL_GET) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 21 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("%d@%zu.%06zu:rdma_res_tbl_get " "tbl %s, handle %d" "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , name, handle);
#line 565 "trace/trace-hw_rdma.h"
        } else {
#line 21 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("rdma_res_tbl_get " "tbl %s, handle %d" "\n", name, handle);
#line 569 "trace/trace-hw_rdma.h"
        }
    }
}

static inline void trace_rdma_res_tbl_get(char * name, uint32_t handle)
{
    if (true) {
        _nocheck__trace_rdma_res_tbl_get(name, handle);
    }
}

#define TRACE_RDMA_RES_TBL_ALLOC_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_RDMA_RES_TBL_ALLOC) || \
    false)

static inline void _nocheck__trace_rdma_res_tbl_alloc(char * name, uint32_t handle)
{
    if (trace_event_get_state(TRACE_RDMA_RES_TBL_ALLOC) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 22 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("%d@%zu.%06zu:rdma_res_tbl_alloc " "tbl %s, handle %d" "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , name, handle);
#line 596 "trace/trace-hw_rdma.h"
        } else {
#line 22 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("rdma_res_tbl_alloc " "tbl %s, handle %d" "\n", name, handle);
#line 600 "trace/trace-hw_rdma.h"
        }
    }
}

static inline void trace_rdma_res_tbl_alloc(char * name, uint32_t handle)
{
    if (true) {
        _nocheck__trace_rdma_res_tbl_alloc(name, handle);
    }
}

#define TRACE_RDMA_RES_TBL_DEALLOC_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_RDMA_RES_TBL_DEALLOC) || \
    false)

static inline void _nocheck__trace_rdma_res_tbl_dealloc(char * name, uint32_t handle)
{
    if (trace_event_get_state(TRACE_RDMA_RES_TBL_DEALLOC) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 23 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("%d@%zu.%06zu:rdma_res_tbl_dealloc " "tbl %s, handle %d" "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , name, handle);
#line 627 "trace/trace-hw_rdma.h"
        } else {
#line 23 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("rdma_res_tbl_dealloc " "tbl %s, handle %d" "\n", name, handle);
#line 631 "trace/trace-hw_rdma.h"
        }
    }
}

static inline void trace_rdma_res_tbl_dealloc(char * name, uint32_t handle)
{
    if (true) {
        _nocheck__trace_rdma_res_tbl_dealloc(name, handle);
    }
}

#define TRACE_RDMA_RM_ALLOC_MR_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_RDMA_RM_ALLOC_MR) || \
    false)

static inline void _nocheck__trace_rdma_rm_alloc_mr(uint32_t mr_handle, void * host_virt, uint64_t guest_start, uint64_t guest_length, int access_flags)
{
    if (trace_event_get_state(TRACE_RDMA_RM_ALLOC_MR) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 24 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("%d@%zu.%06zu:rdma_rm_alloc_mr " "mr_handle=%d, host_virt=%p, guest_start=0x%"PRIx64", length=%" PRId64", access_flags=0x%x" "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , mr_handle, host_virt, guest_start, guest_length, access_flags);
#line 658 "trace/trace-hw_rdma.h"
        } else {
#line 24 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("rdma_rm_alloc_mr " "mr_handle=%d, host_virt=%p, guest_start=0x%"PRIx64", length=%" PRId64", access_flags=0x%x" "\n", mr_handle, host_virt, guest_start, guest_length, access_flags);
#line 662 "trace/trace-hw_rdma.h"
        }
    }
}

static inline void trace_rdma_rm_alloc_mr(uint32_t mr_handle, void * host_virt, uint64_t guest_start, uint64_t guest_length, int access_flags)
{
    if (true) {
        _nocheck__trace_rdma_rm_alloc_mr(mr_handle, host_virt, guest_start, guest_length, access_flags);
    }
}

#define TRACE_RDMA_RM_DEALLOC_MR_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_RDMA_RM_DEALLOC_MR) || \
    false)

static inline void _nocheck__trace_rdma_rm_dealloc_mr(uint32_t mr_handle, uint64_t guest_start)
{
    if (trace_event_get_state(TRACE_RDMA_RM_DEALLOC_MR) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 25 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("%d@%zu.%06zu:rdma_rm_dealloc_mr " "mr_handle=%d, guest_start=0x%"PRIx64 "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , mr_handle, guest_start);
#line 689 "trace/trace-hw_rdma.h"
        } else {
#line 25 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("rdma_rm_dealloc_mr " "mr_handle=%d, guest_start=0x%"PRIx64 "\n", mr_handle, guest_start);
#line 693 "trace/trace-hw_rdma.h"
        }
    }
}

static inline void trace_rdma_rm_dealloc_mr(uint32_t mr_handle, uint64_t guest_start)
{
    if (true) {
        _nocheck__trace_rdma_rm_dealloc_mr(mr_handle, guest_start);
    }
}

#define TRACE_RDMA_RM_ALLOC_QP_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_RDMA_RM_ALLOC_QP) || \
    false)

static inline void _nocheck__trace_rdma_rm_alloc_qp(uint32_t rm_qpn, uint32_t backend_qpn, uint8_t qp_type)
{
    if (trace_event_get_state(TRACE_RDMA_RM_ALLOC_QP) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 26 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("%d@%zu.%06zu:rdma_rm_alloc_qp " "rm_qpn=%d, backend_qpn=0x%x, qp_type=%d" "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , rm_qpn, backend_qpn, qp_type);
#line 720 "trace/trace-hw_rdma.h"
        } else {
#line 26 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("rdma_rm_alloc_qp " "rm_qpn=%d, backend_qpn=0x%x, qp_type=%d" "\n", rm_qpn, backend_qpn, qp_type);
#line 724 "trace/trace-hw_rdma.h"
        }
    }
}

static inline void trace_rdma_rm_alloc_qp(uint32_t rm_qpn, uint32_t backend_qpn, uint8_t qp_type)
{
    if (true) {
        _nocheck__trace_rdma_rm_alloc_qp(rm_qpn, backend_qpn, qp_type);
    }
}

#define TRACE_RDMA_RM_MODIFY_QP_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_RDMA_RM_MODIFY_QP) || \
    false)

static inline void _nocheck__trace_rdma_rm_modify_qp(uint32_t qpn, uint32_t attr_mask, int qp_state, uint8_t sgid_idx)
{
    if (trace_event_get_state(TRACE_RDMA_RM_MODIFY_QP) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 27 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("%d@%zu.%06zu:rdma_rm_modify_qp " "qpn=0x%x, attr_mask=0x%x, qp_state=%d, sgid_idx=%d" "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , qpn, attr_mask, qp_state, sgid_idx);
#line 751 "trace/trace-hw_rdma.h"
        } else {
#line 27 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("rdma_rm_modify_qp " "qpn=0x%x, attr_mask=0x%x, qp_state=%d, sgid_idx=%d" "\n", qpn, attr_mask, qp_state, sgid_idx);
#line 755 "trace/trace-hw_rdma.h"
        }
    }
}

static inline void trace_rdma_rm_modify_qp(uint32_t qpn, uint32_t attr_mask, int qp_state, uint8_t sgid_idx)
{
    if (true) {
        _nocheck__trace_rdma_rm_modify_qp(qpn, attr_mask, qp_state, sgid_idx);
    }
}

#define TRACE_RDMA_PCI_DMA_MAP_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_RDMA_PCI_DMA_MAP) || \
    false)

static inline void _nocheck__trace_rdma_pci_dma_map(uint64_t addr, void * vaddr, uint64_t len)
{
    if (trace_event_get_state(TRACE_RDMA_PCI_DMA_MAP) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 30 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("%d@%zu.%06zu:rdma_pci_dma_map " "0x%"PRIx64" -> %p (len=%" PRId64")" "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , addr, vaddr, len);
#line 782 "trace/trace-hw_rdma.h"
        } else {
#line 30 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("rdma_pci_dma_map " "0x%"PRIx64" -> %p (len=%" PRId64")" "\n", addr, vaddr, len);
#line 786 "trace/trace-hw_rdma.h"
        }
    }
}

static inline void trace_rdma_pci_dma_map(uint64_t addr, void * vaddr, uint64_t len)
{
    if (true) {
        _nocheck__trace_rdma_pci_dma_map(addr, vaddr, len);
    }
}

#define TRACE_RDMA_PCI_DMA_UNMAP_BACKEND_DSTATE() ( \
    trace_event_get_state_dynamic_by_id(TRACE_RDMA_PCI_DMA_UNMAP) || \
    false)

static inline void _nocheck__trace_rdma_pci_dma_unmap(void * vaddr)
{
    if (trace_event_get_state(TRACE_RDMA_PCI_DMA_UNMAP) && qemu_loglevel_mask(LOG_TRACE)) {
        if (message_with_timestamp) {
            struct timeval _now;
            gettimeofday(&_now, NULL);
#line 31 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("%d@%zu.%06zu:rdma_pci_dma_unmap " "%p" "\n",
                     qemu_get_thread_id(),
                     (size_t)_now.tv_sec, (size_t)_now.tv_usec
                     , vaddr);
#line 813 "trace/trace-hw_rdma.h"
        } else {
#line 31 "/home/zuherj/codehub/qemu_pv_device/hw/rdma/trace-events"
            qemu_log("rdma_pci_dma_unmap " "%p" "\n", vaddr);
#line 817 "trace/trace-hw_rdma.h"
        }
    }
}

static inline void trace_rdma_pci_dma_unmap(void * vaddr)
{
    if (true) {
        _nocheck__trace_rdma_pci_dma_unmap(vaddr);
    }
}
#endif /* TRACE_HW_RDMA_GENERATED_TRACERS_H */
