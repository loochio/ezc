// engine.h - core portable common engine code

#ifndef EZC_ENGINE_H
#define EZC_ENGINE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <windows.h>
#include <gl/GL.h>


void E_log(const char *fmt, ...);

void E_run(HINSTANCE hInstance);

#endif //EZC_ENGINE_H
