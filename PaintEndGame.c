/*----------------------------------------------------------------------------
	Program : PaintEndGame.c
	Author  : Tom Stevelt
	Date    : 2022
	Synopsis: End of game, draw the container for the results animation
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

void PaintEndGame ()
{
	printf ( "<input type='hidden' id='Score' value='%d out of %d'>\n", Game.Score, Game.Stage );
	printf ( "<input type='hidden' id='NewGame' name='NewGame' value='N'>\n" );

	printf ( "<style>\n" );
	printf ( "#containerC  { position: relative; }\n" );
	printf ( "</style>\n" );

	printf ( "<div id ='containerC'>\n" );

	printf ( "<canvas id='EndGame'></canvas>\n" );

	printf ( "</div>\n" );

	RunMode = MODE_END;
}
