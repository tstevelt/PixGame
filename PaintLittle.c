/*----------------------------------------------------------------------------
	Program : PaintLittle.c
	Author  : Tom Stevelt
	Date    : 2022
	Synopsis: Paint the three little images, one of which matched the 
				big image shown before the distraction.
	Bug     : Drawing in a different size does not prevent flashing of 
				big images, since there is only one file for each image.
				This can be solved by having two files for each image.
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

void PaintLittle ()
{
	int		ndx;
	int		ImageIndex;
	char	Request[24];
	int		ImageSize = Width / 3.5;

	printf ( "<table align='center'>\n" );
	printf ( "<tr>\n" );
	for ( ndx = 0; ndx < Game.PickCount; ndx++ )
	{
		sprintf ( Request, "rp_%d", Game.Picks[ndx] );
		printf ( "<td onClick='javascript:TouchMode(\"%s\");'>\n", Request );

		ImageIndex = Game.Picks[ndx]-1;
		if ( ImageIndex < 0 || ImageIndex >= ImageCount )
		{
			printf ( "Bad index %d\n", ImageIndex );
		}
		else
		{
			printf ( "<img src='PixGame/%s/%s' alt='%s' width='%d'><br>\n", 
				Game.ImageSet,
				ImageArray[Game.Picks[ndx]-1].ImageFileName, 
				ImageArray[Game.Picks[ndx]-1].ImageFileName,
				ImageSize );
		}
		printf ( "</td>\n" );
	}
	printf ( "</tr>\n" );

#ifdef BEFORE_TOUCH_MODE
	/*----------------------------------------------------------
		radio 'buttons' in a row, centered under three pix
	----------------------------------------------------------*/
	printf ( "<tr>\n" );
	for ( ndx = 0; ndx < Game.PickCount; ndx++ )
	{
		printf ( "<td align='center'>\n" );
		printf ( "<input type='radio' name='radio_pick' value='rp_%d' autofocus>\n", Game.Picks[ndx] );
		printf ( "</td>\n" );
	}
	printf ( "</tr>\n" );

	/*----------------------------------------------------------
		submit centered in two column cell, to avoid being
		too close to a radio 
	----------------------------------------------------------*/
	printf ( "<tr>\n" );
	printf ( "<td colspan='2' align='center'>\n" );
	printf ( "<input type='submit' name='submitLittle' value='Next'>\n" );
	printf ( "</td>\n" );
	printf ( "<td>&nbsp;</td>\n" );
	printf ( "</tr>\n" );
	printf ( "</table>\n" );
#endif
}
