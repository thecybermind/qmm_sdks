#pragma once

// q_shared.h -- included first by ALL program modules.
// A user mod should never modify this file

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include <time.h>
#include <ctype.h>
#include <cfloat> // FLT_MAX
#include <cstdint>
#include <climits>

#include "com_files.h"

// this is the define for determining if we have an asm version of a C function
#if (defined _M_IX86 || defined __i386__) && !defined __sun__  && !defined __LCC__
#define id386	1
#else
#define id386	0
#endif

// for windows fastcall option
#define	QDECL

//======================= WIN32 DEFINES =================================
#ifdef WIN32

#define	MAC_STATIC

#undef QDECL
#define	QDECL	

// buildstring will be incorporated into the version string
#ifdef NDEBUG
#ifdef _M_IX86
#define	CPUSTRING	"win-x86"
#elif defined _M_ALPHA
#define	CPUSTRING	"win-AXP"
#endif
#else
#ifdef _M_IX86
#define	CPUSTRING	"win-x86-debug"
#elif defined _M_ALPHA
#define	CPUSTRING	"win-AXP-debug"
#endif
#endif

#define ID_INLINE __inline 

int  ShortSwap(short l);
int  LongSwap(int l);

static ID_INLINE short BigShort(short l) { return ShortSwap(l); }
#define LittleShort
static ID_INLINE int BigLong(int l) { return LongSwap(l); }
#define LittleLong
//static ID_INLINE float BigFloat(const float *l) { FloatSwap(l); }
#define LittleFloat

#define	PATH_SEP '\\'

#endif // WIN32

#define PI_DIV_180		0.017453292519943295769236907684886
#define INV_PI_DIV_180	57.295779513082320876798154814105

// Punish Aurelio if you don't like these performance enhancements. :-)
#define DEG2RAD( a ) ( ( (a) * PI_DIV_180 ) )
#define RAD2DEG( a ) ( ( (a) * INV_PI_DIV_180 ) )

//=============================================================

typedef unsigned long		ulong;
typedef unsigned short		word;

typedef unsigned char 		byte;

typedef const char* LPCSTR;

typedef enum { qfalse, qtrue }	qboolean;
#define	qboolean	int		//don't want strict type checking on the qboolean

typedef int		qhandle_t;
typedef int		thandle_t;
typedef int		fxHandle_t;
typedef int		sfxHandle_t;
typedef intptr_t	fileHandle_t;
typedef int		clipHandle_t;

#define ptype_int intptr_t


#ifndef NULL
#define NULL ((void *)0)
#endif

#define	MAX_QINT			0x7fffffff
#define	MIN_QINT			(-MAX_QINT-1)


// angle indexes
#define	PITCH				0		// up / down
#define	YAW					1		// left / right
#define	ROLL				2		// fall over

// the game guarantees that no string from the network will ever
// exceed MAX_STRING_CHARS
#define	MAX_STRING_CHARS	1024	// max length of a string passed to Cmd_TokenizeString
#define	MAX_STRING_TOKENS	256		// max tokens resulting from Cmd_TokenizeString
#define	MAX_TOKEN_CHARS		1024	// max length of an individual token

#define	MAX_INFO_STRING		1024
#define	MAX_INFO_KEY		1024
#define	MAX_INFO_VALUE		1024


#define	MAX_QPATH			64		// max length of a quake game pathname
#define	MAX_OSPATH			260		// max length of a filesystem pathname

#define	MAX_NAME_LENGTH		32		// max length of a client name

#ifdef KISAK_SP
#define	MAX_GENTITIES		(2176) // 0x880
#elif KISAK_MP
#define	MAX_GENTITIES		(1024) // 0x400
#endif

#define ENTITYNUM_WORLD (MAX_GENTITIES - 2)
#define ENTITYNUM_NONE (MAX_GENTITIES - 1)

// paramters for command buffer stuffing
typedef enum {
	EXEC_NOW,			// don't return until completed, a VM should NEVER use this,
	// because some commands might cause the VM to be unloaded...
	EXEC_INSERT,		// insert at current position, but don't run yet
	EXEC_APPEND			// add to end of the command buffer (normal case)
} cbufExec_t;


//
// these aren't needed by any of the VMs.  put in another header?
//
#define	MAX_MAP_AREA_BYTES		32		// bit vector of area visibility

// Light Style Constants

#define LS_STYLES_START			0
#define LS_NUM_STYLES			32
#define	LS_SWITCH_START			(LS_STYLES_START+LS_NUM_STYLES)
#define LS_NUM_SWITCH			32
#define MAX_LIGHT_STYLES		64

