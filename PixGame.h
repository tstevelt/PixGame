//     PixGame
// 
//     Copyright (C)  2022 Tom Stevelt
// 
//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU Affero General Public License as
//     published by the Free Software Foundation, either version 3 of the
//     License, or (at your option) any later version.
// 
//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU Affero General Public License for more details.
// 
//     You should have received a copy of the GNU Affero General Public License
//     along with this program.  If not, see <https://www.gnu.org/licenses/>.


#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<string.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<dirent.h>
#include	<stdint.h>
#include	<errno.h>
#include	<libgen.h>		// for basename()

#include	"shslib.h"
#include	"weblib.h"

#ifdef MAIN
#define	TYPE	/* */
#else
#define	TYPE	extern
#endif

#define		LOGFILE		"/var/local/webstate/PixGame/PixGame.log"

TYPE	int		NoDelay;
TYPE	int		Shuffle;

/*---------------------------------------------------------------------------
	this comment may not be up-to-date.  verify against source code.
	123456789-123456789-123456789-123456789-123456789-123456789-123456789-
	0   1       2      3   4    5     6     
	GAM  ID      SET   STG BIGI SCORE ARRAY
	PIX 9999999 CLIPART 00 11   01    99 99 99 ...
	PIX 9999999 TAROT   00 11   01    99 99 99 ...
	WRD 9999999 ...     00 ...
	NUM 9999999 ...     00 ...
	SND 9999999 ...     00 ...
---------------------------------------------------------------------------*/
#define		HSLEN		70
TYPE	char	GameString[HSLEN];
TYPE	char	ImageSet[10];
#define		MAXPICKS	10
typedef struct
{
	int		PlayerID;
	char	ImageSet[10];
	int		Stage;
	int		BigImage;
	int		Score;
	int		Picks[MAXPICKS];
	int		PickCount;
} GAME_RECORD;

TYPE	GAME_RECORD		Game;
TYPE		int			RadioPick;
#define	GAME_LENGTH		10

#define		SHUFFLESIZE		(MAXPICKS*3)
TYPE	int		ShuffleArray [SHUFFLESIZE];
TYPE	int		ShuffleIndex;

#define		BIG		400
#define		SMALL	200

#define		DISTRACT_GET_NUMBER		1
#define		DISTRACT_RANDOM_IMAGE	2
#define		DISTRACT_ARITHMETIC		3
#define		DISTRACT_WORD			4

TYPE		int			RunMode;
#define		MODE_UNKNOWN			0
#define		MODE_START				1
#define		MODE_BIG				2
#define		MODE_DISTRACT			3
#define		MODE_LITTLE				4
#define		MODE_EVAL				5
#define		MODE_END				6
#define		MODE_AGAIN				7
#define		MODE_LITTLE_REPEAT		8
#define		MODE_SHOW_ALL_IMAGES	9

TYPE	int		Debug;
TYPE	int		Width;
TYPE	int		Height;
TYPE	int		TestValue;
TYPE	int		UserValue;
TYPE	char	*TestWord;
TYPE	char	*UserWord;
TYPE	int		DistractionType;

#define		MAXNAMELEN		64
#define		MAXIMAGES		100

typedef struct
{
	char	ImageFileName[MAXNAMELEN];
	int		FileSize;
} IMAGE_RECORD;

TYPE	 IMAGE_RECORD	ImageArray [ MAXIMAGES ];
TYPE	 int			ImageCount;

/*----------------------------
:.,$d
:r ! mkproto -p *.c
----------------------------*/

/* ChkInput.c */
void ChkInput ( void );

/* GameFuncs.c */
int ComparePicks ( int *a , int *b );
void PrintGameRecord ( char *msg , GAME_RECORD *ptr );
GAME_RECORD *StartGame ( char *ImageSet , int PickCount );
GAME_RECORD *StringToGame ( char *String );
char *GameToString ( GAME_RECORD *ptr , size_t Size );

/* GeneratePicks.c */
void GeneratePicks ( void );

/* GetInput.c */
int GetInput ( void );

/* LoadImageArray.c */
void LoadImageArray ( char *ImageSet );

/* LogGame.c */
void LogGame ( void );

/* PaintBig.c */
void PaintBig ( void );

/* PaintBottom.c */
void PaintBottom ( void );

/* PaintDistract.c */
void PaintDistract ( int DistractionType );

/* PaintEndGame.c */
void PaintEndGame ( void );

/* PaintLittle.c */
void PaintLittle ( void );

/* PaintTop.c */
void PaintTop ( int Stage );

/* PixGame.c */
int main ( int argc , char *argv []);

/* ShowAll.c */
void ShowAll ( char *ImageSet );

/* ShufflePicks.c */
void ShufflePicks ( int FirstPass );
