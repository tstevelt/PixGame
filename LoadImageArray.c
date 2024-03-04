/*----------------------------------------------------------------------------
	Program : LoadImageArray.c
	Author  : Tom Stevelt
	Date    : 2022
	Synopsis: Load selected image set into image array.  Image sets are 
				kept in individual directories.
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

/*----------------------------------------------------------
	ls -l | sort -n -k5,5 | 
----------------------------------------------------------*/
static int cmpfilesize ( IMAGE_RECORD *a, IMAGE_RECORD *b )
{
	return ( a->FileSize - b->FileSize );
}

void LoadImageArray ( char *ImageSet )
{
	DIR		*ptrDIR;
	struct dirent	*de;
	struct stat 	statbuf;
	char	Directory[128];
	char	FullName[128];

	sprintf ( Directory, "PixGame/%s", ImageSet );

	if (( ptrDIR = opendir ( Directory )) == NULL )
	{
		printf ( "Cannot open %s<br>\n", Directory );
	}
	else
	{
		ImageCount = 0;
		while (( de = readdir ( ptrDIR )) != NULL )
		{
			if ( de->d_type != DT_REG )
			{
				continue;
			}

			if ( ImageCount >= MAXIMAGES )
			{
				if ( Debug )
				{
					printf ( "No more room in ImageArray<br>\n" );
				}
				break;
			}
			if ( strlen ( de->d_name ) >= MAXNAMELEN )
			{
				if ( Debug )
				{
					printf ( "File name too long: %s<br>\n",  de->d_name );
				}
				continue;
			}

			sprintf ( ImageArray[ImageCount].ImageFileName, "%s", de->d_name );
			snprintf ( FullName, sizeof(FullName), "%s/%s", Directory, de->d_name );
			if (stat( FullName, &statbuf) == -1)
			{
				printf ( "%s, errno %d: %s<br>\n", FullName, errno, strerror(errno) );
				ImageArray[ImageCount].FileSize = 123;
			}
			else
			{
				ImageArray[ImageCount].FileSize = (intmax_t)statbuf.st_size;
			}
			ImageCount++;
		}

		if ( ImageCount == 0 )
		{
			printf ( "Did not load any images!<br>\n" );
		}
		else if ( ImageCount > 1 )
		{
			qsort ( ImageArray, ImageCount, sizeof(IMAGE_RECORD), (int(*)()) cmpfilesize );
		}
	}
}

