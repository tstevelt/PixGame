/*----------------------------------------------------------------------------
	Program : ShufflePicks.c
	Author  : Tom Stevelt
	Date    : 2022
	Synopsis: Loaded 30 plus images in the array, game uses 30 images.  
				Shuffle the entire array randomly to 30 random ones first.
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

typedef struct
{
	double	num;
	int		ndx;
} RECORD;

static	RECORD	Array[SHUFFLESIZE];

static int cmprec ( RECORD *a, RECORD *b )
{
	if ( a->num < b->num )
	{
		return ( -1 );
	}
	if ( a->num > b->num )
	{
		return ( 1 );
	}
	return ( 0 );
}

void ShufflePicks ( int FirstPass )
{
	int		ndx;

	if ( FirstPass )
	{
		for ( ndx = 0; ndx < ImageCount; ndx++ )
		{
			Array[ndx].ndx = ndx;
			Array[ndx].num = d_random ();
		}

		qsort ( Array, ImageCount, sizeof(RECORD), (int(*)()) cmprec );

		for ( ndx = 0; ndx < SHUFFLESIZE; ndx++ )
		{
			ShuffleArray[ndx] = Array[ndx].ndx+1;
		}

		ShuffleIndex = 0;
	}
#ifdef DEBUG
	for ( ndx = 0; ndx < SHUFFLESIZE; ndx++ )
	{
		printf ( " %d", ShuffleArray[ndx] );
	}
	printf ( " Index %d Image %d<br>\n", ShuffleIndex, ShuffleArray[ShuffleIndex] );
#endif	

	/*----------------------------------------------------------
		put next three in Game record
	----------------------------------------------------------*/
	Game.Picks[0] = ShuffleArray[ShuffleIndex];
	Game.Picks[1] = ShuffleArray[ShuffleIndex+1];
	Game.Picks[2] = ShuffleArray[ShuffleIndex+2];
	Game.BigImage = Game.Picks[0];
	Game.PickCount = 3;
	qsort ( &Game.Picks, Game.PickCount, sizeof(int), (int(*)()) ComparePicks );

}


