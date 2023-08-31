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


//fuc1 done,�������Ʋ鳡����Ϣ����Ҫ֮���ID��Ϊ����
//�����꣬��Ҫ�ж��Ƿ�Ϊ������
extern SiteInfo* querySiteInfoByVenueName(SiteInfoNode* head, char siteVenueName[11]);

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

#endif // !__ADMIN_H
