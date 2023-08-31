//	Date: 20230831 靳浩然

#define _PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop))

#ifndef __ADMIN_H
#define __ADMIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StructDef.h"


//fuc1 done,场馆名称查场地信息，需要之后把ID改为名称
//接收完，需要判断是否为空数组
extern SiteInfo* querySiteIDByVenueID(SiteInfoNode* head, char siteVenueID[11]);

//fuc2 done 管理员id查场地订单
/**
  * @brief			管理员查询自己管理的场地预定情况
  * @param[out]		
  * @param[in]		Id：管理员id
  * @retval			OrderInfo：场地订单信息数组
  */
extern ApmtInfo* querySiteOrderInfo(AdminInfoNode* AdminNodehead, SiteInfoNode* SiteNodehead, AppointmentInfoNode* ApmtNodehead, char adminID[11]);

/**
  * @brief			按照场地预定量进行排序，输出倒序，复用用户系统中的函数
  * @param[out]		
  * @param[in]		none
  * @retval			SiteInfo：排序后的场地信息指针数组
  */


//extern SiteInfo_t* sortByOrder(void);
//
////排序场地热门预定时间
//extern uint8_t* sortSiteHotTime(uint8_t SiteId);
//
//extern uint32_t SiteTurnover(uint8_t SiteId);
//
//extern SiteInfo_t* sortByTurnover(uint8_t* AdminId);
//
//extern SiteInfo_t* sortByTime(OrderTime_e Time);
//
//extern Status_e addSite(SiteInfo_t NewSite);
//
//extern AdminInfo_t queryAdminById(uint8_t* AdminId);
#endif // !__ADMIN_H
