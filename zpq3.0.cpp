#include <Windows.h>
#pragma comment(lib, "winmm.lib")
DWORD WINAPI bitblt1(LPVOID lpParam) {
	HDC desktop = GetDC(NULL);
	int xs = GetSystemMetrics(SM_CXSCREEN);
	int ys = GetSystemMetrics(SM_CYSCREEN);
	while (true) {
		desktop = GetDC(NULL);
		BitBlt(desktop, 0, 0, xs, ys, desktop, -1, -1, SRCERASE);
		ReleaseDC(0, desktop);
		Sleep(10);
	}
}
VOID WINAPI sound1() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 60] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((9 * t & t >> 4 | 5 * t & t >> 7 | 3 * t & t >> 10) - 0);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	if (MessageBoxW(NULL, L"Are you sure u want to run this Payload?", L"zpq3.0.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO) {
		ExitProcess(0);
}
	Sleep(500);
	HANDLE BOSS = CreateThread(0, 0, bitblt1, 0, 0, 0);
	sound1();
	Sleep(60000);
	TerminateThread(BOSS, 0);
	CloseHandle(BOSS);
}
