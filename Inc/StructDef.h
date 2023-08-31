//  __          __              _             _ _ _ 
//  \ \        / /             (_)           | | | |
//   \ \  /\  / /_ _ _ __ _ __  _ _ __   __ _| | | |
//    \ \/  \/ / _` | '__| '_ \| | '_ \ / _` | | | |
//     \  /\  / (_| | |  | | | | | | | | (_| |_|_|_|
//      \/  \/ \__,_|_|  |_| |_|_|_| |_|\__, (_|_|_)
//                                       __/ |      
//	                                    |___/       
//  本文件定义了程序运行中使用的数据模型
//  请勿单独修改其中的任何定义，否则将可能影响工具函数的正常运行
//	Date: 20230829 张硕
//



#define BOOL int
#define TRUE 1
#define FALSE 0


//用户个人信息结构体
typedef struct _UserInfo
{
	char usrID[11];						//用户ID，6-10个字符
	char usrName[16]; 					//用户姓名，15个字符（五个汉字）以内
	int usrGender; 						//用户性别，定义0为男，1为女
	int usrAge; 						//用户年龄，整型
	char usrPhone[12]; 					//用户手机号，11个字符
	char usrPwd[21]; 					//用户密码，20个字符以内
	char usrEmail[41]; 					//用户邮箱，40个字符以内
	double usrMoney; 					//用户余额，双精度浮点
	char usrLocation[256]; 				//用户地理位置，256个字符以内
	int usrBreakAppointmentTimes; 		//用户爽约次数，整型
} UserInfo;

//用户个人信息链表节点
typedef struct _UserInfoNode
{
	UserInfo usrInfo;
	struct _UserInfoNode* next;
} UserInfoNode;



//管理员个人信息结构体
typedef struct _AdminInfo
{
	char adminID[11];					//管理员ID，6-10个字符
	char adminName[16];					//管理员姓名，15个字符以内
	int adminGender;					//管理员性别，定义0为男，1为女
	char adminPhone[12];				//管理员手机号，11个字符
	char adminPwd[21];					//管理员密码，20个字符以内
	char adminEmail[41];				//管理员邮箱，40个字符以内
	char adminVenueID[11];				//管理员管理的场馆ID，6-10个字符
} AdminInfo;

//管理员个人信息链表节点
typedef struct _AdminInfoNode
{
	AdminInfo adminInfo;
	struct _AdminInfoNode* next;
} AdminInfoNode;



//场地信息结构体
typedef struct _SiteInfo
{
	char siteID[11];					//场地ID，6-10个字符
	char siteName[16];					//场地名称，15个字符以内
	char siteLocation[256];				//场地位置，20个字符以内
	char siteVenueID[11];				//场地所属的场馆ID，6-10个字符
	char siteSportsType[11];			//场地的运动类型，10个字符以内
	char siteIntro[101];				//场地简介，100个字符以内
	int siteAllowedAge;					//场地准入年龄，整型
	int siteUsedTimes;					//场地被预约次数，整型
} SiteInfo;

//场地信息链表节点
typedef struct _SiteInfoNode
{
	SiteInfo siteInfo;
	struct _SiteInfoNode* next;
} SiteInfoNode;



//预约信息结构体
typedef struct _AppointmentInfo
{
	char apmtUsrID[11];					//发起预约的用户ID，6-10个字符
	char apmtSiteID[11];				//预约的场地ID
	char apmtOrderDated[15];			//发起预约时的时间，格式yyyymmddhhmmss(eg. 20230829105133)，注意d不是误拼
	char apmtStartDateh[11];			//预约的开始时间，格式yyyymmddhh(eg. 2023082909)，注意h不是误拼
	int apmtDurationh;					//预约持续时长，小时，整型，注意h不是误拼
	int apmtUsrGender;					//预约用户的性别，方便统计用，规定0为男，1为女
	BOOL isUsrPresent;					//用户是否到场
} ApmtInfo;

//预约信息链表节点
typedef struct _AppointmentInfoNode
{
	ApmtInfo apmtInfo;
	struct _AppointmentInfoNode* next;
} AppointmentInfoNode;


