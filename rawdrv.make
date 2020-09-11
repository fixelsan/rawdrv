#   File:       rawdrv.make
#   Target:     rawdrv
#   Sources:    rawdrv.c kernel_calls.s
#   Created:    Thursday, September 10, 2020 11:40:25 PM
#
#   Copyright 3DO Company, 1993, 1994
#   All rights reserved.
#
#		Change History (most recent first):
#
#   		<>		---		Created by Create3DOMake 2.4

#####################################
#	Symbol definitions
#####################################

App				= rawdrv
DebugFlag		= 0
SourceDir		= MacHD:Desktop Folder:3do_booter:rawdrv:
ObjectDir		= :Objects:
CC				= armcc
ASM				= armasm
LINK			= armlink
WorkingDisk		= ''

#####################################
#	Default compiler options
#####################################

COptions			= -fa -zps0 -za1
SOptions			= -bi
LOptions			= -aif -r -b 0x00
LStackSize			= 4096

#####################################
#	Object files
#####################################

OBJECTS			=	 {ObjectDir}rawdrv.c.o {ObjectDir}kernel_calls.s.o "{3DOLibs}"cstartup.o

LIBS			=	 ¶
					"{3DOLibs}Lib3DO.lib" ¶
					"{3DOLibs}audio.lib" ¶
					"{3DOLibs}music.lib" ¶
					"{3DOLibs}operamath.lib" ¶
					"{3DOLibs}filesystem.lib" ¶
					"{3DOLibs}graphics.lib" ¶
					"{3DOLibs}input.lib" ¶
					"{3DOLibs}clib.lib" ¶
					"{3DOLibs}swi.lib"

#####################################
#	Default build rules
#####################################

All				Ä	{App}

{ObjectDir}		Ä	:

.c.o	Ä	.c
	{CC} -i "{3DOIncludes}" {COptions} -o {TargDir}{Default}.c.o {DepDir}{Default}.c

.s.o	Ä	.s
	{ASM} -i "{3DOIncludes}" {SOptions} -o {TargDir}{Default}.s.o {DepDir}{Default}.s

#####################################
#	Target build rules
#####################################

{App} Ä {App}.make {OBJECTS}
	{LINK} {LOptions} ¶
		{OBJECTS} ¶
		{LIBS} ¶
		-o "{WorkingDisk}"{Targ}
	SetFile "{WorkingDisk}"{Targ} -c '3DO ' -t APPL
	modbin "{WorkingDisk}"{Targ} -flags 2 -stack {LStackSize}
	stripaif "{WorkingDisk}"{Targ} -o {Targ} -s {Targ}.sym
	duplicate {3DOAutodup} {Targ} "{3DORemote}"

#####################################
#	Additional Target Dependencies
#####################################

{ObjectDir}rawdrv.c.o			Ä	{App}.make
{ObjectDir}kernel_calls.s.o			Ä	{App}.make

