// ezc - main
// main.c - primary entry point for ezc engine.
// win32 only

#include "engine.h"

int CALLBACK WinMain(
	  HINSTANCE hInstance,
	  HINSTANCE hPrevInstance,
	  LPSTR     lpCmdLine,
	  int       nShowCmd)
{
	E_run(hInstance);
	return 0;
}