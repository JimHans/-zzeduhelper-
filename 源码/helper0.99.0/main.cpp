#include <windows.h>
#include <tchar.h>
#include <shellapi.h>
#include<stdio.h>
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
/* ʹ������Ϊȫ�ֱ��� */

TCHAR szClassName[ ] = TEXT("zzeduhelper");

	string stopsys="sc config SysMain start= disabled";
    string stopwu="sc config wuauserv start= disabled";
	string cmd="netsh interface ip set address name=\"��������\" static ";
	string cmd2="netsh interface ip set address name=\"�������� 2\" static ";
	string dns="netsh interface ip set dns \"��������\" static 202.102.224.68";
	string str;
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
/*                   �����ں˴���                 */ 
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

/* ���������Windows����DispatchMessage()���� */
LRESULT CALLBACK WindowProcedure (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc ;
    PAINTSTRUCT ps ;
    RECT rect ;
    TCHAR szText[] = TEXT("�汾V0.99.7���԰�");
    TCHAR szText2[] = TEXT("�ٷ���վ��https://dev.leyoblog.top/zzedubooster.html");
    static int   cxChar, cyChar ;
    static HWND hwndButton;
    static HWND hwndButton2;
    static HWND hwndButton3;
    static HWND hwndButton4;
    static HWND hwndButton5;
    switch (message)                  /* ������Ϣ */
    {
    case WM_PAINT:
        hdc = BeginPaint (hWnd, &ps) ;
        GetClientRect (hWnd, &rect) ;
        DrawText (hdc, TEXT ("\n \n֣��һ�е�������\nDesighed By -���-"), -1, &rect, DT_CENTER) ;
        TextOut(hdc, 75, 400, szText, 17);
        TextOut(hdc, 5, 385, szText2, 17);
        EndPaint (hWnd, &ps) ;
        break ;
    case WM_CREATE:
  cxChar = LOWORD (GetDialogBaseUnits ()) ;
          cyChar = HIWORD (GetDialogBaseUnits ()) ;
  hwndButton = CreateWindow ( TEXT("button"), 
        TEXT ("ϵͳ����"),
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        cxChar, cyChar * 6,
        250, 10 * cyChar / 4,
        hWnd, (HMENU)520,
        ((LPCREATESTRUCT) lParam)->hInstance, NULL) ;

  hwndButton2 = CreateWindow ( TEXT("button"), 
        TEXT ("�����޸�"),
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        cxChar, 20+cyChar * 6 + 10 * cyChar / 4 ,
        250, 10 * cyChar / 4,
        hWnd, (HMENU)521,
        ((LPCREATESTRUCT) lParam)->hInstance, NULL) ;
        
    hwndButton5 = CreateWindow ( TEXT("button"), 
        TEXT ("�����ƽ�"),
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        cxChar, 40 + cyChar * 6 + 20 * cyChar / 4 ,
        250, 10 * cyChar / 4,
        hWnd, (HMENU)556,
        ((LPCREATESTRUCT) lParam)->hInstance, NULL) ;
          
  hwndButton3 = CreateWindow ( TEXT("button"), 
        TEXT ("������־"),
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        cxChar, 60 + cyChar * 6 + 30 * cyChar / 4 ,
        250, 10 * cyChar / 4,
        hWnd, (HMENU)555,
        ((LPCREATESTRUCT) lParam)->hInstance, NULL) ;
        
  hwndButton4 = CreateWindow ( TEXT("button"), 
        TEXT ("����"),
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        cxChar, 80+cyChar * 6 + 40 * cyChar / 4 ,
        250, 10 * cyChar / 4,
        hWnd, (HMENU)523,
        ((LPCREATESTRUCT) lParam)->hInstance, NULL) ;  
          return 0 ;
          
       
    case WM_COMMAND:
		if (LOWORD(wParam) == 520 && HIWORD(wParam) == BN_CLICKED)
		{
			UINT starter = MessageBox(hWnd, TEXT("�Ƿ�ȷ��ִ���Ż���ע�⣺�Ż����ܻ���������ӡ�"), TEXT("��ʾ"), MB_ICONQUESTION|MB_OKCANCEL);
			if(starter == IDOK) 
			{
	RestartService();
	Sleep(300); 
	cout<<stopsys<<endl;
    system("@echo off");
    system(stopsys.c_str());
    system("@echo on");
	RestartServicewu();
	Sleep(300); 
	cout<<stopwu<<endl;
    system("@echo off");
    system(stopwu.c_str());
    system("@echo on");
    system("cls"); 
			MessageBox(hWnd, TEXT("�Ż��ɹ���ɣ��Ż�Ч��������Ҫ�����Ӳ������֡�"), TEXT("��ʾ"), MB_ICONEXCLAMATION|MB_OK);
			}
	
		}
			if (LOWORD(wParam) == 521 && HIWORD(wParam) == BN_CLICKED)
		{
				UINT starter = MessageBox(hWnd, TEXT("�Ƿ�ȷ��ִ�������޸���"), TEXT("��ʾ"), MB_ICONQUESTION|MB_OKCANCEL);
			if(starter == IDOK) 
			{
	    srand((unsigned)time(NULL));
        str=RandIP();
     string push="�����޸��ɹ���ɣ�����IP�ѱ��޸�Ϊ "+str+" ,����׿��tui��Խ��fei���ɣ�";
    string Gateway="10.3.5.1 1"; 
    string Mask="255.255.255.0";          //��������
    cmd+=str+" "+Mask+" "+Gateway;
    //cout<<cmd<<endl;
    //system("@echo off");
    WinExec(cmd.c_str(),SW_HIDE);
    //system(cmd.c_str());
    //system("@echo on");
    //system("ipconfig /all");
    //system("cls");
    //cout<<endl;
    cmd2+=str+" "+Mask+" "+Gateway;
    //cout<<cmd2<<endl;
    //system("@echo off");
    WinExec(cmd2.c_str(),SW_HIDE);
    //system(cmd2.c_str());
    //system("@echo on");
    //system("ipconfig /all");
    //system("cls");
    //cout<<endl;
    //cout<<dns<<endl;
    //system("@echo off");
    WinExec(dns.c_str(),SW_HIDE);
    //system(dns.c_str());
    //system("@echo on");
    //system("ipconfig /all");
    //system("cls");
    MessageBox(hWnd, push.c_str(), TEXT("��ʾ"), MB_ICONEXCLAMATION|MB_OK);
    } 
		}
	if (LOWORD(wParam) == 555 && HIWORD(wParam) == BN_CLICKED)
		{
			MessageBox(hWnd, TEXT("|     V0.95 ������־     |\n|1.�����޸��˲��ֻ��������޸�ʧ�ܵ�����\n \n|     V0.90 ������־     |\n|1.�޸��˴�Сд���ֵ�����\n \n|     V0.85 ������־     |\n|1.������Ӧ��ͼ�겢���ӹ�����ַ\n|2.���ǵ�һ����ʽ�汾  \n \n|   V0.8Beta ������־    |\n|1.�����޸����Ż����ڴ淴��������\n|2.���������Ż���Ϻ���Զ������Ļ�ϵĴ�����\n \n|   V0.7Beta ������־    |\n|1.�װ׵ı������ÿ�   \n \n|   V0.6Beta ������־    |\n|1.�汾��Ϣ�����ѵ����г�\n|2.������־����     \n|3.��ʾ������ͨ���׶�\n|4.�Ż���������򲻻��Զ��˳�\n|5.�޸����Ż�����������\n \n|   V0.5Beta ������־    |\n|1.�޸���IP����ʧЧ������\n|2.���Ӹ�����־����   \n|3.���ڿ���ѡ���Ż���ʽ��"), TEXT("������־"), MB_ICONASTERISK|MB_OK);
		}
	if (LOWORD(wParam) == 523 && HIWORD(wParam) == BN_CLICKED)
		{

			MessageBox(hWnd, TEXT("       ֣��һ�е�������    \n \n       Build0.99.07Beta \n \n     Designed by -���-      \n \n �ٷ���վ��https://dev.leyo\nblog.top/zzeduhelper.html"), TEXT("����"), MB_ICONASTERISK|MB_OKCANCEL);
		}
	if (LOWORD(wParam) == 556 && HIWORD(wParam) == BN_CLICKED)
		{
			MessageBox(hWnd, TEXT("�����ڴ���"), TEXT("���ܿ�����"), MB_ICONEXCLAMATION|MB_OK);
		}
			break; 
    case WM_DESTROY:
        PostQuitMessage (0);       /* ����WM_QUIT����Ϣ���� */
        break;
    default:                      /* ���봦�����Ϣ */
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
    return 0;
}
 
int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil)
{
    HWND hwnd;               /* ���ڵľ�� */
    MSG messages;            /* ���ڴ���Ӧ�ó������Ϣ */
    WNDCLASSEX wincl;        /* ����������ݽṹ */
    /* ���ڽṹ */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* ��Windows���õĺ��� */
    wincl.style = CS_DBLCLKS;                 /* ����˫���¼� */
    wincl.cbSize = sizeof (WNDCLASSEX);
    /* ʹ��Ĭ�ϵ�ͼ������ָ�� */
    wincl.hIcon = LoadIcon (hThisInstance, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (hThisInstance, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* û�в˵� */
    wincl.cbClsExtra = 0;                      /* ���������û�ж�����ֽ� */
    wincl.cbWndExtra = 0;                      /* ����ʵ�����ṹ */
    /* ʹ�ð�ɫ��Ϊ���ڵı���ɫ���Զ��屳����ˢ */
    wincl.hbrBackground = CreateSolidBrush(RGB(255,255,255));
    /* ע�ᴰ���࣬���ʧ�ܣ��˳����� */
    if (!RegisterClassEx (&wincl))
    return 0;
    /* ����౻ע�ᣬ�������� */
    hwnd = CreateWindowEx (
        0,                   /* ��չ�ı仯��Ϣ */
        szClassName,         /* ���� */
        TEXT("֣��һ�е�������"),       /* �������ı� */
        WS_OVERLAPPEDWINDOW&~WS_THICKFRAME&~WS_MINIMIZE&~WS_EX_TOPMOST, /* Ĭ�ϴ��� */
        CW_USEDEFAULT,       /* ʹ��Ĭ�ϵ�λ�� */
        CW_USEDEFAULT,       /* ʹ��Ĭ�ϵ�λ�� */
        274,                 /* ���ڿ�ȣ������ص�Ϊ��λ�� */
        460,                 /* ���ڸ߶ȣ������ص�Ϊ��λ�� */
        HWND_DESKTOP,        /* �˴�����������Ӵ��� */
        NULL,                /* û�в˵� */
        hThisInstance,       /* ����ʵ������� */
        NULL                 /* û�д������ݵĴ��� */
    );
    /* ��ʾ���� */
    ShowWindow (hwnd, nFunsterStil);
    /* ������Ϣѭ����������GetMessage()�������ʱ���˳� */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* �����ⰴ����Ϣ������ַ���Ϣ */
        TranslateMessage(&messages);
        /* ����Ϣ���͵�WindowProcedure���� */
        DispatchMessage(&messages);
    }
    /* ����ķ���ֵ����PostQuitMessage()�ṩ�� */
    return messages.wParam;
}
