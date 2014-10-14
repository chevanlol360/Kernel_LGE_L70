/*
 * Atmel maXTouch Touchscreen driver
 *
 * Copyright (C) 2010 Samsung Electronics Co.Ltd
 * Copyright (C) 2013 LG Electronics Co.Ltd
 * Author: <WX-BSP-TS@lge.com>
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 */

#ifndef __LINUX_ATMEL_MXT_TS_H__
#define __LINUX_ATMEL_MXT_TS_H__

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/notifier.h>
#include <linux/fb.h>
#include <linux/input/mt.h>
#include <linux/sysdev.h>
#include <linux/firmware.h>

#define LGE_TOUCH_NAME			"lge_touch"
#define MXT_DEVICE_NAME		"touch_dev"

#define MXT_FW_MAGIC			0x4D3C2B1A

#define REF_OFFSET_VALUE		16384
#define REF_MIN_VALUE			(19744 - REF_OFFSET_VALUE)
#define REF_MAX_VALUE		(28884 - REF_OFFSET_VALUE)

#define NODE_PER_PAGE		64
#define DATA_PER_NODE		2

/* Diagnostic command defines  */
#define MXT_DIAG_PAGE_UP		0x01
#define MXT_DIAG_PAGE_DOWN		0x02
#define MXT_DIAG_DELTA_MODE		0x10
#define MXT_DIAG_REFERENCE_MODE		0x11
#define MXT_DIAG_CTE_MODE		0x31
#define MXT_DIAG_IDENTIFICATION_MODE	0x80
#define MXT_DIAG_TOCH_THRESHOLD_MODE	0xF4
#define MXT_DIAG_MODE_MASK		0xFC
#define MXT_DIAGNOSTIC_MODE		0
#define MXT_DIAGNOSTIC_PAGE		1
#define MXT_CONFIG_VERSION_LENGTH	30

/* Configuration file */
#define MXT_CFG_MAGIC		"OBP_RAW V1"

/* Registers */
#define MXT_OBJECT_NUM_MAX	200
#define MXT_OBJECT_START	0x07
#define MXT_OBJECT_SIZE		6
#define MXT_INFO_CHECKSUM_SIZE	3
#define MXT_MAX_BLOCK_WRITE	256

/* Object types */
#define MXT_DEBUG_DIAGNOSTIC_T37	37
#define MXT_GEN_MESSAGE_T5		5
#define MXT_GEN_COMMAND_T6		6
#define MXT_GEN_POWER_T7		7
#define MXT_GEN_ACQUIRE_T8		8
#define MXT_TOUCH_KEYARRAY_T15		15
#define MXT_TOUCH_PROXIMITY_T23		23
#define MXT_TOUCH_MULTITOUCHSCREEN_T100 100
#define MXT_PROCI_GRIPSUPPRESSION_T40		40
#define MXT_PROCI_TOUCHSUPPRESSION_T42	42
#define MXT_PROCI_STYLUS_T47		47
#define MXT_PROCI_ADAPTIVETHRESHOLD_T55			55
#define MXT_PROCI_SHIELDLESS_T56				56
#define MXT_PROCI_EXTRATOUCHSCREENDATA_T57      57
#define MXT_PROCI_LENSBENDING_T65				65
#define MXT_PROCI_PALMGESTUREPROCESSOR_T69		69
#define MXT_PROCG_NOISESUPPRESSION_T72	72
#define MXT_GLOVEDETECTION_T78				78
#define MXT_RETRANSMISSIONCOMPENSATION_T80		80
#define MXT_PROCI_GESTUREPROCESSOR_T84			84
#define MXT_PROCI_SCHNOISESUPPRESSION_T103	103
#define MXT_SPT_COMMSCONFIG_T18		18
#define MXT_SPT_GPIOPWM_T19		19
#define MXT_SPT_SELFTEST_T25		25
#define MXT_SPT_USERDATA_T38		38
#define MXT_SPT_MESSAGECOUNT_T44	44
#define MXT_SPT_CTECONFIG_T46		46
#define MXT_SPT_TIMER_T61			61
#define MXT_SPT_GOLDENREFERENCES_T66	66
#define MXT_SPT_DYNAMICCONFIGURATIONCONTROLLER_T70	70
#define MXT_SPT_DYNAMICCONFIGURATIONCONTAINER_T71	71
#define MXT_SPT_SELFCAPCBCRCONFIG_T102		102
#define MXT_SPT_AUXTOUCHCONFIG_T104			104
#define MXT_SPT_TOUCHSCREENHOVER_T101		101
#define MXT_SPT_DRIVENPLATEHOVERCONFIG_T105	105
#define MXT_PROCI_ONETOUCH_T24		24
#define MXT_SPT_PROTOTYPE_T35		35

