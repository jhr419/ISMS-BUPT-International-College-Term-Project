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
  * @Description		    : 管理员操作函数头文件
  * @Author					: 靳浩然
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


//fuc1 done,场馆名称查场地信息，需要之后把ID改为名称
//接收完，需要判断是否为空数组
extern SiteInfo* querySiteInfoByVenueName(SiteInfoNode* head, char siteVenueName[11]);

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

#endif // !__ADMIN_H
