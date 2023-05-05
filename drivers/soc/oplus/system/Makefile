# SPDX-License-Identifier: GPL-2.0-only
# Copyright (C) 2018-2020 Oplus. All rights reserved.

obj-y 	+= platform.o
obj-$(CONFIG_OPLUS_FEATURE_OPROJECT) 	+= oplus_project/
obj-$(CONFIG_OPLUS_FEATURE_PMIC_MONITOR_MTK)     += oplus_pmic_monitor_mtk/
obj-$(CONFIG_OPLUS_FEATURE_CMDLINE)     += cmdline_parser/

ifdef CONFIG_OPLUS_SYSTEM_KERNEL_QCOM
obj-$(CONFIG_OPLUS_FEATURE_PROJECTINFO)	+=  project_info/
endif

#ifdef OPLUS_FEATURE_MISC
#terry.zhong@OPTI.Kernel.Stability, 2020/09/7, enable oplus misc feature
obj-y += misc/
#endif /* OPLUS_FEATURE_MISC */

#ifdef OPLUS_FEATURE_LOG_CORE
obj-$(CONFIG_OPLUS_FEATURE_LOG_CORE) += olc/
#endif /* OPLUS_FEATURE_LOG_CORE */
