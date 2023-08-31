//	Date: 20230831 ����Ȼ

#define _PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop))

#ifndef __ADMIN_H
#define __ADMIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StructDef.h"


//fuc1 done,�������Ʋ鳡����Ϣ����Ҫ֮���ID��Ϊ����
//�����꣬��Ҫ�ж��Ƿ�Ϊ������
extern SiteInfo* querySiteIDByVenueID(SiteInfoNode* head, char siteVenueID[11]);

//fuc2 done ����Աid�鳡�ض���
/**
  * @brief			����Ա��ѯ�Լ�����ĳ���Ԥ�����
  * @param[out]		
  * @param[in]		Id������Աid
  * @retval			OrderInfo�����ض�����Ϣ����
  */
extern ApmtInfo* querySiteOrderInfo(AdminInfoNode* AdminNodehead, SiteInfoNode* SiteNodehead, AppointmentInfoNode* ApmtNodehead, char adminID[11]);

/**
  * @brief			���ճ���Ԥ������������������򣬸����û�ϵͳ�еĺ���
  * @param[out]		
  * @param[in]		none
  * @retval			SiteInfo�������ĳ�����Ϣָ������
  */


//extern SiteInfo_t* sortByOrder(void);
//
////���򳡵�����Ԥ��ʱ��
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
