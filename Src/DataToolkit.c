//  __          __              _             _ _ _ 
//  \ \        / /             (_)           | | | |
//   \ \  /\  / /_ _ _ __ _ __  _ _ __   __ _| | | |
//    \ \/  \/ / _` | '__| '_ \| | '_ \ / _` | | | |
//     \  /\  / (_| | |  | | | | | | | | (_| |_|_|_|
//      \/  \/ \__,_|_|  |_| |_|_|_| |_|\__, (_|_|_)
//                                       __/ |      
//	                                    |___/       
//  本文件实现数据读写的工具函数
//  请勿单独修改其中的任何内容，否则将可能影响程序正常运行
//  Date: 20230829 张硕
//


#include "StructDef.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

//所有节点：UserInfoNode，AdminInfoNode，SiteInfoNode，AppointmentInfoNode

//初始化所有头节点
#define InitAllHeadNode \
UserInfoNode* usrInfoHead = malloc(sizeof(UserInfoNode)); \
usrInfoHead->next = NULL; \
AdminInfoNode* adminInfoHead = malloc(sizeof(AdminInfoNode)); \
adminInfoHead->next = NULL; \
SiteInfoNode* siteInfoHead = malloc(sizeof(SiteInfoNode)); \
siteInfoHead->next = NULL; \
AppointmentInfoNode* apmtInfoHead = malloc(sizeof(AppointmentInfoNode)); \
apmtInfoHead->next = NULL; \


/*========================= 用户信息表 操作函数 =========================*/

int isUserExist(UserInfoNode* head, char strID[11]){
	/*
	 * @brief		判断用户是否存在
	 * @param		用户信息表头节点，用户ID
	 * @note		无
	 * @return		成功: TRUE; 用户未找到: FALSE;
	 */
	UserInfoNode* move = head->next;
	while (move != NULL) {
		if (strcmp(move->usrInfo.usrID, strID) == 0) {
			return TRUE;
		}
		move = move->next;
	}
	return FALSE;
}

