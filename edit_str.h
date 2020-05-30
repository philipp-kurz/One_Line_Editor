#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>

#include "conio.h"
#include "libs/conio32.h"

#ifdef _DEBUG
#pragma comment(lib, "libs/conio32_debug.lib")
#else
#pragma comment(lib, "libs/conio32_release.lib")
#endif

struct pos {
    int x;
    int y;
};

int edit_str(char *, char *, char *, int );