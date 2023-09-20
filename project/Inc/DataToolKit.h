#ifndef __DATATOOLKIT_H
#define __DATATOOLKIT_H

#include "StructDef.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

/*========================= �û���Ϣ�� �������� =========================*/

/*
 * @brief		�ж��û��Ƿ����
 * @param		�û���Ϣ��ͷ�ڵ㣬�û�ID
 * @note		��
 * @return		�ɹ�: TRUE; �û�δ�ҵ�: FALSE;
 */
extern int isUserExist(UserInfoNode* head, char strID[11]);

/*
 * @brief		�� �û���Ϣ�� ����һ������
 * @param		�û���Ϣ��ͷ�ڵ㣬UserInfo�ṹ��
 * @note		�û�IDΪ��ѯ���������ڲ���ǰȷ�ϸ�ֵΨһ
 * @return		�ɹ�: 0; �û��Ѵ���: 1;
 */
extern int InsertToUserInfo(UserInfoNode* head, UserInfo info);

/*
 * @brief		��ӡ �û���Ϣ�� �е�����
 * @param		�û���Ϣ��ͷ�ڵ�
 * @note		�˺�����������ʱʹ��
 * @return		void;
 */
extern void printUserInfo(UserInfoNode* head);

/*
	 * @brief		���ڴ��е� �û���Ϣ�� �������ļ�
	 * @param		�û���Ϣ��ͷ�ڵ�
	 * @note		��
	 * @return		�ɹ�: 0; ʧ��: 1;
	 */
extern int saveUserInfo(UserInfoNode* head);

/*
 * @brief		���� �û���Ϣ�� ���ڴ���
 * @param		�û���Ϣ��ͷ�ڵ�
 * @note		�ļ�������ʱ���Կ���ȫ�µ�ͷ�ڵ���������ݴ�ȡ����˷���1ʱ�ɲ����쳣����
 * @return		�ɹ�: 0; �ļ�������: 1;
 */
extern int loadUserInfo(UserInfoNode* head);

/*
 * @brief		ɾ�� �û���Ϣ�� �е�ĳ����Ŀ
 * @param		�û���Ϣ��ͷ�ڵ㣬�û�ID
 * @note		ע�⣺�˺���Ŀǰ��Ӧ��ʹ��
 * @return		�ɹ�: 0; �û�δ�ҵ�: 1;
 */
extern int deleteUserInfo(UserInfoNode* head, char strID[11]);

/*
 * @brief		�����û�IDȡ���û���Ϣ�ṹ��
 * @param		�û���Ϣ��ͷ�ڵ㣬�û�ID
 * @note		*ע��*�������ж��û������ٵ��ã�������������쳣!!
 * @return		UserInfo�ṹ�����
 */
UserInfo queryUserInfo(UserInfoNode* head, char strID[11]);

/*
 * @brief		�����û�ID�༭�û���Ϣ�ṹ��
 * @param		�û���Ϣ��ͷ�ڵ㣬�û�ID
 * @note		�������������Ǹ�ȡ�ã�ȡ��������������ȥ��
 * @return		�ɹ�: 0; �û�δ�ҵ�: 1;
 */
extern int EditUserInfo(UserInfoNode* head, UserInfo info);

/*========================= ����Ա��Ϣ�� �������� =========================*/

/*
 * @brief		�жϹ���Ա�Ƿ����
 * @param		����Ա��Ϣ��ͷ�ڵ㣬����ԱID
 * @note		��
 * @return		�ɹ�: TRUE; ����Աδ�ҵ�: FALSE;
 */
extern int isAdminExist(AdminInfoNode* head, char strID[11]);

/*
 * @brief		�� ����Ա��Ϣ�� ����һ������
 * @param		����Ա��Ϣ��ͷ�ڵ㣬AdminInfo�ṹ��
 * @note		����ԱIDΪ��ѯ���������ڲ���ǰȷ�ϸ�ֵΨһ���˺�����Ӧ������ҵ���߼���
 * @return		�ɹ�: 0; ����Ա�Ѵ���: 1;
 */
