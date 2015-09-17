#include <windows.h>
#include <stdio.h>

int main(int argc, char* argv[], char* envp[])
{	

	printf("SHIFT+CLICK to set a window alwasys on top\nCTRL+CLICK to remove on top status\nF12 to cancel\n");

	while(1)
  	{
	    if(GetAsyncKeyState(VK_F12)) 
	    {
	      break;
	    }

	   	if(GetAsyncKeyState(VK_LBUTTON))
	   	{

	   		 //needs to be checking if most significant bit is set, if((GetAsyncKeyState(VK_LBUTTON)) & (1<<(15)))?
			//check in watch window to see what position we should really be checking
			
			if(GetAsyncKeyState(VK_SHIFT) & (1<<15))
		    {
			    HWND onTopWindow;
			    POINT pt;

			    if(!GetCursorPos(&pt)) 
			    {
			        wprintf(L"GetCursorPos failed with %d\n", GetLastError());
			    	break;
			    }

			    if((onTopWindow = WindowFromPoint(pt)) != NULL) 
			    {
			    	DWORD  dwPID;
			        HANDLE hProcess;

			        GetWindowThreadProcessId(onTopWindow, &dwPID);

			        hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, dwPID);

			        if(hProcess == NULL) 
			        {
			          wprintf(L"OpenProcess failed with error: %d\n", GetLastError());
			          CloseHandle(hProcess);
			        } 
			        else 
			        {
			          char lpFileName[MAX_PATH];
			          DWORD   dwSize = _countof(lpFileName);

			          QueryFullProcessImageName(hProcess, 0, lpFileName, &dwSize);
			          
			          CloseHandle(hProcess);

			          printf("Setting window always on top: %s\n", lpFileName);
			          
			          RECT windowPos;
			          GetWindowRect(onTopWindow,&windowPos);

			          SetWindowPos(onTopWindow,HWND_TOPMOST,windowPos.left,windowPos.top,windowPos.right-windowPos.left,windowPos.bottom-windowPos.top,0);
			          break;
			        }
	     		}
	    	}
	    	else if(GetAsyncKeyState(VK_CONTROL) & (1<<15))
	    	{
	    		HWND onTopWindow;
			    POINT pt;

			    if(!GetCursorPos(&pt)) 
			    {
			        wprintf(L"GetCursorPos failed with %d\n", GetLastError());
			    	break;
			    }

			    if((onTopWindow = WindowFromPoint(pt)) != NULL) 
			    {
			    	DWORD  dwPID;
			        HANDLE hProcess;

			        GetWindowThreadProcessId(onTopWindow, &dwPID);

			        hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, dwPID);

			        if(hProcess == NULL) 
			        {
			          wprintf(L"OpenProcess failed with error: %d\n", GetLastError());
			          CloseHandle(hProcess);
			        } 
			        else 
			        {
			          char lpFileName[MAX_PATH];
			          DWORD   dwSize = _countof(lpFileName);

			          QueryFullProcessImageName(hProcess, 0, lpFileName, &dwSize);
			          
			          CloseHandle(hProcess);

			          printf("Setting window back to normal: %s\n", lpFileName);
			          
			          RECT windowPos;
			          GetWindowRect(onTopWindow,&windowPos);

			          SetWindowPos(onTopWindow,HWND_NOTOPMOST,windowPos.left,windowPos.top,windowPos.right-windowPos.left,windowPos.bottom-windowPos.top,0);
			          break;
			        }
	     		}
	    	}
	   }
	   	Sleep(100);
	}
}
