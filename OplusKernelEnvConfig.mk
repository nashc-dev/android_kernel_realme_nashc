# Copyright (C), 2008-2030, OPPO Mobile Comm Corp., Ltd
###  All rights reserved.
###
### File: - OplusKernelEnvConfig.mk
### Description:
###     you can get the oplus feature variables set in android side in this file
###     this file will add global macro for common oplus added feature
###     BSP team can do customzation by referring the feature variables
### Version: 1.0
### Date: 2020-03-18
### Author: Liang.Sun
###
### ------------------------------- Revision History: ----------------------------
### <author>                        <date>       <version>   <desc>
### ------------------------------------------------------------------------------
### Liang.Sun@TECH.Build              2020-03-18   1.0         Create this moudle
##################################################################################

-include nativefeatures.mk

ALLOWED_MCROS := \
OPLUS_FEATURE_AOD \
OPLUS_FEATURE_FINGERPRINT \
OPLUS_FEATURE_ONSCREENFINGERPRINT \
OPLUS_FEATURE_SENSOR \
OPLUS_FEATURE_SENSOR_ALGORITHM \
OPLUS_FEATURE_SENSOR_SMEM \
OPLUS_FEATURE_SENSOR_WISELIGHT \
OPLUS_FEATURE_SPEAKER_MUTE \
OPLUS_FEATURE_CHG_BASIC \
OPLUS_BUG_COMPATIBILITY \
OPLUS_BUG_STABILITY \
OPLUS_ARCH_INJECT \
OPLUS_ARCH_EXTENDS \
OPLUS_FEATURE_CAMERA_COMMON

$(foreach myfeature,$(ALLOWED_MCROS),\
         $(eval KBUILD_CFLAGS += -D$(myfeature)) \
         $(eval KBUILD_CPPFLAGS += -D$(myfeature)) \
         $(eval CFLAGS_KERNEL += -D$(myfeature)) \
         $(eval CFLAGS_MODULE += -D$(myfeature)) \
)

#Zhijun.Ye@MM.Display.LCD.Machine, 2020/09/23, add for multibits backlight
ifeq ($(OPLUS_FEATURE_MULTIBITS_BL),yes)
KBUILD_CFLAGS += -DOPLUS_FEATURE_MULTIBITS_BL
KBUILD_CPPFLAGS += -DOPLUS_FEATURE_MULTIBITS_BL
CFLAGS_KERNEL += -DOPLUS_FEATURE_MULTIBITS_BL
CFLAGS_MODULE += -DOPLUS_FEATURE_MULTIBITS_BL
endif

ifeq ($(OPLUS_FEATURE_DFPS3_SUPPORT),yes)
KBUILD_CFLAGS += -DOPLUS_FEATURE_DFPS3_SUPPORT
KBUILD_CPPFLAGS += -DOPLUS_FEATURE_DFPS3_SUPPORT
CFLAGS_KERNEL += -DOPLUS_FEATURE_DFPS3_SUPPORT
CFLAGS_MODULE += -DOPLUS_FEATURE_DFPS3_SUPPORT
endif
