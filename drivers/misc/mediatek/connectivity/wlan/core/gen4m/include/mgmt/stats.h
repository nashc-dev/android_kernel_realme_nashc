/*
 * Copyright (C) 2016 MediaTek Inc.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the
 * GNU General Public License version 2 as published by the Free Software
 * Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 */

/*******************************************************************************
 *						C O M P I L E R	 F L A G S
 *******************************************************************************
 */

/*******************************************************************************
 *            E X T E R N A L	R E F E R E N C E S
 *******************************************************************************
 */

/*******************************************************************************
 *						C O N S T A N T S
 *******************************************************************************
 */
#define AIR_LAT_LVL_NUM 4
#define AIR_LAT_CAT_NUM 5

#define TX_TIME_CAT_NUM 5

/*******************************************************************************
 *            D A T A   T Y P E S
 *******************************************************************************
 */

enum ENUM_STATS_TX_TLV_TAG_ID_T {
	STATS_TX_TAG_QUEUE          = 0,
	STATS_TX_TAG_RETRY          = 1,
	STATS_TX_TAG_TIME          = 2,
	STATS_TX_TAG_LAT           = 3,
	STATS_TX_TAG_MAX_NUM
};

enum ENUM_STATS_RX_TLV_TAG_ID_T {
	STATS_RX_TAG_REORDER_DROP          = 0,
	STATS_RX_TAG_AVG_RSSI          = 1,
	STATS_RX_TAG_MAX_NUM
};

enum ENUM_STATS_CGS_TLV_TAG_ID_T {
	STATS_CGS_TAG_B0_IDLE_SLOT          = 0,
	STATS_CGS_TAG_AIR_LAT          = 1,
	STATS_CGS_TAG_MAX_NUM
};

/* TLV */
struct STATS_TRX_TLV_T {
	uint32_t u4Tag;
	uint32_t u4Len;
	uint8_t  aucBuffer[0];
};

typedef void(*PFN_STATS_HANDLE)(struct net_device *prNetDev,
	struct GLUE_INFO*, void *, uint32_t);
typedef uint32_t(*PFN_STATS_GET_LENGTH)(struct GLUE_INFO *);

/* Tx Queue statistics */
struct STATS_TX_QUEUE_STAT_T {
	uint32_t u4MsduTokenUsed;
	uint32_t u4MsduTokenRsvd;
	uint32_t u4PleHifUsed;
	uint32_t u4PleHifRsvd;
};

/* tx retry statistics */
struct STATS_TX_RETRY_STAT_T {
	uint64_t u8Retry;
	uint64_t u8RtsFail;
	uint64_t u8AckFail;
};

/* tx time statistics */
struct STATS_TX_TIME_STAT_T {
	/* from enqueued to transmission reported. (in ms) */
	uint32_t au4Success[TX_TIME_CAT_NUM];
	uint32_t au4Fail[TX_TIME_CAT_NUM];
};

/* tx latency statistics */
struct STATS_TX_LAT_STAT_T {
	/* from packet arrived driver to enqueued. (in ms) */
	uint32_t au4DriverLat[TX_TIME_CAT_NUM];
	/* the latency in HW MAC to transmission finished. (in ms) */
	uint32_t au4MacLat[TX_TIME_CAT_NUM];
};

/* Avg RSSI from LWTBL */
struct STATS_RX_AVG_RSSI_STAT_T {
	int32_t i4Rssi0;
	int32_t i4Rssi1;
};

struct STATS_CGS_LAT_STAT_T {
	uint32_t au4AirLatLvl[AIR_LAT_LVL_NUM];
	uint32_t au4AirLatMpdu[AIR_LAT_CAT_NUM];
};

struct STATS_TLV_HDLR_T {
	PFN_STATS_GET_LENGTH pfnTlvGetLen;
	PFN_STATS_HANDLE pfnStstsHdl;
};

struct STATS_TLV_MAP_T {
	uint32_t u4Tag;
	struct STATS_TLV_HDLR_T tlvHdl;
};

/*******************************************************************************
 *            M A C R O   D E C L A R A T I O N S
 *******************************************************************************
 */

#if (CFG_SUPPORT_STATISTICS == 1)
#define STATS_RX_PKT_INFO_DISPLAY			StatsRxPktInfoDisplay
#define STATS_TX_PKT_INFO_DISPLAY			StatsTxPktInfoDisplay
#else
#define STATS_RX_PKT_INFO_DISPLAY
#define STATS_TX_PKT_INFO_DISPLAY
#endif /* CFG_SUPPORT_STATISTICS */