// print levels from renderer (FIXME: set up for game / cgame?)
typedef enum {
	PRINT_ALL,
	PRINT_DEVELOPER,		// only print when "developer 1"
	PRINT_WARNING,
	PRINT_ERROR
} printParm_t;

// font rendering values used by ui and cgame
#define PROP_GAP_WIDTH			2
//#define PROP_GAP_WIDTH			3
#define PROP_SPACE_WIDTH		4
#define PROP_HEIGHT				16

#define PROP_TINY_SIZE_SCALE	1
#define PROP_SMALL_SIZE_SCALE	1
#define PROP_BIG_SIZE_SCALE		1
#define PROP_GIANT_SIZE_SCALE	2

#define PROP_TINY_HEIGHT		10
#define PROP_GAP_TINY_WIDTH		1
#define PROP_SPACE_TINY_WIDTH	3

#define PROP_BIG_HEIGHT			24
#define PROP_GAP_BIG_WIDTH		3
#define PROP_SPACE_BIG_WIDTH	6


#define BLINK_DIVISOR			600
#define PULSE_DIVISOR			75

#define UI_LEFT			0x00000000	// default
#define UI_CENTER		0x00000001
#define UI_RIGHT		0x00000002
#define UI_FORMATMASK	0x00000007
#define UI_SMALLFONT	0x00000010
#define UI_BIGFONT		0x00000020	// default
#define UI_GIANTFONT	0x00000040
#define UI_DROPSHADOW	0x00000800
#define UI_BLINK		0x00001000
#define UI_INVERSE		0x00002000
#define UI_PULSE		0x00004000
#define UI_UNDERLINE	0x00008000
#define UI_TINYFONT		0x00010000


// stuff for TA's ROQ cinematic code...
//
#define CIN_system	1
#define CIN_loop	2
#define	CIN_hold	4
#define CIN_silent	8
#define CIN_shader	16



#undef MAKEWORD
#undef MAKELONG
#undef LOWORD
#undef HIWORD
#undef LOBYTE
#undef HIBYTE

#if defined(__GNUC__)
typedef          long long ll;
typedef unsigned long long ull;
#define __int64 long long
#define int int
#define short short
#define char  char
#define MAKELL(num) num ## LL
#define FMT_64 "ll"
#elif defined(_MSC_VER)
typedef          __int64 ll;
typedef unsigned __int64 ull;
#define MAKELL(num) num ## i64
#define FMT_64 "I64"
#elif defined (__BORLANDC__)
typedef          __int64 ll;
typedef unsigned __int64 ull;
#define MAKELL(num) num ## i64
#define FMT_64 "L"
#else
#error "unknown compiler"
#endif
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;

typedef   signed char   int8;
typedef   signed char   sint8;
typedef unsigned char   uint8;
typedef          short  int16;
typedef   signed short  sint16;
typedef unsigned short  uint16;
typedef int				int32;
typedef unsigned int uint32;
typedef signed long			sint32;
typedef ll              int64;
typedef ll              sint64;
typedef ull             uint64;

// Partially defined types. They are used when the decompiler does not know
// anything about the type except its size.
#define _BYTE  uint8
#define _WORD  uint16
#define _DWORD uint32
#define _QWORD uint64
#if !defined(_MSC_VER)
#define _LONGLONG __int128
#endif

#ifndef M_PI
#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h
#endif

#define M_PI_HALF (M_PI / 2.0) 

// Some convenience macros to make partial accesses nicer
#define LAST_IND(x,part_type)    (sizeof(x)/sizeof(part_type) - 1)
#if defined(__BYTE_ORDER) && __BYTE_ORDER == __BIG_ENDIAN
#  define LOW_IND(x,part_type)   LAST_IND(x,part_type)
#  define HIGH_IND(x,part_type)  0
#else
#  define HIGH_IND(x,part_type)  LAST_IND(x,part_type)
#  define LOW_IND(x,part_type)   0
#endif
// first unsigned macros:
#define BYTEn(x, n)   (*((_BYTE*)&(x)+n))
#define WORDn(x, n)   (*((_WORD*)&(x)+n))
#define DWORDn(x, n)  (*((_DWORD*)&(x)+n))

