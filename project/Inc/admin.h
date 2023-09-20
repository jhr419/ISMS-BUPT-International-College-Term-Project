/*
__ /\\\\\\\\\\\_        _____ /\\\\\\\\\\\___        __/\\\\____________/\\\\_        _____/\\\\\\\\\\\___
  _\/////\\\///__         ___/\\\/////////\\\_        _\/\\\\\\________/\\\\\\_        ___/\\\/////////\\\_
   _____\/\\\_____         __\//\\\______\///__        _\/\\\//\\\____/\\\//\\\_        __\//\\\______\///__
	_____\/\\\_____         ___\////\\\_________        _\/\\\\///\\\/\\\/_\/\\\_        ___\////\\\_________
	 _____\/\\\_____         ______\////\\\______        _\/\\\__\///\\\/___\/\\\_        ______\////\\\______
	  _____\/\\\_____         _________\////\\\___        _\/\\\____\///_____\/\\\_        _________\////\\\___
	   _____\/\\\_____         __/\\\______\//\\\__        _\/\\\_____________\/\\\_        __/\\\______\//\\\__
		__/\\\\\\\\\\\_         _\///\\\\\\\\\\\/___        _\/\\\_____________\/\\\_        _\///\\\\\\\\\\\/___
		 _\///////////__         ___\///////////_____        _\///______________\///__        ___\///////////_____
*/

/**
  ******************************************************************************
  * @File					: admin.h
  * @Brief					: admin operations header file
  * @Description		    : ����Ա��������ͷ�ļ�
  * @Author					: ����Ȼ
  * @Created Date			: 2023/8/28
  * @Last modified date		: 2023/8/31
  * @Github repositorie URL	: https://github.com/jhr419/ISMS-BUPT-International-College-Term-Project.git
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023
  * All rights reserved.</center></h2>
  *
  ******************************************************************************
  */


#ifndef __ADMIN_H
#define __ADMIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StructDef.h"

/**
* @Brief			���� <��������> ��ѯ�������� <������Ϣ>
* @Description	���� <��������> ���������� <������Ϣ> ���� <������Ϣ> �� <��������> ����뺯���� ���� <��������>
*					һ�µ� <���ؽṹ��> �������飬�����������г��أ����� <������Ϣ�ṹ��> ����
*	Attention!		<ע�⣡>���������飬��Ҫ�Ƚ����пղ�������Ϊ�գ���û�з���Ҫ��ĳ���
* @param[in]		head			��������Ϣ����ͷ���
* @param[in]		siteVenueName	����������
* @param[out]		buf				�����泡����Ϣ�ṹ������
* @retval			���ض�Ӧ���������г�����Ϣ������ṹ������󷵻������ַ
*/
extern SiteInfo* querySiteInfoByVenueName(SiteInfoNode* head, char siteVenueName[11]);

/**
  * @Brief			���� <����ID>��ѯ��Ӧ���� <������Ϣ>
  * @Description	����һ�����ߺ�������Ҫ��������� querySiteOrderInfo ����
  *	Attention!		������һ�����ߺ���������û�ж� <����ID> �Ƿ���ڽ����жϣ�
  *					������Ҫ�жϣ��ɵ��� DataToolKit.c�к��� isSiteExist
  * @param[in]		head		��������Ϣ����ͷ���
  * @param[in]		strSiteID	������ID
  * @param[out]		buf			�����涩���ṹ������ָ��
  * @retval			���ض�Ӧ���ص�ȫ��������Ϣ�ṹ�壬�����һ������
  */
extern ApmtInfo* queryApmtBySite(AppointmentInfoNode* head, char strSiteID[11]);

