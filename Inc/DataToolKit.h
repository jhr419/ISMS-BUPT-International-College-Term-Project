#ifndef __DATATOOLKIT_H
#define __DATATOOLKIT_H

#include "StructDef.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

/*========================= 用户信息表 操作函数 =========================*/

/*
 * @brief		判断用户是否存在
 * @param		用户信息表头节点，用户ID
 * @note		无
 * @return		成功: TRUE; 用户未找到: FALSE;
 */
extern int isUserExist(UserInfoNode* head, char strID[11]);

/*
 * @brief		向 用户信息表 新增一条数据
 * @param		用户信息表头节点，UserInfo结构体
 * @note		用户ID为查询主键，请在插入前确认该值唯一
 * @return		成功: 0; 用户已存在: 1;
 */
extern int InsertToUserInfo(UserInfoNode* head, UserInfo info);

/*
 * @brief		打印 用户信息表 中的数据
 * @param		用户信息表头节点
 * @note		此函数仅作调试时使用
 * @return		void;
 */
extern void printUserInfo(UserInfoNode* head);

/*
	 * @brief		将内存中的 用户信息表 保存至文件
	 * @param		用户信息表头节点
	 * @note		无
	 * @return		成功: 0; 失败: 1;
	 */
extern int saveUserInfo(UserInfoNode* head);

/*
 * @brief		加载 用户信息表 至内存中
 * @param		用户信息表头节点
 * @note		文件不存在时，仍可在全新的头节点后运行数据存取，因此返回1时可不作异常处理
 * @return		成功: 0; 文件不存在: 1;
 */
extern int loadUserInfo(UserInfoNode* head);

/*
 * @brief		删除 用户信息表 中的某个条目
 * @param		用户信息表头节点，用户ID
 * @note		注意：此函数目前不应被使用
 * @return		成功: 0; 用户未找到: 1;
 */
extern int deleteUserInfo(UserInfoNode* head, char strID[11]);

/*
 * @brief		根据用户ID取用用户信息结构体
 * @param		用户信息表头节点，用户ID
 * @note		*注意*：请先判断用户存在再调用，否则可能引起异常!!
 * @return		UserInfo结构体对象
 */
UserInfo queryUserInfo(UserInfoNode* head, char strID[11]);

/*
 * @brief		根据用户ID编辑用户信息结构体
 * @param		用户信息表头节点，用户ID
 * @note		建议先用上面那个取用，取出来改完了塞回去。
 * @return		成功: 0; 用户未找到: 1;
 */
extern int EditUserInfo(UserInfoNode* head, UserInfo info);

/*========================= 管理员信息表 操作函数 =========================*/

/*
 * @brief		判断管理员是否存在
 * @param		管理员信息表头节点，管理员ID
 * @note		无
 * @return		成功: TRUE; 管理员未找到: FALSE;
 */
extern int isAdminExist(AdminInfoNode* head, char strID[11]);

/*
 * @brief		向 管理员信息表 新增一条数据
 * @param		管理员信息表头节点，AdminInfo结构体
 * @note		管理员ID为查询主键，请在插入前确认该值唯一。此函数不应包含在业务逻辑中
 * @return		成功: 0; 管理员已存在: 1;
 */
extern int InsertToAdminInfo(AdminInfoNode* head, AdminInfo info);

/*
 * @brief		打印 管理员信息表 中的数据
 * @param		管理员信息表头节点
 * @note		此函数仅作调试时使用
 * @return		void;
 */
extern void printAdminInfo(AdminInfoNode* head);

/*
 * @brief		将内存中的 管理员信息表 保存至文件
 * @param		管理员信息表头节点
 * @note		无
 * @return		成功: 0; 失败: 1;
 */
extern int saveAdminInfo(AdminInfoNode* head);

/*
 * @brief		加载 管理员信息表 至内存中
 * @param		管理员信息表头节点
 * @note	s	文件不存在时，仍可在全新的头节点后运行数据存取，因此返回1时可不作异常处理
 * @return		成功: 0; 文件不存在: 1;
 */
extern int loadAdminInfo(AdminInfoNode* head);

/*
 * @brief		删除 管理员信息表 中的某个条目
 * @param		管理员信息表头节点，管理员ID
 * @note		注意：此函数目前不应被使用
 * @return		成功: 0; 管理员未找到: 1;
 */
extern int deleteAdminInfo(AdminInfoNode* head, char strID[11]);

/*
 * @brief		根据管理员ID取用管理员信息结构体
 * @param		管理员信息表头节点，管理员ID
 * @note		*注意*：请先判断管理员存在再调用，否则可能引起异常!!
 * @return		AdminInfo结构体对象
 */
