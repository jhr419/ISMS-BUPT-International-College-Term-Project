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

/**
* @Brief			根据 <场馆名称> 查询其下所有 <场地信息>
* @Description	传入 <场馆名称> ，遍历所有 <场地信息> ，将 <场地信息> 中 <场馆名称> 与进入函数的 参数 <场馆名称>
*					一致的 <场地结构体> 填入数组，待遍历完所有场地，返回 <场地信息结构体> 数组
*	Attention!		<注意！>接收完数组，需要先进行判空操作，若为空，则没有符合要求的场地
* @param[in]		head			：场地信息链表头结点
* @param[in]		siteVenueName	：场馆名称
* @param[out]		buf				：缓存场地信息结构体数组
* @retval			返回对应场馆下所有场地信息，填入结构体数组后返回数组地址
*/
extern SiteInfo* querySiteInfoByVenueName(SiteInfoNode* head, char siteVenueName[11]);

/**
  * @Brief			根据 <场地ID>查询对应场地 <订单信息>
  * @Description	这是一个工具函数，主要用于下面的 querySiteOrderInfo 函数
  *	Attention!		由于是一个工具函数，所以没有对 <场地ID> 是否存在进行判断，
  *					倘若需要判断，可调用 DataToolKit.c中函数 isSiteExist
  * @param[in]		head		：订单信息链表头结点
  * @param[in]		strSiteID	：场地ID
  * @param[out]		buf			：缓存订单结构体数组指针
  * @retval			返回对应场地的全部订单信息结构体，打包成一个数组
  */
extern ApmtInfo* queryApmtBySite(AppointmentInfoNode* head, char strSiteID[11]);

/**
  * @Brief			通过 <管理员ID> 查询其管理的所有场地的所有订单信息
  * @Description	先通过 isAdminExist 函数判断是否存在该管理员，若不存在，返回空订单结构体数组，
					若存在，再通过 queryAdminInfo 函数（在DataToolKit.c中定义）取用该管理员结构体,
					再调用结构体中场馆名称保存备用，再通过 querySiteInfoByVenueName（在此文件定义） 函数查询并保存该
					场馆下的全部场地，保存为场地信息结构体数组，再通过 queryApmtBySite（在此文件定义） 函数查询几个场地的
					订单信息并保存至缓冲区，最后通过缓冲区返回 <订单结构体数组>
  *	Attention!		使用该函数后需要判空
  * @param[in]		AdminNodehead	：管理员信息链表头结点
  * @param[in]		SiteNodehead	：场地信息链表头结点
  * @param[in]		ApmtNodehead	：订单信息链表头结点
  * @param[in]		adminID			：管理员ID
  * @param[out]		Apmtbuf			：缓存订单结构体数组指针
  * @retval			返回该管理员所属场馆的全部订单，填入订单结构体数组后返回
  */
extern ApmtInfo* querySiteOrderInfo(AdminInfoNode* AdminNodehead, SiteInfoNode* SiteNodehead, AppointmentInfoNode* ApmtNodehead, char adminID[11]);

//fuc3 coding 按预定量排序场地 复用用户系统中的函数

/**
  * @Brief			统计各时段的预约量
  * @Description	建立一个长度为16的数组，分别对应从6：00到22：00
  *					之间16个时段，统计特定场地各时段预约情况
  * @param[in]		head		：订单链表头结点
  * @param[in]		strSiteID	：场地ID
  * @param[out]		buf
  * @retval			按6：00到22：00顺序，返回统计结果
  */
extern int* cntSiteTime(AppointmentInfoNode* head, char strSiteID[11]);

/**
  * @Brief			计算特定场地营业额
  * @Description	通过输入场地ID,查询该场地的 历史预约量，乘以租金，得到营业额
  * @param[in]		head		：场地信息链表头结点
  * @param[in]		strSiteID	：场地ID
  * @param[out]		Turnover	：该场地的营业额，整型数
  * @retval			返回特定场地的营业额
  */
extern int cntSiteTurnover(SiteInfoNode* head, char strSiteID[11]);

//fuc6 用户年龄层次分布、男女热门运动

/**
  * @Brief			按营业额排序场馆内所有场地
  * @Description	遍历管理员所管的所有场地，
  *					输入管理员ID，首先判断是否存在管理员，
  *					若存在，提取场馆ID查询场地ID并缓存，同时纪录场地数量
  *					提取营业额信息用于对场地排序，返回场地信息结构体数组
  * @Attention		使用需要判空，当管理员ID错误返回空数组
  * @param[in]		AdminNodehead	：管理员链表头结点
  * @param[in]		SiteNodehead	: 场地链表头结点
  * @param[in]		ApmtNodehead	：订单链表头结点
  *	@param[in]		adminID			：管理员ID
  * @param[out]		Sitebuf			：缓存场地信息结构体数组指针
  * @retval			返回按照营业额排序后的场地信息数组
  */
extern SiteInfo* sortSiteByTurnover(AdminInfoNode* AdminNodehead, SiteInfoNode* SiteNodehead, AppointmentInfoNode* ApmtNodehead, char adminID[11]);

//fuc8输入时间，返回一小时内有预约的场地数组

#endif // !__ADMIN_H
