#include "def.h"

int shader1(RGBQUAD *rgbquad, sinfo s)
{
	RGBQUAD color;

	float x = 0, y = 0, c = s.pixelc;
	float opacity = 0.1f;

	for (uint i = 0; i < c; i++)
	{
		x = i % s.width;
		y = s.height - i / s.width;

		color = rgbquad[i];

		color.rgbRed += (BYTE)(opacity*255 * sin((float)x / s.width * M_PI + 0.001 * s.time / 10.0f));
		color.rgbGreen += (BYTE)(opacity*255 * sin((float)y / s.height * M_PI + 0.001 * s.time / 10.0f));
		color.rgbBlue += (BYTE)(opacity*255 * sin((float)(x + y) / (s.width + s.height) * M_PI + 0.001*s.time / 10.0f));

		rgbquad[i] = color;
	}

	if (s.time >= 8000) return -1;
	return 5;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	RunShaderS(&shader1);

	return 0;
}