#define LOBYTE(x)  BYTEn(x,LOW_IND(x,_BYTE))
#define LOWORD(x)  WORDn(x,LOW_IND(x,_WORD))
#define LODWORD(x) DWORDn(x,LOW_IND(x,_DWORD))
#define HIBYTE(x)  BYTEn(x,HIGH_IND(x,_BYTE))
#define HIWORD(x)  WORDn(x,HIGH_IND(x,_WORD))
#define HIDWORD(x) DWORDn(x,HIGH_IND(x,_DWORD))
#define BYTE1(x)   BYTEn(x,  1)         // byte 1 (counting from 0)
#define BYTE2(x)   BYTEn(x,  2)
#define BYTE3(x)   BYTEn(x,  3)
#define BYTE4(x)   BYTEn(x,  4)
#define BYTE5(x)   BYTEn(x,  5)
#define BYTE6(x)   BYTEn(x,  6)
#define BYTE7(x)   BYTEn(x,  7)
#define BYTE8(x)   BYTEn(x,  8)
#define BYTE9(x)   BYTEn(x,  9)
#define BYTE10(x)  BYTEn(x, 10)
#define BYTE11(x)  BYTEn(x, 11)
#define BYTE12(x)  BYTEn(x, 12)
#define BYTE13(x)  BYTEn(x, 13)
#define BYTE14(x)  BYTEn(x, 14)
#define BYTE15(x)  BYTEn(x, 15)
#define WORD1(x)   WORDn(x,  1)
#define WORD2(x)   WORDn(x,  2)         // third word of the object, unsigned
#define WORD3(x)   WORDn(x,  3)
#define WORD4(x)   WORDn(x,  4)
#define WORD5(x)   WORDn(x,  5)
#define WORD6(x)   WORDn(x,  6)
#define WORD7(x)   WORDn(x,  7)

// now signed macros (the same but with sign extension)
#define SBYTEn(x, n)   (*((int8*)&(x)+n))
#define SWORDn(x, n)   (*((int16*)&(x)+n))
#define SDWORDn(x, n)  (*((int32*)&(x)+n))

#define SLOBYTE(x)  SBYTEn(x,LOW_IND(x,int8))
#define SLOWORD(x)  SWORDn(x,LOW_IND(x,int16))
#define SLODWORD(x) SDWORDn(x,LOW_IND(x,int32))
#define SHIBYTE(x)  SBYTEn(x,HIGH_IND(x,int8))
#define SHIWORD(x)  SWORDn(x,HIGH_IND(x,int16))
#define SHIDWORD(x) SDWORDn(x,HIGH_IND(x,int32))
#define SBYTE1(x)   SBYTEn(x,  1)
#define SBYTE2(x)   SBYTEn(x,  2)
#define SBYTE3(x)   SBYTEn(x,  3)
#define SBYTE4(x)   SBYTEn(x,  4)
#define SBYTE5(x)   SBYTEn(x,  5)
#define SBYTE6(x)   SBYTEn(x,  6)
#define SBYTE7(x)   SBYTEn(x,  7)
#define SBYTE8(x)   SBYTEn(x,  8)
#define SBYTE9(x)   SBYTEn(x,  9)
#define SBYTE10(x)  SBYTEn(x, 10)
#define SBYTE11(x)  SBYTEn(x, 11)
#define SBYTE12(x)  SBYTEn(x, 12)
#define SBYTE13(x)  SBYTEn(x, 13)
#define SBYTE14(x)  SBYTEn(x, 14)
#define SBYTE15(x)  SBYTEn(x, 15)
#define SWORD1(x)   SWORDn(x,  1)
#define SWORD2(x)   SWORDn(x,  2)
#define SWORD3(x)   SWORDn(x,  3)
#define SWORD4(x)   SWORDn(x,  4)
#define SWORD5(x)   SWORDn(x,  5)
#define SWORD6(x)   SWORDn(x,  6)
#define SWORD7(x)   SWORDn(x,  7)

// Generate a pair of operands. S stands for 'signed'
#define __SPAIR16__(high, low)  (((int16)  (high) <<  8) | (uint8) (low))
#define __SPAIR32__(high, low)  (((int32)  (high) << 16) | (uint16)(low))
#define __SPAIR64__(high, low)  (((int64)  (high) << 32) | (uint32)(low))
#define __SPAIR128__(high, low) (((int128) (high) << 64) | (uint64)(low))
#define __PAIR16__(high, low)   (((uint16) (high) <<  8) | (uint8) (low))
#define __PAIR32__(high, low)   (((uint32) (high) << 16) | (uint16)(low))
#define __PAIR64__(high, low)   (((uint64) (high) << 32) | (uint32)(low))
#define __PAIR128__(high, low)  (((uint128)(high) << 64) | (uint64)(low))