extern int InsertToAdminInfo(AdminInfoNode* head, AdminInfo info);

/*
 * @brief		��ӡ ����Ա��Ϣ�� �е�����
 * @param		����Ա��Ϣ��ͷ�ڵ�
 * @note		�˺�����������ʱʹ��
 * @return		void;
 */
extern void printAdminInfo(AdminInfoNode* head);

/*
 * @brief		���ڴ��е� ����Ա��Ϣ�� �������ļ�
 * @param		����Ա��Ϣ��ͷ�ڵ�
 * @note		��
 * @return		�ɹ�: 0; ʧ��: 1;
 */
extern int saveAdminInfo(AdminInfoNode* head);

/*
 * @brief		���� ����Ա��Ϣ�� ���ڴ���
 * @param		����Ա��Ϣ��ͷ�ڵ�
 * @note	s	�ļ�������ʱ���Կ���ȫ�µ�ͷ�ڵ���������ݴ�ȡ����˷���1ʱ�ɲ����쳣����
 * @return		�ɹ�: 0; �ļ�������: 1;
 */
extern int loadAdminInfo(AdminInfoNode* head);

/*
 * @brief		ɾ�� ����Ա��Ϣ�� �е�ĳ����Ŀ
 * @param		����Ա��Ϣ��ͷ�ڵ㣬����ԱID
 * @note		ע�⣺�˺���Ŀǰ��Ӧ��ʹ��
 * @return		�ɹ�: 0; ����Աδ�ҵ�: 1;
 */
extern int deleteAdminInfo(AdminInfoNode* head, char strID[11]);

/*
 * @brief		���ݹ���ԱIDȡ�ù���Ա��Ϣ�ṹ��
 * @param		����Ա��Ϣ��ͷ�ڵ㣬����ԱID
 * @note		*ע��*�������жϹ���Ա�����ٵ��ã�������������쳣!!
 * @return		AdminInfo�ṹ�����
 */
extern AdminInfo queryAdminInfo(AdminInfoNode* head, char strID[11]);

/*
 * @brief		���ݹ���ԱID�༭����Ա��Ϣ�ṹ��
 * @param		����Ա��Ϣ��ͷ�ڵ㣬����ԱID
 * @note		�������������Ǹ�ȡ�ã�ȡ��������������ȥ��
 * @return		AdminInfo�ṹ�����
 */
extern int EditAdminInfo(AdminInfoNode* head, AdminInfo info);

/*========================= ������Ϣ�� �������� =========================*/

/*
 * @brief		�жϳ����Ƿ����
 * @param		������Ϣ��ͷ�ڵ㣬����ID
 * @note		��
 * @return		�ɹ�: TRUE; ����δ�ҵ�: FALSE;
 */
extern int isSiteExist(SiteInfoNode* head, char strID[11]);

/*
 * @brief		�� ������Ϣ�� ����һ������
 * @param		������Ϣ��ͷ�ڵ㣬SiteInfo�ṹ��
 * @note		����IDΪ��ѯ���������ڲ���ǰȷ�ϸ�ֵΨһ��
 * @return		�ɹ�: 0; �����Ѵ���: 1;
 */
extern int InsertToSiteInfo(SiteInfoNode* head, SiteInfo info);

/*
 * @brief		��ӡ ������Ϣ�� �е�����
 * @param		������Ϣ��ͷ�ڵ�
 * @note		�˺�����������ʱʹ��
 * @return		void;
 */
extern void printSiteInfo(SiteInfoNode* head);

/*
 * @brief		���ڴ��е� ������Ϣ�� �������ļ�
 * @param		������Ϣ��ͷ�ڵ�
 * @note		��
 * @return		�ɹ�: 0; ʧ��: 1;
 */