/*******************************************************************************
 *            F U N C T I O N   D E C L A R A T I O N S
 *******************************************************************************
 */
/* common tlv length */
uint32_t statsGetTlvU4Len(struct GLUE_INFO *prGlueInfo);
uint32_t statsGetTlvU8Len(struct GLUE_INFO *prGlueInfo);

/* tx tlv length */
uint32_t statsTxGetQueueLen(struct GLUE_INFO *prGlueInfo);
uint32_t statsTxGetRetryLen(struct GLUE_INFO *prGlueInfo);
uint32_t statsTxGetTimeLen(struct GLUE_INFO *prGlueInfo);
uint32_t statsTxGetLatLen(struct GLUE_INFO *prGlueInfo);

uint32_t statsRxGetAvgRssiLen(struct GLUE_INFO *prGlueInfo);

/* congestion tlv length */
uint32_t statsCgsGetAirLatLen(struct GLUE_INFO *prGlueInfo);

void statsTxQueueHdlr(struct net_device *prNetDev,
	struct GLUE_INFO *prGlueInfo,
	void *prTlvBuf, uint32_t u4TlvLen);
void statsTxGetRetryHdlr(struct net_device *prNetDev,
	struct GLUE_INFO *prGlueInfo,
	void *prTlvBuf, uint32_t u4TlvLen);
void statsTxTimeHdlr(struct net_device *prNetDev,
	struct GLUE_INFO *prGlueInfo,
	void *prTlvBuf, uint32_t u4TlvLen);
void statsTxLatHdlr(struct net_device *prNetDev,
	struct GLUE_INFO *prGlueInfo,
	void *prTlvBuf, uint32_t u4TlvLen);

void statsRxReorderDropHdlr(struct net_device *prNetDev,
	struct GLUE_INFO *prGlueInfo,
	void *prTlvBuf, uint32_t u4TlvLen);
void statsRxAvgRssiHdlr(struct net_device *prNetDev,
	struct GLUE_INFO *prGlueInfo,
	void *prTlvBuf, uint32_t u4TlvLen);

void statsCgsB0IdleSlotHdlr(struct net_device *prNetDev,
	struct GLUE_INFO *prGlueInfo,
	void *prTlvBuf, uint32_t u4TlvLen);
void statsCgsAirLatHdlr(struct net_device *prNetDev,
	struct GLUE_INFO *prGlueInfo,
	void *prTlvBuf, uint32_t u4TlvLen);

/*******************************************************************************
 *						P R I V A T E   D A T A
 *******************************************************************************
 */

/*******************************************************************************
 *						P R I V A T E  F U N C T I O N S
 *******************************************************************************
 */

/*******************************************************************************
 *						P U B L I C  F U N C T I O N S
 *******************************************************************************
 */


#define STATS_TX_TIME_ARRIVE(__Skb__)	\
do { \
	uint64_t __SysTime; \
	__SysTime = StatsEnvTimeGet(); /* us */	\
	GLUE_SET_PKT_XTIME(__Skb__, __SysTime);	\
} while (FALSE)

uint64_t StatsEnvTimeGet(void);

void StatsEnvTxTime2Hif(IN struct ADAPTER *prAdapter,
			IN struct MSDU_INFO *prMsduInfo);

void StatsEnvRxTime2Host(IN struct ADAPTER *prAdapter,
			 struct sk_buff *prSkb,
			 struct net_device *prNetDev);

void StatsRxPktInfoDisplay(struct SW_RFB *prSwRfb);

void StatsTxPktInfoDisplay(struct sk_buff *prSkb);

void StatsResetTxRx(void);

void StatsEnvSetPktDelay(IN uint8_t ucTxOrRx,
			 IN uint8_t ucIpProto, IN uint16_t u2UdpPort,
			 uint32_t u4DelayThreshold);

void StatsEnvGetPktDelay(OUT uint8_t *pucTxRxFlag,
			 OUT uint8_t *pucTxIpProto, OUT uint16_t *pu2TxUdpPort,
			 OUT uint32_t *pu4TxDelayThreshold,
			 OUT uint8_t *pucRxIpProto,
			 OUT uint16_t *pu2RxUdpPort,
			 OUT uint32_t *pu4RxDelayThreshold);

uint32_t statsGetTlvStatTotalLen(struct GLUE_INFO *prGlueInfo,
	uint8_t type, uint8_t ucNum, uint32_t *arTagList);
void
statsGetInfoHdlr(struct net_device *prNetDev, struct GLUE_INFO *prGlueInfo,
	void *prTlvBuf, uint8_t type, uint8_t ucNum, uint32_t *arTagList);

/* End of stats.h */
