//	Date: 20230831 靳浩然

#include "admin.h"
#include "DataToolKit.c"

//new
//fuc1 done,场馆名称查场地信息，需要之后把ID改为名称
//接收完，需要判断是否为空数组
SiteInfo* querySiteIDByVenueID(SiteInfoNode* head, char siteVenueID[11])
{
	SiteInfo buf[256];
	memset(buf, 0, sizeof(buf));

	//遍历所有场地
	SiteInfoNode* move = head->next;
	int cnt = 0;
	while (move != NULL)//开始遍历
	{
		if (strcmp(move->siteInfo.siteVenueID, siteVenueID) == 0)//若场地所属场馆名称与查询名称一致
		{
			buf[cnt] = move->siteInfo;
			cnt++;
		}
		move = move->next;
	}
	return buf;
}


//fuc2 done
//遍历所有订单，通过场地id查询符合要求的订单，最后返回符合要求的订单数组
//接收完，需要判断是否为空数组

//fuc2-3 场地查订单
ApmtInfo* queryApmtBySite(AppointmentInfoNode* head, char strSiteID[11])
{
	ApmtInfo buf[256];
	memset(buf, 0, sizeof(buf));

	//遍历所有订单
	AppointmentInfoNode* move = head->next;
	int cnt = 0;
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

//fuc2-2 场馆查场地
//使用需要判空
//即上方querySiteIDByVenueID

//fuc2-1 queryAdminInfo 

//main 管理员id查场地订单
//使用需要判空
ApmtInfo* querySiteOrderInfo(AdminInfoNode* AdminNodehead,SiteInfoNode* SiteNodehead, AppointmentInfoNode* ApmtNodehead, char adminID[11])
{

	ApmtInfo Apmtbuf[256];
	memset(Apmtbuf, 0, sizeof(Apmtbuf));

	//判断管理员信息是否存在，并存入结构体变量
	if (isAdminExist(AdminNodehead, adminID) == FALSE) return Apmtbuf;//不存在，返回空数组
	AdminInfo adminInfo = queryAdminInfo(AdminNodehead, adminID);//存在，保存管理员信息备用
	//缓存管理员所管的场馆ID
	char adminVenueID[11];
	memcpy(adminVenueID,&adminInfo.adminVenueID,sizeof(adminInfo.adminVenueID)/sizeof(adminInfo.adminVenueID[0]));
	//通过场馆ID查询场地ID并缓存，同时纪录场地数量
	SiteInfo* Sitebuf;
	Sitebuf = querySiteIDByVenueID(SiteNodehead,adminVenueID);
	int SiteBufSize = sizeof(Sitebuf) / sizeof(Sitebuf[0]);
	//将每一个场地的订单copy进Apmtbuf
	int Sizecnt = 0;
	for (int i = 0; i < SiteBufSize; i++)
	{
		ApmtInfo* buf;
		buf = queryApmtBySite(ApmtNodehead, Sitebuf[i].siteID);//查询当前场地的订单并缓存
		int size = sizeof(buf) / sizeof(buf[0]);//记录缓存订单数量
		
		memcpy(&Apmtbuf[Sizecnt],buf,size);//将当前场地的订单结构体数据数据copy进Apmtbuf
		Sizecnt += size;//在总数量上累计本次数量
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
	Turnover *= Rent * (sizeof(cntBuf) / sizeof(cntBuf[0]));//todo:租金Rent未定义
}
