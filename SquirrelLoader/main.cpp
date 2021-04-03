#include <Windows.h>
#include <iostream>
#include "mem.hpp"
#include "isFile.hpp"

using namespace std; Injector inj; DWORD pid;
LPVOID ntOpenFile = GetProcAddress(LoadLibraryW(L"ntdll"), "NtOpenFile");

void bypass()
{
	if (ntOpenFile) {
		char originalBytes[5];
		memcpy(originalBytes, ntOpenFile, 5); WriteProcessMemory(inj.process, ntOpenFile, originalBytes, 5, NULL);
	} else {
		cout << "[-] Imposible hacer bypass\n";
		Sleep(2000); exit(-1);
	}
}
void Backup()
{
	if (ntOpenFile) {
		char originalBytes[5];
		memcpy(originalBytes, ntOpenFile, 5); WriteProcessMemory(inj.process, ntOpenFile, originalBytes, 0, NULL);
	} else {
		cout << "[-] Imposible hacer backup\n";
		Sleep(2000); exit(-1);
	}
}
int main()
{
	SetConsoleTitle("SquirrelLoader por holasoyender - github.com/holasoyender");
	cout << "holasoyender\n	 SquirrelLoader V2\n\n" << endl;

	inj.hwndproc = FindWindowA(0, "Counter-Strike: Global Offensive");

	GetWindowThreadProcessId(inj.hwndproc, &pid);
	inj.process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	inj.clientDLL = inj.GetModule(pid, "client.dll");

	if (DoesFileExist("cheat.dll")) {
		bypass();
		if (inj.inject(pid, "cheat.dll")) {
			cout << "[*] Modulo inyectado correctamente!\n\n" << endl;
			Backup(); Sleep(2000); exit(0);
		} else {
			cout << "[-] Inyeccion fallida!\n\n" << endl;
			Backup(); Sleep(2000); exit(-1);
		}
	} else {
		cout << "[-] No he podido encontrar cheat.dll\n";
		cout << "[-] Inyeccion fallida!\n\n";
		Sleep(2000); exit(-1);
	}

	return 0;
}
