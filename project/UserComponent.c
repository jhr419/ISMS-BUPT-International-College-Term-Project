#include "DataToolkit.c"
#include <ctype.h>
#include <time.h>

extern char glb_usrID[11];

//==========================校验用工具函数===============================

int isValidUserID(char strID[11]) {
	//6-10位，只包含字母与数字
	int i=0;
	for(i=0; strID[i]; i++)
	{
		if (!isalpha(strID[i]) && !isdigit(strID[i])) return FALSE;
	}
	if(i<6 || i >10) return FALSE;
	return TRUE;
}

int isValidUserName(char strName[16]) {
	//char[16]以内，最多七个纯汉字字符
	int i = 0;
	for(i=0; strName[i];)
	{
		i++;
	}
	if(i<1 || i >15) return FALSE;
	return TRUE;
}

int isValidUserGender(char charGender) {
	//建议使用getch()获取用户输入，只能是1或0
	if(charGender == '1' || charGender == '0'){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

int isValidUserAge(char strinput[6]) {
	//输入小于100的纯数字年龄
	int i=0;
	for(i=0; strinput[i]; i++)
	{
		if (!isdigit(strinput[i])) return FALSE;
	}
	if(i > 3) return FALSE;
	int age = atoi(strinput);
	if(age > 100 || age < 1) return FALSE;
	return TRUE;
}

int isValidMinAge(char strinput[6]) {
	//输入小于100的纯数字年龄
	int i=0;
	for(i=0; strinput[i]; i++)
	{
		if (!isdigit(strinput[i])) return FALSE;
	}
	if(i > 3) return FALSE;
	int age = atoi(strinput);
	if(age > 99 || age < 1) return FALSE;
	return TRUE;
}

int isValidUserPhone(char strPhone[12]) {
	//输入11位纯数字手机号，必须以1开头
	int i=0;
	for(i=0; strPhone[i]; i++)
	{
		if(i==0 && strPhone[i] != '1') return FALSE;
		if (!isdigit(strPhone[i])) return FALSE;
	}
	if(i != 11) return FALSE;
	return TRUE;
}

int isValidUserPwd(char strPwd[21]) {
	//输入6-20位内的密码，只允许数字字母字符
	int i=0;
	for(i=0; strPwd[i]; i++)
	{
		if (!isalpha(strPwd[i]) && !isdigit(strPwd[i]) && !ispunct(strPwd[i])) return FALSE;
	}
	if(i<6 || i >20) return FALSE;
	return TRUE;
}

int isValidUserEmail(char pszEmail[41]) {
	//40位以内的邮箱，只能是数字，字母，符号，必须符合邮箱格式
	if(pszEmail == NULL)
	{
		return FALSE;
	}
	int iAtPos = 0;
	int iLastDotPos = 0;
	int i = 0;
	int iAtTimes = 0;
	while(*(pszEmail + i) != '\0')
	{
		char ch = *(pszEmail + i);
		if (!isalpha(ch) && !isdigit(ch) && !ispunct(ch)) return FALSE;
		if(!isprint(ch) || isspace(ch))
		{
			iAtTimes = 0;
			break;
		}
		if(ch == '@')
		{
			iAtPos = i;
			iAtTimes++;
		}
		else if(ch == '.')
		{
			iLastDotPos = i;
		}
		i++;
	}
	if(i > 40 || iAtPos < 1 || (iLastDotPos - 2) < iAtPos ||
		(i - iLastDotPos) < 3 || (i - iLastDotPos) > 5 || iAtTimes > 1 || iAtTimes == 0)
	{
		return FALSE;
	}
	return TRUE;
}

int isValidUserLocation(char strLocation[256]) {
	//char[255]以内，最多七个纯汉字字符
	int i = 0;
	for(i=0; strLocation[i];)
	{
		i++;
	}
	if(i<1 || i >255) return FALSE;
	return TRUE;
}

int isValidVenue(char strVenue[65]) {
	//char[64]以内
	int i = 0;
	for(i=0; strVenue[i];)
	{
		i++;
	}
	if(i<1 || i >64) return FALSE;
	return TRUE;
}

int isValidDoubleNumStr(char strInput[7]){
	int i = 0;
	int num_after_dot = 0;
	BOOL has_dot = FALSE;
	for(i=0; strInput[i];)
	{
		if (!isdigit(strInput[i]) && !(strInput[i] == '.')) return FALSE;
		i++;
		if(has_dot && strInput[i] == '.') return FALSE;
		if(has_dot) num_after_dot++;
		if(strInput[i] == '.') has_dot = TRUE;
	}
	if(i<1 || i >6) return FALSE;
	if(num_after_dot != 3) return FALSE;
	if(strtod(strInput, NULL) < 1.00 || strtod(strInput, NULL) > 200.00) return FALSE;
	return TRUE;
}

int isValidMoneyAdd(char strInput[7]){
	int i = 0;
	int num_after_dot = 0;
	BOOL has_dot = FALSE;
	for(i=0; strInput[i];)
	{
		if (!isdigit(strInput[i]) && !(strInput[i] == '.')) return FALSE;
		i++;
		if(has_dot && strInput[i] == '.') return FALSE;
		if(has_dot) num_after_dot++;
		if(strInput[i] == '.') has_dot = TRUE;
	}
	if(i<1 || i >6) return FALSE;
	if(num_after_dot != 2) return FALSE;
	if(strtod(strInput, NULL) < 1.00 || strtod(strInput, NULL) > 999.99) return FALSE;
	return TRUE;
}

int isValidDate(int year, int month, int day){
	if (month > 12 || month < 1)
	{
		return -1;
	}
	else
	{
		if ((year % 4 == 0 && year % 100 != 0 )|| year % 400 == 0)//是闰年
		{
			if (month == 2)
			{
				if (day > 29 || day < 1)
					return -2;
				else
					return 1;
			}
		}
		if (month == 4 || month == 6 || month == 9 || month == 11)
		{
			if (day < 1 || day>30)
				return -2;
			else return 1;
		}
		else if (month != 2)
		{
			if (day < 1 || day>31)
				return -2;
			else
				return 1;
		}
		else
		{
			if (day < 1 || day>28)
				return -2;
			else
				return 1;
		}
	}
}

int isValidYYYYMMDDHHDate(char strDate[11]) {
	int i = 0;
	for(i=0; strDate[i];)
	{
		i++;
	}
	if(i != 10) return FALSE;
	if(!isdigit(strDate[0])) return FALSE;
	if(!isdigit(strDate[1])) return FALSE;
	if(!isdigit(strDate[2])) return FALSE;
	if(!isdigit(strDate[3])) return FALSE;
	if(strDate[4] != '-') return FALSE;
	if(!isdigit(strDate[5])) return FALSE;
	if(!isdigit(strDate[6])) return FALSE;
	if(strDate[7] != '-') return FALSE;
	if(!isdigit(strDate[8])) return FALSE;
	if(!isdigit(strDate[9])) return FALSE;
	
	int year = (strDate[0]-'0') * 1000 + (strDate[1]-'0') * 100 + (strDate[2]-'0') * 10 + (strDate[3]-'0') * 1;
	int month = (strDate[5]-'0') * 10 + (strDate[6]-'0') * 1;
	int day = (strDate[8]-'0') * 10 + (strDate[9]-'0') * 1;
	
	if(isValidDate(year, month, day) != 1) return FALSE;
	
	return TRUE;
}

int isReserveDateConflict(AppointmentInfoNode* apmthead, char strSiteID[11], char strDate[11], int intStartHour){//yyyy-mm-dd
	AppointmentInfoNode* move = apmthead->next;
	while (move != NULL) {
		char apmtDate[11];
		strcpy(apmtDate, move->apmtInfo.apmtStartDateh);
		//确认为同一天
		if(apmtDate[0] == strDate[0] && apmtDate[1] == strDate[1] && apmtDate[2] == strDate[2] && apmtDate[3] == strDate[3] && apmtDate[4] == strDate[5] && apmtDate[5] == strDate[6] && apmtDate[6] == strDate[8] && apmtDate[7] == strDate[9]){
			int apmtStart = (apmtDate[8]-'0') * 10 + (apmtDate[9]-'0') * 1;
			int apmtEnd = apmtStart + move->apmtInfo.apmtDurationh;
			if(intStartHour >= apmtStart && intStartHour < apmtEnd){
				return TRUE;
			}
		}
		move = move->next;
	}
	return FALSE;
}

int isReserveHourConflict(AppointmentInfoNode* apmthead, char strSiteID[11], char strDate[11], int intStartHour, int intLastHours){//yyyy-mm-dd
	AppointmentInfoNode* move = apmthead->next;
	while (move != NULL) {
		char apmtDate[11];
		strcpy(apmtDate, move->apmtInfo.apmtStartDateh);
		//确认为同一天
		if(apmtDate[0] == strDate[0] && apmtDate[1] == strDate[1] && apmtDate[2] == strDate[2] && apmtDate[3] == strDate[3] && apmtDate[4] == strDate[5] && apmtDate[5] == strDate[6] && apmtDate[6] == strDate[8] && apmtDate[7] == strDate[9]){
			int apmtStart = (apmtDate[8]-'0') * 10 + (apmtDate[9]-'0') * 1;
			int apmtEnd = apmtStart + move->apmtInfo.apmtDurationh;
			int intEnd = intStartHour + intLastHours;
			if(!(intStartHour>=apmtEnd || intEnd <= apmtStart)){
				return TRUE;
			}
		}
		move = move->next;
	}
	return FALSE;
}

int isValidIndex(char strIndex[5], int index) {
	for(int i=0; strIndex[i];)
	{
		if(!isdigit(strIndex[i])) return FALSE;
		i++;
	}
	if(atoi(strIndex) < 0 || atoi(strIndex) > index-1) return FALSE;
	return TRUE;
}

//==========================信息展示函数===============================

void printOneSiteInfo(SiteInfo stifo){
	printf("场地ID：\t%s\n", stifo.siteID);
	printf("场地名称：\t%s\n", stifo.siteName);
	printf("场地位置：\t%s\n", stifo.siteLocation);
	printf("所属场馆：\t%s\n", stifo.siteVenueID);
	printf("运动类型：\t%s\n", stifo.siteSportsType);
	printf("场地简介：\t%s\n", stifo.siteIntro);
	printf("场地租金：\t%.2lf\n", stifo.siteRent);
	printf("准入年龄：\t%d-%d\n", stifo.siteAllowedAgeMin, stifo.siteAllowedAgeMax);
	printf("--------------------------------------------------\n");
}

void printOneApmtInfo(ApmtInfo apifo){
	printf("预约用户：\t%s\n", apifo.apmtUsrID);
	printf("预约场地：\t%s\n", apifo.apmtSiteID);
	printf("下单时间：\t%s\n", apifo.apmtOrderDated);
	printf("开始时间：\t%s\n", apifo.apmtStartDateh);
	printf("持续时长：\t%d\n", apifo.apmtDurationh);
	printf("--------------------------------------------------\n");
}

//==========================注册流程函数===============================

void printRegIcon() {
	printf("\033[0m\033[1;36m%s\033[0m", "    ____             _      __           \n");
	printf("\033[0m\033[1;36m%s\033[0m", "   / __ \\___  ____ _(_)____/ /____  _____\n");
	printf("\033[0m\033[1;36m%s\033[0m", "  / /_/ / _ \\/ __ `/ / ___/ __/ _ \\/ ___/\n");
	printf("\033[0m\033[1;36m%s\033[0m", " / _, _/  __/ /_/ / (__  ) /_/  __/ /    \n");
	printf("\033[0m\033[1;36m%s\033[0m", "/_/ |_|\\___/\\__, /_/____/\\__/\\___/_/     \n");
	printf("\033[0m\033[1;36m%s\033[0m", "           /____/                        \n");
	printf("\033[0m\033[1;36m%s\033[0m", "当前注册完成状态：\n");
}

char *safegets(char data[], int count) {
	//封装了安全的fgets(stdin)，会替换掉读进来的\n
	fgets(data, count, stdin);
	char *find = strchr(data, '\n');
	if(find)
		*find = '\0';
	return safegets;
}

BOOL doRegisterCheck(BOOL valid_id, BOOL valid_name, BOOL valid_gender, BOOL valid_age, BOOL valid_phone, BOOL valid_email, BOOL valid_pwd, BOOL valid_location){
	if(valid_id && valid_name && valid_gender && valid_age && valid_phone && valid_email && valid_pwd && valid_location){
		return TRUE;
	}else{
		return FALSE;
	}
}

void print_status(BOOL valid_id, BOOL valid_name, BOOL valid_gender, BOOL valid_age, BOOL valid_phone, BOOL valid_email, BOOL valid_pwd, BOOL valid_location){
	char status_finished[128] = "\033[0m\033[1;32m[已完成]\033[0m";
	char status_need_fill[128] = "\033[0m\033[1;31m[待填写]\033[0m";
	char* status[2] = {status_need_fill, status_finished};
	printRegIcon();
	printf("--------------------------------------------------\n");
	printf("%s 填写用户ID，要求6-10位，全部由字母或数字组成\n", status[valid_id]);
	printf("%s 填写姓名，要求不得超长\n", status[valid_name]);
	printf("%s 填写性别，只需选择是男或女\n", status[valid_gender]);
	printf("%s 填写年龄，要求为1-100岁之间的纯数字\n", status[valid_age]);
	printf("%s 填写手机号，要求必须为11位，且以1开头\n", status[valid_phone]);
	printf("%s 填写电子邮箱地址，要求必须是有效的邮箱地址\n", status[valid_email]);
	printf("%s 填写密码，要求6-20位，只能包含字母、数字和符号\n", status[valid_pwd]);
	printf("%s 填写地理位置，要求不得超长\n", status[valid_location]);
	printf("--------------------------------------------------\n");
}

void doRegister(UserInfoNode* head) {
	//注册进程的终端用户交互界面
	BOOL valid_id = FALSE, valid_name = FALSE, valid_gender = FALSE, valid_age = FALSE, valid_phone = FALSE, valid_email = FALSE, valid_pwd = FALSE, valid_location = FALSE;
	char strID[12] = "";
	char strName[17] = "";
	char charGender = '3';
	char strinput[7] = "";
	char strPhone[13] = "";
	char strPwd[22] = "";
	char strEmail[42] = "";
	char strLocation[257] = "";
	while(!doRegisterCheck(valid_id, valid_name, valid_gender, valid_age, valid_phone, valid_email, valid_pwd, valid_location)){
		system("cls");
		if(!valid_id){
			while(!valid_id){
				print_status(valid_id, valid_name, valid_gender, valid_age, valid_phone, valid_email, valid_pwd, valid_location);
				printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入用户ID；要求6-10位，全部由字母和数字组成：");
				safegets(strID, 12);
				if(isUserExist(head, strID)){
					fflush(stdin);
					printf("此用户名已存在！");
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
				print_status(valid_id, valid_name, valid_gender, valid_age, valid_phone, valid_email, valid_pwd, valid_location);
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
				print_status(valid_id, valid_name, valid_gender, valid_age, valid_phone, valid_email, valid_pwd, valid_location);
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
		}else if(!valid_age){
			while(!valid_age){
				print_status(valid_id, valid_name, valid_gender, valid_age, valid_phone, valid_email, valid_pwd, valid_location);
				printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入年龄，要求为1-100之间的纯数字：");
				safegets(strinput, 7);
				if(!isValidUserAge(strinput)){
					fflush(stdin);
					printf("输入不符合规范，请重新输入！");
					system("pause");
					system("cls");
				}else{
					valid_age = TRUE;
					fflush(stdin);
					system("cls");
				}
			}
		}else if(!valid_phone){
			while(!valid_phone){
				print_status(valid_id, valid_name, valid_gender, valid_age, valid_phone, valid_email, valid_pwd, valid_location);
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
				print_status(valid_id, valid_name, valid_gender, valid_age, valid_phone, valid_email, valid_pwd, valid_location);
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
				print_status(valid_id, valid_name, valid_gender, valid_age, valid_phone, valid_email, valid_pwd, valid_location);
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
		}else if(!valid_location){
			while(!valid_location){
				print_status(valid_id, valid_name, valid_gender, valid_age, valid_phone, valid_email, valid_pwd, valid_location);
				printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入地理位置，要求不得超长：");
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
		}
	}
	printRegIcon();
	printf("\033[0m\033[1;32m%s\033[0m", "恭喜，注册信息已全部填写完成！\n您输入的信息是：\n");
	printf("--------------------------------------------------\n");
	printf("用户ID：\t%s\n", strID);
	printf("姓名：\t\t%s\n", strName);
	printf("性别：\t\t%d（0代表男，1代表女）\n", charGender - 48);
	printf("年龄：\t\t%s\n", strinput);
	printf("手机号：\t%s\n", strPhone);
	printf("电子邮箱：\t%s\n", strEmail);
	printf("密码：\t\t%s\n", strPwd);
	printf("地理位置：\t%s\n", strLocation);
	printf("--------------------------------------------------\n");
	printf("\033[0m\033[1;33m[提示]\033[0m %s", "新用户首次注册，赠送100元余额！\n");
	printf("正在进行注册...\n");
	//开始构造结构体
	UserInfo usrData = {
		.usrGender = charGender - 48,
		.usrAge = atoi(strinput),
		.usrMoney = 100.00,
		.usrBreakAppointmentTimes = 0
	};
	strcpy(usrData.usrID, strID);
	strcpy(usrData.usrName, strName);
	strcpy(usrData.usrPhone, strPhone);
	strcpy(usrData.usrPwd, strPwd);
	strcpy(usrData.usrEmail, strEmail);
	strcpy(usrData.usrLocation, strLocation);
	//写文件
	if(InsertToUserInfo(head, usrData) == 0){
		printf("\033[0m\033[1;32m[成功]\033[0m %s", "注册已成功完成！\n");
	}else{
		printf("\033[0m\033[1;31m[失败]\033[0m %s", "注册失败！原因：使用了未经检查的数据！\n");
	}
	saveUserInfo(head);
	system("pause");
	system("cls");
}

//==========================登录流程函数===============================

void printLoginIcon(){
	printf("\033[0m\033[1;36m%s\033[0m", "    __                _     \n");
	printf("\033[0m\033[1;36m%s\033[0m", "   / /   ____  ____ _(_)___ \n");
	printf("\033[0m\033[1;36m%s\033[0m", "  / /   / __ \\/ __ `/ / __ \\\n");
	printf("\033[0m\033[1;36m%s\033[0m", " / /___/ /_/ / /_/ / / / / /\n");
	printf("\033[0m\033[1;36m%s\033[0m", "/_____/\\____/\\__, /_/_/ /_/ \n");
	printf("\033[0m\033[1;36m%s\033[0m", "            /____/          \n");
	printf("\033[0m\033[1;36m%s\033[0m", "当前登录信息填写情况：\n");
}

BOOL doLoginCheck(BOOL valid_id, BOOL valid_pwd){
	if(valid_id && valid_pwd){
		return TRUE;
	}else{
		return FALSE;
	}
}

void print_login_status(BOOL valid_id, BOOL valid_pwd){
	char status_finished[128] = "\033[0m\033[1;32m[已完成]\033[0m";
	char status_need_fill[128] = "\033[0m\033[1;31m[待填写]\033[0m";
	char* status[2] = {status_need_fill, status_finished};
	printLoginIcon();
	printf("--------------------------------------------------\n");
	printf("%s 填写用户ID，要求6-10位，全部由字母或数字组成\n", status[valid_id]);
	printf("%s 填写密码，要求6-20位，只能包含字母、数字和符号\n", status[valid_pwd]);
	printf("--------------------------------------------------\n");
}

int doLogin(UserInfoNode* head) {
	//登录进程的终端用户交互界面
	BOOL valid_id = FALSE, valid_pwd = FALSE;
	BOOL matched = FALSE;
	int wrong_pwd_times = 0;
	//使用全局变量glb_usrID[11]来保存用户ID
	char strPwd[22] = "";
	while(!doLoginCheck(valid_id, valid_pwd) || !matched){
		system("cls");
		if(!valid_id){
			while(!valid_id){
				print_login_status(valid_id, valid_pwd);
				printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入用户ID；要求6-10位，全部由字母和数字组成：");
				safegets(glb_usrID, 12);
				if(!isValidUserID(glb_usrID)){
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
				UserInfo lgUsrInfo = queryUserInfo(head, glb_usrID);
				char lgUsrPwd[21];
				strcpy(lgUsrPwd, lgUsrInfo.usrPwd); 
				print_login_status(valid_id, valid_pwd);
				printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入密码，要求6-20位，只能包含字母、数字和符号：");
				safegets(strPwd, 22);
				if(wrong_pwd_times >= 5){
					printf("密码错误次数过多，程序自动返回用户主菜单！");
					system("pause");
					return 1;
				}
				if(!isValidUserPwd(strPwd)){
					fflush(stdin);
					printf("输入不符合规范，本次尝试不计入错误次数，请重新输入！\n");
					system("pause");
					system("cls");
				}else if(!isUserExist(head, glb_usrID)){
					fflush(stdin);
					printf("用户不存在，请重新输入！您还有 %d 次机会\n", 5 - wrong_pwd_times);
					valid_id = FALSE;
					wrong_pwd_times++;
					system("pause");
					system("cls");
					break;
				}
				else if(strcmp(strPwd, lgUsrPwd) != 0){
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
				}
			}
		}
	}
	return 0;
}

//==========================用户信息流程函数===============================

void printUsrCenterIcon(){
	printf("\033[0m\033[1;36m%s\033[0m", "   __  __                  ______           __           \n");
	printf("\033[0m\033[1;36m%s\033[0m", "  / / / /_______  _____   / ____/__  ____  / /____  _____\n");
	printf("\033[0m\033[1;36m%s\033[0m", " / / / / ___/ _ \\/ ___/  / /   / _ \\/ __ \\/ __/ _ \\/ ___/\n");
	printf("\033[0m\033[1;36m%s\033[0m", "/ /_/ (__  )  __/ /     / /___/  __/ / / / /_/  __/ /    \n");
	printf("\033[0m\033[1;36m%s\033[0m", "\\____/____/\\___/_/      \\____/\\___/_/ /_/\\__/\\___/_/     \n");
	printf("欢迎 %s 使用系统！\n", glb_usrID);
	
}

void printCurrentUsrInfo(UserInfoNode* head) {
	UserInfo crUsrInfo = queryUserInfo(head, glb_usrID);
	printf("--------------------------------------------------\n");
	printf("\033[0m\033[1;31m[x>]\033[0m 用户ID：\t%s\n", glb_usrID);
	printf("\033[0m\033[1;31m[x>]\033[0m 姓名：\t%s\n", crUsrInfo.usrName);
	printf("\033[0m\033[1;31m[x>]\033[0m 性别：\t%d（0代表男，1代表女）\n", crUsrInfo.usrGender);
	printf("\033[0m\033[1;31m[x>]\033[0m 年龄：\t%d\n", crUsrInfo.usrAge);
	printf("\033[0m\033[1;32m[0>]\033[0m 手机号：\t%s\n", crUsrInfo.usrPhone);
	printf("\033[0m\033[1;32m[1>]\033[0m 电子邮箱：\t%s\n", crUsrInfo.usrEmail);
	printf("\033[0m\033[1;32m[2>]\033[0m 密码：\t%s\n", crUsrInfo.usrPwd);
	printf("\033[0m\033[1;32m[3>]\033[0m 地理位置：\t%s\n", crUsrInfo.usrLocation);
	printf("\033[0m\033[1;31m[x>]\033[0m 余额：\t%.2lf\n", crUsrInfo.usrMoney);
	printf("\033[0m\033[1;31m[x>]\033[0m 违约次数：\t%d\n", crUsrInfo.usrBreakAppointmentTimes);
	printf("--------------------------------------------------\n");
}

int doUsrInfoEdit(UserInfoNode* head){
	UserInfo lgUsrInfo = queryUserInfo(head, glb_usrID);
	char lgUsrPwd[21];
	char strPwd[22];
	int wrong_pwd_times = 0;
	strcpy(lgUsrPwd, lgUsrInfo.usrPwd); 
	while(TRUE){
		system("cls");
		printUsrCenterIcon();
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
		}else if(strcmp(strPwd, lgUsrPwd) != 0){
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
		printUsrCenterIcon();
		printf("--------------------------------------------------\n");
		printf("您\033[0m\033[1;33m当前的\033[0m用户信息如下：\n");
		printCurrentUsrInfo(head);
		printf("\n带有红色\033[0m\033[1;31m[x>]\033[0m的信息为用户生理和标识信息，不允许修改。\n");
		printf("带有绿色\033[0m\033[1;32m[数字>]\033[0m的信息可以修改。\n");
		printf("如需修改个人信息，请按下需要修改的信息项前\033[0m\033[1;32m[数字>]\033[0m中的数字按键\n");
		printf("如需充值，请联系场馆管理员为您充值。\n");
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
				printUsrCenterIcon();
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
					strcpy(lgUsrInfo.usrPhone, strPhone); 
					EditUserInfo(head, lgUsrInfo);
					saveUserInfo(head);
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
				printUsrCenterIcon();
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
					strcpy(lgUsrInfo.usrEmail, strEmail); 
					EditUserInfo(head, lgUsrInfo);
					saveUserInfo(head);
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
				printUsrCenterIcon();
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
					strcpy(lgUsrInfo.usrPwd, strPwd); 
					EditUserInfo(head, lgUsrInfo);
					saveUserInfo(head);
					fflush(stdin);
					printf("修改成功！");
					system("pause");
					system("cls");
					break;
				}
			}
		} else if (ch_edit_item == '3') {
			char strLocation[256];
			fflush(stdin);
			system("cls");
			while(TRUE){
				printUsrCenterIcon();
				printf("--------------------------------------------------\n");
				printf("修改您保存在系统中的地理位置。\n\n");
				printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入\033[0m\033[1;33m新的\033[0m地理位置，要求不得超长：");
				safegets(strLocation, 256);
				if(!isValidUserLocation(strLocation)){
					fflush(stdin);
					printf("输入不符合规范，请重新输入！");
					system("pause");
					system("cls");
				}else{
					strcpy(lgUsrInfo.usrLocation, strLocation); 
					EditUserInfo(head, lgUsrInfo);
					saveUserInfo(head);
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

//==========================场地预定流程函数===============================

void printReserveIcon(){
	printf("\033[0m\033[1;34m%s\033[0m", "    ____                                  __  _           \n");
	printf("\033[0m\033[1;34m%s\033[0m", "   / __ \\___  ________  ______   ______ _/ /_(_)___  ____ \n");
	printf("\033[0m\033[1;34m%s\033[0m", "  / /_/ / _ \\/ ___/ _ \\/ ___/ | / / __ `/ __/ / __ \\/ __ \\\n");
	printf("\033[0m\033[1;34m%s\033[0m", " / _, _/  __(__  )  __/ /   | |/ / /_/ / /_/ / /_/ / / / /\n");
	printf("\033[0m\033[1;34m%s\033[0m", "/_/ |_|\\___/____/\\___/_/    |___/\\__,_/\\__/_/\\____/_/ /_/ \n\n");
	printf("\033[0m\033[1;34m%s\033[0m", "你还在排队？我已经预约好场地了！\n");
}

void print_reserve_status(BOOL valid_1, BOOL valid_2, BOOL valid_3){
	char status_finished[128] = "\033[0m\033[1;42m[OK] 此场地可以预约\033[0m";
	char status_need_fill[128] = "\033[0m\033[1;43m[-] 待预约\033[0m";
	char* status[2] = {status_need_fill, status_finished};
	printReserveIcon();
	printf("--------------------------------------------------\n");
	printf("[1] %s\n", status[valid_1]);
	printf("[2] %s\n", status[valid_2]);
	printf("[3] %s\n", status[valid_3]);
	printf("--------------------------------------------------\n");
}

void print_specific_reserve_status(BOOL valid_id, BOOL valid_start_date, BOOL valid_start_hour, BOOL valid_duri_hours){
	char status_finished[128] = "\033[0m\033[1;32m[已完成]\033[0m";
	char status_need_fill[128] = "\033[0m\033[1;31m[待填写]\033[0m";
	char* status[2] = {status_need_fill, status_finished};
	printReserveIcon();
	printf("--------------------------------------------------\n");
	printf("%s 填写场馆ID，要求6-10位，全部由字母或数字组成：\n", status[valid_id]);
	printf("%s 填写预约开始日期，要求输入格式为yyyy-mm-dd格式的日期，精确到天：\n", status[valid_start_date]);
	printf("%s 填写预约开始小时，要求输入整数。例如，准备从九点开始预约，则输入9：\n", status[valid_start_hour]);
	printf("%s 填写预约时长，单位为小时，需输入整数：\n", status[valid_duri_hours]);
	printf("--------------------------------------------------\n");
}

int doSiteReserve(SiteInfoNode* sitehead, AppointmentInfoNode* apmthead, UserInfoNode* userhead) {
	BOOL valid_1 = FALSE;
	BOOL valid_2 = FALSE;
	BOOL valid_3 = FALSE;
	char strSiteID[3][11];
	char strStartDate[3][11];
	char strStartHours[3][3];
	char strLastHours[3][3];
	int current_turn;
	
	UserInfo usifo = queryUserInfo(userhead, glb_usrID);
	if(usifo.usrBreakAppointmentTimes >= 3){
		printf("\n\033[0m\033[1;31m您已违约超过三次，不可使用预约功能！\033[0m");
		system("pause");
		return 1;
	}
	
	while(TRUE){
		current_turn = 0;
		if(valid_1) current_turn = 1;
		if(valid_1 && valid_2) current_turn = 2;
		if(valid_1 && valid_2 && valid_3) current_turn = 3;
		system("cls");
		print_reserve_status(valid_1, valid_2, valid_3);
		printf("您每次可预约最多三个场地，可预约时段为6:00-22:00。\n");
		printf("按下 0 开始 \033[0m\033[1;34m[预约场地]\033[0m\n");
		printf("按下 \033[0m\033[1;33mESC\033[0m [提交订单并返回上一级]\n");
		char ch_resserve = getch();
		if (ch_resserve == 27) {
			fflush(stdin);
			system("cls");
			return 0;
		} else if (ch_resserve == '0') {
			if(current_turn == 3){
				system("cls");
				printReserveIcon();
				printf("--------------------------------------------------\n");
				printf("每次最多预约三个场地！\n");
				system("pause");
				continue;
			}
			fflush(stdin);
			system("cls");
			BOOL valid_id = FALSE, valid_start_date = FALSE, valid_start_hour = FALSE, valid_duri_hours = FALSE;
			while(!(valid_id == TRUE && valid_start_date == TRUE && valid_start_hour == TRUE && valid_duri_hours == TRUE)){
				if(!valid_id){
					print_specific_reserve_status(valid_id, valid_start_date, valid_start_hour, valid_duri_hours);
					printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入需要预约的场地ID；要求6-10位，全部由字母和数字组成：");
					safegets(strSiteID[current_turn], 12);
					SiteInfo st = querySiteInfo(sitehead, strSiteID[current_turn]);
					UserInfo ur = queryUserInfo(userhead, glb_usrID);
					int minage = st.siteAllowedAgeMin;
					int maxage = st.siteAllowedAgeMax;
					int usrage = ur.usrAge;
					if(!isValidUserID(strSiteID[current_turn])){
						fflush(stdin);
						printf("输入不符合规范，请重新输入！");
						system("pause");
						system("cls");
					}else if(!isSiteExist(sitehead, strSiteID[current_turn])){
						fflush(stdin);
						printf("您需要预约的场地不存在！");
						system("pause");
						system("cls");
					}else if(usrage < minage || usrage > maxage){
						fflush(stdin);
						printf("您的年龄不符合场地的准入要求！");
						system("pause");
						system("cls");
					}else{
						valid_id = TRUE;
						fflush(stdin);
						system("cls");
					}
				}else if(!valid_start_date){
					print_specific_reserve_status(valid_id, valid_start_date, valid_start_hour, valid_duri_hours);
					printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入预约开始日期，要求输入格式为yyyy-mm-dd格式的日期，精确到天：");
					safegets(strStartDate[current_turn], 12);
					if(!isValidYYYYMMDDHHDate(strStartDate[current_turn])){
						fflush(stdin);
						printf("输入不符合规范或输入的日期不合法，请重新输入！");
						system("pause");
						system("cls");
					}else{//else if ....
						valid_start_date = TRUE;
						fflush(stdin);
						system("cls");
					}
				}else if(!valid_start_hour){
					print_specific_reserve_status(valid_id, valid_start_date, valid_start_hour, valid_duri_hours);
					printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入预约开始小时，要求输入两位整数。例如，准备从九点（上午九点）开始预约，则输入09：");
					safegets(strStartHours[current_turn], 3);
					if(strlen(strStartHours[current_turn]) > 2 || !isdigit(strStartHours[current_turn][0]) || !isdigit(strStartHours[current_turn][1]) || atoi(strStartHours[current_turn]) < 6  || atoi(strStartHours[current_turn]) > 21){
						fflush(stdin);
						printf("输入不符合规范或输入的小时不在可预约范围内，请重新输入！");
						system("pause");
						system("cls");
					}else if(isReserveDateConflict(apmthead, strSiteID[current_turn], strStartDate[current_turn], atoi(strStartHours[current_turn]))){
						fflush(stdin);
						printf("输入的时段与他人预约存在冲突，请重新输入！");
						system("pause");
						system("cls");
					}else{
						valid_start_hour = TRUE;
						fflush(stdin);
						system("cls");
					}
				}else if(!valid_duri_hours){
					print_specific_reserve_status(valid_id, valid_start_date, valid_start_hour, valid_duri_hours);
					printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入预约持续小时，要求输入两位整数。例如，准备预约使用3个小时，则输入03：");
					safegets(strLastHours[current_turn], 3);
					UserInfo userinf = queryUserInfo(userhead, glb_usrID);
					SiteInfo siteinf = querySiteInfo(sitehead, strSiteID[current_turn]);
					double userMoney = userinf.usrMoney;
					double siteRent = siteinf.siteRent;
					if(strlen(strLastHours[current_turn]) > 2 || !isdigit(strLastHours[current_turn][0]) || !isdigit(strLastHours[current_turn][1]) || atoi(strStartHours[current_turn]) + atoi(strLastHours[current_turn]) > 22 || atoi(strLastHours[current_turn]) < 1){
						fflush(stdin);
						printf("输入不符合规范或输入的小时不在可预约范围内，请重新输入！");
						system("pause");
						system("cls");
					}else if(isReserveHourConflict(apmthead, strSiteID[current_turn], strStartDate[current_turn], atoi(strStartHours[current_turn]), atoi(strLastHours[current_turn]))){
						fflush(stdin);
						printf("输入的时段与他人预约存在冲突，请重新输入！");
						system("pause");
						system("cls");
					}else if(userMoney - siteRent * atoi(strLastHours[current_turn]) < 0){
						fflush(stdin);
						printf("您当前账户的余额不足以支付租金，请尝试更小的小时数！");
						system("pause");
						system("cls");
					}else{
						valid_duri_hours = TRUE;
						fflush(stdin);
						system("cls");
					}
				}
			}
			printReserveIcon();
			printf("--------------------------------------------------\n");
			printf("当前场馆可供您使用！预约信息录入完毕，正在进行预约...\n");
			UserInfo usifo = queryUserInfo(userhead, glb_usrID);
			char orderDate[15];
			char apmtStartDate[11];
			time_t timep;
			struct tm *p;
			time (&timep);
			p=gmtime(&timep);
			sprintf(orderDate,"%04d%02d%02d%02d%02d%02d",1900+p->tm_year,1+p->tm_mon,p->tm_mday,8+p->tm_hour,p->tm_min,p->tm_sec);
			int year1, month1, day1;
			sscanf(strStartDate[current_turn], "%d-%d-%d", &year1, &month1, &day1);
			sprintf(apmtStartDate, "%04d%02d%02d%02d", year1, month1, day1, atoi(strStartHours[current_turn]));
			ApmtInfo apmtData = {
				.apmtDurationh = atoi(strLastHours[current_turn]),
				.apmtUsrGender = usifo.usrGender,
				.isUsrPresent = TRUE
			};
			strcpy(apmtData.apmtUsrID, glb_usrID);
			strcpy(apmtData.apmtSiteID, strSiteID[current_turn]);
			strcpy(apmtData.apmtOrderDated, orderDate);
			strcpy(apmtData.apmtStartDateh, apmtStartDate);
			//写文件
			if(InsertToApmtInfo(apmthead, apmtData) == 0){
				printf("\033[0m\033[1;32m[成功]\033[0m %s", "预约已成功完成！\n");
			}else{
				printf("\033[0m\033[1;31m[失败]\033[0m %s", "预约失败！原因：使用了未经检查的数据！\n");
			}
			saveApmtInfo(apmthead);
			SiteInfo stifo = querySiteInfo(sitehead, strSiteID[current_turn]);
			stifo.siteUsedTimes += 1;
			if(EditSiteInfo(sitehead, stifo) == 0){
				printf("\033[0m\033[1;32m[成功]\033[0m %s", "已成功更新场地信息！\n");
			}else{
				printf("\033[0m\033[1;31m[失败]\033[0m %s", "场地信息更新失败！原因：使用了未经检查的数据，找不到场地！\n");
			}
			saveSiteInfo(sitehead);
			usifo.usrMoney = usifo.usrMoney - stifo.siteRent * atoi(strLastHours[current_turn]);
			if(EditUserInfo(userhead, usifo) == 0){
				printf("\033[0m\033[1;32m[成功]\033[0m %s", "已成功扣款！\n");
			}else{
				printf("\033[0m\033[1;31m[失败]\033[0m %s", "扣款失败！原因：使用了未经检查的数据，找不到用户！\n");
			}
			saveUserInfo(userhead);
			if(!valid_1) valid_1 = TRUE;
			else if(!valid_2) valid_2 = TRUE;
			else if(!valid_3) valid_3 = TRUE;
			system("pause");
		}else {
			fflush(stdin);
			printf("输入有误哦，请重新输入！\n");
			system("pause");
			system("cls");
		}
	}
}

//==========================场地查询流程函数===============================

void printSearchIcon() {
	printf("\033[0m\033[1;36m  ____  \033[0m\033[0m\033[1;32m                                 \033[0m\n");
	printf("\033[0m\033[1;36m / __ \\\033[0m\033[0m\033[1;32m   _____                      __  \033[0m\n");
	printf("\033[0m\033[1;36m/ /_/ / \033[0m\033[0m\033[1;32m / ___/___  ____  __________/ /_ \033[0m\n");
	printf("\033[0m\033[1;36m\\_  _/ \033[0m\033[0m\033[1;32m  \\__ \\/ _ \\/ __ `/ ___/ ___/ __ \\\033[0m\n");
	printf("\033[0m\033[1;36m / /    \033[0m\033[0m\033[1;32m __/ /  __/ /_/ / /  / /__/ / / /\033[0m\n");
	printf("\033[0m\033[1;36m/_/     \033[0m\033[0m\033[1;32m/___/\\___/\\__,_/_/   \\___/_/ /_/ \033[0m\n");
	printf("\033[0m\033[1;32m\n查询您“一见钟情”的运动场地\n\033[0m");
}

void goToReserve(SiteInfoNode* sitehead, AppointmentInfoNode* apmthead, UserInfoNode* userhead) {
	printf("\033[0m\033[1;34m查询到了心仪的场地？\033[0m\n按 0 前往 \033[0m\033[1;34m[预约场地]\033[0m\n按 ESC \033[0m\033[1;33m[返回上一级]\033[0m");
	char ch_back_or_reserve = getch();
	if(ch_back_or_reserve == 27){
		return;
	}else if(ch_back_or_reserve == '0'){
		doSiteReserve(sitehead, apmthead, userhead);
	}
}

void searchSiteByName(SiteInfoNode* sitehead, BOOL need_filter, char strSiteName[65]){
	SiteInfoNode* move = sitehead->next;
	int valid_num = 0;
//	if(!need_filter){
		printf("搜索 \033[0m\033[1;33m%s\033[0m 查找到如下结果：\n", strSiteName);
		printf("--------------------------------------------------\n");
		while (move != NULL) {
			if (strstr(move->siteInfo.siteName, strSiteName) != NULL) {
				valid_num++;
				printOneSiteInfo(move->siteInfo);
			}
			move = move->next;
		}
		if(valid_num == 0) printf("\033[0m\033[1;31m%s\033[0m", "未查找到符合要求的场地！\n");
		printf("--------------------------------------------------\n");
//	}
}

void searchSiteByVenue(SiteInfoNode* sitehead, BOOL need_filter, char strSiteVenue[65]){
	SiteInfoNode* move = sitehead->next;
	int valid_num = 0;
//	if(!need_filter){
		printf("搜索 \033[0m\033[1;33m%s\033[0m 查找到如下结果：\n", strSiteVenue);
		printf("--------------------------------------------------\n");
		while (move != NULL) {
			if (strstr(move->siteInfo.siteVenueID, strSiteVenue) != NULL) {
				valid_num++;
				printOneSiteInfo(move->siteInfo);
			}
			move = move->next;
		}
		if(valid_num == 0) printf("\033[0m\033[1;31m%s\033[0m", "未查找到符合要求的场地！\n");
		printf("--------------------------------------------------\n");
//	}
}

void searchSiteBySportsType(SiteInfoNode* sitehead, BOOL need_filter, char strSiteSportsType[65]){
	SiteInfoNode* move = sitehead->next;
	int valid_num = 0;
//	if(!need_filter){
		printf("搜索 \033[0m\033[1;33m%s\033[0m 查找到如下结果：\n", strSiteSportsType);
		printf("--------------------------------------------------\n");
		while (move != NULL) {
			if (strstr(move->siteInfo.siteSportsType, strSiteSportsType) != NULL) {
				valid_num++;
				printOneSiteInfo(move->siteInfo);
			}
			move = move->next;
		}
		if(valid_num == 0) printf("\033[0m\033[1;31m%s\033[0m", "未查找到符合要求的场地！\n");
		printf("--------------------------------------------------\n");
//	}
}

void searchSiteByLocation(SiteInfoNode* sitehead, BOOL need_filter, char strSiteLocation[256]){
	SiteInfoNode* move = sitehead->next;
	int valid_num = 0;
//	if(!need_filter){
		printf("搜索 \033[0m\033[1;33m%s\033[0m 查找到如下结果：\n", strSiteLocation);
		printf("--------------------------------------------------\n");
		while (move != NULL) {
			if (strstr(move->siteInfo.siteLocation, strSiteLocation) != NULL) {
				valid_num++;
				printOneSiteInfo(move->siteInfo);
			}
			move = move->next;
		}
		if(valid_num == 0) printf("\033[0m\033[1;31m%s\033[0m", "未查找到符合要求的场地！\n");
		printf("--------------------------------------------------\n");
//	}
}

int doSiteSearch(SiteInfoNode* sitehead, AppointmentInfoNode* apmthead, UserInfoNode* userhead) {
	while(TRUE){
		system("cls");
		printSearchIcon();
		printf("--------------------------------------------------\n");
		printf("您想要：\n");
		printf("按下 0 进行 \033[0m\033[1;34m[场地检索]\033[0m\n");
		printf("按下 1 查看 \033[0m\033[1;34m[场地排名]\033[0m\n");
		printf("按下 \033[0m\033[1;33mESC\033[0m [返回上一级]\n");
		char ch_search_or_rank = getch();
		if (ch_search_or_rank == 27) {
			fflush(stdin);
			system("cls");
			return 0;
		} else if (ch_search_or_rank == '0') {
			fflush(stdin);
			system("cls");
			while(TRUE){
				printSearchIcon();
				printf("--------------------------------------------------\n");
				printf("按照一定条件，检索您需要的场地。\n\n");
				printf("按下 0 进行 \033[0m\033[1;34m[按场地名称检索]\033[0m\n");
				printf("按下 1 进行 \033[0m\033[1;34m[按场馆名称检索]\033[0m\n");
				printf("按下 2 进行 \033[0m\033[1;34m[按场馆运动类型检索]\033[0m\n");
				printf("按下 3 进行 \033[0m\033[1;34m[按场馆所属区域检索]\033[0m\n");
				printf("按下 \033[0m\033[1;33mESC\033[0m [返回上一级]\n");
				char ch_search_type = getch();
				if(ch_search_type == 27){
					fflush(stdin);
					system("cls");
					return 0;
				}else if(ch_search_type == '0'){
					char strName[66];
					char ch_need_filter;
					while(TRUE){
						fflush(stdin);
						system("cls");
						printSearchIcon();
						printf("--------------------------------------------------\n");
						printf("请输入需要检索的场地名称：\n");
						printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入场地名称，要求不得超长：");
						safegets(strName, 66);
						if(!isValidVenue(strName)){
							fflush(stdin);
							printf("输入不符合规范，请重新输入！");
							system("pause");
							system("cls");
						}else{
							fflush(stdin);
							system("cls");
							break;
						}
					}
					while(TRUE){
						fflush(stdin);
						system("cls");
						printSearchIcon();
						printf("--------------------------------------------------\n");
						printf("是否需要自动过滤预约已满的场地？\n");
						printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请确认是否需要过滤已预约满的场地，按 0 表示不需要，按 1 表示需要：");
						ch_need_filter = getch();
						if(ch_need_filter == '0' || ch_need_filter == '1'){
							fflush(stdin);
							system("cls");
							break;
						}else{
							fflush(stdin);
							printf("输入不符合规范，请重新输入！");
							system("pause");
							system("cls");
						}
					}
					system("cls");
					printSearchIcon();
					printf("--------------------------------------------------\n");
					searchSiteByName(sitehead, ch_need_filter - '0', strName);
					goToReserve(sitehead, apmthead, userhead);
					system("cls");
				}else if(ch_search_type == '1'){
					char strVenue[66];
					char ch_need_filter;
					while(TRUE){
						fflush(stdin);
						system("cls");
						printSearchIcon();
						printf("--------------------------------------------------\n");
						printf("请输入需要检索的场地所属的场馆：\n");
						printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入场馆名称，要求不得超长：");
						safegets(strVenue, 66);
						if(!isValidVenue(strVenue)){
							fflush(stdin);
							printf("输入不符合规范，请重新输入！");
							system("pause");
							system("cls");
						}else{
							fflush(stdin);
							system("cls");
							break;
						}
					}
					while(TRUE){
						fflush(stdin);
						system("cls");
						printSearchIcon();
						printf("--------------------------------------------------\n");
						printf("是否需要自动过滤预约已满的场地？\n");
						printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请确认是否需要过滤已预约满的场地，按 0 表示不需要，按 1 表示需要：");
						ch_need_filter = getch();
						if(ch_need_filter == '0' || ch_need_filter == '1'){
							fflush(stdin);
							system("cls");
							break;
						}else{
							fflush(stdin);
							printf("输入不符合规范，请重新输入！");
							system("pause");
							system("cls");
						}
					}
					system("cls");
					printSearchIcon();
					printf("--------------------------------------------------\n");
					searchSiteByVenue(sitehead, ch_need_filter - '0', strVenue);
					goToReserve(sitehead, apmthead, userhead);
					system("cls");
				}else if(ch_search_type == '2'){
					char strSportsType[66];
					char ch_need_filter;
					while(TRUE){
						fflush(stdin);
						system("cls");
						printSearchIcon();
						printf("--------------------------------------------------\n");
						printf("请输入需要检索的场地的运动类型：\n");
						printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入运动类型，要求不得超长：");
						safegets(strSportsType, 66);
						if(!isValidVenue(strSportsType)){
							fflush(stdin);
							printf("输入不符合规范，请重新输入！");
							system("pause");
							system("cls");
						}else{
							fflush(stdin);
							system("cls");
							break;
						}
					}
					while(TRUE){
						fflush(stdin);
						system("cls");
						printSearchIcon();
						printf("--------------------------------------------------\n");
						printf("是否需要自动过滤预约已满的场地？\n");
						printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请确认是否需要过滤已预约满的场地，按 0 表示不需要，按 1 表示需要：");
						ch_need_filter = getch();
						if(ch_need_filter == '0' || ch_need_filter == '1'){
							fflush(stdin);
							system("cls");
							break;
						}else{
							fflush(stdin);
							printf("输入不符合规范，请重新输入！");
							system("pause");
							system("cls");
						}
					}
					system("cls");
					printSearchIcon();
					printf("--------------------------------------------------\n");
					searchSiteBySportsType(sitehead, ch_need_filter - '0', strSportsType);
					goToReserve(sitehead, apmthead, userhead);
					system("cls");
				}else if(ch_search_type == '3'){
					char strLocation[256];
					char ch_need_filter;
					while(TRUE){
						fflush(stdin);
						system("cls");
						printSearchIcon();
						printf("--------------------------------------------------\n");
						printf("请输入需要检索的场地的地理位置：\n");
						printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入地理位置，要求不得超长：");
						safegets(strLocation, 256);
						if(!isValidUserLocation(strLocation)){
							fflush(stdin);
							printf("输入不符合规范，请重新输入！");
							system("pause");
							system("cls");
						}else{
							fflush(stdin);
							system("cls");
							break;
						}
					}
					while(TRUE){
						fflush(stdin);
						system("cls");
						printSearchIcon();
						printf("--------------------------------------------------\n");
						printf("是否需要自动过滤预约已满的场地？\n");
						printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请确认是否需要过滤已预约满的场地，按 0 表示不需要，按 1 表示需要：");
						ch_need_filter = getch();
						if(ch_need_filter == '0' || ch_need_filter == '1'){
							fflush(stdin);
							system("cls");
							break;
						}else{
							fflush(stdin);
							printf("输入不符合规范，请重新输入！");
							system("pause");
							system("cls");
						}
					}
					system("cls");
					printSearchIcon();
					printf("--------------------------------------------------\n");
					searchSiteByLocation(sitehead, ch_need_filter - '0', strLocation);
					goToReserve(sitehead, apmthead, userhead);
					system("cls");
				}else{
					fflush(stdin);
					printf("输入有误哦，请重新输入！\n");
					system("pause");
					system("cls");
				}
			}
		} else if (ch_search_or_rank == '1') {
			fflush(stdin);
			system("cls");
			while(TRUE){
				printSearchIcon();
				printf("--------------------------------------------------\n");
				printf("查看所有场地的各项数据排名。\n\n");
				printf("按下 0 查看 \033[0m\033[1;34m[按租金排序所有场地]\033[0m\n");
				printf("按下 1 查看 \033[0m\033[1;34m[按预定量排序所有场地]\033[0m\n");
				printf("按下 \033[0m\033[1;33mESC\033[0m [返回上一级]\n");
				char ch_search_type = getch();
				if(ch_search_type == 27){
					fflush(stdin);
					system("cls");
					return 0;
				}else if(ch_search_type == '0'){
					system("cls");
					printSearchIcon();
					printf("--------------------------------------------------\n");
					printf("按照租金排序的结果如下：\n");
					printf("--------------------------------------------------\n");
					SiteInfoNode* move = sitehead->next;
					int num = 0;
					while (move != NULL) {
						num++;
						move = move->next;
					}
					const int SITE_NUM = num;
					
					char IDArray[SITE_NUM][11];
					move = sitehead->next;
					num = 0;
					while (move != NULL) {
						strcpy(IDArray[num], move->siteInfo.siteID);
						num++;
						move = move->next;
					}
					
					for (int i = 1; i <= SITE_NUM - 1; i++)
					{
						for (int j = 0; j <= SITE_NUM - 1 - i; j++)
						{
							SiteInfo site_j = querySiteInfo(sitehead, IDArray[j]);
							SiteInfo site_j_add1 = querySiteInfo(sitehead, IDArray[j+1]);
							if (site_j.siteRent > site_j_add1.siteRent)//相邻两个元素的租金如果逆序，则交换位置
							{
								char temp[11];
//								strcpy(temp, "");
								strcpy(temp, IDArray[j]);
								strcpy(IDArray[j], IDArray[j + 1]);
								strcpy(IDArray[j + 1], temp);
							}
						}
					}
					for(int i=0;i<=SITE_NUM-1;i++){
						SiteInfo site_i = querySiteInfo(sitehead, IDArray[i]);
						printOneSiteInfo(site_i);
						printf("该场地的租金为：\033[0m\033[1;33m%.2lf\033[0m\n\n", site_i.siteRent);
					}
					goToReserve(sitehead, apmthead, userhead);
					system("cls");
				}else if(ch_search_type == '1'){
					system("cls");
					printSearchIcon();
					printf("--------------------------------------------------\n");
					printf("按照预定量排序的结果如下：\n");
					printf("--------------------------------------------------\n");
					SiteInfoNode* move = sitehead->next;
					int num = 0;
					while (move != NULL) {
						num++;
						move = move->next;
					}
					const int SITE_NUM = num;
					
					char IDArray[SITE_NUM][11];
					move = sitehead->next;
					num = 0;
					while (move != NULL) {
						strcpy(IDArray[num], move->siteInfo.siteID);
						num++;
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
						printOneSiteInfo(site_i);
						printf("该场地的预定量为：\033[0m\033[1;33m%d\033[0m\n\n", site_i.siteUsedTimes);
					}
					goToReserve(sitehead, apmthead, userhead);
					system("cls");
				}else {
					fflush(stdin);
					printf("输入有误哦，请重新输入！\n");
					system("pause");
					system("cls");
				}
			}
		} else {
			fflush(stdin);
			printf("输入有误哦，请重新输入！\n");
			system("pause");
			system("cls");
		}
	}
}

//==========================订单管理流程函数===============================

int doApmtManage(UserInfoNode* userhead, SiteInfoNode* sitehead, AppointmentInfoNode* apmthead) {
	while(TRUE){
		system("cls");
		printSearchIcon();
		printf("--------------------------------------------------\n");
		printf("您当前已有的预约内容为：\n");
		printf("--------------------------------------------------\n");
		int index = 0; 
		AppointmentInfoNode* move = apmthead->next;
		while (move != NULL) {
			if(strcmp(move->apmtInfo.apmtUsrID, glb_usrID) == 0){
				printf("\033[0m\033[1;34m[%d]\033[0m", index);
				printOneApmtInfo(move->apmtInfo);
				index++;
			}
			move = move->next;
		}
		if(index == 0){
			printf("当前没有任何订单！\n");
			printf("--------------------------------------------------\n");
		}
		printf("按下 0 开始 \033[0m\033[1;34m[取消预约]\033[0m\n");
		printf("按下 \033[0m\033[1;33mESC\033[0m [返回上一级]\n");
		char ch_search_or_rank = getch();
		if (ch_search_or_rank == 27) {
			fflush(stdin);
			system("cls");
			return 0;
		}else if(ch_search_or_rank == '0'){
			char index_num[5];
			fflush(stdin);
			printf("注意：取消预约后，预缴纳的租金不会退款！\n请输入需要取消的预约前的标志序号数字：");
			safegets(index_num, 5);
			if(!isValidIndex(index_num, index)){
				fflush(stdin);
				printf("输入不合规范或超出范围，请重试！");
				system("pause");
				system("cls");
			}else{
				int del_index = 0;
				AppointmentInfoNode* move = apmthead;
				while (move->next != NULL) {
					if(strcmp(move->next->apmtInfo.apmtUsrID, glb_usrID) == 0){
						del_index++;
						if(del_index == atoi(index_num)+1){
							printf("正在删除...\n");
							AppointmentInfoNode* tmp = move->next;
							move->next = move->next->next;
							free(tmp);
							tmp = NULL;
							saveApmtInfo(apmthead);
							printf("预约信息删除成功！...\n");
							system("pause");
							continue;
						}
					}
					move = move->next;
				}
			}
		}
	}
}
