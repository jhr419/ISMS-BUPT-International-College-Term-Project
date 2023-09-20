/* 
* @File					: UserComponent.c
* @Brief			    : user operations function file
* @Description		    : 用户操作的函数实现文件
* @Author				: 张硕、高德润
* @Created Date			: 2023/8/28
* @Last modified date	: 2023/8/31 
* @note                 ：本函数实现用户操作的校验函数和流程控制函数。
 * 该设计的亮点在于，该系统的流程控制函数采用循环+状态变量的设计，不需要过多的循环嵌套。
 * 可读性强，思路清晰，同时在用户层面更加便捷、可视化强。
 */
#include "DataToolkit.c"
#include <ctype.h>//该头文件用于识别输入内容类别（字母或数字）

extern char glb_usrID[11];

//==========================校验用工具函数===============================
//函数1：判断用户输入的ID是否合法
int isValidUserID(char strID[11]) {

	/*
	 * @brief		判断用户输入的ID是否合法
	 * @param		用户输入的ID字符串
	 * @note		6-10位，只包含字母与数字
	 * @return		合法: TRUE; 不合法: FALSE;
	 */
	int i=0;
	for(i=0; strID[i]; i++)
	{
		if (!isalpha(strID[i]) && !isdigit(strID[i])) return FALSE;
	}
	//逐个遍历，判断是否为数字或字母。该方法后续复用，不再解释。
	if(i<6 || i >10) return FALSE;//长度判断
	return TRUE;
}
//函数2：判断用户输入的名字是否合法
int isValidUserName(char strName[16]) {
	
	/*
	 * @brief		判断用户输入的名字是否合法
	 * @param		用户输入的名字字符串
	 * @note		char[16]以内，最多七个纯汉字字符
	 * @return		合法: TRUE; 不合法: FALSE;
	 */
	int i = 0;
	for(i=0; strName[i];)
	{
		i++;//使用strlen函数亦可，作者基于敏捷开发使用循环实现多函数内复用。此后不再解释。
	}
	if(i<1 || i >15) return FALSE;
	return TRUE;
}
//函数3：判断用户输入的性别是否合法
int isValidUserGender(char charGender) {
	
	/*
	 * @brief		判断用户输入的性别是否合法
	 * @param		用户输入的性别字符
	 * @note		建议主函数使用getch()获取用户输入，判断时只能是1或0
	 * @return		合法: TRUE; 不合法: FALSE;
	 */
	if(charGender == '1' || charGender == '0'){
		return TRUE;
	}
	else{
		return FALSE;
	}
}
//函数4：判断用户输入的年龄是否合法
int isValidUserAge(char strinput[6]) {
	
	/*
	 * @brief		判断用户输入的年龄是否合法
	 * @param		用户输入的年龄字符串
	 * @note		输入小于100的纯数字年龄
	 * @return		合法: TRUE; 不合法: FALSE;
	 */
	int i=0;
	for(i=0; strinput[i]; i++)
	{
		if (!isdigit(strinput[i])) return FALSE;
	}
	if(i > 3) return FALSE;
	int age = atoi(strinput);//非常见函数。用于将数字字符串转化为整数int型，便于下文进行判断。
	if(age > 99 || age < 1) return FALSE;
	return TRUE;
}

