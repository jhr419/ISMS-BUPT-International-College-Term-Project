#include "UserComponent.c"
extern char glb_adminID[11];
//==========================管理员注册流程函数===============================

void printAdminIcon(){
	printf("\033[0m\033[1;35m%s\033[0m", "    ___       __          _     \n");
	printf("\033[0m\033[1;35m%s\033[0m", "   /   | ____/ /___ ___  (_)___ \n");
	printf("\033[0m\033[1;35m%s\033[0m", "  / /| |/ __  / __ `__ \\/ / __ \\\n");
	printf("\033[0m\033[1;35m%s\033[0m", " / ___ / /_/ / / / / / / / / / /\n");
	printf("\033[0m\033[1;35m%s\033[0m", "/_/  |_\\__,_/_/ /_/ /_/_/_/ /_/ \n");
	printf("\033[0m\033[1;35m%s\033[0m", "                                \n");
	printf("\033[0m\033[1;35m%s\033[0m", "你好，管理员。\n");
}

void printStaffLeaderIcon(){
	printf("\033[0m\033[1;31m%s\033[0m", "   _____ __        ________   __                   __         \n");
	printf("\033[0m\033[1;31m%s\033[0m", "  / ___// /_____ _/ __/ __/  / /   ___  ____ _____/ /__  _____\n");
	printf("\033[0m\033[1;31m%s\033[0m", "  \\__ \\/ __/ __ `/ /_/ /_   / /   / _ \\/ __ `/ __  / _ \\/ ___/\n");
	printf("\033[0m\033[1;31m%s\033[0m", " ___/ / /_/ /_/ / __/ __/  / /___/  __/ /_/ / /_/ /  __/ /    \n");
	printf("\033[0m\033[1;31m%s\033[0m", "/____/\\__/\\__,_/_/ /_/    /_____/\\___/\\__,_/\\__,_/\\___/_/     \n");
	printf("\033[0m\033[1;31m%s\033[0m", "                                                              \n");
	printf("\033[0m\033[1;31m%s\033[0m", "正在以*主管*身份执行系统操作。\n");
}

BOOL doAdminRegisterCheck(BOOL valid_id, BOOL valid_name, BOOL valid_gender, BOOL valid_phone, BOOL valid_email, BOOL valid_pwd, BOOL valid_venue){
	if(valid_id && valid_name && valid_gender && valid_phone && valid_email && valid_pwd && valid_venue){
		return TRUE;
	}else{
		return FALSE;
	}
}

void print_admin_reg_status(BOOL valid_id, BOOL valid_name, BOOL valid_gender, BOOL valid_phone, BOOL valid_email, BOOL valid_pwd, BOOL valid_venue){
	char status_finished[128] = "\033[0m\033[1;32m[已完成]\033[0m";
	char status_need_fill[128] = "\033[0m\033[1;31m[待填写]\033[0m";
	char* status[2] = {status_need_fill, status_finished};
	printStaffLeaderIcon();
	printf("--------------------------------------------------\n");
	printf("%s 填写管理员ID，要求6-10位，全部由字母或数字组成\n", status[valid_id]);
	printf("%s 填写姓名，要求不得超长\n", status[valid_name]);
	printf("%s 填写性别，只需选择是男或女\n", status[valid_gender]);
	printf("%s 填写手机号，要求必须为11位，且以1开头\n", status[valid_phone]);
	printf("%s 填写电子邮箱地址，要求必须是有效的邮箱地址\n", status[valid_email]);
	printf("%s 填写密码，要求6-20位，只能包含字母、数字和符号\n", status[valid_pwd]);
	printf("%s 填写需管理的场馆名称\n", status[valid_venue]);
	printf("--------------------------------------------------\n");
}