/* Not for ATMEL S540 */
#define MXT_GEN_DATASOURCE_T53		53
#define MXT_TOUCH_MULTI_T9		9
#define MXT_TOUCH_PROXKEY_T52		52
#define MXT_PROCI_GRIPFACE_T20		20
#define MXT_PROCG_NOISE_T22		22
#define MXT_PROCI_TWOTOUCH_T27		27
#define MXT_PROCI_PALM_T41		41
#define MXT_PROCG_NOISESUPPRESSION_T48	48
#define MXT_SPT_CTECONFIG_T28		28
#define MXT_SPT_DIGITIZER_T43		43
#define MXT_SPT_NOISESUPPRESSION_T48	48
#define MXT_PROCI_ACTIVE_STYLUS_T63	63
#define MXT_RESERVED_T255 255

/* MXT_GEN_MESSAGE_T5 object */
#define MXT_RPTID_NOMSG		0xff

/* MXT_GEN_COMMAND_T6 field */
#define MXT_COMMAND_RESET	0
#define MXT_COMMAND_BACKUPNV	1
#define MXT_COMMAND_CALIBRATE	2
#define MXT_COMMAND_REPORTALL	3
#define MXT_COMMAND_DIAGNOSTIC	5

/* Define for T6 status byte */
#define MXT_T6_STATUS_RESET	(1 << 7)
#define MXT_T6_STATUS_OFL	(1 << 6)
#define MXT_T6_STATUS_SIGERR	(1 << 5)
#define MXT_T6_STATUS_CAL	(1 << 4)
#define MXT_T6_STATUS_CFGERR	(1 << 3)
#define MXT_T6_STATUS_COMSERR	(1 << 2)

#define MXT_POWER_CFG_RUN		0
#define MXT_POWER_CFG_DEEPSLEEP		1

/* MXT_TOUCH_MULTI_T9 field */
#define MXT_T9_ORIENT		9
#define MXT_T9_RANGE		18

/* MXT_TOUCH_MULTI_T9 status */
#define MXT_T9_UNGRIP		(1 << 0)
#define MXT_T9_SUPPRESS		(1 << 1)
#define MXT_T9_AMP		(1 << 2)
#define MXT_T9_VECTOR		(1 << 3)
#define MXT_T9_MOVE		(1 << 4)
#define MXT_T9_RELEASE		(1 << 5)
#define MXT_T9_PRESS		(1 << 6)
#define MXT_T9_DETECT		(1 << 7)

/* MXT_TOUCH_MULTI_T9 orient */
#define MXT_T9_ORIENT_SWITCH	(1 << 0)

/* MXT_SPT_COMMSCONFIG_T18 */
#define MXT_COMMS_CTRL		0
#define MXT_COMMS_CMD		1
#define MXT_COMMS_RETRIGEN      (1 << 6)

/* Define for MXT_GEN_COMMAND_T6 */
#define MXT_BOOT_VALUE		0xa5
#define MXT_RESET_VALUE		0x01
#define MXT_BACKUP_VALUE	0x55
#define MXT_STOP_DYNAMIC_CONFIG	0x33

