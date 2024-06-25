/***************************************************
 * File:touch.c
 * Copyright (c)  2008- 2030  oplus Mobile communication Corp.ltd.
 * Description:
 *             tp dev
 * Version:1.0:
 * Date created:2016/09/02
 * TAG: BSP.TP.Init
*/

#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/input.h>
#include <linux/serio.h>
#include "oplus_touchscreen/tp_devices.h"
#include "oplus_touchscreen/touchpanel_common.h"
#include <soc/oplus/system/oplus_project.h>
#include <soc/oplus/device_info.h>

#define MAX_LIMIT_DATA_LENGTH         100
#define GT9886_FW_NAME_19551 "tp/19551/FW_GT9886_SAMSUNG.img"
#define GT9886_BASELINE_TEST_LIMIT_NAME_19551 "tp/19551/LIMIT_GT9886_SAMSUNG.img"
#define GT9886_FW_NAME_19357 "tp/19357/FW_GT9886_SAMSUNG.img"
#define GT9886_BASELINE_TEST_LIMIT_NAME_19357 "tp/19357/LIMIT_GT9886_SAMSUNG.img"
#define GT9886_FW_NAME_19537 "tp/19537/FW_GT9886_SAMSUNG.img"
#define GT9886_BASELINE_TEST_LIMIT_NAME_19537 "tp/19537/LIMIT_GT9886_SAMSUNG.img"

extern char *saved_command_line;
int g_tp_dev_vendor = TP_UNKNOWN;
int g_tp_prj_id = 0;
struct hw_resource *g_hw_res;
int tp_type = 0;
int ret = 0;
static bool is_tp_type_got_in_match = false;    /*indicate whether the tp type is specified in the dts*/


/*if can not compile success, please update vendor/oppo_touchsreen*/
struct tp_dev_name tp_dev_names[] =
{
	{TP_SAMSUNG, "SAMSUNG"},
};

typedef enum {
	TP_INDEX_NULL,
	goodix_gt9886,
	focal_ft3518,
} TP_USED_INDEX;
TP_USED_INDEX tp_used_index  = TP_INDEX_NULL;

#define GET_TP_DEV_NAME(tp_type) ((tp_dev_names[tp_type].type == (tp_type))?tp_dev_names[tp_type].name:"UNMATCH")

#ifndef CONFIG_MTK_FB
void primary_display_esd_check_enable(int enable)
{
	return;
}
EXPORT_SYMBOL(primary_display_esd_check_enable);
#endif /*CONFIG_MTK_FB*/

bool __init tp_judge_ic_match(char *tp_ic_name)
{
	int prj_id = 0;
	pr_err("[TP] tp_ic_name = %s \n", tp_ic_name);
	prj_id = get_project();

	switch(prj_id)
	{
	case 20730:
	case 20731:
	case 20732:
		pr_info("%s forward for 20730\n", __func__);
		if (strstr(tp_ic_name, "focaltech,fts") && strstr(saved_command_line, "oppo20730_samsung_ams643xy04_lcm_drv_1")) {
			return true;
		}

		if (strstr(tp_ic_name, "Goodix-gt9886") && strstr(saved_command_line, "oppo20730_samsung_ams643xy04_lcm_drv_2")) {
		return true;
		}

		if (strstr(tp_ic_name, "Goodix-gt9886") && strstr(saved_command_line, "oppo20730_samsung_ams643xy04_lcm_drv_3")) {
		return true;
		}
		pr_err("[TP] ERROR! ic is not match driver\n");
		return false;
	default:
		break;
	}
	return true;
}
EXPORT_SYMBOL(tp_judge_ic_match);

