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
  * @File					: admin.c
  * @Brief					: admin operations file
  * @Description		    : 管理员操作函数定义
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

#include "admin.h"
#include "DataToolKit.c"

#define RENT 100//人为定义每小时租金100
#define BUFSIZE 256//缓存区长度

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
SiteInfo* querySiteInfoByVenueName(SiteInfoNode* head, char siteVenueName[11])
{
	//建立缓存区，缓存区长度为定长,初始化清空缓存区
	SiteInfo buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	//遍历所有场地
	SiteInfoNode* move = head->next;

	BOOL flag = 0;
	int cnt = 0;
	while (move != NULL)//开始遍历
	{
		//判断场地所属场馆名称与查询名称是否一致
		if (strcmp(move->siteInfo.siteVenueName, siteVenueName) == 0)
		{
			//将满足要求的结构体填入数组
			buf[cnt] = move->siteInfo;
			cnt++;
			flag = 1;
		}
		move = move->next;
	}

	//判断是否存在符合条件的场地，若无则返回空指针
	if (flag == 0)
	{
		return NULL;
	}
	return buf;
}

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
ApmtInfo* queryApmtBySite(AppointmentInfoNode* head, char strSiteID[11])
{
	//建立缓存区，缓存区长度为定长,初始化清空缓存区
	ApmtInfo buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	//遍历所有订单
	AppointmentInfoNode* move = head->next;
	int cnt = 0;//记录缓存区长度
	while (move != NULL) {
		if (strcmp(move->next->apmtInfo.apmtSiteID, strSiteID) == 0)
		{
			buf[cnt] = move->apmtInfo;
			cnt++;
		}
		move = move->next;
	}
	return buf;
}

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
ApmtInfo* querySiteOrderInfo(AdminInfoNode* AdminNodehead,SiteInfoNode* SiteNodehead, AppointmentInfoNode* ApmtNodehead, char adminID[11])
{
	//建立缓存区，缓存区长度为定长,初始化清空缓存区
	ApmtInfo Apmtbuf[BUFSIZE];
	memset(Apmtbuf, 0, sizeof(Apmtbuf));

	//判断管理员信息是否存在，并存入结构体变量
	if (isAdminExist(AdminNodehead, adminID) == FALSE)
	{
		//释放缓存区
		free(Apmtbuf);
		return NULL;//不存在，返回空指针
	}
	AdminInfo adminInfo = queryAdminInfo(AdminNodehead, adminID);//存在，保存管理员信息备用
	
	//缓存管理员所管的场馆名称
	char adminVenueName[11];
	memcpy(adminVenueName,&adminInfo.adminVenueName,sizeof(adminInfo.adminVenueName)/sizeof(adminInfo.adminVenueName[0]));
	
	//通过 场馆名称 查询 场地 并缓存，同时纪录场地数量
	SiteInfo* Sitebuf;
	Sitebuf = querySiteInfoByVenueName(SiteNodehead, adminVenueName);
	//判断返回值是否为空
	if (Sitebuf == NULL)
	{
		//释放缓存区
		free(Apmtbuf);
		return NULL;//返回空指针
	}
	//若不为空，记录场地个数
	int SiteBufSize = sizeof(Sitebuf) / sizeof(Sitebuf[0]);

	//将每一个场地的订单copy进 待返回缓存区
	int Sizecnt = 0;//记录缓存区长度
	for (int i = 0; i < SiteBufSize; i++)
	{
		ApmtInfo* buf = NULL;//建立订单结构体指针并初始化

		buf = queryApmtBySite(ApmtNodehead, Sitebuf[i].siteID);//查询当前场地的订单并缓存
		int size = sizeof(buf) / sizeof(buf[0]);//记录缓存订单数量
		
		memcpy(&Apmtbuf[Sizecnt],buf,size);//将当前场地的订单结构体数据copy进 待返回缓存区
		
		//释放指针
		free(buf);
		buf = NULL;
		
		Sizecnt += size;//在总数量上累计本次数量，用于记录 待返回缓存区 总长度
	}
	return Apmtbuf;
}

//fuc3 coding 按预定量排序场地 复用用户系统中的函数



//fuc4 done
//统计各时段的预约量
int* cntSiteTime(AppointmentInfoNode* head,char strSiteID[11])
{
	int buf[16];//时段，从6到22共16个时段
	memset(buf, 0, sizeof(buf));

	AppointmentInfoNode* move = head->next;

	while (move != NULL) {
		if (strcmp(move->next->apmtInfo.apmtSiteID, strSiteID) == 0)
		{
			int startTime = atoi(&move->apmtInfo.apmtStartDateh[8]);
			int duration = move->apmtInfo.apmtDurationh;
			for (int i = 0; i < duration; i++)
			{
				buf[startTime - 6 + i]++;
			}
		}
		move = move->next;
	}
	return buf;
}

