#pragma once
#include <Windows.h>
#include <math.h>

#define M_PI 3.14159265358979323846f

#define RunShaderS(s) RunShader(s, TRUE)
#define RunShaderA(s) RunShader(s, FALSE)

typedef unsigned int uint;

typedef struct {
	HINSTANCE hInstance;
	int nCmdShow;
} wdata;

typedef struct {
	uint width;
	uint height;
	uint time;
	uint pixelc;
} sinfo;
