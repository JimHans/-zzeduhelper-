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
/* 使类名成为全局变量 */

TCHAR szClassName[ ] = TEXT("zzeduhelper");

	string stopsys="sc config SysMain start= disabled";
    string stopwu="sc config wuauserv start= disabled";
	string cmd="netsh interface ip set address name=\"本地连接\" static ";
	string cmd2="netsh interface ip set address name=\"本地连接 2\" static ";
	string dns="netsh interface ip set dns \"本地连接\" static 202.102.224.68";
	string str;
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
/*                   加速内核代码                 */ 
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

/* 这个函数由Windows函数DispatchMessage()调用 */
LRESULT CALLBACK WindowProcedure (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc ;
    PAINTSTRUCT ps ;
    RECT rect ;
    TCHAR szText[] = TEXT("版本V0.99.7测试版");
    TCHAR szText2[] = TEXT("官方网站：https://dev.leyoblog.top/zzedubooster.html");
    static int   cxChar, cyChar ;
    static HWND hwndButton;
    static HWND hwndButton2;
    static HWND hwndButton3;
    static HWND hwndButton4;
    static HWND hwndButton5;
    switch (message)                  /* 处理信息 */
    {
    case WM_PAINT:
        hdc = BeginPaint (hWnd, &ps) ;
        GetClientRect (hWnd, &rect) ;
        DrawText (hdc, TEXT ("\n \n郑州一中电阅助手\nDesighed By -翎风-"), -1, &rect, DT_CENTER) ;
        TextOut(hdc, 75, 400, szText, 17);
        TextOut(hdc, 5, 385, szText2, 17);
        EndPaint (hWnd, &ps) ;
        break ;
    case WM_CREATE:
  cxChar = LOWORD (GetDialogBaseUnits ()) ;
          cyChar = HIWORD (GetDialogBaseUnits ()) ;
  hwndButton = CreateWindow ( TEXT("button"), 
        TEXT ("系统加速"),
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        cxChar, cyChar * 6,
        250, 10 * cyChar / 4,
        hWnd, (HMENU)520,
        ((LPCREATESTRUCT) lParam)->hInstance, NULL) ;

  hwndButton2 = CreateWindow ( TEXT("button"), 
        TEXT ("网络修复"),
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        cxChar, 20+cyChar * 6 + 10 * cyChar / 4 ,
        250, 10 * cyChar / 4,
        hWnd, (HMENU)521,
        ((LPCREATESTRUCT) lParam)->hInstance, NULL) ;
        
    hwndButton5 = CreateWindow ( TEXT("button"), 
        TEXT ("限速破解"),
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        cxChar, 40 + cyChar * 6 + 20 * cyChar / 4 ,
        250, 10 * cyChar / 4,
        hWnd, (HMENU)556,
        ((LPCREATESTRUCT) lParam)->hInstance, NULL) ;
          
  hwndButton3 = CreateWindow ( TEXT("button"), 
        TEXT ("更新日志"),
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        cxChar, 60 + cyChar * 6 + 30 * cyChar / 4 ,
        250, 10 * cyChar / 4,
        hWnd, (HMENU)555,
        ((LPCREATESTRUCT) lParam)->hInstance, NULL) ;
        
  hwndButton4 = CreateWindow ( TEXT("button"), 
        TEXT ("关于"),
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        cxChar, 80+cyChar * 6 + 40 * cyChar / 4 ,
        250, 10 * cyChar / 4,
        hWnd, (HMENU)523,
        ((LPCREATESTRUCT) lParam)->hInstance, NULL) ;  
          return 0 ;
          
       
    case WM_COMMAND:
		if (LOWORD(wParam) == 520 && HIWORD(wParam) == BN_CLICKED)
		{
			UINT starter = MessageBox(hWnd, TEXT("是否确定执行优化？注意：优化可能会持续几分钟。"), TEXT("提示"), MB_ICONQUESTION|MB_OKCANCEL);
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
			MessageBox(hWnd, TEXT("优化成功完成！优化效果可能需要几分钟才能显现。"), TEXT("提示"), MB_ICONEXCLAMATION|MB_OK);
			}
	
		}
			if (LOWORD(wParam) == 521 && HIWORD(wParam) == BN_CLICKED)
		{
				UINT starter = MessageBox(hWnd, TEXT("是否确定执行网络修复？"), TEXT("提示"), MB_ICONQUESTION|MB_OKCANCEL);
			if(starter == IDOK) 
			{
	    srand((unsigned)time(NULL));
        str=RandIP();
     string push="网络修复成功完成！您的IP已被修改为 "+str+" ,尽情卓（tui）越（fei）吧！";
    string Gateway="10.3.5.1 1"; 
    string Mask="255.255.255.0";          //子网掩码
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
    MessageBox(hWnd, push.c_str(), TEXT("提示"), MB_ICONEXCLAMATION|MB_OK);
    } 
		}
	if (LOWORD(wParam) == 555 && HIWORD(wParam) == BN_CLICKED)
		{
			MessageBox(hWnd, TEXT("|     V0.95 更新日志     |\n|1.紧急修复了部分机器网络修复失败的问题\n \n|     V0.90 更新日志     |\n|1.修复了大小写不分的问题\n \n|     V0.85 更新日志     |\n|1.加入了应用图标并增加官网地址\n|2.这是第一个正式版本  \n \n|   V0.8Beta 更新日志    |\n|1.终于修复了优化后内存反弹的问题\n|2.电阅助手优化完毕后会自动清除屏幕上的代码了\n \n|   V0.7Beta 更新日志    |\n|1.白白的背景更好看   \n \n|   V0.6Beta 更新日志    |\n|1.版本信息现在已单独列出\n|2.更新日志美化     \n|3.提示语句更加通俗易懂\n|4.优化结束后程序不会自动退出\n|5.修复了优化卡死的问题\n \n|   V0.5Beta 更新日志    |\n|1.修复了IP设置失效的问题\n|2.增加更新日志功能   \n|3.现在可以选择优化方式了"), TEXT("更新日志"), MB_ICONASTERISK|MB_OK);
		}
	if (LOWORD(wParam) == 523 && HIWORD(wParam) == BN_CLICKED)
		{

			MessageBox(hWnd, TEXT("       郑州一中电阅助手    \n \n       Build0.99.07Beta \n \n     Designed by -翎风-      \n \n 官方网站：https://dev.leyo\nblog.top/zzeduhelper.html"), TEXT("关于"), MB_ICONASTERISK|MB_OKCANCEL);
		}
	if (LOWORD(wParam) == 556 && HIWORD(wParam) == BN_CLICKED)
		{
			MessageBox(hWnd, TEXT("敬请期待！"), TEXT("功能开发中"), MB_ICONEXCLAMATION|MB_OK);
		}
			break; 
    case WM_DESTROY:
        PostQuitMessage (0);       /* 发送WM_QUIT到消息队列 */
        break;
    default:                      /* 不想处理的消息 */
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
    return 0;
}
 