//=============================================
enum CvarType
{
	CVAR_TYPE_BOOL = 0x0,
	CVAR_TYPE_FLOAT = 0x1,
	CVAR_TYPE_FLOAT_2 = 0x2,
	CVAR_TYPE_FLOAT_3 = 0x3,
	CVAR_TYPE_FLOAT_4 = 0x4,
	CVAR_TYPE_INT = 0x5,
	CVAR_TYPE_ENUM = 0x6,
	CVAR_TYPE_STRING = 0x7,
	CVAR_TYPE_COLOR = 0x8,
	CVAR_TYPE_COUNT = 0x9,
};

enum CvarFlags : uint16
{
	CVAR_NOFLAG             = 0x0,
	CVAR_ARCHIVE            = 0x1,  // will be saved to config(_mp).cfg
	CVAR_USERINFO           = 0x2,  // sent to server on connect or change
	CVAR_SERVERINFO         = 0x4,  // sent in response to front end requests
	CVAR_SYSTEMINFO         = 0x8,  // this is sent (replicated) to all clients if you are host
	CVAR_INIT               = 0x10, // don't allow change from console at all (i think)
	CVAR_LATCH              = 0x20, // will only change when C code next does
                                    // a Cvar_Get(), so it can't be changed
                                    // without proper initialization.  modified
                                    // will be set, even though the value hasn't changed yet
	
	CVAR_ROM                = 0x40, // display only, cannot be set by user at all (can be set by code)
	CVAR_CHEAT              = 0x80, // can not be changed if cheats are disabled

	// CVAR_AUTOEXEC, CVAR_SAVED, and CVAR_CHANGEABLE_RESET are not 100% sure
	CVAR_TEMP               = 0x100,
	CVAR_AUTOEXEC           = 0x200,
	CVAR_NORESTART          = 0x400,    // do not clear when a cvar_restart is issued
	CVAR_SAVED              = 0x1000,
	CVAR_EXTERNAL           = 0x4000,   // created by a set command or setclientdvar
	CVAR_CHANGEABLE_RESET   = 0x8000,
};

union CvarValue 
{                
	CvarValue()
	{
		integer = 0;
	}
	CvarValue(int i)
	{
		integer = i;
	}
	CvarValue(bool b)
	{
		enabled = b;
	}
	CvarValue(float f)
	{
		value = f;
	}
	CvarValue(const char *str)
	{
		string = str;
	}
	CvarValue(char *str)
	{
		string = str;
	}
    bool enabled;
    int integer;
    unsigned int unsignedInt;
    float value;
    float vector[4];
    const char *string;
    byte color[4];
};
struct CvarLimits_Enumeration
{
	int stringCount;
	const char** strings;
};
struct CvarLimits_Integer
{
	int min;
	int max;
};
struct CvarLimits_Value
{
	float min; 
	float max;
};
struct CvarLimits_Vector
{
	float min;
	float max;
};
union CvarLimits
{
	CvarLimits()
	{
		integer.min = INT_MIN;
		integer.max = INT_MAX;
	}
	CvarLimits(uint64 val)
	{
		integer.max = HIDWORD(val);
		integer.min = LODWORD(val);
	}
	CvarLimits(int min, int max)
	{
		integer.min = min; 
		integer.max = max;
	}
	CvarLimits_Enumeration enumeration;
	CvarLimits_Integer integer;
	CvarLimits_Value value;
	CvarLimits_Vector vector;
};

// nothing outside the Dvar_*() functions should modify these fields!
struct cvar_s {
	const char *name;
	const char *description;
	word flags;
	byte type;
	bool modified;
	CvarValue current;
	CvarValue latched;
	CvarValue reset;
	CvarLimits domain;
	bool ( *domainFunc)(cvar_s*, CvarValue);
	cvar_s* hashNext;
};

using cvar_t = cvar_s;

//=============================================

struct cspField_t 
{                                       
	const char *szName;                 
	int iOffset;                        
	int iFieldType;                     
};

union FloatWriteSwap_union 
{                                       
	float f;
	int n;
	unsigned char b[4];
};

union FloatReadSwap_union 
{                                       
	float f;
	int n;
	unsigned char b[4];
};

