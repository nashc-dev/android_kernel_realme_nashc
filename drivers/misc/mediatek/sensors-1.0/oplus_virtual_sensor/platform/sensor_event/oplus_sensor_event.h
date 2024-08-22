/* SPDX-License-Identifier: GPL-2.0-only  */
/*
 * Copyright (C) 2018-2020 Oplus. All rights reserved.
 */

#ifndef _OPLUS_SENSOR_EVENT_H
#define _OPLUS_SENSOR_EVENT_H
#include <linux/poll.h>
#include <linux/ratelimit.h>
#include <uapi/oplus/oplus_sensor_event.h>

#define CONTINUE_SENSOR_BUF_SIZE    2048
#define BIO_SENSOR_BUF_SIZE    0x20000 /* ((512 + 1024 + 1024) * 60) */
#define OTHER_SENSOR_BUF_SIZE    1024
#define MINOR_NUM_FOR_VIRTUAL_SENSOR 0
#define MINOR_NUM_MAX 0

ssize_t oplus_sensor_event_read(unsigned char handle, struct file *file,
    char __user *buffer,
              size_t count, loff_t *ppos);
unsigned int oplus_sensor_event_poll(unsigned char handle, struct file *file,
    poll_table *wait);
int oplus_sensor_input_event(unsigned char handle,
             const struct oplus_sensor_event *event);
unsigned int oplus_sensor_event_register(unsigned char handle);
unsigned int oplus_sensor_event_deregister(unsigned char handle);
#endif