//数组排序函数，快排算法
void quick_sort(int num[], int low, int high)
{
	int i, j, temp;
	int tmp;

	i = low;
	j = high;
	tmp = num[low];   //任命为中间分界线，左边比他小，右边比他大,通常第一个元素是基准数

	if (i > j)  //如果下标i大于下标j，函数结束运行
	{
		return;
	}

	while (i != j)
	{
		while (num[j] >= tmp && j > i)
		{
			j--;
		}

		while (num[i] <= tmp && j > i)
		{
			i++;
		}

		if (j > i)
		{
			temp = num[j];
			num[j] = num[i];
			num[i] = temp;
		}
	}

	num[low] = num[i];
	num[i] = tmp;

	quick_sort(num, low, i - 1);
	quick_sort(num, i + 1, high);
}
//main
/**
  * @Brief			对特定场地的预定时间进行排序
  * @Description
  * @param[in]		head		：
  * @param[in]		strSiteID	：
  * @param[out]		sortBuf		：
  * @retval
  */
int* sortSiteHotTime(AppointmentInfoNode* head,char strSiteID[11])
{
	int* sortBuf;
	//根据场地id查询场地信息，返回一个场地信息结构体
	sortBuf = cntSiteTime(head,strSiteID);
	quick_sort(sortBuf, 0, 16 - 1);
	return sortBuf;
}

//fuc5 计算场地营业额
int cntSiteTurnover(AppointmentInfoNode* head, char strSiteID[11])
{
	int Turnover = 0;
	int* cntBuf;
	cntBuf = cntSiteTime(head, strSiteID);
	Turnover *= RENT * (sizeof(cntBuf) / sizeof(cntBuf[0]));//todo:租金RENT未定义
	return Turnover;
}


//fuc6

//fuc7 按营业额排序场馆内所有场地

//fuc7-1 结构体数组排序,倒序
// 比较函数，用于排序
int compare(const void* a, const void* b) {
	return ((SiteInfo*)b)->turnover - ((SiteInfo*)a)->turnover;
}

// 函数：对结构体数组按照 turnover 排序
void sortStructArray(struct SiteInfo arr[], int size) {
	qsort(arr, size, sizeof(SiteInfo), compare);
}

//main
SiteInfo* sortSiteByTurnover(AdminInfoNode* AdminNodehead, SiteInfoNode* SiteNodehead, AppointmentInfoNode* ApmtNodehead, char adminID[11])
{

	SiteInfo buf[256];
	memset(buf, 0, sizeof(buf));

	//判断管理员信息是否存在，并存入结构体变量
	if (isAdminExist(AdminNodehead, adminID) == FALSE) return buf;//不存在，返回空数组
	AdminInfo adminInfo = queryAdminInfo(AdminNodehead, adminID);//存在，保存管理员信息备用
	//缓存管理员所管的场馆ID
	char adminVenueName[11];
	memcpy(adminVenueName, &adminInfo.adminVenueName, sizeof(adminInfo.adminVenueName) / sizeof(adminInfo.adminVenueName[0]));
	//通过场馆ID查询场地ID并缓存，同时纪录场地数量
	SiteInfo* Sitebuf;
	Sitebuf = querySiteInfoByVenueName(SiteNodehead, adminVenueName);
	int SiteBufSize = sizeof(Sitebuf) / sizeof(Sitebuf[0]);

	int* turnoverBuf;
	turnoverBuf = (int*)calloc(SiteBufSize, sizeof(int));
	for (int i = 0; i < SiteBufSize; i++)
	{
		Sitebuf[i].turnover = cntSiteTurnover(AdminNodehead, Sitebuf[i].siteID);
	}
	sortStructArray(Sitebuf, SiteBufSize);

	return Sitebuf;
}

//fuc8输入时间，返回一小时内有预约的场地数组
//main
SiteInfo* querySiteByTime(int startTime)
{

}

int addSite()
{

}

int InsertToSiteInfo(UserInfoNode* head, UserInfo info) {
	/*
	 * @brief		向 用户信息表 新增一条数据
	 * @param		用户信息表头节点，UserInfo结构体
	 * @note		用户ID为查询主键，请在插入前确认该值唯一
	 * @return		成功: 0; 用户已存在: 1;
	 */
	if (isUserExist(head, info.usrID) == TRUE) return 1;
	UserInfoNode* newline = malloc(sizeof(UserInfoNode));
	newline->next = NULL;
	newline->usrInfo = info;
	UserInfoNode* move = head;
	while (move->next != NULL) {
		move = move->next;
	}
	move->next = newline;
	return 0;
}