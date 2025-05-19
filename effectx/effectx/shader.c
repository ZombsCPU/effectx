#include "def.h"

DWORD ShaderThread(LPVOID lpParam)
{
	int (*Shader)(RGBQUAD*,sinfo) = (int(*)(RGBQUAD*,sinfo))lpParam;

	uint stime = GetTickCount();
	sinfo info;

	uint width = GetSystemMetrics(SM_CXSCREEN),
		height = GetSystemMetrics(SM_CYSCREEN),
		pixelc = width * height;

	info.width = width;
	info.height = height;
	info.pixelc = pixelc;

	int sleep = 0;

	HDC hDC = GetDC(NULL);
	HDC mDC = CreateCompatibleDC(hDC);

	HBITMAP hBitmap = NULL;
	BITMAPINFO bmi = { 0 };
	BITMAPINFOHEADER* bmh = &bmi.bmiHeader;

	bmh->biSize = sizeof(bmi);
	bmh->biWidth = width;
	bmh->biHeight = height;
	bmh->biPlanes = 1;
	bmh->biBitCount = 32;
	bmh->biCompression = BI_RGB;

	RGBQUAD* rgbquad = { 0 };

	hBitmap = CreateDIBSection(
		hDC,
		&bmi,
		DIB_RGB_COLORS,
		&rgbquad,
		NULL,
		0
	);

	if (hBitmap == NULL) return 1;

	SelectObject(mDC, hBitmap);

	while (TRUE)
	{
		BitBlt(mDC, 0, 0, width, height, hDC, 0, 0, SRCCOPY);

		info.time = GetTickCount() - stime;
		sleep = Shader(rgbquad, info);

		BitBlt(hDC, 0, 0, width, height, mDC, 0, 0, SRCCOPY);

		if (sleep < 0) break;
		if (sleep != 0) Sleep(sleep);
	}
}

HANDLE RunShader(LPTHREAD_START_ROUTINE Shader, BOOL Wait)
{
	HANDLE hThread = NULL;
	hThread = CreateThread(
		NULL,
		0,
		ShaderThread,
		Shader,
		0,
		NULL
	);

	if (hThread == NULL) return NULL;
	
	if (Wait)
	{
		WaitForSingleObject(hThread, INFINITE);
		CloseHandle(hThread);

		return NULL;
	}

	return hThread;
}
