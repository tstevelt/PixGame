/*----------------------------------------------------------------------------
	Program : PaintTop.c
	Author  : Tom Stevelt
	Date    : 2022
	Synopsis: Start HTML output
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

void PaintTop ( int Stage )
{
	WEBPARMS	*ptrWebParms = webInitParms();
	char		*ScriptFilename = getenv ( "SCRIPT_FILENAME" );
	char		*Basename = basename ( ScriptFilename );

	if ( Stage == 1 )
	{
		webContentHtml ();

		ptrWebParms->WP_Title = "PixGame";
		webStartHead ( ptrWebParms );

		printf ( "<meta name='viewport' content='width=device-width, initial-scale=1.0'>\n" );

		printf ( "<meta http-equiv='Cache-Control' content='no-cache, no-store, must-revalidate'>\n" );
		printf ( "<meta http-equiv='Pragma' content='no-cache'>\n" );
		printf ( "<meta http-equiv='Expires' content='0'>\n" );
	}
	else if ( Stage == 2 )
	{
		printf ( "<script src='TouchMode.js'></script>\n" );
		if ( RunMode == MODE_DISTRACT &&  DistractionType == DISTRACT_RANDOM_IMAGE )
		{
			printf ( "<script src='Functions.js'></script>\n" );
			printf ( "<script src='Distract.js'></script>\n" );
		}
		else if ( Game.Stage == 9 && RunMode == MODE_EVAL )
		{
			printf ( "<script src='Functions.js'></script>\n" );
			printf ( "<script src='EndGame.js'></script>\n" );
		}

		printf ( "</head>\n" );

		if ( RunMode == MODE_DISTRACT &&  DistractionType == DISTRACT_RANDOM_IMAGE )
		{
			printf ( "<body onLoad='javascript:DrawDistraction();'>\n" );
		}
		else if ( Game.Stage == 9 && RunMode == MODE_EVAL )
		{
			printf ( "<body onLoad='javascript:Eval();'>\n" );
		}
		else
		{
			printf ( "<body>\n" );
		}

		ptrWebParms->WP_FormName   = "PixGame";
		ptrWebParms->WP_FormAction = Basename;
		ptrWebParms->WP_FormMethod = "POST";
		ptrWebParms->WP_FormOther  = (char *)0;
		webStartForm ( ptrWebParms );

		webFreeParms ( ptrWebParms );

		printf ( "<input type='hidden' id='GameStage' value='%d'>\n", Game.Stage );
		switch ( DistractionType )
		{
			case DISTRACT_GET_NUMBER:
				printf ( "<input type='hidden' name='mode' value='N'>\n" );
				break;
			case DISTRACT_RANDOM_IMAGE:
				printf ( "<input type='hidden' name='mode' value='R'>\n" );
				break;
			case DISTRACT_ARITHMETIC:
				printf ( "<input type='hidden' name='mode' value='A'>\n" );
				break;
			case DISTRACT_WORD:
				printf ( "<input type='hidden' name='mode' value='W'>\n" );
				break;
		}
		printf ( "<input type='hidden' id='nodelay' name='nodelay' value='%d'>\n", NoDelay );
		printf ( "<input type='hidden' id='Width' name='Width' value='%d'>\n", Width );
		printf ( "<input type='hidden' id='Height' name='Height' value='%d'>\n", Height );
		printf ( "<input type='hidden' id='ButtonName' name='ButtonName' value='xxx'>\n" );
	}
}