/* Define for MXT_PROCI_TOUCHSUPPRESSION_T42 */
#define MXT_T42_MSG_TCHSUP	(1 << 0)

/* Delay times */
#define MXT_BACKUP_TIME		20	/* msec */
#define MXT_RESET_TIME		30	/* msec */
#define MXT_RESET_TIMEOUT	3000	/* msec */
#define MXT_CRC_TIMEOUT		1000	/* msec */
#define MXT_FW_RESET_TIME	1000	/* msec */
#define MXT_FW_CHG_TIMEOUT	300	/* msec */
#define MXT_WAKEUP_TIME		25	/* msec */
#define MXT_REGULATOR_DELAY	150	/* msec */
#define MXT_POWERON_DELAY	150	/* msec */
#define MXT_SELFTEST_TIME	3000	/* msec */

/* Command to unlock bootloader */
#define MXT_UNLOCK_CMD_MSB	0xaa
#define MXT_UNLOCK_CMD_LSB	0xdc

/* Bootloader mode status */
#define MXT_WAITING_BOOTLOAD_CMD	0xc0	/* valid 7 6 bit only */
#define MXT_WAITING_FRAME_DATA	0x80	/* valid 7 6 bit only */
#define MXT_FRAME_CRC_CHECK	0x02
#define MXT_FRAME_CRC_FAIL	0x03
#define MXT_FRAME_CRC_PASS	0x04
#define MXT_APP_CRC_FAIL	0x40	/* valid 7 8 bit only */
#define MXT_BOOT_STATUS_MASK	0x3f
#define MXT_BOOT_EXTENDED_ID	(1 << 5)
#define MXT_BOOT_ID_MASK	0x1f

/* Touchscreen absolute values */
#define MXT_MAX_AREA		25

#define MXT_PIXELS_PER_MM	20

#define MXT_STATE_INACTIVE                 0
#define MXT_STATE_RELEASE                   1
#define MXT_STATE_PRESS                        2
#define MXT_STATE_MOVE                       3

#define MXT_MAX_KEY			4
#define MXT_MAX_FINGER			10
#define MXT_MAX_FW_PATH			30
#define MXT_DISALEEVT_VALUE		0x33

#define TOUCHEVENTFILTER	0

/* patch Event */
#define CHARGER_PLUGGED             0
#define CHARGER_UNplugged            1
#define CHARGER_KNOCKON_SLEEP     2
#define CHARGER_KNOCKON_WAKEUP   3
#define NOCHARGER_KNOCKON_SLEEP   4
#define NOCHARGER_KNOCKON_WAKEUP	5
#define DEEP_SLEEP_WAKEUP			6

#define MXT_INFOMATION_BLOCK_SIZE		7
#define MXT_OBJECT_TABLE_ELEMENT_SIZE	6
#define MXT_OBJECT_TABLE_START_ADDRESS	7

#define PATCH_EVENT_KNOCKON	(0x01 << 1)
#define PATCH_EVENT_TA			(0x01 << 2)
#define POWERLOCK_FW_UP		(0x01 << 1)
#define POWERLOCK_SYSFS		(0x01 << 2)

#define SELF_DIAGNOSTIC_FILE_PATH "/data/touch_self_test.txt"
#define SELF_DIAGNOSTIC_STATUS_COMPLETE	0
#define SELF_DIAGNOSTIC_STATUS_RUNNING	1

/* MXT_GEN_POWER_T7 field */
struct t7_config {
	u8 idle;
	u8 active;
} __packed;

struct t9_range {
	u16 x;
	u16 y;
} __packed;

enum {
	POWER_OFF = 0,
	POWER_ON,
	POWER_SLEEP,
	POWER_WAKE
};

