//	Date: 20230831 靳浩然

//#ifndef __STRYCTDEF_H
//#define __STRYCTDEF_H
//
//#include <stdint.h>
//
//typedef enum
//{
//	SUCCEED,
//	FAILED
//}Status_e;
//
//typedef enum
//{
//	MALE,
//	FEMALE
//}Gender_e;
//
//typedef enum
//{
//	BasketBall,
//	Tennis
//}SportType_e;
//
//typedef enum
//{
//	OnLease,
//	NotLeased
//}LeaseStatus_e;
//
//#define TimeBlockNum 4
//typedef enum
//{
//	Time_7_9,
//	Time_9_11,
//	Time_13_15,
//	Time_15_17
//
//}OrderTime_e;
//
//struct TimeInfo;
//struct AdminInfo;
//struct OrderInfo;
//struct VenueInfo;
//struct SiteInfo;
//
//typedef struct VenueInfo VenueInfo_t;
//typedef struct TimeInfo  TimeInfo_t;
//typedef struct AdminInfo AdminInfo_t;
//typedef struct OrderInfo OrderInfo_t;
//typedef struct SiteInfo  SiteInfo_t;
//
//typedef struct VenueInfo_t VenueNode;
//typedef struct TimeInfo_t  TimeNode;
//typedef struct AdminInfo_t AdminNode;
//typedef struct OrderInfo_t OrderNode;
//typedef struct SiteInfo_t  SiteNode;
//
//_PACK
//(
//	typedef struct TimeInfo
//{
//	uint16_t Year;
//	uint8_t	 Month;
//	uint8_t	 Day;
//	uint8_t	 Hour;
//	uint8_t	 Min;
//}TimeInfo_t;
//)
//
//_PACK
//(
//	struct AdminInfo
//{
//	uint8_t Id[11];
//	uint8_t PassWord[6];
//	uint8_t Name[5];
//	uint8_t Gender;
//	uint8_t TeleNum[12];
//	uint8_t MailBox[30];
//	VenueInfo_t* Venue;
//	struct AdminInfo* next;
//};
//)
//
//_PACK
//(
//	typedef struct OrderInfo
//{
//	uint8_t Id;
//	TimeInfo_t Time;
//	uint16_t strTimeInfo[20];
//	struct OrderInfo* next;
//}OrderInfo_t;
//)
//
//_PACK
//(
//	struct VenueInfo
//{
//	uint8_t Name[10];
//	AdminInfo_t* AdInfo;
//	uint8_t SiteAmount;
//	SiteInfo_t* SiteInfo;
//	struct VenueInfo* next;
//};
//)
//
//_PACK
//(
//	typedef struct SiteInfo
//{
//	uint8_t Id;
//	uint8_t Area;
//	VenueInfo_t Venue;
//	uint8_t SportType;
//	uint8_t Profile;
//	uint8_t AdmAge[2];
//	uint8_t Rent;
//	uint8_t LeaseStatus;
//	uint8_t OrderAmount;//场地订单数量
//	OrderInfo_t* OrderInfo;//场馆订单数组
//	struct SiteInfo* next;
//}SiteInfo_t;
//)
//
//typedef struct _AdminInfoNode
//{
//	AdminInfo_t adminInfo;
//	struct _AdminInfoNode* next;
//} AdminInfoNode;
//
//typedef struct _OrderInfoNode
//{
//	OrderInfo_t orderInfo;
//	struct _OrderInfoNode* next;
//} OrderInfoNode;
//
//typedef struct _VenueInfoNode
//{
//	VenueInfo_t venueInfo;
//	struct _VenueInfoNode* next;
//} VenueInfoNode;
//
//typedef struct _SiteInfoNode
//{
//	SiteInfo_t siteInfo;
//	struct _SiteInfoNode* next;
//} SiteInfoNode;
//#endif // !__STRYCTDEF_H
