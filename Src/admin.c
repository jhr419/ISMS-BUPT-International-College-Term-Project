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
  * @Description		    : ����Ա������������
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

#include "admin.h"
#include "DataToolKit.c"

#define RENT 100//��Ϊ����ÿСʱ���100
#define BUFSIZE 256//����������

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
SiteInfo* querySiteInfoByVenueName(SiteInfoNode* head, char siteVenueName[11])
{
	//����������������������Ϊ����,��ʼ����ջ�����
	SiteInfo buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	//�������г���
	SiteInfoNode* move = head->next;

	BOOL flag = 0;
	int cnt = 0;
	while (move != NULL)//��ʼ����
	{
		//�жϳ������������������ѯ�����Ƿ�һ��
		if (strcmp(move->siteInfo.siteVenueName, siteVenueName) == 0)
		{
			//������Ҫ��Ľṹ����������
			buf[cnt] = move->siteInfo;
			cnt++;
			flag = 1;
		}
		move = move->next;
	}

	//�ж��Ƿ���ڷ��������ĳ��أ������򷵻ؿ�ָ��
	if (flag == 0)
	{
		return NULL;
	}
	return buf;
}

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
ApmtInfo* queryApmtBySite(AppointmentInfoNode* head, char strSiteID[11])
{
	//����������������������Ϊ����,��ʼ����ջ�����
	ApmtInfo buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	//�������ж���
	AppointmentInfoNode* move = head->next;
	int cnt = 0;//��¼����������
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
ApmtInfo* querySiteOrderInfo(AdminInfoNode* AdminNodehead,SiteInfoNode* SiteNodehead, AppointmentInfoNode* ApmtNodehead, char adminID[11])
{
	//����������������������Ϊ����,��ʼ����ջ�����
	ApmtInfo Apmtbuf[BUFSIZE];
	memset(Apmtbuf, 0, sizeof(Apmtbuf));

	//�жϹ���Ա��Ϣ�Ƿ���ڣ�������ṹ�����
	if (isAdminExist(AdminNodehead, adminID) == FALSE)
	{
		//�ͷŻ�����
		free(Apmtbuf);
		return NULL;//�����ڣ����ؿ�ָ��
	}
	AdminInfo adminInfo = queryAdminInfo(AdminNodehead, adminID);//���ڣ��������Ա��Ϣ����
	
	//�������Ա���ܵĳ�������
	char adminVenueName[11];
	memcpy(adminVenueName,&adminInfo.adminVenueName,sizeof(adminInfo.adminVenueName)/sizeof(adminInfo.adminVenueName[0]));
	
	//ͨ�� �������� ��ѯ ���� �����棬ͬʱ��¼��������
	SiteInfo* Sitebuf;
	Sitebuf = querySiteInfoByVenueName(SiteNodehead, adminVenueName);
	//�жϷ���ֵ�Ƿ�Ϊ��
	if (Sitebuf == NULL)
	{
		//�ͷŻ�����
		free(Apmtbuf);
		return NULL;//���ؿ�ָ��
	}
	//����Ϊ�գ���¼���ظ���
	int SiteBufSize = sizeof(Sitebuf) / sizeof(Sitebuf[0]);

	//��ÿһ�����صĶ���copy�� �����ػ�����
	int Sizecnt = 0;//��¼����������
	for (int i = 0; i < SiteBufSize; i++)
	{
		ApmtInfo* buf = NULL;//���������ṹ��ָ�벢��ʼ��

		buf = queryApmtBySite(ApmtNodehead, Sitebuf[i].siteID);//��ѯ��ǰ���صĶ���������
		int size = sizeof(buf) / sizeof(buf[0]);//��¼���涩������
		
		memcpy(&Apmtbuf[Sizecnt],buf,size);//����ǰ���صĶ����ṹ������copy�� �����ػ�����
		
		//�ͷ�ָ��
		free(buf);
		buf = NULL;
		
		Sizecnt += size;//�����������ۼƱ������������ڼ�¼ �����ػ����� �ܳ���
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
/**
  * @Brief			���ض����ص�Ԥ��ʱ���������
  * @Description
  * @param[in]		head		��
  * @param[in]		strSiteID	��
  * @param[out]		sortBuf		��
  * @retval
  */
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
	Turnover *= RENT * (sizeof(cntBuf) / sizeof(cntBuf[0]));//todo:���RENTδ����
	return Turnover;
}


//fuc6

//fuc7 ��Ӫҵ�����򳡹������г���

//fuc7-1 �ṹ����������,����
// �ȽϺ�������������
int compare(const void* a, const void* b) {
	return ((SiteInfo*)b)->turnover - ((SiteInfo*)a)->turnover;
}

// �������Խṹ�����鰴�� turnover ����
void sortStructArray(struct SiteInfo arr[], int size) {
	qsort(arr, size, sizeof(SiteInfo), compare);
}

//main
SiteInfo* sortSiteByTurnover(AdminInfoNode* AdminNodehead, SiteInfoNode* SiteNodehead, AppointmentInfoNode* ApmtNodehead, char adminID[11])
{

	SiteInfo buf[256];
	memset(buf, 0, sizeof(buf));

	//�жϹ���Ա��Ϣ�Ƿ���ڣ�������ṹ�����
	if (isAdminExist(AdminNodehead, adminID) == FALSE) return buf;//�����ڣ����ؿ�����
	AdminInfo adminInfo = queryAdminInfo(AdminNodehead, adminID);//���ڣ��������Ա��Ϣ����
	//�������Ա���ܵĳ���ID
	char adminVenueName[11];
	memcpy(adminVenueName, &adminInfo.adminVenueName, sizeof(adminInfo.adminVenueName) / sizeof(adminInfo.adminVenueName[0]));
	//ͨ������ID��ѯ����ID�����棬ͬʱ��¼��������
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

//fuc8����ʱ�䣬����һСʱ����ԤԼ�ĳ�������
//main
SiteInfo* querySiteByTime(int startTime)
{

}

int addSite()
{

}

int InsertToSiteInfo(UserInfoNode* head, UserInfo info) {
	/*
	 * @brief		�� �û���Ϣ�� ����һ������
	 * @param		�û���Ϣ��ͷ�ڵ㣬UserInfo�ṹ��
	 * @note		�û�IDΪ��ѯ���������ڲ���ǰȷ�ϸ�ֵΨһ
	 * @return		�ɹ�: 0; �û��Ѵ���: 1;
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