/**
  * @Brief			ͨ�� <����ԱID> ��ѯ���������г��ص����ж�����Ϣ
  * @Description	��ͨ�� isAdminExist �����ж��Ƿ���ڸù���Ա���������ڣ����ؿն����ṹ�����飬
					�����ڣ���ͨ�� queryAdminInfo ��������DataToolKit.c�ж��壩ȡ�øù���Ա�ṹ��,
					�ٵ��ýṹ���г������Ʊ��汸�ã���ͨ�� querySiteInfoByVenueName���ڴ��ļ����壩 ������ѯ�������
					�����µ�ȫ�����أ�����Ϊ������Ϣ�ṹ�����飬��ͨ�� queryApmtBySite���ڴ��ļ����壩 ������ѯ�������ص�
					������Ϣ�������������������ͨ������������ <�����ṹ������>
  *	Attention!		ʹ�øú�������Ҫ�п�
  * @param[in]		AdminNodehead	������Ա��Ϣ����ͷ���
  * @param[in]		SiteNodehead	��������Ϣ����ͷ���
  * @param[in]		ApmtNodehead	��������Ϣ����ͷ���
  * @param[in]		adminID			������ԱID
  * @param[out]		Apmtbuf			�����涩���ṹ������ָ��
  * @retval			���ظù���Ա�������ݵ�ȫ�����������붩���ṹ������󷵻�
  */
extern ApmtInfo* querySiteOrderInfo(AdminInfoNode* AdminNodehead, SiteInfoNode* SiteNodehead, AppointmentInfoNode* ApmtNodehead, char adminID[11]);

//fuc3 coding ��Ԥ�������򳡵� �����û�ϵͳ�еĺ���

/**
  * @Brief			ͳ�Ƹ�ʱ�ε�ԤԼ��
  * @Description	����һ������Ϊ16�����飬�ֱ��Ӧ��6��00��22��00
  *					֮��16��ʱ�Σ�ͳ���ض����ظ�ʱ��ԤԼ���
  * @param[in]		head		����������ͷ���
  * @param[in]		strSiteID	������ID
  * @param[out]		buf
  * @retval			��6��00��22��00˳�򣬷���ͳ�ƽ��
  */
extern int* cntSiteTime(AppointmentInfoNode* head, char strSiteID[11]);

/**
  * @Brief			�����ض�����Ӫҵ��
  * @Description	ͨ�����볡��ID,��ѯ�ó��ص� ��ʷԤԼ����������𣬵õ�Ӫҵ��
  * @param[in]		head		��������Ϣ����ͷ���
  * @param[in]		strSiteID	������ID
  * @param[out]		Turnover	���ó��ص�Ӫҵ�������
  * @retval			�����ض����ص�Ӫҵ��
  */
extern int cntSiteTurnover(SiteInfoNode* head, char strSiteID[11]);

//fuc6 �û������ηֲ�����Ů�����˶�

/**
  * @Brief			��Ӫҵ�����򳡹������г���
  * @Description	��������Ա���ܵ����г��أ�
  *					�������ԱID�������ж��Ƿ���ڹ���Ա��
  *					�����ڣ���ȡ����ID��ѯ����ID�����棬ͬʱ��¼��������
  *					��ȡӪҵ����Ϣ���ڶԳ������򣬷��س�����Ϣ�ṹ������
  * @Attention		ʹ����Ҫ�пգ�������ԱID���󷵻ؿ�����
  * @param[in]		AdminNodehead	������Ա����ͷ���
  * @param[in]		SiteNodehead	: ��������ͷ���
  * @param[in]		ApmtNodehead	����������ͷ���
  *	@param[in]		adminID			������ԱID
  * @param[out]		Sitebuf			�����泡����Ϣ�ṹ������ָ��
  * @retval			���ذ���Ӫҵ�������ĳ�����Ϣ����
  */
extern SiteInfo* sortSiteByTurnover(AdminInfoNode* AdminNodehead, SiteInfoNode* SiteNodehead, AppointmentInfoNode* ApmtNodehead, char adminID[11]);

//fuc8����ʱ�䣬����һСʱ����ԤԼ�ĳ�������

#endif // !__ADMIN_H
