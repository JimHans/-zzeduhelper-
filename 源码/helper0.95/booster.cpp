#include<windows.h>
#include <shellapi.h>
#include<ctime>
#include<iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#define SERVICE_NO_ERROR 0
#define OPEN_SCMANAGER_ERROR 2
#define OPEN_SERVICE_ERROR 3
#define QUERY_SERVICESTATUS_ERROR 4
#define STOP_SERVICE_ERROR 5
#define START_SERVICE_ERROR 6

 
 using namespace std;

 //产生随机IP地址
string RandIP()
{
stringstream ss;
ss << '1';
ss << '0';
ss << '.';
ss << '3';
ss << '.';
ss << '5';
ss << '.';
ss << (rand()%256);
return ss.str();
}

 /***************************************************/ 
 int RestartService()
{
 
    // 打开服务管理对象
    SC_HANDLE hSC = ::OpenSCManager( NULL,
        NULL, GENERIC_EXECUTE);
    if( hSC == NULL)
    {      
        return OPEN_SCMANAGER_ERROR;
    }
    // 打开sysmain服务。
    SC_HANDLE hSvc = ::OpenService( hSC, "SysMain",
        SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);
    if( hSvc == NULL)
    {
        ::CloseServiceHandle( hSC);
        return OPEN_SERVICE_ERROR;
    }
    // 获得服务的状态
    SERVICE_STATUS status;
    if( ::QueryServiceStatus( hSvc, &status) == FALSE)
    {
        ::CloseServiceHandle( hSvc);
        ::CloseServiceHandle( hSC);
        return QUERY_SERVICESTATUS_ERROR;
    }
    //如果处于运行状态则停止服务
    if( status.dwCurrentState == SERVICE_RUNNING)
    {
        // 停止服务
        if( ::ControlService( hSvc,
            SERVICE_CONTROL_STOP, &status) == FALSE)
        {
            ::CloseServiceHandle( hSvc);
            ::CloseServiceHandle( hSC);
            return STOP_SERVICE_ERROR;
        }
        // 等待服务停止
        while( ::QueryServiceStatus( hSvc, &status) == TRUE)
        {
            ::Sleep( status.dwWaitHint);
            if( status.dwCurrentState == SERVICE_STOPPED)
            {
                break;
            }
        }


    }

   
    ::CloseServiceHandle( hSvc);
    ::CloseServiceHandle( hSC);
    return SERVICE_NO_ERROR;
}

int RestartServicewu()
{
 
    // 打开服务管理对象
    SC_HANDLE hSC = ::OpenSCManager( NULL,
        NULL, GENERIC_EXECUTE);
    if( hSC == NULL)
    {      
        return OPEN_SCMANAGER_ERROR;
    }
    // 打开update服务。
    SC_HANDLE hSvc = ::OpenService( hSC, "wuauserv",
        SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);
    if( hSvc == NULL)
    {
        ::CloseServiceHandle( hSC);
        return OPEN_SERVICE_ERROR;
    }
    // 获得服务的状态
    SERVICE_STATUS status;
    if( ::QueryServiceStatus( hSvc, &status) == FALSE)
    {
        ::CloseServiceHandle( hSvc);
        ::CloseServiceHandle( hSC);
        return QUERY_SERVICESTATUS_ERROR;
    }
    //如果处于运行状态则停止服务
    if( status.dwCurrentState == SERVICE_RUNNING)
    {
        // 停止服务
        if( ::ControlService( hSvc,
            SERVICE_CONTROL_STOP, &status) == FALSE)
        {
            ::CloseServiceHandle( hSvc);
            ::CloseServiceHandle( hSC);
            return STOP_SERVICE_ERROR;
        }

        
        /**************************************************** 
        // 等待服务停止
        while( ::QueryServiceStatus( hSvc, &status) == TRUE)
        {
            ::Sleep( status.dwWaitHint);
            if( status.dwCurrentState == SERVICE_STOPPED)
            {
                break;
            }
        }
        ******************************************************/
    }

   
    ::CloseServiceHandle( hSvc);
    ::CloseServiceHandle( hSC);
    return SERVICE_NO_ERROR;
}



