/*----------------------------------------------------------------------------
	Program : GameFuncs.c
	Author  : Tom Stevelt
	Date    : 2022
	Synopsis: Game functions
				ComparePicks - comparisonn function for qsort/bsearch
				PrintGameRecord - development/debugging function. not called.
				StartGame - initialize game record.

				Game progress is passed back and forth between browser
				and server.  Game is stateless.
				StringToGame - Get string from browser and convert to game record.
				GameToString - Make string to send to browser.
	Return  : 
----------------------------------------------------------------------------*/
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

#include	"PixGame.h"

int ComparePicks ( int *a, int *b )
{
	if ( *a < *b )
	{
		return ( -1 );
	}
	if ( *a > *b )
	{
		return ( 1 );
	}
	return ( 0 );
}

void PrintGameRecord ( char *msg, GAME_RECORD *ptr )
{
	int		x;

	return;

	printf ( "PrintGameRecord from %s<br>\n", msg );
	printf ( "ID %d<br>\n", ptr->PlayerID );
	printf ( "SET %s<br>\n", ptr->ImageSet );
	printf ( "STG %d<br>\n", ptr->Stage );
	printf ( "BIG %d<br>\n", ptr->BigImage );
	printf ( "COUNT %d<br>\n", ptr->PickCount );
	for ( x = 0; x < ptr->PickCount; x++ )
	{
		printf ( "PICK %d<br>\n", ptr->Picks[x] );
	}
	printf ( "SCORE %d<br>\n", ptr->Score );
}

GAME_RECORD *StartGame ( char *ImageSet, int PickCount )
{
	static	GAME_RECORD		game;

	if ( PickCount >= MAXPICKS )
	{
		return ( (GAME_RECORD *) NULL );
	}

	game.PlayerID = random_range ( 1001, 9999 ) * 10 + DistractionType;
	snprintf ( game.ImageSet, sizeof(game.ImageSet), "%s", ImageSet );
	game.Stage = 0;
	game.Score = 0;
	game.BigImage = 1;
	game.PickCount = PickCount;
	memset ( game.Picks, '\0', sizeof(game.Picks) );

	PrintGameRecord ( "StartGame", &game );

	return ( &game );
}

GAME_RECORD *StringToGame ( char *String )
{
	static	GAME_RECORD		game;
	char	xbuffer[1024];
	#define		MAXTOK		20
	char	*tokens[MAXTOK];
	int		tokcnt, xt;

	/*----------------------------------------------------------
		0   1       2       3   4   5     6  7  8  ...
		PIX 9999999 CLIPART STG BIG SCORE 99 99 99 ...
	----------------------------------------------------------*/
	#define		NDX		6
	#define		MINTOKS	7

	snprintf ( xbuffer, sizeof(xbuffer), "%s", String );
	if (( tokcnt = GetTokensD ( xbuffer, " _",  tokens, MAXTOK )) < MINTOKS )
	{
		fprintf ( stderr, "StringToGame: tokcnt %d\n", tokcnt );
		return ( (GAME_RECORD *) 0 );
	}

	if ( strcmp ( tokens[0], "PIX" ) != 0 )
	{
		fprintf ( stderr, "StringToGame: not PIX game\n" );
		return ( (GAME_RECORD *) 0 );
	}

	game.PlayerID = atoi ( tokens[1] );
	DistractionType = game.PlayerID % 10;
	snprintf ( game.ImageSet, sizeof(game.ImageSet), "%s", tokens[2] );
	game.Stage = atoi ( tokens[3] );
	game.BigImage = atoi ( tokens[4] );
	game.Score = atoi ( tokens[5] );
	game.PickCount = 0;
	memset ( game.Picks, '\0', sizeof(game.Picks) );
	for ( xt = NDX; xt < tokcnt; xt++ )
	{
		if ( xt - NDX >= MAXPICKS )
		{
			break;
		}
		game.Picks[xt-NDX] = atoi ( tokens[xt] );
		game.PickCount++;
	}

	PrintGameRecord ( "StringToGame", &game );

	return ( &game );
}

char *GameToString ( GAME_RECORD *ptr, size_t Size )
{
	static	char	*cp = NULL;
	char	Fragment[8];
	int		x;

	PrintGameRecord ( "GameToString", ptr );

	cp = calloc ( 1, Size );
	snprintf ( cp, Size, "PIX_%d_%s_%d_%d_%d", ptr->PlayerID, ptr->ImageSet, ptr->Stage, ptr->BigImage, ptr->Score );

	for ( x = 0; x < ptr->PickCount; x++ )
	{
		sprintf ( Fragment, "_%d", ptr->Picks[x] );
		strcat ( cp, Fragment );
	}

	// printf ( "%s<br>\n", cp );

	return ( cp );
}
