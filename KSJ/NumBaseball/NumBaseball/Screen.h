#pragma once

#include <windows.h>

static int g_nScreenIndex;
static HANDLE g_hScreen[2];

void ScreenInit();
void ScreenFlipping();
void ScreenClear();
void ScreenRelease();
void ScreenPrint(int, int, char*);
void SetColor(unsigned short);