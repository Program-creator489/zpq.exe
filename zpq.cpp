#include <Windows.h>
#define _USE_MATH_DEFINES 1
#include <cmath>
#pragma comment (lib, "winmm.lib")
//#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "kernel32.lib")
DWORD WINAPI WeirdInvert(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	while (true)
	{
		hdc = GetDC(0);
		BitBlt(hdc, 1, 1, w, h, hdc, 0, 0, SRCINVERT);
		BitBlt(hdc, -1, -1, w, h, hdc, 0, 0, SRCINVERT);
		ReleaseDC(GetDesktopWindow(), hdc);
		DeleteDC(hdc);
		Sleep(10);
	}

}
VOID WINAPI sound1()
{
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

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	if (MessageBoxW(NULL, L"Are u sure u want to run this payload?", L"zpq.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
	{
		ExitProcess(0);
	}
	else
	{
			Sleep(500);
			HANDLE P7 = CreateThread(0, 0, WeirdInvert, 0, 0, 0);
			sound1();
			Sleep(60000);
			TerminateThread(P7, 0);
			CloseHandle(P7);
			InvalidateRect(0, 0, 0);
			Sleep(100);
		}
	}