static const float colorBlack[4] = { 0.0, 0.0, 0.0, 1.0 }; // idb
static const float colorRed[4] = { 1.0, 0.0, 0.0, 1.0 }; // idb
static const float colorGreen[4] = { 0.0, 1.0, 0.0, 1.0 }; // idb
static const float colorLtGreen[4] = { 0.0, 0.69999999f, 0.0, 1.0 }; // idb
static const float colorBlue[4] = { 0.0, 0.0, 1.0, 1.0 }; // idb
static const float colorLtBlue[4] = { 0.5, 0.5, 1.0, 1.0 }; // idb
static const float colorYellow[4] = { 1.0, 1.0, 0.0, 1.0 }; // idb
static const float colorLtYellow[4] = { 0.75, 0.75f, 0.0f, 1.0f };
static const float colorMdYellow[4] = { 0.5, 0.5, 0.0, 1.0 }; // idb
static const float colorMagenta[4] = { 1.0, 0.0, 1.0, 1.0 }; // idb
static const float colorCyan[4] = { 0.0f, 1.0f, 1.0f, 1.0f };
static const float colorLtCyan[4] = { 0.0, 0.75, 0.75, 1.0 }; // idb
static const float colorMdCyan[4] = { 0.0f, 0.5f, 0.5f, 1.0f };
static const float colorDkCyan[4] = { 0.0f, 0.25f, 0.25f, 1.0f };
static const float colorWhite[4] = { 1.0, 1.0, 1.0, 1.0 }; // idb
static const float colorLtGrey[4] = { 0.75, 0.75, 0.75, 1.0 }; // idb
static const float colorMdGrey[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
static const float colorDkGrey[4] = { 0.25f, 0.25f, 0.25f, 1.0f };
static const float colorOrange[4] = { 1.0, 0.69999999f, 0.0, 1.0 }; // idb
static const float colorLtOrange[4] = { 0.75, 0.52499998f, 0.0, 1.0 }; // idb
static const float colorWhiteFaded[4] = { 1.0, 1.0, 1.0, 0.75 }; // idb
static const float colorGreenFaded[4] = { 0.0, 1.0, 0.0, 0.75 }; // idb
static const float colorRedFaded[4] = { 0.75, 0.25, 0.0, 0.75 }; // idb


#define arr_esize(a) (sizeof((a)[0]))
#define arr_cnt(a) (sizeof(a)/arr_esize(a))
#define ARRAY_COUNT(a) arr_cnt(a)
struct va_info_t
{
	char va_string[2][1024];
	int index;
};


struct TraceCheckCount
{
	int global;
	int *partitions;
};
struct TraceThreadInfo
{
	TraceCheckCount checkcount;
	struct cbrush_t *box_brush;
	struct cmodel_t *box_model;
};

enum TraceHitType
{                                       
	TRACE_HITTYPE_NONE = 0x0,
	TRACE_HITTYPE_ENTITY = 0x1,
	TRACE_HITTYPE_DYNENT_MODEL = 0x2,
	TRACE_HITTYPE_DYNENT_BRUSH = 0x3,
};

#define SURF_INVALID -1

struct trace_t 
{   
	trace_t()
	{
		memset(this, 0, sizeof(trace_t));
	}
	
	float fraction;                     
	float normal[3];                    
	int surfaceFlags;                   
	int contents;                       
	const char *material;               
	TraceHitType hitType;               
	unsigned short hitId;
	unsigned short modelIndex;        
	unsigned short partName;          
	unsigned short partGroup;         
	bool allsolid;                      
	bool startsolid;                    
	bool walkable;                      
	
};


// com_shared
struct qtime_s 
{                                       
	int tm_sec;
	int tm_min;                         
	int tm_hour;                        
	int tm_mday;                        
	int tm_mon;                         
	int tm_year;                        
	int tm_wday;
	int tm_yday;
	int tm_isdst;
};


enum trType_t
{                                       
	TR_STATIONARY = 0x0,
	TR_INTERPOLATE = 0x1,
	TR_LINEAR = 0x2,
	TR_LINEAR_STOP = 0x3,
	TR_SINE = 0x4,
	TR_GRAVITY = 0x5,
	TR_ACCELERATE = 0x6,
	TR_DECELERATE = 0x7,
	TR_PHYSICS = 0x8,
	TR_FIRST_RAGDOLL = 0x9,
	TR_RAGDOLL = 0x9,
	TR_RAGDOLL_GRAVITY = 0xA,
	TR_RAGDOLL_INTERPOLATE = 0xB,
	TR_LAST_RAGDOLL = 0xB,
};

struct trajectory_t 
{                                       
	trType_t trType;                    
	int trTime;                         
	int trDuration;                     
	float trBase[3];                    
	float trDelta[3];                   
};

// com_stringtable
struct StringTable 
{                                       
	const char *name;
	int columnCount;
	int rowCount;
	const char **values;
};

union XAssetHeader;
