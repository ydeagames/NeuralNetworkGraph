#pragma once

#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>

// STL
#include <exception>
#include <memory>
#include <stdexcept>

#include <cstdio>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

#include <fstream>

#include <algorithm>
#include <random>

#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <deque>

#include <chrono>
#include <locale> 
#include <codecvt> 

#include <thread>
#include <future>

#include <DxLib.h>

#define EXIT_KEY (KEY_INPUT_ESCAPE)    // 強制終了キー

// ゲームの終了
inline void ExitGame(void)
{
	PostQuitMessage(0);
}

enum ColorCode : unsigned int
{
	COLOR_BLACK = 0xFF000000,    // 黒色
	COLOR_NAVY = 0xFF000080,    // 濃紺色
	COLOR_GREEN = 0xFF008000,    // 緑色
	COLOR_TEAL = 0xFF008080,    // 青緑色
	COLOR_MAROON = 0xFF800000,    // マルーン色
	COLOR_PURPLE = 0xFF800080,    // 紫色
	COLOR_OLIVE = 0xFF808000,    // オリーブ色
	COLOR_GRAY = 0xFF808080,    // 灰色
	COLOR_SILVER = 0xFFC0C0C0,    // 銀色
	COLOR_BLUE = 0xFF0000FF,    // 青色
	COLOR_LIME = 0xFF00FF00,    // ライムグリーン色
	COLOR_AQUA = 0xFF00FFFF,    // 水色
	COLOR_RED = 0xFFFF0000,    // 赤色
	COLOR_FUCHSIA = 0xFFFF00FF,    // 赤紫色
	COLOR_YELLOW = 0xFFFFFF00,    // 黄色
	COLOR_WHITE = 0xFFFFFFFF,    // 白色
};