//函数5：判断用户输入的手机号是否合法
int isValidUserPhone(char strPhone[12]) {
	
	/*
	 * @brief		判断用户输入的手机号是否合法
	 * @param		用户输入的手机号字符串
	 * @note		输入11位纯数字手机号，必须以1开头（根据常识，原则上应限制首两位数字>=13）
	 * @return		合法: TRUE; 不合法: FALSE;
	 */
	int i=0;
	for(i=0; strPhone[i]; i++)
	{
		if(i==0 && strPhone[i] != '1') return FALSE;
		if (!isdigit(strPhone[i])) return FALSE;
	}
	if(i != 11) return FALSE;
	return TRUE;
}
//函数6：判断用户输入的密码是否合法
int isValidUserPwd(char strPwd[21]) {
	
	/*
	 * @brief		判断用户输入的密码是否合法
	 * @param		用户输入的密码字符串
	 * @note		输入6-20位内的密码，只允许输入数字、字母和字符
	 * @return		合法: TRUE; 不合法: FALSE;
	 */
	int i=0;
	for(i=0; strPwd[i]; i++)
	{
		 if(!isalpha(strPwd[i]) && !isdigit(strPwd[i]) && !ispunct(strPwd[i])) return FALSE;
	}
	if(i<6 || i >20) return FALSE;
	return TRUE;
}
//函数7：判断用户输入的邮箱是否合法
int isValidUserEmail(char pszEmail[41]) {

	/*
	 * @brief		判断用户输入的邮箱是否合法
	 * @param		用户输入的邮箱字符串
	 * @note		输入40位以内的邮箱，只能是数字，字母，符号，必须符合邮箱格式（详细功能见下方解释）
	 * @return		合法: TRUE; 不合法: FALSE;
	 */
	if(pszEmail == NULL)
	{
		return FALSE;//输入邮箱不能为空
	}
	int iAtPos = 0;//@出现的位置
	int iLastDotPos = 0;//最后一个点的位置
	int i = 0;//总长度捏
	int iAtTimes = 0;//@出现的次数
	while(*(pszEmail + i) != '\0')
	{
		char ch = *(pszEmail + i);
		if (!isalpha(ch) && !isdigit(ch) && !ispunct(ch)) return FALSE;//既不是字母也不是数字还不是标点则有误
		if(!isprint(ch) || isspace(ch))//如果是空格或不可显示字符则有误
		{
			iAtTimes = 0;
			break;
		}
		if(ch == '@')
		{
			iAtPos = i;
			//实际上，坦白来讲，这里和下面的i改为i+1，下面的3改为2更好理解。差之毫厘谬以千里。之所以写成这样是由于指针缘故
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
//函数8：判断用户输入的地理位置是否合法
int isValidUserLocation(char strLocation[256]) {
	
	/*
	 * @brief		判断用户输入的地理位置是否合法
	 * @param		用户输入的地理位置字符串
	 * @note		char[255]以内
	 * @return		合法: TRUE; 不合法: FALSE;
	 */
	int i = 0;
	for(i=0; strLocation[i];)
	{
		i++;
	}
	if(i<1 || i >255) return FALSE;
	return TRUE;
}
//函数9：判断用户输入的场地是否合法
int isValidVenue(char strVenue[65]) {
	
	/*
	 * @brief		判断用户输入的场地是否合法
	 * @param		用户输入的场地字符串
	 * @note		char[64]以内
	 * @return		合法: TRUE; 不合法: FALSE;
	 */
	int i = 0;
	for(i=0; strVenue[i];)
	{
		i++;
	}
	if(i<1 || i >64) return FALSE;
	return TRUE;
}
//函数10：判断管理员输入的场地价格是否合法
int isValidDoubleNumStr(char strInput[7]){
	/*
	 * @brief		判断管理员输入的场地价格是否合法
	 * @param		管理员输入的场地价格字符串
	 * @note		char[7]以内，必须是两位小数，大小在1.00和200.00之间
	 * @return		合法: TRUE; 不合法: FALSE;
	 */
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
	if(num_after_dot != 3) return FALSE;//实践出真知。不论怎样，此处字符串末尾的\0也被当做了数字。。
	if(strtod(strInput, NULL) < 1.00 || strtod(strInput, NULL) > 200.00) return FALSE;
	//strtod用于将字符串转化为浮点数。两个参数分别对应字符串的起始和末尾。末尾一般默认为null
	return TRUE;
}

//==================================以下是注册流程函数==========================================

void printRegIcon() {
	/*
	 * @brief		用于打印“register”图标
	 * @param		null
	 * @note		注册图标打印函数
	 * @return		null
	 */
	printf("\033[0m\033[1;36m%s\033[0m", "    ____             _      __           \n");
	printf("\033[0m\033[1;36m%s\033[0m", "   / __ \\___  ____ _(_)____/ /____  _____\n");
	printf("\033[0m\033[1;36m%s\033[0m", "  / /_/ / _ \\/ __ `/ / ___/ __/ _ \\/ ___/\n");
	printf("\033[0m\033[1;36m%s\033[0m", " / _, _/  __/ /_/ / (__  ) /_/  __/ /    \n");
	printf("\033[0m\033[1;36m%s\033[0m", "/_/ |_|\\___/\\__, /_/____/\\__/\\___/_/     \n");
	printf("\033[0m\033[1;36m%s\033[0m", "           /____/                        \n");
	printf("\033[0m\033[1;36m%s\033[0m", "当前注册完成状态：\n");
}

char *safegets(char data[], int count) {
	
	/*
	 * @brief		用于安全读入字符串
	 * @param		待输入的字符串、最大读取的字符串的长度
	 * @note		封装了安全的fgets(stdin)，会替换掉读进来的\n
	 * @return		成功: 字符串指针safegets; 失败: 不返回;
	 */
	
	fgets(data, count, stdin);
	char *find = strchr(data, '\n');//字符串中查找字符操作
	if(find)
		*find = '\0';
	return safegets;
}

BOOL doRegisterCheck(BOOL valid_id, BOOL valid_name, BOOL valid_gender, BOOL valid_age, BOOL valid_phone, BOOL valid_email, BOOL valid_pwd, BOOL valid_location){
	/*
	 * @brief		用于检验是否注册成功
	 * @param		各种用户输入的数据是否有效的bool型变量
	 * @note		短小但很重要！！！
	 * @return		均合法: TRUE; 存在不合法: FALSE;
	 */
	if(valid_id && valid_name && valid_gender && valid_age && valid_phone && valid_email && valid_pwd && valid_location){
		return TRUE;
	}else{
		return FALSE;
	}
}

void print_status(BOOL valid_id, BOOL valid_name, BOOL valid_gender, BOOL valid_age, BOOL valid_phone, BOOL valid_email, BOOL valid_pwd, BOOL valid_location){
	/*
	 * @brief		打印注册数据录入状态的函数
	 * @param		各种用户输入的数据是否有效的bool型变量
	 * @note		对于系统进程可视性十分关键
	 * @return		null
	 */
	char status_finished[128] = "\033[0m\033[1;32m[已完成]\033[0m";
	char status_need_fill[128] = "\033[0m\033[1;31m[待填写]\033[0m";
	char* status[2] = {status_need_fill, status_finished};//巧妙的状态数组（用于打印，展示给用户）
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
	
	/*
	 * @brief		用户注册进程界面函数
	 * @param		用户信息头结点指针
	 * @note		注册进程的终端用户交互界面
	 * @return		null
	 */
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
				//每个数据的输入及校验都要包含进程提示图标函数
				printf("\033[0m\033[1;33m[进行中]\033[0m %s", "请输入用户ID；要求6-10位，全部由字母和数字组成：");
				safegets(strID, 12);
				if(isUserExist(head, strID)){
					fflush(stdin);
					printf("此用户名已存在！");
					system("pause");
					system("cls");//应注意到，每次输入后不论正确与否，都要进行清屏操作，给用户以清晰的体验。
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
	//可以看到，将校验函数与流程控制（页面）函数分立开设计，可以使整个逻辑清晰可辨。
	printRegIcon();//首尾呼应！
	//将用户输入的合法信息通过打印进行展示
	printf("\033[0m\033[1;32m%s\033[0m", "恭喜，注册已全部成功完成！\n您输入的信息是：\n");
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
		.usrGender = charGender - 48,//字符转数字
		.usrAge = atoi(strinput),
		.usrMoney = 100.00,
		.usrBreakAppointmentTimes = 0//用户违约次数————埋下伏笔
	};
	strcpy(usrData.usrID, strID);
	strcpy(usrData.usrName, strName);
	strcpy(usrData.usrPhone, strPhone);
	strcpy(usrData.usrPwd, strPwd);
	strcpy(usrData.usrEmail, strEmail);
	strcpy(usrData.usrLocation, strLocation);
	//利用链表写文件
	if(InsertToUserInfo(head, usrData) == 0){
		printf("\033[0m\033[1;32m[成功]\033[0m %s", "注册已成功完成！\n");
	}else{
		printf("\033[0m\033[1;31m[失败]\033[0m %s", "注册失败！原因：使用了未经检查的数据！\n");
	}
	saveUserInfo(head);
	system("pause");
	system("cls");
}

//==============================================登录流程函数=====================================================

void printLoginIcon(){
	/*
	 * @brief		用于打印“Login”图标
	 * @param		null
	 * @note		登录图标打印函数
	 * @return		null
	 */
	printf("\033[0m\033[1;36m%s\033[0m", "    __                _     \n");
	printf("\033[0m\033[1;36m%s\033[0m", "   / /   ____  ____ _(_)___ \n");
	printf("\033[0m\033[1;36m%s\033[0m", "  / /   / __ \\/ __ `/ / __ \\\n");
	printf("\033[0m\033[1;36m%s\033[0m", " / /___/ /_/ / /_/ / / / / /\n");
	printf("\033[0m\033[1;36m%s\033[0m", "/_____/\\____/\\__, /_/_/ /_/ \n");
	printf("\033[0m\033[1;36m%s\033[0m", "            /____/          \n");
	printf("\033[0m\033[1;36m%s\033[0m", "当前登录信息填写情况：\n");
}

BOOL doLoginCheck(BOOL valid_id, BOOL valid_pwd){
	/*
	 * @brief		用于检验是否登录成功
	 * @param		显示用户输入的ID、密码等数据是否有效的bool型变量
	 * @note		短小但很重要！！！
	 * @return		均合法: TRUE; 存在不合法: FALSE;
	 */
	if(valid_id && valid_pwd){
		return TRUE;
	}else{
		return FALSE;
	}
}

void print_login_status(BOOL valid_id, BOOL valid_pwd){
	/*
	 * @brief		打印登录数据录入状态的函数
	 * @param		各种用户输入的数据是否有效的bool型变量
	 * @note		对于系统进程可视性十分关键
	 * @return		null
	 */
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
	/*
	 * @brief		用户登录进程界面函数
	 * @param		用户信息头结点指针
	 * @note		登录进程的终端用户交互界面
	 * @return		成功：0；失败：1
	 */
	BOOL valid_id = FALSE, valid_pwd = FALSE;
	BOOL matched = FALSE;
	int wrong_pwd_times = 0;
	//使用全局变量glb_usrID[11]来保存用户ID，十分滴巧妙
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
	/*
	 * @brief		用于打印用户中心图标
	 * @param		null
	 * @note		用户中心图标打印函数
	 * @return		null
	 */
	printf("\033[0m\033[1;36m%s\033[0m", "   __  __                  ______           __           \n");
	printf("\033[0m\033[1;36m%s\033[0m", "  / / / /_______  _____   / ____/__  ____  / /____  _____\n");
	printf("\033[0m\033[1;36m%s\033[0m", " / / / / ___/ _ \\/ ___/  / /   / _ \\/ __ \\/ __/ _ \\/ ___/\n");
	printf("\033[0m\033[1;36m%s\033[0m", "/ /_/ (__  )  __/ /     / /___/  __/ / / / /_/  __/ /    \n");
	printf("\033[0m\033[1;36m%s\033[0m", "\\____/____/\\___/_/      \\____/\\___/_/ /_/\\__/\\___/_/     \n");
	printf("欢迎 %s 使用系统！\n", glb_usrID);
	
}

void printCurrentUsrInfo(UserInfoNode* head) {
	/*
	 * @brief		用于修改信息前打印用户信息
	 * @param		用户信息头结点
	 * @note		用户信息打印函数
	 * @return		null
	 */
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
	printf("\033[0m\033[1;31m[x>]\033[0m 余额：\t%lf\n", crUsrInfo.usrMoney);
	printf("\033[0m\033[1;31m[x>]\033[0m 违约次数：\t%d\n", crUsrInfo.usrBreakAppointmentTimes);
	printf("--------------------------------------------------\n");
}

int doUsrInfoEdit(UserInfoNode* head){
	/*
	 * @brief		用户信息修改函数
	 * @param		用户信息头结点指针
	 * @note		null 
	 * @return		成功：0；失败：1
	 */
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
	printf("\033[0m\033[1;34m%s\033[0m", "   / __ \___  ________  ______   ______ _/ /_(_)___  ____ \n");
	printf("\033[0m\033[1;34m%s\033[0m", "  / /_/ / _ \\/ ___/ _ \\/ ___/ | / / __ `/ __/ / __ \\/ __ \\\n");
	printf("\033[0m\033[1;34m%s\033[0m", " / _, _/  __(__  )  __/ /   | |/ / /_/ / /_/ / /_/ / / / /\n");
	printf("\033[0m\033[1;34m%s\033[0m", "/_/ |_|\\___/____/\\___/_/    |___/\\__,_/\\__/_/\\____/_/ /_/ \n\n");
	printf("\033[0m\033[1;34m%s\033[0m", "你还在排队？我已经预约好场馆了！");
}

void print_reserve_status(BOOL valid_1, BOOL valid_2, BOOL valid_3){
	char status_finished[128] = "\033[0m\033[1;32m[OK]\033[0m";
	char status_need_fill[128] = "\033[0m\033[1;31m[-]\033[0m";
	char* status[2] = {status_need_fill, status_finished};
	printReserveIcon();
	printf("--------------------------------------------------\n");
	printf("%s 填写用户ID，要求6-10位，全部由字母或数字组成\n", status[valid_1]);
	printf("%s 填写密码，要求6-20位，只能包含字母、数字和符号\n", status[valid_2]);
	printf("%s 填写密码，要求6-20位，只能包含字母、数字和符号\n", status[valid_3]);
	printf("--------------------------------------------------\n");
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

void searchSiteByName(SiteInfoNode* sitehead, BOOL need_filter, char strSiteName[65]){
	SiteInfoNode* move = sitehead->next;
	int valid_num = 0;
	if(!need_filter){
		printf("搜索 \033[0m\033[1;33m%s\033[0m 查找到如下结果：\n", strSiteName);
		printf("--------------------------------------------------\n");
		while (move != NULL) {
			if (strstr(move->siteInfo.siteName, strSiteName) != NULL) {
				valid_num++;
				printf("场地ID：%s 场地名称：%s 场地位置：%s 场地所属场馆：%s 场地运动类型：%s\n", move->siteInfo.siteID, move->siteInfo.siteName, move->siteInfo.siteLocation, move->siteInfo.siteVenueID, move->siteInfo.siteSportsType);
			}
			move = move->next;
		}
		if(valid_num == 0) printf("\033[0m\033[1;31m%s\033[0m", "未查找到符合要求的场地！\n");
		printf("--------------------------------------------------\n");
	}
}

void searchSiteByVenue(SiteInfoNode* sitehead, BOOL need_filter, char strSiteVenue[65]){
	SiteInfoNode* move = sitehead->next;
	int valid_num = 0;
	if(!need_filter){
		printf("搜索 \033[0m\033[1;33m%s\033[0m 查找到如下结果：\n", strSiteVenue);
		printf("--------------------------------------------------\n");
		while (move != NULL) {
			if (strstr(move->siteInfo.siteVenueID, strSiteVenue) != NULL) {
				valid_num++;
				printf("场地ID：%s 场地名称：%s 场地位置：%s 场地所属场馆：%s 场地运动类型：%s\n", move->siteInfo.siteID, move->siteInfo.siteName, move->siteInfo.siteLocation, move->siteInfo.siteVenueID, move->siteInfo.siteSportsType);
			}
			move = move->next;
		}
		if(valid_num == 0) printf("\033[0m\033[1;31m%s\033[0m", "未查找到符合要求的场地！\n");
		printf("--------------------------------------------------\n");
	}
}

void searchSiteBySportsType(SiteInfoNode* sitehead, BOOL need_filter, char strSiteSportsType[65]){
	SiteInfoNode* move = sitehead->next;
	int valid_num = 0;
	if(!need_filter){
		printf("搜索 \033[0m\033[1;33m%s\033[0m 查找到如下结果：\n", strSiteSportsType);
		printf("--------------------------------------------------\n");
		while (move != NULL) {
			if (strstr(move->siteInfo.siteSportsType, strSiteSportsType) != NULL) {
				valid_num++;
				printf("场地ID：%s 场地名称：%s 场地位置：%s 场地所属场馆：%s 场地运动类型：%s\n", move->siteInfo.siteID, move->siteInfo.siteName, move->siteInfo.siteLocation, move->siteInfo.siteVenueID, move->siteInfo.siteSportsType);
			}
			move = move->next;
		}
		if(valid_num == 0) printf("\033[0m\033[1;31m%s\033[0m", "未查找到符合要求的场地！\n");
		printf("--------------------------------------------------\n");
	}
}

void searchSiteByLocation(SiteInfoNode* sitehead, BOOL need_filter, char strSiteLocation[256]){
	SiteInfoNode* move = sitehead->next;
	int valid_num = 0;
	if(!need_filter){
		printf("搜索 \033[0m\033[1;33m%s\033[0m 查找到如下结果：\n", strSiteLocation);
		printf("--------------------------------------------------\n");
		while (move != NULL) {
			if (strstr(move->siteInfo.siteLocation, strSiteLocation) != NULL) {
				valid_num++;
				printf("场地ID：%s 场地名称：%s 场地位置：%s 场地所属场馆：%s 场地运动类型：%s\n", move->siteInfo.siteID, move->siteInfo.siteName, move->siteInfo.siteLocation, move->siteInfo.siteVenueID, move->siteInfo.siteSportsType);
			}
			move = move->next;
		}
		if(valid_num == 0) printf("\033[0m\033[1;31m%s\033[0m", "未查找到符合要求的场地！\n");
		printf("--------------------------------------------------\n");
	}
}

int doSiteSearch(SiteInfoNode* sitehead) {
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
					system("pause");
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
					system("pause");
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
					system("pause");
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
					system("pause");
					system("cls");
				}
			}
		} else if (ch_search_or_rank == '1') {
			printf("2");
		} else {
			fflush(stdin);
			printf("输入有误哦，请重新输入！\n");
			system("pause");
			system("cls");
		}
	}
}
