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

 //�������IP��ַ
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
 
    // �򿪷���������
    SC_HANDLE hSC = ::OpenSCManager( NULL,
        NULL, GENERIC_EXECUTE);
    if( hSC == NULL)
    {      
        return OPEN_SCMANAGER_ERROR;
    }
    // ��sysmain����
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
    // ��update����
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
        // ֹͣ����
        if( ::ControlService( hSvc,
            SERVICE_CONTROL_STOP, &status) == FALSE)
        {
            ::CloseServiceHandle( hSvc);
            ::CloseServiceHandle( hSC);
            return STOP_SERVICE_ERROR;
        }

        
        /**************************************************** 
        // �ȴ�����ֹͣ
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
	string cmd="netsh interface ip set address name=\"��������\" static ";
	string cmd2="netsh interface ip set address name=\"�������� 2\" static ";
	
	cout<<endl;
	cout<<"��ӭʹ��֣��һ�е������֣�"<<endl;

    char input;
	
		start: 
	cout<<endl;
	cout<<"�����Y�����»س������Ż�������R�����»س��޸��������⡣"<<endl; 
	cout<<"����U�����»س��鿴������־������I�����»س��鿴�汾��Ϣ��"<<endl;
	cout<<"������������˳��������֡�"<<endl; 
	cin>>input;
	if(input=='y'||input=='Y')
	{
    Sleep(800); 
	cout<<"���ڽ����Ż�����������Ŀ��"<<endl; 
	cout<<endl;
	RestartService();
	cout<<stopsys<<endl;
    system("@echo off");
    system(stopsys.c_str());
    system("@echo on");
	cout<<"���ڽ����Ż��������һ����Ŀ��ʣ��һ����Ŀ��"<<endl;
	cout<<endl;
	RestartServicewu();
	cout<<stopwu<<endl;
    system("@echo off");
    system(stopwu.c_str());
    system("@echo on");
    system("cls");
	cout<<"�Ż�ȫ����ɣ�"<<endl;
	goto start;  
	}
	if(input=='r'||input=='R') 
	{
    cout<<"�����Զ��޸�������󡣡���"<<endl; 
	string str;
    str=RandIP();
    
    string Gateway="10.3.5.1 1"; 
    string Mask="255.255.255.0";          //��������
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
    cout<<"����������޸�������IP�ѱ�����Ϊ"<<str<<"����ʼ׿��tui��Խ��fei���ɣ�"<<endl;
	goto start;  
}
if(input=='u'||input=='U')
	{
		   cout<<"__________________________"<<endl;
           cout<<"|     V0.95 ������־     |"<<endl;
		   cout<<"|1.�����޸��˲��ֻ�������|"<<endl;
		   cout<<"|     �޸�ʧ�ܵ�����     |"<<endl;
		   cout<<"__________________________"<<endl;
           cout<<"|     V0.90 ������־     |"<<endl;
		   cout<<"|1.�޸��˴�Сд���ֵ�����|"<<endl;
		   cout<<"__________________________"<<endl;
           cout<<"|     V0.85 ������־     |"<<endl;
		   cout<<"|1.������Ӧ��ͼ�겢���ӹ�|"<<endl;
		   cout<<"|         ����ַ         |"<<endl; 
           cout<<"|  2.���ǵ�һ����ʽ�汾  |"<<endl;
		   cout<<"__________________________"<<endl;
           cout<<"|   V0.8Beta ������־    |"<<endl;
		   cout<<"|1.�����޸����Ż����ڴ淴|"<<endl; 
           cout<<"|        ��������        |"<<endl;
           cout<<"|2.���������Ż���Ϻ����|"<<endl;
           cout<<"|  �������Ļ�ϵĴ�����  |"<<endl;
		   cout<<"__________________________"<<endl;
           cout<<"|   V0.7Beta ������־    |"<<endl;
           cout<<"|   1.�װ׵ı������ÿ�   |"<<endl; 
           cout<<"__________________________"<<endl;
           cout<<"|   V0.6Beta ������־    |"<<endl; 
           cout<<"|1.�汾��Ϣ�����ѵ����г�|"<<endl;   
           cout<<"|     2.������־����     |"<<endl; 
           cout<<"| 3.��ʾ������ͨ���׶� |"<<endl;
		   cout<<"|  4.�Ż���������򲻻�  |"<<endl; 
		   cout<<"|        �Զ��˳�        |"<<endl;
		   cout<<"| 5.�޸����Ż����������� |"<<endl;
		   cout<<"__________________________"<<endl;
           cout<<"|   V0.5Beta ������־    |"<<endl; 
           cout<<"|1.�޸���IP����ʧЧ������|"<<endl;   
           cout<<"|   2.���Ӹ�����־����   |"<<endl; 
           cout<<"|3.���ڿ���ѡ���Ż���ʽ��|"<<endl; 
           cout<<"__________________________"<<endl;  
           goto start; 
              } 
              if(input=='i'||input=='I')
	{
           cout<<"__________________________"<<endl;
           cout<<"|����  ֣��һ�е����Ż���|"<<endl; 
           cout<<"|      �汾�ţ�V0.95     |"<<endl;   
           cout<<"|      ������-���-      |"<<endl; 
           cout<<"|   ����IDE��DevC++      |"<<endl;
		   cout<<"|         ������         |"<<endl; 
		   cout<<"|https://dev.leyoblog.top|"<<endl;
		   cout<<"|https://github.com/JimHa|"<<endl;
		   cout<<"|ns/zzedubooster         |"<<endl;
           cout<<"|   ��л���ʹ����֧�֣� |"<<endl; 
           cout<<"__________________________"<<endl;  
           goto start; 
              } 
	Sleep(2000);
	hard:
	 cout<<"�˳��ɹ���"<<endl;
system("pause");
	return 0;
 } 