int main()
{
	string stopsys="sc config SysMain start= disabled";
string stopwu="sc config wuauserv start= disabled"; 
	system("color F0");
	srand((unsigned)time(NULL));
	string cmd="netsh interface ip set address name=\"本地连接\" static ";
	string cmd2="netsh interface ip set address name=\"本地连接 2\" static ";
	
	cout<<endl;
	cout<<"欢迎使用郑州一中电阅助手！"<<endl;

    char input;
	
		start: 
	cout<<endl;
	cout<<"请键入Y并按下回车进行优化，键入R并按下回车修复网络问题。"<<endl; 
	cout<<"键入U并按下回车查看更新日志，键入I并按下回车查看版本信息。"<<endl;
	cout<<"按其他任意键退出电阅助手。"<<endl; 
	cin>>input;
	if(input=='y'||input=='Y')
	{
    Sleep(800); 
	cout<<"正在进行优化，共两个项目。"<<endl; 
	cout<<endl;
	RestartService();
	cout<<stopsys<<endl;
    system("@echo off");
    system(stopsys.c_str());
    system("@echo on");
	cout<<"正在进行优化，已完成一个项目，剩余一个项目。"<<endl;
	cout<<endl;
	RestartServicewu();
	cout<<stopwu<<endl;
    system("@echo off");
    system(stopwu.c_str());
    system("@echo on");
    system("cls");
	cout<<"优化全部完成！"<<endl;
	goto start;  
	}
	if(input=='r'||input=='R') 
	{
    cout<<"正在自动修复网络错误。。。"<<endl; 
	string str;
    str=RandIP();
    
    string Gateway="10.3.5.1 1"; 
    string Mask="255.255.255.0";          //子网掩码
    cmd+=str+" "+Mask+" "+Gateway;
    cout<<cmd<<endl;
    system("@echo off");
    system(cmd.c_str());
    system("@echo on");
    system("ipconfig /all");
    system("cls");
    cout<<endl;
    cmd2+=str+" "+Mask+" "+Gateway;
    cout<<cmd2<<endl;
    system("@echo off");
    system(cmd2.c_str());
    system("@echo on");
    system("ipconfig /all");
    system("cls");
    cout<<endl;
    cout<<"网络错误已修复！您的IP已被更改为"<<str<<"，开始卓（tui）越（fei）吧！"<<endl;
	goto start;  
}
if(input=='u'||input=='U')
	{
		   cout<<"__________________________"<<endl;
           cout<<"|     V0.95 更新日志     |"<<endl;
		   cout<<"|1.紧急修复了部分机器网络|"<<endl;
		   cout<<"|     修复失败的问题     |"<<endl;
		   cout<<"__________________________"<<endl;
           cout<<"|     V0.90 更新日志     |"<<endl;
		   cout<<"|1.修复了大小写不分的问题|"<<endl;
		   cout<<"__________________________"<<endl;
           cout<<"|     V0.85 更新日志     |"<<endl;
		   cout<<"|1.加入了应用图标并增加官|"<<endl;
		   cout<<"|         网地址         |"<<endl; 
           cout<<"|  2.这是第一个正式版本  |"<<endl;
		   cout<<"__________________________"<<endl;
           cout<<"|   V0.8Beta 更新日志    |"<<endl;
		   cout<<"|1.终于修复了优化后内存反|"<<endl; 
           cout<<"|        弹的问题        |"<<endl;
           cout<<"|2.电阅助手优化完毕后会自|"<<endl;
           cout<<"|  动清除屏幕上的代码了  |"<<endl;
		   cout<<"__________________________"<<endl;
           cout<<"|   V0.7Beta 更新日志    |"<<endl;
           cout<<"|   1.白白的背景更好看   |"<<endl; 
           cout<<"__________________________"<<endl;
           cout<<"|   V0.6Beta 更新日志    |"<<endl; 
           cout<<"|1.版本信息现在已单独列出|"<<endl;   
           cout<<"|     2.更新日志美化     |"<<endl; 
           cout<<"| 3.提示语句更加通俗易懂 |"<<endl;
		   cout<<"|  4.优化结束后程序不会  |"<<endl; 
		   cout<<"|        自动退出        |"<<endl;
		   cout<<"| 5.修复了优化卡死的问题 |"<<endl;
		   cout<<"__________________________"<<endl;
           cout<<"|   V0.5Beta 更新日志    |"<<endl; 
           cout<<"|1.修复了IP设置失效的问题|"<<endl;   
           cout<<"|   2.增加更新日志功能   |"<<endl; 
           cout<<"|3.现在可以选择优化方式了|"<<endl; 
           cout<<"__________________________"<<endl;  
           goto start; 
              } 
              if(input=='i'||input=='I')
	{
           cout<<"__________________________"<<endl;
           cout<<"|关于  郑州一中电阅优化器|"<<endl; 
           cout<<"|      版本号：V0.95     |"<<endl;   
           cout<<"|      制作：-翎风-      |"<<endl; 
           cout<<"|   编译IDE：DevC++      |"<<endl;
		   cout<<"|         官网：         |"<<endl; 
		   cout<<"|https://dev.leyoblog.top|"<<endl;
		   cout<<"|https://github.com/JimHa|"<<endl;
		   cout<<"|ns/zzedubooster         |"<<endl;
           cout<<"|   感谢你的使用与支持！ |"<<endl; 
           cout<<"__________________________"<<endl;  
           goto start; 
              } 
	Sleep(2000);
	hard:
	 cout<<"退出成功！"<<endl;
system("pause");
	return 0;
 } 



