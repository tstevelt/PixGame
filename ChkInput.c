/*----------------------------------------------------------------------------
	Program : ChkInput.c
	Author  : Tom Stevelt
	Date    : 2022
	Synopsis: Validate user input
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

void ChkInput ()
{
	switch ( RunMode )
	{
		case MODE_EVAL:
			if ( RadioPick == 0 )
			{
				printf ( "<h2>Gotta pick one</h2>\n" );
				RunMode = MODE_LITTLE_REPEAT;
			}
			break;
		case MODE_LITTLE:
			if ( TestValue == -1 && UserValue == -1 )
			{
				if ( strcasecmp ( TestWord, UserWord ) != 0 )
				{
					RunMode = MODE_DISTRACT;;
				}
			}
			else if ( TestValue != UserValue )
			{
				RunMode = MODE_DISTRACT;;
			}
			break;
		default:
			break;
	}
}