/* The platform data for the Atmel maXTouch touchscreen driver */
struct mxt_platform_data {
	size_t config_array_size;
	u8    numtouch;	/* Number of touches to report	*/
	int   max_x;    /* The default reported X range   */
	int   max_y;    /* The default reported Y range   */
	bool i2c_pull_up;
	unsigned long irqflags;
	int t15_num_keys;
	unsigned int t15_keystate[MXT_MAX_KEY];
	unsigned int t15_extra_keystate[MXT_MAX_KEY];
	unsigned int t15_keymap[MXT_MAX_KEY];
	unsigned long gpio_reset;
	unsigned long gpio_int;
	unsigned int panel_check;
	unsigned char panel_on;
	const char *fw_name;
	const char *extra_fw_name;
	unsigned char auto_fw_update;
	char knock_on_type;
	int global_access_pixel;
	u8 use_mfts;
	u8 fw_ver[2];
	u8 product[10];
};

struct mxt_finger {
	u16 x;
	u16 y;
	u16 w;
	u16 z;
	u16 component;
	u8 state;
	u8 type;
	u8 event;
	u16 mcount;
};

struct mxt_info {
	u8 family_id;
	u8 variant_id;
	u8 version;
	u8 build;
	u8 matrix_xsize;
	u8 matrix_ysize;
	u8 object_num;
};

struct mxt_object {
	u8 type;
	u16 start_address;
	u8 size_minus_one;
	u8 instances_minus_one;
	u8 num_report_ids;
} __packed;

struct mxt_raw_data {
	u8 num_xnode;
	u8 num_ynode;
	u16 num_nodes;
	u16 *reference;
	s16 *delta;
};

/**
 * struct mxt_fw_image - Represents a firmware file.
 * @ magic_code: Identifier of file type.
 * @ hdr_len: Size of file header (struct mxt_fw_image).
 * @ cfg_len: Size of configuration data.
 * @ fw_len: Size of firmware data.
 * @ cfg_crc: CRC of configuration settings.
 * @ bin_ver: Version of binary firmware.
 * @ build_ver: Build version of firmware.
 * @ data: Configuration data followed by firmware image.
 */
struct mxt_fw_image {
	__le32 magic_code;
	__le32 hdr_len;
	__le32 cfg_len;
	__le32 fw_len;
	__le32 cfg_crc;
	u8 bin_ver;
	u8 build_ver;
	u8 extra_info[32];
	u8 data[0];
} __packed;

/**
 * struct mxt_cfg_data - Represents a configuration data item.
 * @ type: Type of object.
 * @ instance: Instance number of object.
 * @ size: Size of object.
 * @ register_val: Series of register values for object.
 */
struct mxt_cfg_data {
	u8 type;
	u8 instance;
	u8 size;
	u8 register_val[0];
} __packed;

struct mxt_fw_info {
	u8 bin_ver;
	u8 build_ver;
	u32 hdr_len;
	u32 cfg_len;
	u32 fw_len;
	u32 cfg_crc;
	const u8 *cfg_raw_data;	/* start address of configuration data */
	const u8 *fw_raw_data;	/* start address of firmware data */
	struct mxt_data *data;
};

struct mxt_patch{
	u8* patch;
	u16* stage_addr;
	u16* tline_addr;
	u16* trigger_addr;
	u16* event_addr;
	u16* src_item;
	u16* check_cnt;
	u16 period;
	u8 stage_cnt;
	u8 tline_cnt;
	u8 trigger_cnt;
	u8 event_cnt;
	u8 option;
	u8 debug;
	u8 timer_id;
	u8 cur_stage;
	u8 cur_stage_opt;
	u8 run_stage;
	u8 start;
	u8 finger_cnt;
	u8 start_stage;
	u8 skip_test;
	u8 cal_flag;
	u32 stage_timestamp;
};

struct mxt_message {
	u8 reportid;
	u8 message[8];
};

struct mxt_reportid {
	u8 type;
	u8 index;
};

