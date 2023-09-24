# Copyright (C), 2008-2030, OPLUS Mobile Comm Corp., Ltd
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
##################################################################################

ALLOWED_MCROS := \
OPLUS_ARCH_EXTENDS \
OPLUS_ARCH_INJECT \
OPLUS_BUG_COMPATIBILITY \
OPLUS_BUG_STABILITY \
OPLUS_FEATURE_AOD \
OPLUS_FEATURE_CAMERA_COMMON \
OPLUS_FEATURE_CHG_BASIC \
OPLUS_FEATURE_DISPLAY \
OPLUS_FEATURE_MIPICLKCHANGE \
OPLUS_FEATURE_MULTIBITS_BL \
OPLUS_FEATURE_NFC_CONSOFT \
OPLUS_FEATURE_ONSCREENFINGERPRINT \
OPLUS_FEATURE_SDCARD_INFO \
OPLUS_FEATURE_SECURITY_COMMON \
OPLUS_FEATURE_SENSOR \
OPLUS_FEATURE_SENSOR_ALGORITHM \
OPLUS_FEATURE_SENSOR_SMEM \
OPLUS_FEATURE_SENSOR_WISELIGHT \
OPLUS_FEATURE_SPEAKER_MUTE \
OPLUS_FEATURE_TP_BASIC \
OPLUS_FEATURE_TP_BSPFWUPDATE

$(foreach myfeature,$(ALLOWED_MCROS),\
         $(eval KBUILD_CFLAGS += -D$(myfeature)) \
         $(eval KBUILD_CPPFLAGS += -D$(myfeature)) \
         $(eval CFLAGS_KERNEL += -D$(myfeature)) \
         $(eval CFLAGS_MODULE += -D$(myfeature)) \
)