int InsertToUserInfo(UserInfoNode* head, UserInfo info) {
	/*
	 * @brief		向 用户信息表 新增一条数据
	 * @param		用户信息表头节点，UserInfo结构体
	 * @note		用户ID为查询主键，请在插入前确认该值唯一
	 * @return		成功: 0; 用户已存在: 1;
	 */
	if(isUserExist(head, info.usrID) == TRUE) return 1;
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

void printUserInfo(UserInfoNode* head) {
	/*
	 * @brief		打印 用户信息表 中的数据
	 * @param		用户信息表头节点
	 * @note		此函数仅作调试时使用
	 * @return		void;
	 */
	UserInfoNode* move = head->next;
	while (move != NULL) {
		printf("用户ID:%s 姓名:%s 年龄:%d 电话:%s\n", move->usrInfo.usrID, move->usrInfo.usrName, move->usrInfo.usrAge, move->usrInfo.usrPhone);
		move = move->next;
	}
}

int saveUserInfo(UserInfoNode* head) {
	/*
	 * @brief		将内存中的 用户信息表 保存至文件
	 * @param		用户信息表头节点
	 * @note		无
	 * @return		成功: 0; 失败: 1;
	 */
	FILE* file = fopen("./userInfo.data", "wb+");
	UserInfoNode* move = head->next;
	while (move != NULL) {
		if (fwrite(&move->usrInfo, sizeof(UserInfo), 1, file) != 1) {
			return 1;
		}
		move = move->next;
	}
	fclose(file);
	return 0;
}

int loadUserInfo(UserInfoNode* head) {
	/*
	 * @brief		加载 用户信息表 至内存中
	 * @param		用户信息表头节点
	 * @note		文件不存在时，仍可在全新的头节点后运行数据存取，因此返回1时可不作异常处理
	 * @return		成功: 0; 文件不存在: 1;
	 */
	FILE* file = fopen("./userInfo.data", "rb+");
	if (!file) {
		return 1;
	}
	UserInfoNode* fresh = malloc(sizeof(UserInfoNode));
	fresh->next = NULL;
	UserInfoNode* move = head;
	while (fread(&fresh->usrInfo, sizeof(UserInfo), 1, file) == 1) {
		move->next = fresh;
		move = fresh;
		fresh = malloc(sizeof(UserInfoNode));
		fresh->next = NULL;
	}
	free(fresh);
	fclose(file);
	return 0;
}

int deleteUserInfo(UserInfoNode* head, char strID[11]) {
	/*
	 * @brief		删除 用户信息表 中的某个条目
	 * @param		用户信息表头节点，用户ID
	 * @note		注意：此函数目前不应被使用
	 * @return		成功: 0; 用户未找到: 1;
	 */
	UserInfoNode* move = head;
	while (move->next != NULL) {
		if (strcmp(move->next->usrInfo.usrID, strID) == 0) {
			UserInfoNode* tmp = move->next;
			move->next = move->next->next;
			free(tmp);
			tmp = NULL;
			saveUserInfo(head);
			return 0;
		}
		move = move->next;
	}
	return 1;
}

UserInfo queryUserInfo(UserInfoNode* head, char strID[11]) {
	/*
	 * @brief		根据用户ID取用用户信息结构体
	 * @param		用户信息表头节点，用户ID
	 * @note		*注意*：请先判断用户存在再调用，否则可能引起异常!!
	 * @return		UserInfo结构体对象
	 */
	UserInfoNode* move = head->next;
	while (move != NULL) {
		if (strcmp(move->usrInfo.usrID, strID) == 0) {
			return move->usrInfo;
		}
		move = move->next;
	}
}

int EditUserInfo(UserInfoNode* head, UserInfo info) {
	/*
	 * @brief		根据用户ID编辑用户信息结构体
	 * @param		用户信息表头节点，用户ID
	 * @note		建议先用上面那个取用，取出来改完了塞回去。
	 * @return		成功: 0; 用户未找到: 1;
	 */
	UserInfoNode* move = head->next;
	while (move != NULL) {
		if (strcmp(move->usrInfo.usrID, info.usrID) == 0) {
			move->usrInfo = info;
			return 0;
		}
		move = move->next;
	}
	return 1;
}


/*========================= 管理员信息表 操作函数 =========================*/

int isAdminExist(AdminInfoNode* head, char strID[11]){
	/*
	 * @brief		判断管理员是否存在
	 * @param		管理员信息表头节点，管理员ID
	 * @note		无
	 * @return		成功: TRUE; 管理员未找到: FALSE;
	 */
	AdminInfoNode* move = head->next;
	while (move != NULL) {
		if (strcmp(move->adminInfo.adminID, strID) == 0) {
			return TRUE;
		}
		move = move->next;
	}
	return FALSE;
}

int InsertToAdminInfo(AdminInfoNode* head, AdminInfo info) {
	/*
	 * @brief		向 管理员信息表 新增一条数据
	 * @param		管理员信息表头节点，AdminInfo结构体
	 * @note		管理员ID为查询主键，请在插入前确认该值唯一。此函数不应包含在业务逻辑中
	 * @return		成功: 0; 管理员已存在: 1;
	 */
	if(isAdminExist(head, info.adminID) == TRUE) return 1;
	AdminInfoNode* newline = malloc(sizeof(AdminInfoNode));
	newline->next = NULL;
	newline->adminInfo = info;
	AdminInfoNode* move = head;
	while (move->next != NULL) {
		move = move->next;
	}
	move->next = newline;
	return 0;
}

void printAdminInfo(AdminInfoNode* head) {
	/*
	 * @brief		打印 管理员信息表 中的数据
	 * @param		管理员信息表头节点
	 * @note		此函数仅作调试时使用
	 * @return		void;
	 */
	AdminInfoNode* move = head->next;
	while (move != NULL) {
		printf("管理员ID:%s 姓名:%s 性别:%d 电话:%s\n", move->adminInfo.adminID, move->adminInfo.adminName, move->adminInfo.adminGender, move->adminInfo.adminPhone);
		move = move->next;
	}
}

int saveAdminInfo(AdminInfoNode* head) {
	/*
	 * @brief		将内存中的 管理员信息表 保存至文件
	 * @param		管理员信息表头节点
	 * @note		无
	 * @return		成功: 0; 失败: 1;
	 */
	FILE* file = fopen("./adminInfo.data", "wb+");
	AdminInfoNode* move = head->next;
	while (move != NULL) {
		if (fwrite(&move->adminInfo, sizeof(AdminInfo), 1, file) != 1) {
			return 1;
		}
		move = move->next;
	}
	fclose(file);
	return 0;
}

int loadAdminInfo(AdminInfoNode* head) {
	/*
	 * @brief		加载 管理员信息表 至内存中
	 * @param		管理员信息表头节点
	 * @note		文件不存在时，仍可在全新的头节点后运行数据存取，因此返回1时可不作异常处理
	 * @return		成功: 0; 文件不存在: 1;
	 */
	FILE* file = fopen("./adminInfo.data", "rb+");
	if (!file) {
		return 1;
	}
	AdminInfoNode* fresh = malloc(sizeof(AdminInfoNode));
	fresh->next = NULL;
	AdminInfoNode* move = head;
	while (fread(&fresh->adminInfo, sizeof(AdminInfo), 1, file) == 1) {
		move->next = fresh;
		move = fresh;
		fresh = malloc(sizeof(AdminInfoNode));
		fresh->next = NULL;
	}
	free(fresh);
	fclose(file);
	return 0;
}

int deleteAdminInfo(AdminInfoNode* head, char strID[11]) {
	/*
	 * @brief		删除 管理员信息表 中的某个条目
	 * @param		管理员信息表头节点，管理员ID
	 * @note		注意：此函数目前不应被使用
	 * @return		成功: 0; 管理员未找到: 1;
	 */
	AdminInfoNode* move = head;
	while (move->next != NULL) {
		if (strcmp(move->next->adminInfo.adminID, strID) == 0) {
			AdminInfoNode* tmp = move->next;
			move->next = move->next->next;
			free(tmp);
			tmp = NULL;
			saveAdminInfo(head);
			return 0;
		}
		move = move->next;
	}
	return 1;
}

AdminInfo queryAdminInfo(AdminInfoNode* head, char strID[11]) {
	/*
	 * @brief		根据管理员ID取用管理员信息结构体
	 * @param		管理员信息表头节点，管理员ID
	 * @note		*注意*：请先判断管理员存在再调用，否则可能引起异常!!
	 * @return		AdminInfo结构体对象
	 */
	AdminInfoNode* move = head->next;
	while (move != NULL) {
		if (strcmp(move->adminInfo.adminID, strID) == 0) {
			return move->adminInfo;
		}
		move = move->next;
	}
}

int EditAdminInfo(AdminInfoNode* head, AdminInfo info) {
	/*
	 * @brief		根据管理员ID编辑管理员信息结构体
	 * @param		管理员信息表头节点，管理员ID
	 * @note		建议先用上面那个取用，取出来改完了塞回去。
	 * @return		AdminInfo结构体对象
	 */
	AdminInfoNode* move = head->next;
	while (move != NULL) {
		if (strcmp(move->adminInfo.adminID, info.adminID) == 0) {
			move->adminInfo = info;
			return 0;
		}
		move = move->next;
	}
	return 1;
}

/*========================= 场地信息表 操作函数 =========================*/

int isSiteExist(SiteInfoNode* head, char strID[11]){
	/*
	 * @brief		判断场地是否存在
	 * @param		场地信息表头节点，场地ID
	 * @note		无
	 * @return		成功: TRUE; 场地未找到: FALSE;
	 */
	SiteInfoNode* move = head->next;
	while (move != NULL) {
		if (strcmp(move->siteInfo.siteID, strID) == 0) {
			return TRUE;
		}
		move = move->next;
	}
	return FALSE;
}

int InsertToSiteInfo(SiteInfoNode* head, SiteInfo info) {
	/*
	 * @brief		向 场地信息表 新增一条数据
	 * @param		场地信息表头节点，SiteInfo结构体
	 * @note		场地ID为查询主键，请在插入前确认该值唯一。
	 * @return		成功: 0; 场地已存在: 1;
	 */
	if(isSiteExist(head, info.siteID) == TRUE) return 1;
	SiteInfoNode* newline = malloc(sizeof(SiteInfoNode));
	newline->next = NULL;
	newline->siteInfo = info;
	SiteInfoNode* move = head;
	while (move->next != NULL) {
		move = move->next;
	}
	move->next = newline;
	return 0;
}

void printSiteInfo(SiteInfoNode* head) {
	/*
	 * @brief		打印 场地信息表 中的数据
	 * @param		场地信息表头节点
	 * @note		此函数仅作调试时使用
	 * @return		void;
	 */
	SiteInfoNode* move = head->next;
	while (move != NULL) {
		printf("场地ID:%s 名称:%s 准入年龄:%d 运动类型:%s\n", move->siteInfo.siteID, move->siteInfo.siteName, move->siteInfo.siteAllowedAge, move->siteInfo.siteSportsType);
		move = move->next;
	}
}

int saveSiteInfo(SiteInfoNode* head) {
	/*
	 * @brief		将内存中的 场地信息表 保存至文件
	 * @param		场地信息表头节点
	 * @note		无
	 * @return		成功: 0; 失败: 1;
	 */
	FILE* file = fopen("./siteInfo.data", "wb+");
	SiteInfoNode* move = head->next;
	while (move != NULL) {
		if (fwrite(&move->siteInfo, sizeof(SiteInfo), 1, file) != 1) {
			return 1;
		}
		move = move->next;
	}
	fclose(file);
	return 0;
}

int loadSiteInfo(SiteInfoNode* head) {
	/*
	 * @brief		加载 场地信息表 至内存中
	 * @param		场地信息表头节点
	 * @note		文件不存在时，仍可在全新的头节点后运行数据存取，因此返回1时可不作异常处理
	 * @return		成功: 0; 文件不存在: 1;
	 */
	FILE* file = fopen("./siteInfo.data", "rb+");
	if (!file) {
		return 1;
	}
	SiteInfoNode* fresh = malloc(sizeof(SiteInfoNode));
	fresh->next = NULL;
	SiteInfoNode* move = head;
	while (fread(&fresh->siteInfo, sizeof(SiteInfo), 1, file) == 1) {
		move->next = fresh;
		move = fresh;
		fresh = malloc(sizeof(SiteInfoNode));
		fresh->next = NULL;
	}
	free(fresh);
	fclose(file);
	return 0;
}

int deleteSiteInfo(SiteInfoNode* head, char strID[11]) {
	/*
	 * @brief		删除 场地信息表 中的某个条目
	 * @param		场地信息表头节点，场地ID
	 * @note		注意：此函数目前不应被使用
	 * @return		成功: 0; 场地未找到: 1;
	 */
	SiteInfoNode* move = head;
	while (move->next != NULL) {
		if (strcmp(move->next->siteInfo.siteID, strID) == 0) {
			SiteInfoNode* tmp = move->next;
			move->next = move->next->next;
			free(tmp);
			tmp = NULL;
			saveSiteInfo(head);
			return 0;
		}
		move = move->next;
	}
	return 1;
}

SiteInfo querySiteInfo(SiteInfoNode* head, char strID[11]) {
	/*
	 * @brief		根据场地ID取用场地信息结构体
	 * @param		场地信息表头节点，场地ID
	 * @note		*注意*：请先判断场地存在再调用，否则可能引起异常!!
	 * @return		SiteInfo结构体对象
	 */
	SiteInfoNode* move = head->next;
	while (move != NULL) {
		if (strcmp(move->siteInfo.siteID, strID) == 0) {
			return move->siteInfo;
		}
		move = move->next;
	}
}

int EditSiteInfo(SiteInfoNode* head, SiteInfo info) {
	/*
	 * @brief		根据场地ID编辑场地信息结构体
	 * @param		场地信息表头节点，场地ID
	 * @note		建议先用上面那个取用，取出来改完了塞回去。
	 * @return		SiteInfo结构体对象
	 */
	SiteInfoNode* move = head->next;
	while (move != NULL) {
		if (strcmp(move->siteInfo.siteID, info.siteID) == 0) {
			move->siteInfo = info;
			return 0;
		}
		move = move->next;
	}
	return 1;
}

/*========================= 预约信息表 操作函数 =========================*/


int InsertToApmtInfo(AppointmentInfoNode* head, ApmtInfo info) {
	/*
	 * @brief		向 预约信息表 新增一条数据
	 * @param		预约信息表头节点，ApmtInfo结构体
	 * @note		无
	 * @return		成功: 0;
	 */
	AppointmentInfoNode* newline = malloc(sizeof(AppointmentInfoNode));
	newline->next = NULL;
	newline->apmtInfo = info;
	AppointmentInfoNode* move = head;
	while (move->next != NULL) {
		move = move->next;
	}
	move->next = newline;
	return 0;
}

void printApmtInfo(AppointmentInfoNode* head) {
	/*
	 * @brief		打印 预约信息表 中的数据
	 * @param		预约信息表头节点
	 * @note		此函数仅作调试时使用
	 * @return		void;
	 */
	AppointmentInfoNode* move = head->next;
	while (move != NULL) {
		printf("发起预定的用户ID:%s 用户发起预约时间:%s 预约的开始时间:%s 是否到场:%d\n", move->apmtInfo.apmtUsrID, move->apmtInfo.apmtOrderDated, move->apmtInfo.apmtStartDateh, move->apmtInfo.isUsrPresent);
		move = move->next;
	}
}

int saveApmtInfo(AppointmentInfoNode* head) {
	/*
	 * @brief		将内存中的 预约信息表 保存至文件
	 * @param		预约信息表头节点
	 * @note		无
	 * @return		成功: 0; 失败: 1;
	 */
	FILE* file = fopen("./apmtInfo.data", "wb+");
	AppointmentInfoNode* move = head->next;
	while (move != NULL) {
		if (fwrite(&move->apmtInfo, sizeof(ApmtInfo), 1, file) != 1) {
			return 1;
		}
		move = move->next;
	}
	fclose(file);
	return 0;
}

int loadApmtInfo(AppointmentInfoNode* head) {
	/*
	 * @brief		加载 预约信息表 至内存中
	 * @param		预约信息表头节点
	 * @note		文件不存在时，仍可在全新的头节点后运行数据存取，因此返回1时可不作异常处理
	 * @return		成功: 0; 文件不存在: 1;
	 */
	FILE* file = fopen("./apmtInfo.data", "rb+");
	if (!file) {
		return 1;
	}
	AppointmentInfoNode* fresh = malloc(sizeof(AppointmentInfoNode));
	fresh->next = NULL;
	AppointmentInfoNode* move = head;
	while (fread(&fresh->apmtInfo, sizeof(ApmtInfo), 1, file) == 1) {
		move->next = fresh;
		move = fresh;
		fresh = malloc(sizeof(AppointmentInfoNode));
		fresh->next = NULL;
	}
	free(fresh);
	fclose(file);
	return 0;
}

int deleteApmtInfo(AppointmentInfoNode* head, char strUsrID[11], char strSiteID[11], char strStartDate[11]) {
	/*
	 * @brief		删除 预约信息表 中的某个条目
	 * @param		预约信息表头节点，发起预约的用户ID，场地ID，预约开始时间
	 * @note		无
	 * @return		成功: 0; 未找到: 1;
	 */
	AppointmentInfoNode* move = head;
	while (move->next != NULL) {
		if (strcmp(move->next->apmtInfo.apmtUsrID, strUsrID) == 0 && strcmp(move->next->apmtInfo.apmtSiteID, strSiteID) == 0 && strcmp(move->next->apmtInfo.apmtStartDateh, strStartDate) == 0) {
			AppointmentInfoNode* tmp = move->next;
			move->next = move->next->next;
			free(tmp);
			tmp = NULL;
			saveApmtInfo(head);
			return 0;
		}
		move = move->next;
	}
	return 1;
}

ApmtInfo queryApmtInfo(AppointmentInfoNode* head, char strUsrID[11], char strSiteID[11], char strStartDate[11]) {
	/*
	 * @brief		取用场地信息结构体
	 * @param		场地信息表头节点，场地ID
	 * @note		*注意*：请先判断场地存在再调用，否则可能引起异常!!
	 * @return		SiteInfo结构体对象
	 */
	AppointmentInfoNode* move = head->next;
	while (move != NULL) {
		if (strcmp(move->next->apmtInfo.apmtUsrID, strUsrID) == 0 && strcmp(move->next->apmtInfo.apmtSiteID, strSiteID) == 0 && strcmp(move->next->apmtInfo.apmtStartDateh, strStartDate) == 0) {
			return move->apmtInfo;
		}
		move = move->next;
	}
}
