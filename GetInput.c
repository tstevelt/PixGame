/*----------------------------------------------------------------------------
	Program : GetInput.c
	Author  : Tom Stevelt
	Date    : 2022
	Synopsis: Get user input from screen or query_string
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

int GetInput ()
{
	int		xa;
	int		rv = 0;

	if ( webGetInput () != 0 )
	{
		printf ( "cgiIntergrate: Input error!<br>\n" );
	}

	for ( xa = 0; xa < webCount; xa++ )
	{
		webFixHex ( webValues[xa] );

// printf ( "name value pair %s = %s<br>\n", webNames[xa], webValues[xa] );

		if ( strcmp (webNames[xa], "showall" ) == 0 )
		{
			RunMode = MODE_SHOW_ALL_IMAGES;
		}
		else if ( strcmp (webNames[xa], "nodelay" ) == 0 )
		{
			NoDelay = nsAtoi ( webValues[xa] );
		}
		else if ( strcmp (webNames[xa], "Width" ) == 0 )
		{
			Width = nsAtoi ( webValues[xa] );
		}
		else if ( strcmp (webNames[xa], "Height" ) == 0 )
		{
			Height = nsAtoi ( webValues[xa] );
		}
		else if ( strcmp (webNames[xa], "mode" ) == 0 )
		{
			switch ( webValues[xa][0] )
			{
				case '1':
				case 'N':
					DistractionType = DISTRACT_GET_NUMBER;
					break;
				case '2':
				case 'R':
					DistractionType = DISTRACT_RANDOM_IMAGE;
					break;
				case '3':
				case 'A':
					DistractionType = DISTRACT_ARITHMETIC;
					break;
				case '4':
				case 'W':
					DistractionType = DISTRACT_WORD;
					break;
				default:
					printf ( "Unknown mode, using default<br>\n" );
					DistractionType = DISTRACT_GET_NUMBER;
					break;
			}
		}

		else if ( strcmp (webNames[xa], "GameString" ) == 0 )
		{
			snprintf ( GameString, sizeof(GameString), "%s", webValues[xa] );
			memcpy ( &Game, StringToGame(GameString), sizeof(Game) );
			rv = 1;
		}
		else if ( strcmp (webNames[xa], "ImageSet" ) == 0 )
		{
			snprintf ( ImageSet, sizeof(ImageSet), "%s", webValues[xa] );
		}

		else if ( strcmp (webNames[xa], "radio_pick" ) == 0 )
		{
			RadioPick = atoi ( &webValues[xa][3] );
		}
		else if ( strcmp (webNames[xa], "submitBig" ) == 0 )
		{
			RunMode = MODE_DISTRACT;;
		}

		else if ( strncmp (webNames[xa], "Test_", 5 ) == 0 )
		{
			TestValue = atoi ( &webNames [xa][5] );
			UserValue = atoi (  webValues[xa]    );
		}
		else if ( strncmp (webNames[xa], "Word_", 5 ) == 0 )
		{
			TestValue = UserValue = -1;
			TestWord = &webNames [xa][5];
			UserWord =  webValues[xa];
		}
		else if ( strcmp (webNames[xa], "submitTest" ) == 0 )
		{
			RunMode = MODE_LITTLE;
		}
		else if ( strcmp (webNames[xa], "submitNoTest" ) == 0 )
		{
			TestValue = UserValue = 123;
			RunMode = MODE_LITTLE;
		}

		else if ( strcmp (webNames[xa], "submitLittle" ) == 0 )
		{
			RunMode = MODE_EVAL;
		}
		else if ( strcmp (webNames[xa], "submitAgain" ) == 0 )
		{
			RunMode = MODE_AGAIN;
		}

		else if ( strcmp (webNames[xa], "NewGame" ) == 0 )
		{
			if ( webValues[xa][0] == 'Y' )
			{
				RunMode = MODE_AGAIN;
			}
		}

		else if ( strcmp (webNames[xa], "GameStage" ) == 0 )
		{
			Game.Stage = atoi ( webValues[xa] );
		}
		else if ( strcmp (webNames[xa], "ButtonName" ) == 0 )
		{
			if ( strcmp (webValues[xa], "submitBig" ) == 0 )
			{
				RunMode = MODE_DISTRACT;;
			}
			else if ( strncmp (webValues[xa], "submitLittle_", 13 ) == 0 )
			{
				/*----------------------------------------------------------
					-123456789-123456789-123456789
					submitLittle_rp_##
				----------------------------------------------------------*/
				RadioPick = atoi ( &webValues[xa][16] );
				RunMode = MODE_EVAL;
			}
			else if ( strcmp (webValues[xa], "submitNoTest" ) == 0 )
			{
				TestValue = UserValue = 123;
				RunMode = MODE_LITTLE;
			}
			// else
			// {
			// 	printf ( "Unknown value for ButtonName = %s<br>\n", webValues[xa] );
			// }
		}

		else if ( strcmp (webNames[xa], "ShuffleArray" ) == 0 )
		{
			char	*tokens[SHUFFLESIZE];
			int		tokcnt, xt;

			tokcnt = GetTokensD ( webValues[xa], ",", tokens, SHUFFLESIZE );
			for ( xt = 0; xt < tokcnt; xt++ )
			{
				ShuffleArray[xt] = nsAtoi ( tokens[xt] );
			}
		}
		else if ( strcmp (webNames[xa], "ShuffleIndex" ) == 0 )
		{
			ShuffleIndex = nsAtoi (  webValues[xa] );
		}

		else
		{
			printf ( "Unknown name value pair %s = %s<br>\n", webNames[xa], webValues[xa] );
		}
	}

	if ( Width == 0 )
	{
		Width = 1000;
	}
	if ( Height == 0 )
	{
		Height = 1000;
	}

	return ( rv );
}