int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil)
{
    HWND hwnd;               /* 窗口的句柄 */
    MSG messages;            /* 用于储存应用程序的消息 */
    WNDCLASSEX wincl;        /* 窗口类的数据结构 */
    /* 窗口结构 */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* 被Windows调用的函数 */
    wincl.style = CS_DBLCLKS;                 /* 捕获双击事件 */
    wincl.cbSize = sizeof (WNDCLASSEX);
    /* 使用默认的图表和鼠标指针 */
    wincl.hIcon = LoadIcon (hThisInstance, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (hThisInstance, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* 没有菜单 */
    wincl.cbClsExtra = 0;                      /* 窗口类后面没有额外的字节 */
    wincl.cbWndExtra = 0;                      /* 窗口实例化结构 */
    /* 使用白色作为窗口的背景色，自定义背景画刷 */
    wincl.hbrBackground = CreateSolidBrush(RGB(255,255,255));
    /* 注册窗口类，如果失败，退出程序 */
    if (!RegisterClassEx (&wincl))
    return 0;
    /* 如果类被注册，创建窗口 */
    hwnd = CreateWindowEx (
        0,                   /* 扩展的变化信息 */
        szClassName,         /* 类名 */
        TEXT("郑州一中电阅助手"),       /* 标题栏文本 */
        WS_OVERLAPPEDWINDOW&~WS_THICKFRAME&~WS_MINIMIZE&~WS_EX_TOPMOST, /* 默认窗口 */
        CW_USEDEFAULT,       /* 使用默认的位置 */
        CW_USEDEFAULT,       /* 使用默认的位置 */
        274,                 /* 窗口宽度（以像素点为单位） */
        460,                 /* 窗口高度（以像素点为单位） */
        HWND_DESKTOP,        /* 此窗口是桌面的子窗口 */
        NULL,                /* 没有菜单 */
        hThisInstance,       /* 程序实例化句柄 */
        NULL                 /* 没有创建数据的窗口 */
    );
    /* 显示窗口 */
    ShowWindow (hwnd, nFunsterStil);
    /* 运行消息循环。它将在GetMessage()返回零的时候退出 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* 把虚拟按键消息翻译成字符消息 */
        TranslateMessage(&messages);
        /* 把消息发送到WindowProcedure函数 */
        DispatchMessage(&messages);
    }
    /* 程序的返回值，由PostQuitMessage()提供。 */
    return messages.wParam;
}
