#include "Util.h"

#include <time.h>
#include <Windows.h>

// LOGGING
const char* progname = "RTSConsole" ;

//  Info    = 1 << 0, // 1
//  Warning = 1 << 1, // 2
//  Error   = 1 << 2  // 4
const char* ErrorLevelName[] = {
  "", //0
  "Info", //1
  "Warning", //2
  "",//3
  "Error", //4
  "","","" //5,6,7
} ;

tm* getCurrentTime()
{
  static time_t raw ;

  // grab the current time
  time( &raw ) ;

  // Now create that timeinfo struct
  static tm* timeinfo ;
  timeinfo = localtime( &raw ) ;

  return timeinfo ;
}

// decorates the log message with [appname][thread][error level][current time]:  message
void logDecorate( int logLevel, short color, const char *fmt, va_list args )
{
  // to be threadsafe, removed static
  char msgBuffer[ 4096 ] ;  // oops. Had a 623 char error (from shader) and it err-d out.
  vsprintf( msgBuffer, fmt, args ) ;
  
  // write time into timeBuff. Should be about 8 chars hh:mm:ss
  char timeBuf[ 32 ] ;
  strftime( timeBuf, 255, "%X", getCurrentTime() ) ;

  // Put it all together
  char buf[ 4096 ] ;
  
  sprintf( buf, "[ %s ][ %s ][ %s ]:  %s", progname, ErrorLevelName[ logLevel ], timeBuf, msgBuffer ) ;
  SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), color );
  //printf( "%s\n", buf ) ; // don't want inserted.
  puts( buf ) ;
  SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE );

}

void error( const char *fmt, ... )
{
  va_list lp ;
  va_start( lp, fmt ) ;

  logDecorate( ErrorLevel::Error, ConsoleRed, fmt, lp ) ;
}

void warning( const char *fmt, ... )
{
  va_list lp ;
  va_start( lp, fmt ) ;

  logDecorate( ErrorLevel::Warning, ConsoleYellow, fmt, lp ) ;
}

void info( const char *fmt, ... )
{
  va_list lp ;
  va_start( lp, fmt ) ;

  logDecorate( ErrorLevel::Info, ConsoleGray, fmt, lp ) ;
}