int doAdminRegister(AdminInfoNode* head) {
	//注册进程的终端用户交互界面
	BOOL valid_id = FALSE, valid_name = FALSE, valid_gender = FALSE, valid_phone = FALSE, valid_email = FALSE, valid_pwd = FALSE, valid_venue = FALSE;
	char strID[12] = "";
	char strName[17] = "";
	char charGender = '3';
	char strPhone[13] = "";
	char strPwd[22] = "";
	char strEmail[42] = "";
	char strVenue[65] = "";
	int wrong_sl_pwd_times = 0;
	while(TRUE){
		system("cls");
		printStaffLeaderIcon();
		printf("--------------------------------------------------\n");
		printf("添加场馆，绑定管理员前需要\033[0m\033[1;33m校验主管身份\033[0m：\n\n");
		printf("\033[0m\033[1;35m[进行中]\033[0m %s", "请输入系统主管密码：");
		safegets(strPwd, 22);
		if(wrong_sl_pwd_times >= 3){
			printf("密码错误次数过多，程序自动返回上一级！");
			system("pause");
			return 1;
		}
		if(!isValidUserPwd(strPwd)){
			fflush(stdin);
			printf("输入不符合规范，本次尝试不计入错误次数，请重新输入！\n");
			system("pause");
			system("cls");
		}else if(strcmp(strPwd, "XIAOXUEQI") != 0){
			fflush(stdin);
			printf("密码错误！您还有 %d 次机会\n", 3 - wrong_sl_pwd_times);
			wrong_sl_pwd_times++;
			system("pause");
			system("cls");
		}else{
			fflush(stdin);
			system("cls");
			break;
		}
	}
	while(!doAdminRegisterCheck(valid_id, valid_name, valid_gender, valid_phone, valid_email, valid_pwd, valid_venue)){
		system("cls");
		if(!valid_id){
			while(!valid_id){
				print_admin_reg_status(valid_id, valid_name, valid_gender, valid_phone, valid_email, valid_pwd, valid_venue);
				printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入管理员ID；要求6-10位，全部由字母和数字组成：");
				safegets(strID, 12);
				if(isAdminExist(head, strID)){
					fflush(stdin);
					printf("此管理员ID已存在！");
					system("pause");
					system("cls");
				}else if(!isValidUserID(strID)){
					fflush(stdin);
					printf("输入不符合规范，请重新输入！");
					system("pause");
					system("cls");
				}else{
					valid_id = TRUE;
					fflush(stdin);
					system("cls");
				}
			}
		}else if(!valid_name){
			while(!valid_name){
				print_admin_reg_status(valid_id, valid_name, valid_gender, valid_phone, valid_email, valid_pwd, valid_venue);
				printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入姓名，要求不得超长：");
				safegets(strName, 17);
				if(!isValidUserName(strName)){
					fflush(stdin);
					printf("输入不符合规范，请重新输入！");
					system("pause");
					system("cls");
				}else{
					valid_name = TRUE;
					fflush(stdin);
					system("cls");
				}
			}
		}else if(!valid_gender){
			while(!valid_gender){
				print_admin_reg_status(valid_id, valid_name, valid_gender, valid_phone, valid_email, valid_pwd, valid_venue);
				printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请选择您的性别：按下0表示男性，按下1表示女性");
				charGender = getch();
				if(!isValidUserGender(charGender)){
					fflush(stdin);
					printf("输入不符合规范，请重新输入！");
					system("pause");
					system("cls");
				}else{
					valid_gender = TRUE;
					fflush(stdin);
					system("cls");
				}
			}
		}else if(!valid_phone){
			while(!valid_phone){
				print_admin_reg_status(valid_id, valid_name, valid_gender, valid_phone, valid_email, valid_pwd, valid_venue);
				printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入手机号，要求必须为11位，且以1开头：");
				safegets(strPhone, 13);
				if(!isValidUserPhone(strPhone)){
					fflush(stdin);
					printf("输入不符合规范，请重新输入！");
					system("pause");
					system("cls");
				}else{
					valid_phone = TRUE;
					fflush(stdin);
					system("cls");
				}
			}
		}else if(!valid_email){
			while(!valid_email){
				print_admin_reg_status(valid_id, valid_name, valid_gender, valid_phone, valid_email, valid_pwd, valid_venue);
				printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入电子邮箱地址，要求必须是有效的邮箱地址，且不得超过40位：");
				safegets(strEmail, 42);
				if(!isValidUserEmail(strEmail)){
					fflush(stdin);
					printf("输入不符合规范，请重新输入！");
					system("pause");
					system("cls");
				}else{
					valid_email = TRUE;
					fflush(stdin);
					system("cls");
				}
			}
		}else if(!valid_pwd){
			while(!valid_pwd){
				print_admin_reg_status(valid_id, valid_name, valid_gender, valid_phone, valid_email, valid_pwd, valid_venue);
				printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入密码，要求6-20位，只能包含字母、数字和符号：");
				safegets(strPwd, 22);
				if(!isValidUserPwd(strPwd)){
					fflush(stdin);
					printf("输入不符合规范，请重新输入！");
					system("pause");
					system("cls");
				}else{
					valid_pwd = TRUE;
					fflush(stdin);
					system("cls");
				}
			}
		}else if(!valid_venue){
			while(!valid_venue){
				print_admin_reg_status(valid_id, valid_name, valid_gender, valid_phone, valid_email, valid_pwd, valid_venue);
				printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入需要管理的场馆名称：");
				safegets(strVenue, 65);
				if(!isValidVenue(strVenue)){
					fflush(stdin);
					printf("输入超长，请重新输入！");
					system("pause");
					system("cls");
				}else{
					valid_venue = TRUE;
					fflush(stdin);
					system("cls");
				}
			}
		}
	}
	printStaffLeaderIcon();
	printf("\033[0m\033[1;32m%s\033[0m", "场馆管理员绑定完成！\n请牢记以下管理员信息：\n");
	printf("--------------------------------------------------\n");
	printf("管理员ID：\t%s\n", strID);
	printf("姓名：\t\t%s\n", strName);
	printf("性别：\t\t%d（0代表男，1代表女）\n", charGender - 48);
	printf("手机号：\t%s\n", strPhone);
	printf("电子邮箱：\t%s\n", strEmail);
	printf("密码：\t\t%s\n", strPwd);
	printf("管理场馆：\t%s\n", strVenue);
	printf("--------------------------------------------------\n");
	printf("正在进行管理员注册...\n");
	//开始构造结构体
	AdminInfo adminData = {
		.adminGender = charGender - 48,
	};
	strcpy(adminData.adminID, strID);
	strcpy(adminData.adminName, strName);
	strcpy(adminData.adminPhone, strPhone);
	strcpy(adminData.adminPwd, strPwd);
	strcpy(adminData.adminEmail, strEmail);
	strcpy(adminData.adminVenueID, strVenue);
	//写文件
	if(InsertToAdminInfo(head, adminData) == 0){
		printf("\033[0m\033[1;32m[成功]\033[0m %s", "管理员注册已成功完成！\n");
	}else{
		printf("\033[0m\033[1;31m[失败]\033[0m %s", "管理员注册失败！原因：使用了未经检查的数据！\n");
	}
	system("pause");
	saveAdminInfo(head);
	return 0;
}

//==========================登录流程函数===============================

BOOL doAdminLoginCheck(BOOL valid_id, BOOL valid_pwd){
	if(valid_id && valid_pwd){
		return TRUE;
	}else{
		return FALSE;
	}
}

void print_admin_login_status(BOOL valid_id, BOOL valid_pwd){
	char status_finished[128] = "\033[0m\033[1;32m[已完成]\033[0m";
	char status_need_fill[128] = "\033[0m\033[1;31m[待填写]\033[0m";
	char* status[2] = {status_need_fill, status_finished};
	printAdminIcon();
	printf("--------------------------------------------------\n");
	printf("%s 填写管理员ID，要求6-10位，全部由字母或数字组成\n", status[valid_id]);
	printf("%s 填写密码，要求6-20位，只能包含字母、数字和符号\n", status[valid_pwd]);
	printf("--------------------------------------------------\n");
}

int doAdminLogin(AdminInfoNode* head) {
	//登录进程的终端用户交互界面
	BOOL valid_id = FALSE, valid_pwd = FALSE;
	BOOL matched = FALSE;
	int wrong_pwd_times = 0;
	//使用全局变量glb_usrID[11]来保存用户ID
	char strPwd[22] = "";
	while(!doAdminLoginCheck(valid_id, valid_pwd) || !matched){
		system("cls");
		if(!valid_id){
			while(!valid_id){
				print_admin_login_status(valid_id, valid_pwd);
				printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入管理员ID；要求6-10位，全部由字母和数字组成：");
				safegets(glb_adminID, 12);
				if(!isValidUserID(glb_adminID)){
					fflush(stdin);
					printf("输入不符合规范，请重新输入！");
					system("pause");
					system("cls");
				}else{
					valid_id = TRUE;
					fflush(stdin);
					system("cls");
				}
			}
		}else if(!valid_pwd){
			while(!valid_pwd){
				AdminInfo lgAdminInfo = queryAdminInfo(head, glb_adminID);
				char lgAdminPwd[21];
				strcpy(lgAdminPwd, lgAdminInfo.adminPwd); 
				print_admin_login_status(valid_id, valid_pwd);
				printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入密码，要求6-20位，只能包含字母、数字和符号：");
				safegets(strPwd, 22);
				if(wrong_pwd_times >= 5){
					printf("密码错误次数过多，程序自动返回管理员主菜单！");
					system("pause");
					return 1;
				}
				if(!isValidUserPwd(strPwd)){
					fflush(stdin);
					printf("输入不符合规范，本次尝试不计入错误次数，请重新输入！\n");
					system("pause");
					system("cls");
				}else if(!isAdminExist(head, glb_adminID)){
					fflush(stdin);
					printf("管理员不存在，请重新输入！您还有 %d 次机会\n", 5 - wrong_pwd_times);
					valid_id = FALSE;
					wrong_pwd_times++;
					system("pause");
					system("cls");
					break;
				}
				else if(strcmp(strPwd, lgAdminPwd) != 0){
					fflush(stdin);
					printf("密码错误！您还有 %d 次机会\n", 5 - wrong_pwd_times);
					wrong_pwd_times++;
					system("pause");
					system("cls");
				}else{
					valid_pwd = TRUE;
					matched = TRUE;
					fflush(stdin);
					system("cls");
					return 0;
				}
			}
		}
	}
	return 0;
}

