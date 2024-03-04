/*----------------------------------------------------------------------------
	Program : PixGame.c
	Author  : Tom Stevelt
	Date    : Oct 2022
	Synopsis: Remember image after being distracted.
	See     : https://github.com/craigastewart/rorschach

	Who		Date		Modification
	---------------------------------------------------------------------

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

#define		MAIN
#include	"PixGame.h"

int main ( int argc, char *argv[] )
{
	GAME_RECORD	*ptr;
	char		*cp;

	seed_random_with_usec ();

	Shuffle = 1;
	NoDelay = 0;

	PaintTop ( 1 );

	if ( GetInput () != 1 )
	{
		if ( RunMode == MODE_SHOW_ALL_IMAGES )
		{
			ShowAll ( ImageSet );
			PaintBottom ();
			exit ( 0 );
		}

		if ( DistractionType == 0 )
		{
			DistractionType = DISTRACT_GET_NUMBER;
		}
		if ( strlen ( ImageSet ) > 0 )
		{
			ptr = StartGame ( ImageSet, 3 );
		}
		else
		{
			ptr = StartGame ( "CLIPART", 3 );
		}
		memcpy ( &Game, ptr, sizeof(GAME_RECORD) );
		RunMode = MODE_START;
	}

	PaintTop ( 2 );

	ChkInput ();

	switch ( RunMode )
	{
		case MODE_AGAIN:
			ptr = StartGame ( Game.ImageSet, 3 );
			memcpy ( &Game, ptr, sizeof(GAME_RECORD) );
			/* fall through */
		case MODE_UNKNOWN:
			RunMode = MODE_START;
			/* fall through */
		case MODE_START:
			LoadImageArray ( Game.ImageSet );
			if ( Shuffle )
			{
				ShufflePicks ( 1 );
			}
			else
			{
				GeneratePicks ();
			}
			/* fall through */
		case MODE_BIG:
			PaintBig();
			break;
		case MODE_DISTRACT:
			PaintDistract ( DistractionType );
			break;
		case MODE_LITTLE:
			if ( Shuffle )
			{
				ShuffleIndex += 3;
			}
			/* fall-through */
		case MODE_LITTLE_REPEAT:
			LoadImageArray ( Game.ImageSet );
			PaintLittle ();
			break;
		case MODE_EVAL:
			Game.Stage++;
			if ( RadioPick == Game.BigImage )
			{
				Game.Score++;
			}
			if ( Game.Stage < GAME_LENGTH )
			{
				LoadImageArray ( Game.ImageSet );
				if ( Shuffle )
				{
					ShufflePicks ( 0 );
				}
				else
				{
					GeneratePicks ();
				}
				PaintBig ();
				// js.eval() does nothing, just exists to keep browser happy
				printf ( "<script>\n" );
				printf ( "function Eval()\n" );
				printf ( "{\n" );
				printf ( "}\n" );
				printf ( "</script>\n" );
				break;
			}
			RunMode = MODE_END;
			/* fall through */
		case MODE_END:
			// js.eval() calls js.endgame()
			printf ( "<script>\n" );
			printf ( "function Eval()\n" );
			printf ( "{\n" );
			printf ( "\tEndGame();\n" );
			printf ( "}\n" );
			printf ( "</script>\n" );
			PaintEndGame ();
			LogGame ();
			break;
	}

	cp = GameToString(&Game,HSLEN);

#ifdef DEBUG
#define DEBUG
	printf ( "ShuffleArray = " );
	for ( int ndx = 0; ndx < SHUFFLESIZE; ndx++ )
	{
		printf ( "%s%d", ndx ? "," : "", ShuffleArray[ndx] );
	}
	printf ( "<br>\n" );

	printf ( "ShuffleIndex = %d<br>\n", ShuffleIndex );

	printf ( "GameString = %s<br>\n", cp );

#endif

	printf ( "<input type='hidden' name='GameStage' value='%d'>\n", Game.Stage );
	printf ( "<input type='hidden' name='ShuffleArray' value='" );
	for ( int ndx = 0; ndx < SHUFFLESIZE; ndx++ )
	{
		printf ( "%s%d", ndx ? "," : "", ShuffleArray[ndx] );
	}
	printf ( "'>\n" );
	printf ( "<input type='hidden' name='ShuffleIndex' value='%d'>\n", ShuffleIndex );

	printf ( "<input type='hidden' name='GameString' value='%s'>\n", cp );

	PaintBottom ();

	return ( 0 );
}
