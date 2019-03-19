#include<windows.h>
#include <shellapi.h>
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
int main()
{
    
	string str;
    str=RandIP();
    
   cout<<str<<endl;
 
	Sleep(3000); 
	return 0;
	
 } 
