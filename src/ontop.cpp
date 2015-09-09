#include <windows.h>
#include <stdio.h>

int main(int argc, char* argv[], char* envp[])
{	

	printf("SHIFT+CLICK to set a window always on top\nCTRL+CLICK to remove on top status\nF12 to quit\n");

	while(1)
  	{
	    if(GetAsyncKeyState(VK_F12)) 
	    {
	      break;
	    }

	   	if(GetAsyncKeyState(VK_LBUTTON))
	   	{
	   		if(GetAsyncKeyState(VK_SHIFT))
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
	    	else if(GetAsyncKeyState(VK_CONTROL))
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