bool  tp_judge_ic_match_commandline(struct panel_info *panel_data)
{
	int prj_id = 0;
	int i = 0;
	bool ic_matched = false;
	prj_id = get_project();

	pr_err("[TP] get_project() = %d \n", prj_id);
	pr_err("[TP] boot_command_line = %s \n", saved_command_line);
	for(i = 0; i < panel_data->project_num; i++)
	{
		if(prj_id == panel_data->platform_support_project[i])
		{
			g_tp_prj_id = panel_data->platform_support_project_dir[i];
			pr_err("[TP] platform_support_commandline = %s \n", panel_data->platform_support_commandline[i]);
			if(strstr(saved_command_line, panel_data->platform_support_commandline[i]) || strstr("default_commandline", panel_data->platform_support_commandline[i]) )
			{
				pr_err("[TP] Driver match the project\n");
				ic_matched = true;
			}
		}
	}

	if (!ic_matched) {
		pr_err("[TP] Driver does not match the project\n");
		pr_err("Lcd module not found\n");
		return false;
	}

	switch (prj_id) {
	case 20730:
	case 20731:
	case 20732:
		pr_info("%s forward for 20730\n", __func__);
		is_tp_type_got_in_match = true;
		if (strstr(saved_command_line, "oppo20730_samsung_ams643xy04_lcm_drv_1")) {
			pr_err("[TP] touch ic = FT_3518 \n");
			tp_used_index = focal_ft3518;
			g_tp_dev_vendor = TP_SAMSUNG;
		}

		if (strstr(saved_command_line, "oppo20730_samsung_ams643xy04_lcm_drv_2")) {
			pr_err("[TP] touch ic = Goodix-gt9886 \n");
			tp_used_index =  goodix_gt9886;
			g_tp_dev_vendor = TP_SAMSUNG;
		}

		if (strstr(saved_command_line, "oppo20730_samsung_ams643xy04_lcm_drv_3")) {
			pr_err("[TP] touch ic = Goodix-gt9886 \n");
			tp_used_index =  goodix_gt9886;
			g_tp_dev_vendor = TP_SAMSUNG;
		}
		break;
	default:
		pr_info("other project, no need process here!\n");
		break;
	}
	pr_info("[TP]ic:%d, vendor:%d\n", tp_used_index, g_tp_dev_vendor);
	return true;
}
EXPORT_SYMBOL(tp_judge_ic_match_commandline);

