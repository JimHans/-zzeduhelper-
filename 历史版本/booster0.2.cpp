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
 
    // �򿪷���������
    SC_HANDLE hSC = ::OpenSCManager( NULL,
        NULL, GENERIC_EXECUTE);
    if( hSC == NULL)
    {      
        return OPEN_SCMANAGER_ERROR;
    }
    // ��apache����
    SC_HANDLE hSvc = ::OpenService( hSC, "SysMain",
        SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);
    if( hSvc == NULL)
    {
        ::CloseServiceHandle( hSC);
        return OPEN_SERVICE_ERROR;
    }
    // ��÷����״̬
    SERVICE_STATUS status;
    if( ::QueryServiceStatus( hSvc, &status) == FALSE)
    {
        ::CloseServiceHandle( hSvc);
        ::CloseServiceHandle( hSC);
        return QUERY_SERVICESTATUS_ERROR;
    }
    //�����������״̬��ֹͣ����
    if( status.dwCurrentState == SERVICE_RUNNING)
    {
    	cout<<"�����Ż���һ����Ŀ������"<<endl; 
        // ֹͣ����
        if( ::ControlService( hSvc,
            SERVICE_CONTROL_STOP, &status) == FALSE)
        {
            ::CloseServiceHandle( hSvc);
            ::CloseServiceHandle( hSC);
            return STOP_SERVICE_ERROR;
        }
        // �ȴ�����ֹͣ
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
 
    // �򿪷���������
    SC_HANDLE hSC = ::OpenSCManager( NULL,
        NULL, GENERIC_EXECUTE);
    if( hSC == NULL)
    {      
        return OPEN_SCMANAGER_ERROR;
    }
    // ��apache����
    SC_HANDLE hSvc = ::OpenService( hSC, "wuauserv",
        SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);
    if( hSvc == NULL)
    {
        ::CloseServiceHandle( hSC);
        return OPEN_SERVICE_ERROR;
    }
    // ��÷����״̬
    SERVICE_STATUS status;
    if( ::QueryServiceStatus( hSvc, &status) == FALSE)
    {
        ::CloseServiceHandle( hSvc);
        ::CloseServiceHandle( hSC);
        return QUERY_SERVICESTATUS_ERROR;
    }
    //�����������״̬��ֹͣ����
    if( status.dwCurrentState == SERVICE_RUNNING)
    {
    	cout<<"�����Ż��ڶ�����Ŀ������"<<endl; 
        // ֹͣ����
        if( ::ControlService( hSvc,
            SERVICE_CONTROL_STOP, &status) == FALSE)
        {
            ::CloseServiceHandle( hSvc);
            ::CloseServiceHandle( hSC);
            return STOP_SERVICE_ERROR;
        }
        // �ȴ�����ֹͣ
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
	cout<<"��ӭʹ��֣��һ�е����Ż�����Designed by ��� Ver0.2Beta"<<endl; 
	Sleep(800); 
	cout<<"���ڽ����Ż�����������Ŀ�������;�������������Ż�����"<<endl; 
	RestartService();
	cout<<"���ڽ����Ż��������һ����Ŀ��ʣ��һ����Ŀ��"<<endl;
	RestartServicewu();
	cout<<"�Ż�ȫ����ɣ�"<<endl; 
	Sleep(3000); 
	return 0;
	
 } 

