//	Date: 20230831 ����Ȼ

#include "admin.h"
#include "DataToolKit.c"

//new
//fuc1 done,�������Ʋ鳡����Ϣ����Ҫ֮���ID��Ϊ����
//�����꣬��Ҫ�ж��Ƿ�Ϊ������
SiteInfo* querySiteIDByVenueID(SiteInfoNode* head, char siteVenueID[11])
{
	SiteInfo buf[256];
	memset(buf, 0, sizeof(buf));

	//�������г���
	SiteInfoNode* move = head->next;
	int cnt = 0;
	while (move != NULL)//��ʼ����
	{
		if (strcmp(move->siteInfo.siteVenueID, siteVenueID) == 0)//���������������������ѯ����һ��
		{
			buf[cnt] = move->siteInfo;
			cnt++;
		}
		move = move->next;
	}
	return buf;
}


//fuc2 done
//�������ж�����ͨ������id��ѯ����Ҫ��Ķ�������󷵻ط���Ҫ��Ķ�������
//�����꣬��Ҫ�ж��Ƿ�Ϊ������

//fuc2-3 ���ز鶩��
ApmtInfo* queryApmtBySite(AppointmentInfoNode* head, char strSiteID[11])
{
	ApmtInfo buf[256];
	memset(buf, 0, sizeof(buf));

	//�������ж���
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

//fuc2-2 ���ݲ鳡��
//ʹ����Ҫ�п�
//���Ϸ�querySiteIDByVenueID

//fuc2-1 queryAdminInfo 

//main ����Աid�鳡�ض���
//ʹ����Ҫ�п�
ApmtInfo* querySiteOrderInfo(AdminInfoNode* AdminNodehead,SiteInfoNode* SiteNodehead, AppointmentInfoNode* ApmtNodehead, char adminID[11])
{

	ApmtInfo Apmtbuf[256];
	memset(Apmtbuf, 0, sizeof(Apmtbuf));

	//�жϹ���Ա��Ϣ�Ƿ���ڣ�������ṹ�����
	if (isAdminExist(AdminNodehead, adminID) == FALSE) return Apmtbuf;//�����ڣ����ؿ�����
	AdminInfo adminInfo = queryAdminInfo(AdminNodehead, adminID);//���ڣ��������Ա��Ϣ����
	//�������Ա���ܵĳ���ID
	char adminVenueID[11];
	memcpy(adminVenueID,&adminInfo.adminVenueID,sizeof(adminInfo.adminVenueID)/sizeof(adminInfo.adminVenueID[0]));
	//ͨ������ID��ѯ����ID�����棬ͬʱ��¼��������
	SiteInfo* Sitebuf;
	Sitebuf = querySiteIDByVenueID(SiteNodehead,adminVenueID);
	int SiteBufSize = sizeof(Sitebuf) / sizeof(Sitebuf[0]);
	//��ÿһ�����صĶ���copy��Apmtbuf
	int Sizecnt = 0;
	for (int i = 0; i < SiteBufSize; i++)
	{
		ApmtInfo* buf;
		buf = queryApmtBySite(ApmtNodehead, Sitebuf[i].siteID);//��ѯ��ǰ���صĶ���������
		int size = sizeof(buf) / sizeof(buf[0]);//��¼���涩������
		
		memcpy(&Apmtbuf[Sizecnt],buf,size);//����ǰ���صĶ����ṹ����������copy��Apmtbuf
		Sizecnt += size;//�����������ۼƱ�������
	}
	return Apmtbuf;
}

//fuc3 coding ��Ԥ�������򳡵� �����û�ϵͳ�еĺ���

//fuc4 done
//ͳ�Ƹ�ʱ�ε�ԤԼ��
int* cntSiteTime(AppointmentInfoNode* head,char strSiteID[11])
{
	int buf[16];//ʱ�Σ���6��22��16��ʱ��
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

//�����������������㷨
void quick_sort(int num[], int low, int high)
{
	int i, j, temp;
	int tmp;

	i = low;
	j = high;
	tmp = num[low];   //����Ϊ�м�ֽ��ߣ���߱���С���ұ߱�����,ͨ����һ��Ԫ���ǻ�׼��

	if (i > j)  //����±�i�����±�j��������������
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
	//���ݳ���id��ѯ������Ϣ������һ��������Ϣ�ṹ��
	sortBuf = cntSiteTime(head,strSiteID);
	quick_sort(sortBuf, 0, 16 - 1);
	return sortBuf;
}

//fuc5 ���㳡��Ӫҵ��
int cntSiteTurnover(AppointmentInfoNode* head, char strSiteID[11])
{
	int Turnover = 0;
	int* cntBuf;
	cntBuf = cntSiteTime(head, strSiteID);
	Turnover *= Rent * (sizeof(cntBuf) / sizeof(cntBuf[0]));//todo:���Rentδ����
}
