/*----------------------------------------------------------------------------
	Program : GeneratePicks.c
	Author  : Tom Stevelt
	Date    : 2022
	Synopsis: progname
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

void GeneratePicks ()
{
	int		ndx;
	int		LastBig, Pick, IsDupePick;

	if ( ImageCount < 3 )
	{
		printf ( "Not enough images loaded, ImageCount = %d<br>\n", ImageCount );
		exit ( 0 );
	}

	/*----------------------------------------------------------
		three random picks
	----------------------------------------------------------*/
	LastBig = Game.Picks[0];
	memset ( Game.Picks, '\0', sizeof(Game.Picks) );
	for  ( Game.PickCount = 0; Game.PickCount < 3; )
	{
		Pick = random_range ( 1, ImageCount );
		IsDupePick = 0;
		for ( ndx = 0; ndx < Game.PickCount; ndx++ )
		{
			/*----------------------------------------------------------
				don't use the same BIG image twice in a row
			----------------------------------------------------------*/
			if ( LastBig == Pick && ndx == 0 )
			{
				IsDupePick = 1;
				break;
			}

			/*----------------------------------------------------------
				already picked this one in this group
			----------------------------------------------------------*/
			if ( Game.Picks[ndx] == Pick )
			{
				IsDupePick = 1;
				break;
			}
		}
		if ( IsDupePick )
		{
			continue;
		}
		Game.Picks[Game.PickCount] = Pick;
		Game.PickCount++;
	}


	/*----------------------------------------------------------
		pick one at random
		show on top bigger
	----------------------------------------------------------*/
	Game.BigImage = Game.Picks[0];

	/*----------------------------------------------------------
		pick two more at random
		show three across and smaller
	----------------------------------------------------------*/
	PrintGameRecord ( "GeneratePicks before qsort", &Game );
	qsort ( Game.Picks, Game.PickCount, sizeof(int), (int(*)()) ComparePicks );
	PrintGameRecord ( "GeneratePicks after qsort", &Game );
}
