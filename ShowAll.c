/*----------------------------------------------------------------------------
	Program : ShowAll.c
	Author  : Tom Stevelt
	Date    : 2022
	Synopsis: Show all images in the image set
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

void ShowAll ( char *ImageSet )
{
	int		ndx;

	LoadImageArray ( ImageSet );

	for ( ndx = 0; ndx < ImageCount; ndx++ )
	{
		printf ( "%s", ImageArray[ndx].ImageFileName );
		printf ( "<img src='PixGame/%s/%s' alt='%s' style='width:%dpx;'><br>\n", 
				ImageSet,
				ImageArray[ndx].ImageFileName, 
				ImageArray[ndx].ImageFileName, 
				SMALL );
	}
}