extern int saveSiteInfo(SiteInfoNode* head);
/**
 * @brief		���� ������Ϣ�� ���ڴ���
 * @param		������Ϣ��ͷ�ڵ�
 * @note		�ļ�������ʱ���Կ���ȫ�µ�ͷ�ڵ���������ݴ�ȡ����˷���1ʱ�ɲ����쳣����
 * @return		�ɹ�: 0; �ļ�������: 1;
 */
extern int loadSiteInfo(SiteInfoNode* head);

/**
 * @brief		ɾ�� ������Ϣ�� �е�ĳ����Ŀ
 * @param		������Ϣ��ͷ�ڵ㣬����ID
 * @note		ע�⣺�˺���Ŀǰ��Ӧ��ʹ��
 * @return		�ɹ�: 0; ����δ�ҵ�: 1;
 */
extern int deleteSiteInfo(SiteInfoNode* head, char strID[11]);

/**
 * @brief		���ݳ���IDȡ�ó�����Ϣ�ṹ��
 * @param		������Ϣ��ͷ�ڵ㣬����ID
 * @note		*ע��*�������жϳ��ش����ٵ��ã�������������쳣!!
 * @return		SiteInfo�ṹ�����
 */
SiteInfo querySiteInfo(SiteInfoNode* head, char strID[11]);

/**
 * @brief		���ݳ���ID�༭������Ϣ�ṹ��
 * @param		������Ϣ��ͷ�ڵ㣬����ID
 * @note		�������������Ǹ�ȡ�ã�ȡ��������������ȥ��
 * @return		SiteInfo�ṹ�����
 */
extern int EditSiteInfo(SiteInfoNode* head, SiteInfo info);

/*========================= ԤԼ��Ϣ�� �������� =========================*/

/**
 * @brief		�� ԤԼ��Ϣ�� ����һ������
 * @param		ԤԼ��Ϣ��ͷ�ڵ㣬ApmtInfo�ṹ��
 * @note		��
 * @return		�ɹ�: 0;
 */
//extern int InsertToApmtInfo(AppointmentInfoNode* head, ApmtInfo info);

/**
 * @brief		��ӡ ԤԼ��Ϣ�� �е�����
 * @param		ԤԼ��Ϣ��ͷ�ڵ�
 * @note		�˺�����������ʱʹ��
 * @return		void;
 */
extern void printApmtInfo(AppointmentInfoNode* head);

/**
 * @brief		���ڴ��е� ԤԼ��Ϣ�� �������ļ�
 * @param		ԤԼ��Ϣ��ͷ�ڵ�
 * @note		��
 * @return		�ɹ�: 0; ʧ��: 1;
 */
extern int saveApmtInfo(AppointmentInfoNode* head);

/**
 * @brief		���� ԤԼ��Ϣ�� ���ڴ���
 * @param		ԤԼ��Ϣ��ͷ�ڵ�
 * @note		�ļ�������ʱ���Կ���ȫ�µ�ͷ�ڵ���������ݴ�ȡ����˷���1ʱ�ɲ����쳣����
 * @return		�ɹ�: 0; �ļ�������: 1;
 */
extern int loadApmtInfo(AppointmentInfoNode* head);

/**
 * @brief		ɾ�� ԤԼ��Ϣ�� �е�ĳ����Ŀ
 * @param		ԤԼ��Ϣ��ͷ�ڵ㣬����ԤԼ���û�ID������ID��ԤԼ��ʼʱ��
 * @note		��
 * @return		�ɹ�: 0; δ�ҵ�: 1;
 */
extern int deleteApmtInfo(AppointmentInfoNode* head, char strUsrID[11], char strSiteID[11], char strStartDate[11]);

/**
 * @brief		ȡ�ó�����Ϣ�ṹ��
 * @param		������Ϣ��ͷ�ڵ㣬����ID
 * @note		*ע��*�������жϳ��ش����ٵ��ã�������������쳣!!
 * @return		SiteInfo�ṹ�����
 */
ApmtInfo queryApmtInfo(AppointmentInfoNode* head, char strUsrID[11], char strSiteID[11], char strStartDate[11]);

#endif // !__DATATOOLKIT_H