//=====================管理员个人信息流程函数==========================

void printCurrentAdminInfo(AdminInfoNode* head) {
	AdminInfo crAdminInfo = queryAdminInfo(head, glb_adminID);
	printf("--------------------------------------------------\n");
	printf("\033[0m\033[1;31m[x>]\033[0m 管理ID：\t%s\n", glb_adminID);
	printf("\033[0m\033[1;31m[x>]\033[0m 姓名：\t%s\n", crAdminInfo.adminName);
	printf("\033[0m\033[1;31m[x>]\033[0m 性别：\t%d（0代表男，1代表女）\n", crAdminInfo.adminGender);
	printf("\033[0m\033[1;32m[0>]\033[0m 手机号：\t%s\n", crAdminInfo.adminPhone);
	printf("\033[0m\033[1;32m[1>]\033[0m 电子邮箱：\t%s\n", crAdminInfo.adminEmail);
	printf("\033[0m\033[1;32m[2>]\033[0m 密码：\t%s\n", crAdminInfo.adminPwd);
	printf("\033[0m\033[1;31m[x>]\033[0m 管理场馆：\t%s\n", crAdminInfo.adminVenueID);
	printf("--------------------------------------------------\n");
}

int doAdminInfoEdit(AdminInfoNode* head){
	AdminInfo lgAdminInfo = queryAdminInfo(head, glb_adminID);
	char lgAdminPwd[21];
	char strPwd[22];
	int wrong_pwd_times = 0;
	strcpy(lgAdminPwd, lgAdminInfo.adminPwd); 
	while(TRUE){
		system("cls");
		printAdminIcon();
		printf("--------------------------------------------------\n");
		printf("修改个人信息前需要\033[0m\033[1;33m再次校验账户密码\033[0m：\n\n");
		printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入密码，要求6-20位，只能包含字母、数字和符号：");
		safegets(strPwd, 22);
		if(wrong_pwd_times >= 5){
			printf("密码错误次数过多，程序自动返回上一级！");
			system("pause");
			return 1;
		}
		if(!isValidUserPwd(strPwd)){
			fflush(stdin);
			printf("输入不符合规范，本次尝试不计入错误次数，请重新输入！\n");
			system("pause");
			system("cls");
		}else if(strcmp(strPwd, lgAdminPwd) != 0){
			fflush(stdin);
			printf("密码错误！您还有 %d 次机会\n", 5 - wrong_pwd_times);
			wrong_pwd_times++;
			system("pause");
			system("cls");
		}else{
			fflush(stdin);
			system("cls");
			break;
		}
	}
	while(TRUE){
		system("cls");
		printAdminIcon();
		printf("--------------------------------------------------\n");
		printf("您\033[0m\033[1;33m当前的\033[0m管理员信息如下：\n");
		printCurrentAdminInfo(head);
		printf("\n带有红色\033[0m\033[1;31m[x>]\033[0m的信息为管理员生理、标识和管理信息，不允许修改。\n");
		printf("带有绿色\033[0m\033[1;32m[数字>]\033[0m的信息可以修改。\n");
		printf("如需修改管理员个人信息，请按下需要修改的信息项前\033[0m\033[1;32m[数字>]\033[0m中的数字按键\n");
		printf("按下\033[0m\033[1;33m[ESC]\033[0m键完成修改并返回上一级\n");
		char ch_edit_item = getch();
		if (ch_edit_item == 27) {
			fflush(stdin);
			system("cls");
			return 0;
		} else if (ch_edit_item == '0') {
			char strPhone[13];
			fflush(stdin);
			system("cls");
			while(TRUE){
				printAdminIcon();
				printf("--------------------------------------------------\n");
				printf("修改您保存在系统中的手机号。\n\n");
				printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入\033[0m\033[1;33m新的\033[0m手机号，要求必须为11位，且以1开头：");
				safegets(strPhone, 13);
				if(!isValidUserPhone(strPhone)){
					fflush(stdin);
					printf("输入不符合规范，请重新输入！");
					system("pause");
					system("cls");
				}else{
					strcpy(lgAdminInfo.adminPhone, strPhone); 
					EditAdminInfo(head, lgAdminInfo);
					saveAdminInfo(head);
					fflush(stdin);
					printf("修改成功！");
					system("pause");
					system("cls");
					break;
				}
			}
		} else if (ch_edit_item == '1') {
			char strEmail[42];
			fflush(stdin);
			system("cls");
			while(TRUE){
				printAdminIcon();
				printf("--------------------------------------------------\n");
				printf("修改您保存在系统中的电子邮箱。\n\n");
				printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入\033[0m\033[1;33m新的\033[0m电子邮箱，要求必须为有效的电子邮箱地址，且不得超过40位：");
				safegets(strEmail, 42);
				if(!isValidUserEmail(strEmail)){
					fflush(stdin);
					printf("输入不符合规范，请重新输入！");
					system("pause");
					system("cls");
				}else{
					strcpy(lgAdminInfo.adminEmail, strEmail); 
					EditAdminInfo(head, lgAdminInfo);
					saveAdminInfo(head);
					fflush(stdin);
					printf("修改成功！");
					system("pause");
					system("cls");
					break;
				}
			}
		} else if (ch_edit_item == '2') {
			char strPwd[22];
			fflush(stdin);
			system("cls");
			while(TRUE){
				printAdminIcon();
				printf("--------------------------------------------------\n");
				printf("修改您保存在系统中的密码。\n\n");
				printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入\033[0m\033[1;33m新的\033[0m密码，要求6-20位，只能包含字母、数字和符号：");
				safegets(strPwd, 22);
				if(!isValidUserPwd(strPwd)){
					fflush(stdin);
					printf("输入不符合规范，请重新输入！");
					system("pause");
					system("cls");
				}else{
					strcpy(lgAdminInfo.adminPwd, strPwd); 
					EditAdminInfo(head, lgAdminInfo);
					saveAdminInfo(head);
					fflush(stdin);
					printf("修改成功！");
					system("pause");
					system("cls");
					break;
				}
			}
		} else {
			fflush(stdin);
			printf("输入有误哦，请重新输入！\n");
			system("pause");
			system("cls");
		}
	}
	return 0;
}

//=====================管理员管理场地流程函数==========================

void printCurrentVenueSiteInfo(SiteInfoNode* sitehead, AdminInfoNode* adminhead) {
	//根据当前管理员获取到其管理的场馆名称
	AdminInfo crAdminInfo = queryAdminInfo(adminhead, glb_adminID);
	char crVenue[65];
	strcpy(crVenue, crAdminInfo.adminVenueID);
	
	SiteInfoNode* move = sitehead->next;
	int cr_venue_has_site_num = 0;
	printf("--------------------------------------------------\n");
	while (move != NULL) {
		if(strcmp(crVenue, move->siteInfo.siteVenueID) == 0){
			printf("场地ID:%s 名称:%s 准入年龄:%d 运动类型:%s\n", move->siteInfo.siteID, move->siteInfo.siteName, move->siteInfo.siteAllowedAgeMin, move->siteInfo.siteSportsType);
			cr_venue_has_site_num++;
		}
		move = move->next;
	}
	if(cr_venue_has_site_num == 0){
		printf("\033[0m\033[1;31m您当前管理的场馆没有任何场地！\033[0m \n");
	}
	printf("--------------------------------------------------\n");
}

BOOL doAdminAddSiteCheck(BOOL valid_id, BOOL valid_name, BOOL valid_location, BOOL valid_sports_type, BOOL valid_intro, BOOL valid_rent, BOOL valid_agemin, BOOL valid_agemax){
	if(valid_id && valid_name && valid_location && valid_sports_type && valid_intro && valid_rent && valid_agemin && valid_agemax){
		return TRUE;
	}else{
		return FALSE;
	}
}

void print_admin_add_site_status(BOOL valid_id, BOOL valid_name, BOOL valid_location, BOOL valid_sports_type, BOOL valid_intro, BOOL valid_rent, BOOL valid_agemin, BOOL valid_agemax){
	char status_finished[128] = "\033[0m\033[1;32m[已完成]\033[0m";
	char status_need_fill[128] = "\033[0m\033[1;31m[待填写]\033[0m";
	char* status[2] = {status_need_fill, status_finished};
	printAdminIcon();
	printf("--------------------------------------------------\n");
	printf("%s 填写场馆ID，要求6-10位，全部由字母或数字组成\n", status[valid_id]);
	printf("%s 填写场馆名称，要求不得超长\n", status[valid_name]);
	printf("%s 填写场地地理位置，要求不得超长\n", status[valid_location]);
	printf("%s 填写场地运动类型，要求不得超长\n", status[valid_sports_type]);
	printf("%s 填写场地简介，要求不得超长\n", status[valid_intro]);
	printf("%s 填写场地每小时租金，要求为1.00-200.00的浮点数\n", status[valid_rent]);
	printf("%s 填写场地最小准入年龄，要求为1-99岁的整数\n", status[valid_agemin]);
	printf("%s 填写场地最大准入年龄，要求为1-100岁的整数，且不得小于最小准入年龄\n", status[valid_agemax]);
	printf("--------------------------------------------------\n");
}

int doAddSite(SiteInfoNode* sitehead, AdminInfoNode* adminhead) {
	//添加场地进程的终端用户交互界面
	
	AdminInfo crAdmin = queryAdminInfo(adminhead, glb_adminID);
	BOOL valid_id = FALSE, valid_name = FALSE, valid_location = FALSE, valid_sports_type = FALSE, valid_intro = FALSE, valid_rent = FALSE, valid_agemin = FALSE, valid_agemax = FALSE;
	char strID[12] = "";
	char strName[66] = "";
	char strLocation[257] = "";
	
	char strVenue[66];
	strcpy(strVenue, crAdmin.adminVenueID);
	
	char strSportsType[66] = "";
	char strIntro[257] = "";

	char strInputRent[7] = "";
	
	char strInputMinAge[6] = "";
	
	char strInputMaxAge[6] = "";
	
	int intUsedTimes = 0;
	
	while(!doAdminAddSiteCheck(valid_id, valid_name, valid_location, valid_sports_type, valid_intro, valid_rent, valid_agemin, valid_agemax)){
		system("cls");
		if(!valid_id){
			while(!valid_id){
				print_admin_add_site_status(valid_id, valid_name, valid_location, valid_sports_type, valid_intro, valid_rent, valid_agemin, valid_agemax);
				printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入场地ID；要求6-10位，全部由字母和数字组成：");
				safegets(strID, 12);
				if(isSiteExist(sitehead, strID)){
					fflush(stdin);
					printf("此场地ID已存在！");
					system("pause");
					system("cls");
				}else if(!isValidUserID(strID)){
					fflush(stdin);
					printf("输入不符合规范，请重新输入！");
					system("pause");
					system("cls");
				}else{
					valid_id = TRUE;
					fflush(stdin);
					system("cls");
				}
			}
		}else if(!valid_name){
			while(!valid_name){
				print_admin_add_site_status(valid_id, valid_name, valid_location, valid_sports_type, valid_intro, valid_rent, valid_agemin, valid_agemax);
				printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入场地名称，要求不得超长：");
				safegets(strName, 66);
				if(!isValidVenue(strName)){
					fflush(stdin);
					printf("输入不符合规范，请重新输入！");
					system("pause");
					system("cls");
				}else{
					valid_name = TRUE;
					fflush(stdin);
					system("cls");
				}
			}
		}else if(!valid_location){
			while(!valid_location){
				print_admin_add_site_status(valid_id, valid_name, valid_location, valid_sports_type, valid_intro, valid_rent, valid_agemin, valid_agemax);
				printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入场地位置，要求不得超长");
				safegets(strLocation, 257);
				if(!isValidUserLocation(strLocation)){
					fflush(stdin);
					printf("输入不符合规范，请重新输入！");
					system("pause");
					system("cls");
				}else{
					valid_location = TRUE;
					fflush(stdin);
					system("cls");
				}
			}
		}else if(!valid_sports_type){
			while(!valid_sports_type){
				print_admin_add_site_status(valid_id, valid_name, valid_location, valid_sports_type, valid_intro, valid_rent, valid_agemin, valid_agemax);
				printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入场地的运动类型，要求不得超长：");
				safegets(strSportsType, 66);
				if(!isValidVenue(strSportsType)){
					fflush(stdin);
					printf("输入不符合规范，请重新输入！");
					system("pause");
					system("cls");
				}else{
					valid_sports_type = TRUE;
					fflush(stdin);
					system("cls");
				}
			}
		}else if(!valid_intro){
			while(!valid_intro){
				print_admin_add_site_status(valid_id, valid_name, valid_location, valid_sports_type, valid_intro, valid_rent, valid_agemin, valid_agemax);
				printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入场地简介，要求不得超长：");
				safegets(strIntro, 257);
				if(!isValidUserLocation(strIntro)){
					fflush(stdin);
					printf("输入不符合规范，请重新输入！");
					system("pause");
					system("cls");
				}else{
					valid_intro = TRUE;
					fflush(stdin);
					system("cls");
				}
			}
		}else if(!valid_rent){
			while(!valid_rent){
				print_admin_add_site_status(valid_id, valid_name, valid_location, valid_sports_type, valid_intro, valid_rent, valid_agemin, valid_agemax);
				printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入场地每小时租金，要求为1.00-200.00的小数，且小数点后只允许有两位数字：");
				safegets(strInputRent, 7);
				if(!isValidDoubleNumStr(strInputRent)){
					fflush(stdin);
					printf("输入不符合规范，请重新输入！");
					system("pause");
					system("cls");
				}else{
					valid_rent = TRUE;
					fflush(stdin);
					system("cls");
				}
			}
		}else if(!valid_agemin){
			while(!valid_agemin){
				print_admin_add_site_status(valid_id, valid_name, valid_location, valid_sports_type, valid_intro, valid_rent, valid_agemin, valid_agemax);
				printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入场馆准入的最小年龄，要求为1-99岁的整数：");
				safegets(strInputMinAge, 6);
				if(!isValidMinAge(strInputMinAge)){
					fflush(stdin);
					printf("输入不符合规范，请重新输入！");
					system("pause");
					system("cls");
				}else{
					valid_agemin = TRUE;
					fflush(stdin);
					system("cls");
				}
			}
		}else if(!valid_agemax){
			while(!valid_agemax){
				print_admin_add_site_status(valid_id, valid_name, valid_location, valid_sports_type, valid_intro, valid_rent, valid_agemin, valid_agemax);
				printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入场馆准入的最大年龄，要求为1-100岁的整数，且不得小于最小准入年龄：");
				safegets(strInputMaxAge, 6);
				if(!isValidUserAge(strInputMaxAge)){
					fflush(stdin);
					printf("输入不符合规范，请重新输入！");
					system("pause");
					system("cls");
				}else if(atoi(strInputMaxAge) < atoi(strInputMinAge)){
					fflush(stdin);
					printf("最大准入年龄不得小于最小准入年龄！");
					system("pause");
					system("cls");
				}else{
					valid_agemax = TRUE;
					fflush(stdin);
					system("cls");
				}
			}
		}
	}
	printAdminIcon();
	printf("\033[0m\033[1;32m%s\033[0m", "场地创建成功！\n以下为刚刚输入的场地信息：\n");
	printf("--------------------------------------------------\n");
	printf("场地ID：\t%s\n", strID);
	printf("场地名称：\t%s\n", strName);
	printf("场地位置：\t%s\n", strLocation);
	printf("运动类型：\t%s\n", strSportsType);
	printf("场地简介：\t%s\n", strIntro);
	printf("租金：\t\t%s\n", strInputRent);
	printf("最小年龄：\t%s\n", strInputMinAge);
	printf("最大年龄：\t%s\n", strInputMaxAge);
	printf("--------------------------------------------------\n");
	printf("以下场地已定信息也会被一同录入：\n");
	printf("所属场馆：\t%s\n", strVenue);
	printf("使用次数：\t%d\n", intUsedTimes);
	printf("--------------------------------------------------\n");
	printf("正在进行场地新建...\n");
	//开始构造结构体
	SiteInfo siteData = {
		.siteAllowedAgeMin = atoi(strInputMinAge),
		.siteAllowedAgeMax = atoi(strInputMaxAge),
		.siteUsedTimes = intUsedTimes,
		.siteRent = strtod(strInputRent, NULL),
	};
	strcpy(siteData.siteID, strID);
	strcpy(siteData.siteName, strName);
	strcpy(siteData.siteLocation, strLocation);
	strcpy(siteData.siteVenueID, strVenue);
	strcpy(siteData.siteSportsType, strSportsType);
	strcpy(siteData.siteIntro, strIntro);
	//写文件
	if(InsertToSiteInfo(sitehead, siteData) == 0){
		printf("\033[0m\033[1;32m[成功]\033[0m %s", "场地新建已成功完成！\n");
	}else{
		printf("\033[0m\033[1;31m[失败]\033[0m %s", "场地新建失败！原因：使用了未经检查的数据！\n");
	}
	saveSiteInfo(sitehead);
	system("pause");
	return 0;
}

int doAdminAddSite(SiteInfoNode* sitehead, AdminInfoNode* adminhead) {
	AdminInfo lgAdmin = queryAdminInfo(adminhead, glb_adminID);
	while(TRUE){
		system("cls");
		printAdminIcon();
		printf("--------------------------------------------------\n");
		printf("当前管理员 %s（ID：%s）\n管理的场馆名称为：\033[0m\033[1;33m%s\033[0m\n", lgAdmin.adminName, glb_adminID, lgAdmin.adminVenueID);
		printf("在此场馆中，所有场地信息查询如下：\n");
		printCurrentVenueSiteInfo(sitehead, adminhead);
		printf("按 0 可在此场馆中 \033[0m\033[1;34m[添加新的场地]\033[0m。\n");
		printf("按 ESC \033[0m\033[1;31m[返回上一级]\033[0m\n");
		char ch_admin_add_site = getch();
		if(ch_admin_add_site == 27){
			fflush(stdin);
			system("cls");
			return 0;
		}else if(ch_admin_add_site == '0'){
			system("cls");
			doAddSite(sitehead, adminhead);
		}else{
			fflush(stdin);
			printf("输入有误哦，请重新输入！\n");
			system("pause");
			system("cls");
		}
	}
	return 0;
}

//=====================管理员查看预定流程函数==========================

void printAdminVenueApmt(SiteInfoNode* sitehead, AdminInfoNode* adminhead, AppointmentInfoNode* apmthead){
	AdminInfo amifo = queryAdminInfo(adminhead, glb_adminID);
	AppointmentInfoNode* move = apmthead->next;
	int num = 0;
	while (move != NULL) {
		SiteInfo stifo = querySiteInfo(sitehead, move->apmtInfo.apmtSiteID);
		if(strcmp(stifo.siteVenueID, amifo.adminVenueID) == 0){
			num++;
			printf("预约场地：%s 预约用户：%s 预约开始时间：%s 预约持续时长：%d\n", move->apmtInfo.apmtSiteID, move->apmtInfo.apmtUsrID, move->apmtInfo.apmtStartDateh, move->apmtInfo.apmtDurationh);
		}
		move = move->next;
	}
	if(num == 0){
		printf("当前管理的场馆没有任何预定\n");
	}
}

int doAdminStatistics(SiteInfoNode* sitehead, AdminInfoNode* adminhead, AppointmentInfoNode* apmthead, UserInfoNode* userhead){
	AdminInfo lgAdmin = queryAdminInfo(adminhead, glb_adminID);
	while(TRUE){
		system("cls");
		printAdminIcon();
		printf("--------------------------------------------------\n");
		printf("当前管理员 %s（ID：%s）\n管理的场馆名称为：\033[0m\033[1;33m%s\033[0m\n", lgAdmin.adminName, glb_adminID, lgAdmin.adminVenueID);
		printf("按 0 查看 \033[0m\033[1;34m[按预定量排序]\033[0m。\n");
		printf("按 1 查看 \033[0m\033[1;34m[热门预约时间统计]\033[0m。\n");
		printf("按 2 查看 \033[0m\033[1;34m[场馆总营业额]\033[0m。\n");
		printf("按 3 查看 \033[0m\033[1;34m[场地年龄层次]\033[0m。\n");
		printf("按 4 查看 \033[0m\033[1;34m[按营业额排序]\033[0m。\n");
		printf("按 5 查看 \033[0m\033[1;34m[男士最爱运动]\033[0m。\n");
		printf("按 6 查看 \033[0m\033[1;34m[女士最爱运动]\033[0m。\n");
		printf("按 7 查看 \033[0m\033[1;34m[场地均利用率]\033[0m。\n");
		printf("按 ESC \033[0m\033[1;31m[返回上一级]\033[0m\n");
		char ch_admin_see_stc = getch();
		if(ch_admin_see_stc == 27){
			fflush(stdin);
			system("cls");
			return 0;
		}else if(ch_admin_see_stc == '0'){
			system("cls");
			printAdminIcon();
			printf("--------------------------------------------------\n");
			printf("针对当前场馆，按照预定量排序的结果如下：\n");
			SiteInfoNode* move = sitehead->next;
			AdminInfo lgAdmin = queryAdminInfo(adminhead, glb_adminID);
			int num = 0;
			while (move != NULL) {
				if(strcmp(move->siteInfo.siteVenueID, lgAdmin.adminVenueID) == 0){
					num++;
				}
				move = move->next;
			}
			const int SITE_NUM = num;
			
			char IDArray[SITE_NUM][11];
			move = sitehead->next;
			num = 0;
			while (move != NULL) {
				if(strcmp(move->siteInfo.siteVenueID, lgAdmin.adminVenueID) == 0){
					strcpy(IDArray[num], move->siteInfo.siteID);
					num++;
				}
				move = move->next;
			}
			
			for (int i = 1; i <= SITE_NUM - 1; i++)
			{
				for (int j = 0; j <= SITE_NUM - 1 - i; j++)
				{
					SiteInfo site_j = querySiteInfo(sitehead, IDArray[j]);
					SiteInfo site_j_add1 = querySiteInfo(sitehead, IDArray[j+1]);
					if (site_j.siteUsedTimes > site_j_add1.siteUsedTimes)//相邻两个元素的预定量如果逆序，则交换位置
					{
						char temp[11];
						strcpy(temp, IDArray[j]);
						strcpy(IDArray[j], IDArray[j + 1]);
						strcpy(IDArray[j + 1], temp);
					}
				}
			}
			for(int i=SITE_NUM-1;i>=0;i--){
				SiteInfo site_i = querySiteInfo(sitehead, IDArray[i]);
				printf("场地ID：%s 场地名称：%s 场地预定量：%d\n", site_i.siteID, site_i.siteName, site_i.siteUsedTimes);
			}
			system("pause");
			system("cls");
		}else if(ch_admin_see_stc == '1'){
			system("cls");
			printAdminIcon();
			printf("--------------------------------------------------\n");
			printf("场馆中场地的热门预约时间分别为：\n");
			SiteInfoNode* sitemove = sitehead->next;
			while (sitemove != NULL) {
				AppointmentInfoNode* apmtmove = apmthead->next;
				char stasHour[128];
				int stasi = 0;
				while (apmtmove != NULL) {
					if (strcmp(apmtmove->apmtInfo.apmtSiteID, sitemove->siteInfo.siteID) == 0) {
						int hh = (apmtmove->apmtInfo.apmtStartDateh[8] - '0') * 10 + (apmtmove->apmtInfo.apmtStartDateh[9]-'0') * 1;
						char hc = hh+'0';
						stasHour[stasi] = hc;
						stasi++;
						stasHour[stasi] = '\0';
					}
					apmtmove = apmtmove->next;
				}
				int count[256] = {0};
				for(int i=0; stasHour[i]; i++) count[stasHour[i]]++;
				
				int max = -1;
				char c = 0;
				for(int i=0; i<256; i++){
					if(count[i] > max){
						max = count[i];
						c = (char)i;
					}
				}
				if(stasi != 0)printf("ID为%s的场馆最热门的预约时间是：%d点\n", sitemove->siteInfo.siteID, c - '0');
				else printf("ID为%s的场馆从未被预约过\n", sitemove->siteInfo.siteID);
				sitemove = sitemove->next;
			}
			system("pause");
			system("cls");
		}else if(ch_admin_see_stc == '2'){
			system("cls");
			printAdminIcon();
			printf("--------------------------------------------------\n");
			AppointmentInfoNode* move = apmthead->next;
			AdminInfo lgAdmin = queryAdminInfo(adminhead, glb_adminID);
			double tam = 0.00;
			while (move != NULL) {
				SiteInfo stifo = querySiteInfo(sitehead, move->apmtInfo.apmtSiteID);
				if(strcmp(stifo.siteVenueID, lgAdmin.adminVenueID) == 0){
					tam = tam + stifo.siteRent * move->apmtInfo.apmtDurationh;
				}
				move = move->next;
			}
			printf("当前管理场馆的总营业额为：%.2lf元\n", tam);
			system("pause");
			system("cls");
		}else if(ch_admin_see_stc == '3'){
			system("cls");
			printAdminIcon();
			printf("--------------------------------------------------\n");
			printf("场馆中场地的年龄层次分布为：\n");
			SiteInfoNode* sitemove = sitehead->next;
			while (sitemove != NULL) {
				AppointmentInfoNode* apmtmove = apmthead->next;
				int shaonian = 0;
				int qingnian = 0;
				int zhongnian = 0;
				int laonian = 0;
				while (apmtmove != NULL) {
					if (strcmp(apmtmove->apmtInfo.apmtSiteID, sitemove->siteInfo.siteID) == 0) {
						UserInfo usifo =queryUserInfo(userhead, apmtmove->apmtInfo.apmtUsrID);
						if(usifo.usrAge < 15) shaonian ++;
						if(usifo.usrAge > 14 && usifo.usrAge < 36) qingnian++;
						if(usifo.usrAge > 35 && usifo.usrAge < 66) zhongnian++;
						if(usifo.usrAge > 65) laonian ++;
					}
					apmtmove = apmtmove->next;
				}
				if(shaonian == 0 && qingnian == 0 && zhongnian == 0 && laonian == 0) printf("ID为%s的场馆从未被预约过\n", sitemove->siteInfo.siteID);
				else printf("ID为%s的场馆的年龄层次为：少年(1-14)%d人，青年(14-35)%d人，中年(35-65)%d人，老年(65+)%d人。\n", sitemove->siteInfo.siteID, shaonian, qingnian, zhongnian, laonian);
				sitemove = sitemove->next;
			}
			system("pause");
			system("cls");
		}else if(ch_admin_see_stc == '4'){
			system("cls");
			printAdminIcon();
			printf("--------------------------------------------------\n");
			printf("针对当前场馆，按照营业额排序的结果如下：\n");
			SiteInfoNode* move = sitehead->next;
			AdminInfo lgAdmin = queryAdminInfo(adminhead, glb_adminID);
			int num = 0;
			while (move != NULL) {
				if(strcmp(move->siteInfo.siteVenueID, lgAdmin.adminVenueID) == 0){
					num++;
				}
				move = move->next;
			}
			const int SITE_NUM = num;
			
			char IDArray[SITE_NUM][11];
			move = sitehead->next;
			num = 0;
			while (move != NULL) {
				if(strcmp(move->siteInfo.siteVenueID, lgAdmin.adminVenueID) == 0){
					strcpy(IDArray[num], move->siteInfo.siteID);
					num++;
				}
				move = move->next;
			}
			
			for (int i = 1; i <= SITE_NUM - 1; i++)
			{
				for (int j = 0; j <= SITE_NUM - 1 - i; j++)
				{
					SiteInfo site_j = querySiteInfo(sitehead, IDArray[j]);
					SiteInfo site_j_add1 = querySiteInfo(sitehead, IDArray[j+1]);
					double money_j = 0.00, money_j_add1 = 0.00;
					AppointmentInfoNode* move = apmthead->next;
					while (move != NULL) {
						if(strcmp(site_j.siteID, move->apmtInfo.apmtSiteID) == 0){
							money_j = money_j + site_j.siteRent * move->apmtInfo.apmtDurationh;
						}
						if(strcmp(site_j_add1.siteID, move->apmtInfo.apmtSiteID) == 0){
							money_j_add1 = money_j_add1 + site_j_add1.siteRent * move->apmtInfo.apmtDurationh;
						}
						move = move->next;
					}
					if (money_j > money_j_add1)//相邻两个元素的营业额如果逆序，则交换位置
					{
						char temp[11];
						strcpy(temp, IDArray[j]);
						strcpy(IDArray[j], IDArray[j + 1]);
						strcpy(IDArray[j + 1], temp);
					}
				}
			}
			for(int i=SITE_NUM-1;i>=0;i--){
				SiteInfo site_i = querySiteInfo(sitehead, IDArray[i]);
				double money_i = 0.00;
				AppointmentInfoNode* move = apmthead->next;
				while (move != NULL) {
					if(strcmp(site_i.siteID, move->apmtInfo.apmtSiteID) == 0){
						money_i = money_i + site_i.siteRent * move->apmtInfo.apmtDurationh;
					}
					move = move->next;
				}
				printf("场地ID：%s 场地名称：%s 场地营业额：%.2lf\n", site_i.siteID, site_i.siteName, money_i);
			}
			system("pause");
			system("cls");
		}else if(ch_admin_see_stc == '5'){
			system("cls");
			printAdminIcon();
			printf("--------------------------------------------------\n");
			printf("当前场馆中，最受男性欢迎的运动是：\n");
			SiteInfoNode* move = sitehead->next;
			AdminInfo lgAdmin = queryAdminInfo(adminhead, glb_adminID);
			int num = 0;
			while (move != NULL) {
				if(strcmp(move->siteInfo.siteVenueID, lgAdmin.adminVenueID) == 0){
					num++;
				}
				move = move->next;
			}
			const int SITE_NUM = num;
			
			char IDArray[SITE_NUM][11];
			move = sitehead->next;
			num = 0;
			while (move != NULL) {
				if(strcmp(move->siteInfo.siteVenueID, lgAdmin.adminVenueID) == 0){
					strcpy(IDArray[num], move->siteInfo.siteID);
					num++;
				}
				move = move->next;
			}
			
			for (int i = 1; i <= SITE_NUM - 1; i++)
			{
				for (int j = 0; j <= SITE_NUM - 1 - i; j++)
				{
					SiteInfo site_j = querySiteInfo(sitehead, IDArray[j]);
					SiteInfo site_j_add1 = querySiteInfo(sitehead, IDArray[j+1]);
					int male_use_j = 0, male_use_j_add1 = 0;
					AppointmentInfoNode* move = apmthead->next;
					while (move != NULL) {
						if(strcmp(site_j.siteID, move->apmtInfo.apmtSiteID) == 0 && move->apmtInfo.apmtUsrGender == 0){
							male_use_j++;
						}
						if(strcmp(site_j_add1.siteID, move->apmtInfo.apmtSiteID) == 0 && move->apmtInfo.apmtUsrGender == 0){
							male_use_j_add1++;
						}
						move = move->next;
					}
					if (male_use_j > male_use_j_add1)//相邻两个元素的营业额如果逆序，则交换位置
					{
						char temp[11];
						strcpy(temp, IDArray[j]);
						strcpy(IDArray[j], IDArray[j + 1]);
						strcpy(IDArray[j + 1], temp);
					}
				}
			}
			SiteInfo site_i = querySiteInfo(sitehead, IDArray[SITE_NUM-1]);
			printf("%s\n", site_i.siteSportsType);
			system("pause");
			system("cls");
		}else if(ch_admin_see_stc == '6'){
			system("cls");
			printAdminIcon();
			printf("--------------------------------------------------\n");
			printf("当前场馆中，最受女性欢迎的运动是：\n");
			SiteInfoNode* move = sitehead->next;
			AdminInfo lgAdmin = queryAdminInfo(adminhead, glb_adminID);
			int num = 0;
			while (move != NULL) {
				if(strcmp(move->siteInfo.siteVenueID, lgAdmin.adminVenueID) == 0){
					num++;
				}
				move = move->next;
			}
			const int SITE_NUM = num;
			
			char IDArray[SITE_NUM][11];
			move = sitehead->next;
			num = 0;
			while (move != NULL) {
				if(strcmp(move->siteInfo.siteVenueID, lgAdmin.adminVenueID) == 0){
					strcpy(IDArray[num], move->siteInfo.siteID);
					num++;
				}
				move = move->next;
			}
			
			for (int i = 1; i <= SITE_NUM - 1; i++)
			{
				for (int j = 0; j <= SITE_NUM - 1 - i; j++)
				{
					SiteInfo site_j = querySiteInfo(sitehead, IDArray[j]);
					SiteInfo site_j_add1 = querySiteInfo(sitehead, IDArray[j+1]);
					int female_use_j = 0, female_use_j_add1 = 0;
					AppointmentInfoNode* move = apmthead->next;
					while (move != NULL) {
						if(strcmp(site_j.siteID, move->apmtInfo.apmtSiteID) == 0 && move->apmtInfo.apmtUsrGender == 1){
							female_use_j++;
						}
						if(strcmp(site_j_add1.siteID, move->apmtInfo.apmtSiteID) == 0 && move->apmtInfo.apmtUsrGender == 1){
							female_use_j_add1++;
						}
						move = move->next;
					}
					if (female_use_j > female_use_j_add1)//相邻两个元素如果逆序，则交换位置
					{
						char temp[11];
						strcpy(temp, IDArray[j]);
						strcpy(IDArray[j], IDArray[j + 1]);
						strcpy(IDArray[j + 1], temp);
					}
				}
			}
			SiteInfo site_i = querySiteInfo(sitehead, IDArray[SITE_NUM-1]);
			printf("%s\n", site_i.siteSportsType);
			system("pause");
			system("cls");
		}else if(ch_admin_see_stc == '7'){
			system("cls");
			printAdminIcon();
			printf("--------------------------------------------------\n");
			printf("针对当前场馆，所有场地的均利用率为：\n");
			SiteInfoNode* move = sitehead->next;
			AdminInfo lgAdmin = queryAdminInfo(adminhead, glb_adminID);
			int num = 0;
			while (move != NULL) {
				if(strcmp(move->siteInfo.siteVenueID, lgAdmin.adminVenueID) == 0){
					num++;
				}
				move = move->next;
			}
			const int SITE_NUM = num;
			
			char IDArray[SITE_NUM][11];
			move = sitehead->next;
			num = 0;
			while (move != NULL) {
				if(strcmp(move->siteInfo.siteVenueID, lgAdmin.adminVenueID) == 0){
					strcpy(IDArray[num], move->siteInfo.siteID);
					num++;
				}
				move = move->next;
			}
			
			for (int i = 1; i <= SITE_NUM - 1; i++)
			{
				for (int j = 0; j <= SITE_NUM - 1 - i; j++)
				{
					SiteInfo site_j = querySiteInfo(sitehead, IDArray[j]);
					SiteInfo site_j_add1 = querySiteInfo(sitehead, IDArray[j+1]);
					double h_j = 0, h_j_add1 = 0;
					int time_j = 0, time_j_add1 = 0;
					AppointmentInfoNode* move = apmthead->next;
					while (move != NULL) {
						if(strcmp(site_j.siteID, move->apmtInfo.apmtSiteID) == 0){
							h_j = h_j + move->apmtInfo.apmtDurationh;
							time_j++;
						}
						if(strcmp(site_j_add1.siteID, move->apmtInfo.apmtSiteID) == 0){
							h_j_add1 = h_j_add1 + move->apmtInfo.apmtDurationh;
							time_j_add1++;
						}
						move = move->next;
					}
					double rate_j = h_j / time_j;
					double rate_j_add1 = h_j_add1 / time_j_add1;
					if (rate_j > rate_j_add1)//相邻两个元素的营业额如果逆序，则交换位置
					{
						char temp[11];
						strcpy(temp, IDArray[j]);
						strcpy(IDArray[j], IDArray[j + 1]);
						strcpy(IDArray[j + 1], temp);
					}
				}
			}
			for(int i=SITE_NUM-1;i>=0;i--){
				double h_i = 0;
				int time_i = 0;
				AppointmentInfoNode* move = apmthead->next;
				while (move != NULL) {
					if(strcmp(IDArray[i], move->apmtInfo.apmtSiteID) == 0){
						h_i = h_i + move->apmtInfo.apmtDurationh;
						time_i++;
					}
					move = move->next;
				}
				double rate_i = h_i / time_i;
				SiteInfo site_i = querySiteInfo(sitehead, IDArray[i]);
				if(rate_i == rate_i) printf("场地ID：%s 场地名称：%s 均利用率：%.4lf小时/次\n", site_i.siteID, site_i.siteName, rate_i);
				else printf("场地ID：%s 场地名称：%s 均利用率：从未被使用过\n", site_i.siteID, site_i.siteName);
			}
			system("pause");
			system("cls");
		}else{
			fflush(stdin);
			printf("输入有误哦，请重新输入！\n");
			system("pause");
			system("cls");
		}
	}
	return 0;
}

int doCredit(UserInfoNode* usrInfoHead)
{
	char strUserID[11];
	char strMoney[6];
	
	while (TRUE){
		system("cls");
		printAdminIcon();
		printf("--------------------------------------------------\n");
		printf("请输入需要充值的用户ID：");
		safegets(strUserID,10);
		if (isUserExist(usrInfoHead, strUserID) == FALSE)
		{
			fflush(stdin);
			printf("未查询到该用户，请重新输入！\n");
			system("pause");
			system("cls");
		}
		else if (isUserExist(usrInfoHead, strUserID) == TRUE)
		{
			while (TRUE)
			{
				UserInfo crUser = queryUserInfo(usrInfoHead, strUserID);
				system("cls");
				printAdminIcon();
				printf("--------------------------------------------------\n");
				printf("正在为 ID 为 %s 的用户余额充值\n", strUserID);
				printf("当前账户余额：%.2lf\n", crUser.usrMoney);
				printf("单次充值金额上限为999.99,为当前账户充值金额：");
				safegets(strMoney, 6);
				fflush(stdin);
				if (isValidMoneyAdd(strMoney)) {
					crUser.usrMoney += strtod(strMoney, NULL);
					EditUserInfo(usrInfoHead, crUser);
					printf("充值成功！\n");
					saveUserInfo(usrInfoHead);
					system("pause");
					return 0;
				}
				else{
					printf("充值金额格式错误，或超出单次充值金额上限，请重新输入！");
					system("pause");
					system("cls");
				}
			}
		}
	}
}

int doSetUserBreak(UserInfoNode* usrInfoHead)
{
	char strUserID[11];
	char strMoney[6];
	
	while (TRUE){
		system("cls");
		printAdminIcon();
		printf("--------------------------------------------------\n");
		printf("请输入需要设置违约的用户ID：");
		safegets(strUserID,10);
		if (isUserExist(usrInfoHead, strUserID) == FALSE)
		{
			fflush(stdin);
			printf("未查询到该用户，请重新输入！\n");
			system("pause");
			system("cls");
		}
		else if (isUserExist(usrInfoHead, strUserID) == TRUE)
		{
			while (TRUE)
			{
				UserInfo crUser = queryUserInfo(usrInfoHead, strUserID);
				system("cls");
				printAdminIcon();
				printf("--------------------------------------------------\n");
				printf("确认设置用户 %s 发生了违约？\n", strUserID);
				printf("该用户当前违约次数：%d\n", crUser.usrBreakAppointmentTimes);
				printf("按 0 确认设置用户违约一次\n");
				printf("按 ESC 放弃设置并返回上一级\n");
				char ch_br = getch();
				fflush(stdin);
				if (ch_br == '0') {
					crUser.usrBreakAppointmentTimes += 1;
					EditUserInfo(usrInfoHead, crUser);
					printf("设置成功！\n");
					saveUserInfo(usrInfoHead);
					system("pause");
					return 0;
				}else if(ch_br == 27){
					return 0;
				}else{
					printf("输入有误，请重新输入！");
					system("pause");
					system("cls");
				}
			}
		}
	}
}
