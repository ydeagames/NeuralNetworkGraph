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

#define EXIT_KEY (KEY_INPUT_ESCAPE)    // �����I���L�[

// �Q�[���̏I��
inline void ExitGame(void)
{
	PostQuitMessage(0);
}

enum ColorCode : unsigned int
{
	COLOR_BLACK = 0xFF000000,    // ���F
	COLOR_NAVY = 0xFF000080,    // �Z���F
	COLOR_GREEN = 0xFF008000,    // �ΐF
	COLOR_TEAL = 0xFF008080,    // �ΐF
	COLOR_MAROON = 0xFF800000,    // �}���[���F
	COLOR_PURPLE = 0xFF800080,    // ���F
	COLOR_OLIVE = 0xFF808000,    // �I���[�u�F
	COLOR_GRAY = 0xFF808080,    // �D�F
	COLOR_SILVER = 0xFFC0C0C0,    // ��F
	COLOR_BLUE = 0xFF0000FF,    // �F
	COLOR_LIME = 0xFF00FF00,    // ���C���O���[���F
	COLOR_AQUA = 0xFF00FFFF,    // ���F
	COLOR_RED = 0xFFFF0000,    // �ԐF
	COLOR_FUCHSIA = 0xFFFF00FF,    // �Ԏ��F
	COLOR_YELLOW = 0xFFFFFF00,    // ���F
	COLOR_WHITE = 0xFFFFFFFF,    // ���F
};