extern AdminInfo queryAdminInfo(AdminInfoNode* head, char strID[11]);

/*
 * @brief		根据管理员ID编辑管理员信息结构体
 * @param		管理员信息表头节点，管理员ID
 * @note		建议先用上面那个取用，取出来改完了塞回去。
 * @return		AdminInfo结构体对象
 */
extern int EditAdminInfo(AdminInfoNode* head, AdminInfo info);

/*========================= 场地信息表 操作函数 =========================*/

/*
 * @brief		判断场地是否存在
 * @param		场地信息表头节点，场地ID
 * @note		无
 * @return		成功: TRUE; 场地未找到: FALSE;
 */
extern int isSiteExist(SiteInfoNode* head, char strID[11]);

/*
 * @brief		向 场地信息表 新增一条数据
 * @param		场地信息表头节点，SiteInfo结构体
 * @note		场地ID为查询主键，请在插入前确认该值唯一。
 * @return		成功: 0; 场地已存在: 1;
 */
extern int InsertToSiteInfo(SiteInfoNode* head, SiteInfo info);

/*
 * @brief		打印 场地信息表 中的数据
 * @param		场地信息表头节点
 * @note		此函数仅作调试时使用
 * @return		void;
 */
extern void printSiteInfo(SiteInfoNode* head);

/*
 * @brief		将内存中的 场地信息表 保存至文件
 * @param		场地信息表头节点
 * @note		无
 * @return		成功: 0; 失败: 1;
 */
extern int saveSiteInfo(SiteInfoNode* head);
/**
 * @brief		加载 场地信息表 至内存中
 * @param		场地信息表头节点
 * @note		文件不存在时，仍可在全新的头节点后运行数据存取，因此返回1时可不作异常处理
 * @return		成功: 0; 文件不存在: 1;
 */
extern int loadSiteInfo(SiteInfoNode* head);

/**
 * @brief		删除 场地信息表 中的某个条目
 * @param		场地信息表头节点，场地ID
 * @note		注意：此函数目前不应被使用
 * @return		成功: 0; 场地未找到: 1;
 */
extern int deleteSiteInfo(SiteInfoNode* head, char strID[11]);

/**
 * @brief		根据场地ID取用场地信息结构体
 * @param		场地信息表头节点，场地ID
 * @note		*注意*：请先判断场地存在再调用，否则可能引起异常!!
 * @return		SiteInfo结构体对象
 */
SiteInfo querySiteInfo(SiteInfoNode* head, char strID[11]);

/**
 * @brief		根据场地ID编辑场地信息结构体
 * @param		场地信息表头节点，场地ID
 * @note		建议先用上面那个取用，取出来改完了塞回去。
 * @return		SiteInfo结构体对象
 */
extern int EditSiteInfo(SiteInfoNode* head, SiteInfo info);

/*========================= 预约信息表 操作函数 =========================*/

/**
 * @brief		向 预约信息表 新增一条数据
 * @param		预约信息表头节点，ApmtInfo结构体
 * @note		无
 * @return		成功: 0;
 */
//extern int InsertToApmtInfo(AppointmentInfoNode* head, ApmtInfo info);

/**
 * @brief		打印 预约信息表 中的数据
 * @param		预约信息表头节点
 * @note		此函数仅作调试时使用
 * @return		void;
 */
extern void printApmtInfo(AppointmentInfoNode* head);

/**
 * @brief		将内存中的 预约信息表 保存至文件
 * @param		预约信息表头节点
 * @note		无
 * @return		成功: 0; 失败: 1;
 */
extern int saveApmtInfo(AppointmentInfoNode* head);

/**
 * @brief		加载 预约信息表 至内存中
 * @param		预约信息表头节点
 * @note		文件不存在时，仍可在全新的头节点后运行数据存取，因此返回1时可不作异常处理
 * @return		成功: 0; 文件不存在: 1;
 */
extern int loadApmtInfo(AppointmentInfoNode* head);

/**
 * @brief		删除 预约信息表 中的某个条目
 * @param		预约信息表头节点，发起预约的用户ID，场地ID，预约开始时间
 * @note		无
 * @return		成功: 0; 未找到: 1;
 */
extern int deleteApmtInfo(AppointmentInfoNode* head, char strUsrID[11], char strSiteID[11], char strStartDate[11]);

/**
 * @brief		取用场地信息结构体
 * @param		场地信息表头节点，场地ID
 * @note		*注意*：请先判断场地存在再调用，否则可能引起异常!!
 * @return		SiteInfo结构体对象
 */
ApmtInfo queryApmtInfo(AppointmentInfoNode* head, char strUsrID[11], char strSiteID[11], char strStartDate[11]);

#endif // !__DATATOOLKIT_H
