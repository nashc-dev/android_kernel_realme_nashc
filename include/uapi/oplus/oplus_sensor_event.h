/* SPDX-License-Identifier: GPL-2.0-only  */
/*
 * Copyright (C) 2018-2020 Oplus. All rights reserved.
 */

#ifndef _UAPI_OPLUS_SENSOR_EVENT_H
#define _UAPI_OPLUS_SENSOR_EVENT_H

#include <linux/types.h>

enum flushAction {
    DATA_ACTION,
    FLUSH_ACTION,
    BIAS_ACTION,
    CALI_ACTION,
    TEMP_ACTION,
    TEST_ACTION,
};

struct oplus_sensor_event {
    __s64 time_stamp;
    __s8 handle;
    __s8 flush_action;
    __s8 status;
    __s8 reserved;
    union {
        __s32 word[6];
        __s8 byte[0];
    };
} __attribute__((__packed__));

typedef struct oplus_sensor_event oplus_sensor_event_t;

#endif
