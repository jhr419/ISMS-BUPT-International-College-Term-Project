#include "AdminComponent.c"

//GLOBAL VARIABLES
BOOL is_user = FALSE;
BOOL is_admin = FALSE;
BOOL has_logined = FALSE;
char glb_usrID[11];
char glb_adminID[11];

void printWelcomeIcon() {
	printf("\033[0m\033[1;36m%s\033[0m", " _       __     __                          __\n");
	printf("\033[0m\033[1;36m%s\033[0m", "| |     / /__  / /________  ____ ___  ___  / /\n");
	printf("\033[0m\033[1;36m%s\033[0m", "| | /| / / _ \\/ / ___/ __ \\/ __ `__ \\/ _ \\/ / \n");
	printf("\033[0m\033[1;36m%s\033[0m", "| |/ |/ /  __/ / /__/ /_/ / / / / / /  __/_/  \n");
	printf("\033[0m\033[1;36m%s\033[0m", "|__/|__/\\___/_/\\___/\\____/_/ /_/ /_/\\___(_)   \n");
	printf("\033[0m\033[1;36m%s\033[0m", "                                              \n");
	printf("\033[0m\033[1;36m%s\033[0m", "欢迎使用综合体育场馆管理系统！\n");
}

int main() {
	InitAllHeadNode
	while (TRUE) {
		if (!is_user && !is_admin && !has_logined) {
			system("cls");
			printWelcomeIcon();
			printf("--------------------------------------------------\n");
			printf("您的使用者身份是？\n\n");
			printf("按下 0 选择 \033[0m\033[1;34m[用户]\033[0m 身份\n");
			printf("按下 1 选择 \033[0m\033[1;35m[管理员]\033[0m 身份\n");
			printf("按下 ESC 直接 \033[0m\033[1;31m[退出系统]\033[0m\n");
			char ch_choose_identity = getch();
			if(ch_choose_identity == 27){
				exit(0);
			}
			if (ch_choose_identity == '0') {
				fflush(stdin);
				is_user = TRUE;
				continue;
			} else if (ch_choose_identity == '1') {
				fflush(stdin);
				is_admin = TRUE;
				continue;
			} else {
				fflush(stdin);
				printf("输入有误哦，请重新输入！\n");
				system("pause");
				system("cls");
			}
		} else if (is_user && !is_admin && !has_logined) {
			system("cls");
			printWelcomeIcon();
			printf("--------------------------------------------------\n");
			printf("登录？还是注册一个新的账号？\n\n");
			printf("按下 0 开始 \033[0m\033[1;34m[登录]\033[0m\n");
			printf("按下 1 开始 \033[0m\033[1;32m[注册新账号]\033[0m\n");
			printf("按下 ESC 直接 \033[0m\033[1;31m[返回上一级]\033[0m\n");
			char ch_login_or_reg = getch();
			if (ch_login_or_reg == '0') {
				fflush(stdin);
				if (doLogin(usrInfoHead) == 0) has_logined = TRUE;
				continue;
			} else if (ch_login_or_reg == '1') {
				fflush(stdin);
				doRegister(usrInfoHead);
				continue;
			} else if (ch_login_or_reg == 27) {
				fflush(stdin);
				is_user = FALSE;
				continue;
			} else {
				fflush(stdin);
				printf("输入有误哦，请重新输入！\n");
				system("pause");
				system("cls");
			}
		} else if (!is_user && is_admin && !has_logined) {
			system("cls");
			printAdminIcon();
			printf("--------------------------------------------------\n");
			printf("登录为管理员，或以主管身份添加场馆并指定其管理者。\n\n");
			printf("按下 0 开始 \033[0m\033[1;34m[管理员登录]\033[0m\n");
			printf("按下 1 开始 \033[0m\033[1;32m[添加新场馆并指定管理者]\033[0m\n");
			printf("按下 ESC 直接 \033[0m\033[1;31m[返回上一级]\033[0m\n");
			char ch_admin_login_or_reg = getch();
			if (ch_admin_login_or_reg == '0') {
				fflush(stdin);
				if (doAdminLogin(adminInfoHead) == 0) has_logined = TRUE;
				continue;
			} else if (ch_admin_login_or_reg == '1') {
				fflush(stdin);
				doAdminRegister(adminInfoHead);
				continue;
			} else if (ch_admin_login_or_reg == 27) {
				fflush(stdin);
				is_admin = FALSE;
				continue;
			} else {
				fflush(stdin);
				printf("输入有误哦，请重新输入！\n");
				system("pause");
				system("cls");
			}
		} else if (is_user && !is_admin && has_logined) {
			system("cls");
			printUsrCenterIcon();
			printf("--------------------------------------------------\n");
			printf("您希望执行什么操作？\n\n");
			printf("按下 0 开始 \033[0m\033[1;34m[查询场地]\033[0m，查询现有的场地，查询后可直接预定\n");
			printf("按下 1 开始 \033[0m\033[1;34m[预定场地]\033[0m，直接预定场地\n");
			printf("按下 2 开始 \033[0m\033[1;34m[管理订单]\033[0m，查询/取消自己预定的场地\n");
			printf("按下 3 开始 \033[0m\033[1;34m[修改信息]\033[0m，修改自己的电话、密码等信息\n");
			printf("按下 ESC 退出登录并 \033[0m\033[1;33m[返回上一级]\033[0m\n");
			char ch_usr_op = getch();
			if (ch_usr_op == '0') {
				fflush(stdin);
				system("cls");
				doSiteSearch(siteInfoHead, apmtInfoHead, usrInfoHead);
				continue;
			} else if (ch_usr_op == '1') {
				fflush(stdin);
				system("cls");
				doSiteReserve(siteInfoHead, apmtInfoHead, usrInfoHead);
				continue;
			} else if (ch_usr_op == '2') {
				fflush(stdin);
				system("cls");
				doApmtManage(usrInfoHead, siteInfoHead, apmtInfoHead);
				continue;
			} else if (ch_usr_op == '3') {
				fflush(stdin);
				system("cls");
				doUsrInfoEdit(usrInfoHead);
				continue;
			} else if (ch_usr_op == 27) {
				fflush(stdin);
				system("cls");
				printUsrCenterIcon();
				printf("--------------------------------------------------\n");
				printf("已退出登录。\n");
				strcpy(glb_usrID, "");
				has_logined = FALSE;
				system("pause");
				continue;
			} else {
				fflush(stdin);
				printf("输入有误哦，请重新输入！\n");
				system("pause");
				system("cls");
			}
		} else if (!is_user && is_admin && has_logined) {
			system("cls");
			printAdminIcon();
			printf("--------------------------------------------------\n");
			printf("您希望执行什么操作？\n\n");
			printf("按下 0 开始 \033[0m\033[1;34m[查看预定信息]\033[0m，查看用户预定情况\n");
			printf("按下 1 开始 \033[0m\033[1;34m[查看统计信息]\033[0m，查看管理场馆中场地的统计信息\n");
			printf("按下 2 开始 \033[0m\033[1;34m[管理场地]\033[0m，查看/添加场馆中的场地\n");
			printf("按下 3 开始 \033[0m\033[1;34m[修改信息]\033[0m，修改自己的电话、密码等信息\n");
			printf("按下 4 开始 \033[0m\033[1;34m[用户充值]\033[0m，为用户充值\n");
			printf("按下 5 开始 \033[0m\033[1;31m[设置用户违约]\033[0m，确认这一用户有违约行为\n");
			printf("按下 ESC 退出登录并 \033[0m\033[1;33m[返回上一级]\033[0m\n");
			char ch_admin_op = getch();
			if (ch_admin_op == '0') {
				fflush(stdin);
				system("cls");
				printAdminIcon();
				printf("--------------------------------------------------\n");
				printAdminVenueApmt(siteInfoHead, adminInfoHead, apmtInfoHead);
				system("pause");
				continue;
			} else if (ch_admin_op == '1') {
				fflush(stdin);
				system("cls");
				doAdminStatistics(siteInfoHead, adminInfoHead, apmtInfoHead, usrInfoHead);
				continue;
			} else if (ch_admin_op == '2') {
				fflush(stdin);
				system("cls");
				doAdminAddSite(siteInfoHead, adminInfoHead);
				continue;
			} else if (ch_admin_op == '3') {
				fflush(stdin);
				system("cls");
				doAdminInfoEdit(adminInfoHead);
				continue;
			} else if (ch_admin_op == '4') {
				fflush(stdin);
				system("cls");
				doCredit(usrInfoHead);
				continue;
			}else if (ch_admin_op == '5') {
				fflush(stdin);
				system("cls");
				doSetUserBreak(usrInfoHead);
				continue;
			} else if (ch_admin_op == 27) {
				fflush(stdin);
				system("cls");
				printAdminIcon();
				printf("--------------------------------------------------\n");
				printf("已退出登录。\n");
				strcpy(glb_adminID, "");
				has_logined = FALSE;
				system("pause");
				continue;
			} else {
				fflush(stdin);
				printf("输入有误哦，请重新输入！\n");
				system("pause");
				system("cls");
			}
		}
	}
}