/* Each client has this additional data */
struct mxt_data {
	struct i2c_client *client;
	struct input_dev *input_dev;
	char phys[64];		/* device physical location */
	struct mxt_platform_data *pdata;
	struct mxt_object *object_table;
	struct mxt_reportid *reportids;
	struct mxt_info *info;
	void *raw_info_block;
	unsigned int irq;
	unsigned int max_x;
	unsigned int max_y;
	bool in_bootloader;
	u16 mem_size;

	struct bin_attribute mem_access_attr;
	bool debug_enabled;
	bool t57_debug_enabled;
	u8 max_reportid;
	u32 config_crc;
	u32 info_crc;
	u8 bootloader_addr;
	struct t7_config t7_cfg;
	u8 *msg_buf;
	u8 t6_status;
	bool update_input;
	u8 last_message_count;
	u8 num_touchids;
	unsigned long t15_keystatus;
	bool use_retrigen_workaround;
	bool use_regulator;
	u8 regulator_status;
	struct regulator *vdd_ana;
	struct regulator *vcc_i2c;
	struct regulator *vcc_dig;
#if defined(CONFIG_FB)
	struct notifier_block fb_notif;
#endif
	struct kobject 				lge_touch_kobj;
	/* Cached parameters from object table */
	u16 T5_address;
	u8 T5_msg_size;
	u8 T6_reportid;
	u16 T6_address;
	u16 T7_address;
	u16 T8_address;
	u16 T9_address;
	u8 T9_reportid_min;
	u8 T9_reportid_max;
	u8 T15_reportid_min;
	u8 T15_reportid_max;
	u16 T18_address;

	u8 T24_reportid;
	u8 T35_reportid;
	u8 T25_reportid;
	u16 T25_address;
	u16 T42_address;
	u8 T42_reportid_min;
	u8 T42_reportid_max;

	u16 T46_address;
	u8 T48_reportid;
	u16 T56_address;
	u16 T65_address;
	u16 T71_address;
	u16 T72_address;

	/* for fw update in bootloader */
	struct completion bl_completion;

	/* for reset handling */
	struct completion reset_completion;

	/* for reset handling */
	struct completion crc_completion;

	/* Auto touch test */
	struct completion t25_completion;

	/* Enable reporting of input events */
	bool enable_reporting;

	/* Indicates whether device is in suspend */
	bool suspended;
	struct mxt_raw_data *rawdata;
	bool mxt_knock_on_enable;
	bool mxt_character_enable;
	bool self_test_result;
	u8 self_test_status[4];
	u8 self_test_result_status;
	u16 reported_keycode;
	struct mxt_patch patch;
	struct mxt_finger fingers[MXT_MAX_FINGER];
	bool	button_lock;
	struct delayed_work	work_button_lock;
	u8 mfts_enable;
	u8 charging_mode; /*Charger mode in patch*/
};

#define TOUCH_INFO_MSG(fmt, args...) 	printk(KERN_ERR "[Touch] " fmt, ##args)
#define TOUCH_PATCH_INFO_MSG(fmt, args...) 	printk(KERN_ERR "[Touch Patch] " fmt, ##args)

int fb_notifier_callback(struct notifier_block *self, unsigned long event, void *data);
int mxt_initialize_t9_input_device(struct mxt_data *data);
void mxt_request_firmware_work(const struct firmware *fw,void *context);
int mxt_write_mem(struct mxt_data *data, u16 reg, u8 len, const u8 *buf);
int mxt_read_mem(struct mxt_data *data, u16 reg, u8 len, void *buf);
int mxt_write_object(struct mxt_data *data, u8 type, u8 offset, u8 val);
struct mxt_object *mxt_get_object(struct mxt_data *data, u8 type);
int mxt_read_object(struct mxt_data *data, u8 type, u8 offset, u8 *val);
int mxt_update_firmware(struct mxt_data *data, const char *fwname);

#endif /* __LINUX_ATMEL_MXT_TS_H__ */
