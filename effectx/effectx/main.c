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

int shader2(RGBQUAD* rgbquad, sinfo s)
{
	RGBQUAD color;
	uint x = 0, y = 0, c = s.pixelc;

	double ang = 0;

	POINT mouse;
	GetCursorPos(&mouse);

	for (uint i = 0; i < c; i++)
	{
		x = i % s.width;
		y = s.height - i / s.width;
		color = rgbquad[i];

		color.rgbRed += (BYTE)(0.2f * (rand()%256) * cos(i));
		color.rgbBlue += (BYTE)(0.2f * (rand()%256) * cos(i));
		color.rgbGreen += 1;


		rgbquad[i] = color;
	}

	if (s.time > 3500) return -1;
	return 16;
}

float noise = 50.0f; // 1 = 100% noise, 2 = 50% noise, 3 = 33% noise...
float noise_increment = 0.30f;

int shader3(RGBQUAD* rgbquad, sinfo s)
{
	// Shader settings
	float whiteness = 0.5f;
	float speed = 1.0f;
	//

	float blackness = 1.0f - whiteness;
	float st = speed * s.time / 1000.0f;

	RGBQUAD color;
	float x = 0, y = 0, c = s.pixelc;
	float t = (float)s.time / 1000.0f;

	float uvx = 0, uvy;

	POINT mouse;
	GetCursorPos(&mouse);

	for (uint i = 0; i < c; i++)
	{
		x = i % s.width;
		y = s.height - i / s.width;

		color = rgbquad[i];
		uvx = x / s.width;
		uvy = y / s.height;

		float dist = hypot(x - mouse.x, y - mouse.y);

		if ( dist >= 100 && rand() % (int)noise == 0) dist = 0;

		if (dist < 60)
		{
			if (dist > 45)
			{
				color.rgbRed = 255 * (1 - (dist - 50) / 10);
				color.rgbGreen = 255 * (1 - (dist - 50) / 10);
				color.rgbBlue = 255 * (1 - (dist - 50) / 10);
			}
			else
			{
				color.rgbRed = rand() % 256;
				color.rgbGreen = rand() % 256;
				color.rgbBlue = rand() % 256;
			}
		}
		else
		{

			color.rgbRed = 255 * (whiteness + blackness * cos(st + uvx));
			color.rgbGreen = 255 * (whiteness + blackness * cos(st + uvy + 2));
			color.rgbBlue = 255 * (whiteness + blackness * cos(st + 4));

		}

		rgbquad[i] = color;
	}

	noise -= noise_increment;
	if (noise < 1) noise = 1;

	if (s.time > 15000) return -1;
	return 0;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	RunShaderS(&shader1);
	RunShaderS(&shader2);
	RunShaderS(&shader3);

	MessageBoxA(NULL, " ", "effectx.exe", MB_OK | MB_ICONINFORMATION);

	return 0;
}