#include <Windows.h>
#include <iostream>
#include "mem.h"
#include "isFile.h"

using namespace std; Injector inj; DWORD pid;
LPVOID ntOpenFile = GetProcAddress(LoadLibraryW(L"ntdll"), "NtOpenFile");

void bypass()
{
	if (ntOpenFile) {
		char originalBytes[5];
		memcpy(originalBytes, ntOpenFile, 5); WriteProcessMemory(inj.process, ntOpenFile, originalBytes, 5, NULL);
	} else {
		int msgboxID1 = MessageBox(
			NULL,
			"No se ha podido hacer Bypass",
			"SquirrelLoader",
			MB_ICONEXCLAMATION | MB_OK | MB_DEFBUTTON2
		);
		msgboxID1;
		Sleep(2000); exit(-1);
	}
}
void Backup()
{
	if (ntOpenFile) {
		char originalBytes[5];
		memcpy(originalBytes, ntOpenFile, 5); WriteProcessMemory(inj.process, ntOpenFile, originalBytes, 0, NULL);
	} else {
		int msgboxID2 = MessageBox(
			NULL,
			"No se ha podido hacer Backup",
			"SquirrelLoader",
			MB_ICONEXCLAMATION | MB_OK | MB_DEFBUTTON2
		);
		msgboxID2;
		Sleep(2000); exit(-1);
	}
}
int main()
{
	FreeConsole();

	inj.hwndproc = FindWindowA(0, "Counter-Strike: Global Offensive - Direct3D 9");

	GetWindowThreadProcessId(inj.hwndproc, &pid);
	inj.process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	inj.clientDLL = inj.GetModule(pid, "client.dll");

	if (DoesFileExist("cheat.dll")) {
		bypass();
		if (inj.inject(pid, "cheat.dll")) {
			int msgboxID3 = MessageBox(
				NULL,
				"DLL inyectado correctamente!",
				"SquirrelLoader",
				MB_ICONINFORMATION | MB_OK | MB_DEFBUTTON2
			);
			msgboxID3;
			Backup(); Sleep(2000); exit(0);
		} else {
			int msgboxID5 = MessageBox(
				NULL,
				"Inyeccion fallida, comprueba que tienes CS:GO abierto",
				"SquirrelLoader",
				MB_ICONEXCLAMATION | MB_RETRYCANCEL | MB_DEFBUTTON2
			);
			msgboxID5;
			if (msgboxID5 == IDRETRY)
				main();
			{
			}
			if (msgboxID5 == IDCANCEL)
			{
				Backup(); Sleep(2000); exit(-1);
			}
			Backup(); Sleep(2000); exit(-1);
		}
	} else {
		int msgboxID4 = MessageBox(
			NULL,
			"No se ha encontrado cheat.dll",
			"SquirrelLoader",
			MB_ICONEXCLAMATION | MB_RETRYCANCEL | MB_DEFBUTTON2
		);
		msgboxID4;
		if (msgboxID4 == IDRETRY)
			main();
		{
		}
		if (msgboxID4 == IDCANCEL)
		{
			Backup(); Sleep(2000); exit(-1);
		}
		Sleep(2000); exit(-1);
	}

	return 0;
}
