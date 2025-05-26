#ifndef CORES_HPP
#define CORES_HPP

#include <windows.h>

inline void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

#endif 