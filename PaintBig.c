/*----------------------------------------------------------------------------
	Program : PaintBig.c
	Author  : Tom Stevelt
	Date    : 2022
	Synopsis: Draw the big image
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

void PaintBig()
{
	int		ndx;
	int		ImageSize = Width / 3.5;

	printf ( "<table align='center'>\n" );
	printf ( "<tr>\n" );
	for ( ndx = 0; ndx < Game.PickCount; ndx++ )
	{
		if ( ndx == 0 || ndx + 1 == Game.PickCount )
		{
			printf ( "<td align='center' width='33%%'>\n" );
		}
		else
		{
			printf ( "<td align='center' width='33%%' onClick='javascript:TouchMode(\"big\");'>\n" );
			// printf ( "<img src='PixGame/%s/%s' alt='%s' style='width:100%%; max-width:600px; max-height:600px;'><br>\n", 
			printf ( "<img src='PixGame/%s/%s' alt='%s' width='%d'><br>\n", 
					Game.ImageSet,
					ImageArray[Game.BigImage-1].ImageFileName, 
					ImageArray[Game.BigImage-1].ImageFileName,
					ImageSize );
		}
		printf ( "</td>\n" );
	}
	printf ( "</tr>\n" );
#ifdef BEFORE_TOUCH_MODE
	printf ( "<tr>\n" );
	printf ( "<td align='center'>\n" );
	printf ( "<input type='submit' name='submitBig' value='Next' autofocus>\n" );
	printf ( "</td>\n" );
	printf ( "</tr>\n" );
#endif
	printf ( "</table>\n" );
}
