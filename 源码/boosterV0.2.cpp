#include<windows.h>
#include<iostream>
#define SERVICE_NO_ERROR 0
#define OPEN_SCMANAGER_ERROR 2
#define OPEN_SERVICE_ERROR 3
#define QUERY_SERVICESTATUS_ERROR 4
#define STOP_SERVICE_ERROR 5
#define START_SERVICE_ERROR 6

 
 using namespace std;
 
 int RestartService()
{
 
    // 打开服务管理对象
    SC_HANDLE hSC = ::OpenSCManager( NULL,
        NULL, GENERIC_EXECUTE);
    if( hSC == NULL)
    {      
        return OPEN_SCMANAGER_ERROR;
    }
    // 打开apache服务。
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
    	cout<<"正在优化第一个项目。。。"<<endl; 
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
    // 打开apache服务。
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
    	cout<<"正在优化第二个项目。。。"<<endl; 
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


int main()
{
	cout<<"欢迎使用郑州一中电阅优化器！Designed by 翎风 Ver0.2Beta"<<endl; 
	Sleep(800); 
	cout<<"正在进行优化，共两个项目。如果中途卡死，请重启优化器！"<<endl; 
	RestartService();
	cout<<"正在进行优化，已完成一个项目，剩余一个项目。"<<endl;
	RestartServicewu();
	cout<<"优化全部完成！"<<endl; 
	Sleep(3000); 
	return 0;
	
 } 

