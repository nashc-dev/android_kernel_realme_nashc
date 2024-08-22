/* SPDX-License-Identifier: GPL-2.0-only  */
/*
 * Copyright (C) 2018-2020 Oplus. All rights reserved.
 */

#ifndef _UAPI_OPLUS_SENSOR_TYPES_H
#define _UAPI_OPLUS_SENSOR_TYPES_H

#define SENSOR_TYPE_CAMERA_PROTECT                     73
#define SENSOR_TYPE_FREE_FALL                          74
#define SENSOR_TYPE_PICKUP_DETECT                      75
#define SENSOR_TYPE_FP_DISPLAY                         76
#define SENSOR_TYPE_LUX_AOD                            78
#define SENSOR_TYPE_PEDO_MINUTE                        79
//#ifdef OPLUS_FEATURE_ACTIVITY_RECOGNITION
#define SENSOR_TYPE_OPLUS_ACTIVITY_RECOGNITION          81
//#endif //OPLUS_FEATURE_ACTIVITY_RECOGNITION
#define SENSOR_TYPE_TP_GESTURE                         82
#define SENSOR_TYPE_ELEVATOR_DETECT                    83
/* end sensor type */
#define SENSOR_TYPE_CCT                                84
#define SENSOR_TYPE_MAX_NUM                            SENSOR_TYPE_CCT


#define ID_OPLUS_BASE 			(0)
#define ID_CAMERA_PROTECT       (ID_OPLUS_BASE + SENSOR_TYPE_CAMERA_PROTECT - 1)
#define ID_FREE_FALL            (ID_OPLUS_BASE + SENSOR_TYPE_FREE_FALL - 1)
#define ID_PICKUP_DETECT        (ID_OPLUS_BASE + SENSOR_TYPE_PICKUP_DETECT- 1)
#define ID_FP_DISPLAY           (ID_OPLUS_BASE + SENSOR_TYPE_FP_DISPLAY - 1)
#define ID_LUX_AOD              (ID_OPLUS_BASE + SENSOR_TYPE_LUX_AOD - 1)
#define ID_PEDO_MINUTE          (ID_OPLUS_BASE + SENSOR_TYPE_PEDO_MINUTE - 1)
//#ifdef OPLUS_FEATURE_ACTIVITY_RECOGNITION
#define ID_OPLUS_ACTIVITY_RECOGNITION (ID_OPLUS_BASE + SENSOR_TYPE_OPLUS_ACTIVITY_RECOGNITION - 1)
//#endif //OPLUS_FEATURE_ACTIVITY_RECOGNITION
#define ID_TP_GESTURE           (ID_OPLUS_BASE + SENSOR_TYPE_TP_GESTURE - 1)
#define ID_ELEVATOR_DETECT      (ID_OPLUS_BASE + SENSOR_TYPE_ELEVATOR_DETECT - 1)
#define ID_CCT                  (ID_OPLUS_BASE+SENSOR_TYPE_CCT - 1)
/* end sensor ID */
#define ID_SENSOR_MAX_HANDLE    (ID_CCT)

#endif