int tp_util_get_vendor(struct hw_resource *hw_res, struct panel_info *panel_data)
{
	char *vendor;
	int prj_id = 0;
	prj_id = get_project();
	g_hw_res = hw_res;

	panel_data->test_limit_name = kzalloc(MAX_LIMIT_DATA_LENGTH, GFP_KERNEL);
	if (panel_data->test_limit_name == NULL)
	{
		pr_err("[TP]panel_data.test_limit_name kzalloc error\n");
	}
	panel_data->extra = kzalloc(MAX_LIMIT_DATA_LENGTH, GFP_KERNEL);
	if (panel_data->extra == NULL)
	{
		pr_err("[TP]panel_data.test_limit_name kzalloc error\n");
	}
	if (is_tp_type_got_in_match) {
		panel_data->tp_type = g_tp_dev_vendor;
	}
	if (panel_data->tp_type == TP_UNKNOWN)
	{
		pr_err("[TP]%s type is unknown\n", __func__);
		return 0;
	}

	vendor = GET_TP_DEV_NAME(panel_data->tp_type);
/*BSP.TP.Function, add tp path for Moss.*/
	if (20730 == prj_id || 20731 == prj_id || 20732 == prj_id) {
		if (focal_ft3518 == tp_used_index) {
		memcpy(panel_data->manufacture_info.version, "focalt_", 7);
		}
		if (goodix_gt9886 == tp_used_index) {
		memcpy(panel_data->manufacture_info.version, "goodix_", 7);
		}
	}

	strcpy(panel_data->manufacture_info.manufacture, vendor);
	pr_err("[TP]tp_util_get_vendor line =%d\n", __LINE__);
	pr_err("[TP] enter case %d\n", prj_id);

	snprintf(panel_data->fw_name, MAX_FW_NAME_LENGTH,
	         "tp/%d/FW_%s_%s.img",
	         g_tp_prj_id, panel_data->chip_name, vendor);

	if (panel_data->test_limit_name)
	{
		snprintf(panel_data->test_limit_name, MAX_LIMIT_DATA_LENGTH,
		         "tp/%d/LIMIT_%s_%s.img",
		         g_tp_prj_id, panel_data->chip_name, vendor);
	}
	if (panel_data->extra) {
		snprintf(panel_data->extra, MAX_LIMIT_DATA_LENGTH,
				"tp/%d/BOOT_FW_%s_%s.ihex",
				prj_id, panel_data->chip_name, vendor);
	}

	switch (prj_id) {
	case 20730:
	case 20731:
	case 20732:
		pr_info("%s forward for 20730\n", __func__);
		if (tp_used_index == focal_ft3518) {
			snprintf(panel_data->fw_name, MAX_FW_NAME_LENGTH,
				 "tp/20730/FW_%s_%s.img",
				 "FT3518", vendor);

			if (panel_data->test_limit_name) {
				snprintf(panel_data->test_limit_name, MAX_LIMIT_DATA_LENGTH,
					 "tp/20730/LIMIT_%s_%s.img",
					 "FT3518", vendor);
			}

			if (panel_data->extra) {
				snprintf(panel_data->extra, MAX_LIMIT_DATA_LENGTH,
					 "tp/20730/BOOT_FW_%s_%s.ihex",
					 "FT3518", vendor);
			}
		}

		if (tp_used_index == goodix_gt9886) {
			snprintf(panel_data->fw_name, MAX_FW_NAME_LENGTH,
				 "tp/20730/FW_%s_%s.img",
				"GT9886", vendor);

			if (panel_data->test_limit_name) {
				snprintf(panel_data->test_limit_name, MAX_LIMIT_DATA_LENGTH,
					 "tp/20730/LIMIT_%s_%s.img",
					 "GT9886", vendor);
			}

			if (panel_data->extra) {
				snprintf(panel_data->extra, MAX_LIMIT_DATA_LENGTH,
					 "tp/20730/BOOT_FW_%s_%s.ihex",
					 "GT9886", vendor);
			}
		}
		panel_data->manufacture_info.fw_path = panel_data->fw_name;
		break;
	default:
		break;
	}
	panel_data->manufacture_info.fw_path = panel_data->fw_name;
	pr_info("[TP]vendor:%s fw:%s limit:%s\n",
	        vendor,
	        panel_data->fw_name,
	        panel_data->test_limit_name == NULL ? "NO Limit" : panel_data->test_limit_name);

	return 0;
}
EXPORT_SYMBOL(tp_util_get_vendor);

/**
 * Description:
 * pulldown spi7 cs to avoid current leakage
 * because of current sourcing from cs (pullup state) flowing into display module
 **/
void switch_spi7cs_state(bool normal)
{
	if (!g_hw_res) {
		return;
	}

	if(normal) {
		if (!IS_ERR_OR_NULL(g_hw_res->pin_set_high)) {
			pr_info("%s: going to set spi7 cs to spi mode .\n", __func__);
			pinctrl_select_state(g_hw_res->pinctrl, g_hw_res->pin_set_high);
		} else {
			pr_info("%s: cannot to set spi7 cs to spi mode .\n", __func__);
		}
	} else {
		if (!IS_ERR_OR_NULL(g_hw_res->pin_set_low)) {
			pr_info("%s: going to set spi7 cs to pulldown .\n", __func__);
			pinctrl_select_state(g_hw_res->pinctrl, g_hw_res->pin_set_low);
		} else {
			pr_info("%s: cannot to set spi7 cs to pulldown .\n", __func__);
		}
	}
}
EXPORT_SYMBOL(switch_spi7cs_state);
