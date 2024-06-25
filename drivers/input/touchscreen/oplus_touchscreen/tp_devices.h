/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2018-2020 Oplus. All rights reserved.
 */

#ifndef OPLUS_TP_DEVICES_H
#define OPLUS_TP_DEVICES_H
//device list define
typedef enum tp_dev{
    TP_SAMSUNG,
    TP_UNKNOWN,
}tp_dev;

struct tp_dev_name {
    tp_dev type;
    char name[32];
};

#endif
