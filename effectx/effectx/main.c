#include "def.h"

int WaveShader(RGBQUAD* pixels, sinfo info)
{
    RGBQUAD* temp = (RGBQUAD*)malloc(sizeof(RGBQUAD) * info.pixelc);
    if (!temp) return -1;

    memcpy(temp, pixels, sizeof(RGBQUAD) * info.pixelc);

    float time = info.time / 1000.0f;
    float frequency = 0.02f;
    float amplitude = 20.0f;
    int width = info.width;
    int height = info.height;

    for (int y = 0; y < height; ++y)
    {
        float offsetX = sinf(time + y * frequency) * amplitude;

        for (int x = 0; x < width; ++x)
        {
            int srcX = x + (int)offsetX;

            if (srcX >= 0 && srcX < width)
            {
                int dstIndex = y * width + x;
                int srcIndex = y * width + srcX;
                pixels[dstIndex] = temp[srcIndex];
            }
        }
    }

    free(temp);
    if (time >= 8) return -1;
    return 16; // ~60 FPS
}

int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	RunShaderS(&WaveShader);

	return 0;
}
