#include <iostream>
#include <windows.h>

class centralCommand {
	public:
		void wutFaces(char target[]) {
			std::cout << "Target : " << target << "\n";
			// var 
			SERVICE_STATUS_PROCESS ssp;
			DWORD BN; 
			INT16 waitTime = 0;
			INT16 timeout = 10000;
			
			// Create handler service manager (?)
			SC_HANDLE handler = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
			if (handler == NULL) {
				std::cout << "Error With Code: " << GetLastError() << "\n[x] Please run with administrator";
				return;
			}
			
			// Create instance service (?)
			SC_HANDLE serviceHandler = OpenService(handler, target, SERVICE_ALL_ACCESS);
			if (serviceHandler == NULL) {
				std::cout << "Riot service is not found!\nPlease re/install valorant!";
				return;
			}
			
			// create what
			if (!QueryServiceStatusEx(serviceHandler, SC_STATUS_PROCESS_INFO, (LPBYTE) &ssp, sizeof(SERVICE_STATUS_PROCESS), &BN)) {
				std::cout << "Failed with error : " << GetLastError();
				return;
			}
			
			// checking your riot service run
			if (ssp.dwCurrentState != SERVICE_STOPPED) {
				std::cout << "Riot service is active\nPlease (re)run your valorant.";
				return;
			}
			
			// start service ?
			if (!StartService(serviceHandler, 0, NULL)) {
				std::cout << "Service start failed! " << GetLastError();
				return;
			}
			
			while(ssp.dwCurrentState == SERVICE_START_PENDING) {
				// checking
				std::cout << "Service is starting . . .\n";
				std::cout << "Current state : " << ssp.dwCurrentState;
				waitTime += 100;
				system("cls");
				if (timeout < waitTime) {
					std::cout << "Taking too long to respond. force exit!";
					return;
				}
			}
			std::cout << "\nService " << target << " now active thank you for downloading ... :)";
			return;
		}
};

// main
int main() {
	char _t[] = "vgc";
	centralCommand pepega = centralCommand();
	pepega.wutFaces(_t);
	std::cin.get();
	return 0;
}
