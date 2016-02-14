#pragma once

#include <stdio.h>
#include <stdarg.h>
#include <Windows.h>

enum ErrorLevel
{
  Info    = 1 << 0, // 1
  Warning = 1 << 1, // 2
  Error   = 1 << 2  // 4
} ;

enum ConsoleColor
{
  ConsoleRed = FOREGROUND_INTENSITY|FOREGROUND_RED,
  ConsoleYellow = FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN,
  ConsoleGray = FOREGROUND_INTENSITY
} ;

extern const char* progname ;
extern const char* ErrorLevelName[] ;

void error( const char *fmt, ... );
void warning( const char *fmt, ... );
void info( const char *fmt, ... );

