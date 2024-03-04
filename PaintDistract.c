/*----------------------------------------------------------------------------
	Program : PaintDistract.c
	Author  : Tom Stevelt
	Date    : 2022
	Synopsis: Paint Distraction.
				* Prompt for random number
				Other options could include:
				* Prompt for longer string of letters / words.
				* Display timed moving image (no submit needed)
				Prompts could be tested by javascript instead of submit 
---------------------------------------------------------------------------*/
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

void PaintDistract ( int DistractionType )
{
	int		Number, Number1, Number2, Operator;
	char	Equation[20];
	char	*Word;
	FILE	*fp;
	char	xbuffer[10];

	switch ( DistractionType )
	{
		case DISTRACT_GET_NUMBER:
			Number = random_range ( 101, 999 );
			printf ( "<p>\n" );
			printf ( "<table align='center' cellspacing='15px'>\n" );
			printf ( "<tr>\n" );
			printf ( "<th>\n" );
			printf ( "%d", Number );
			printf ( "</th>\n" );
			printf ( "</tr>\n" );
			printf ( "<tr>\n" );
			printf ( "<th>\n" );
			printf ( "<input name='Test_%d' size='10' autofocus>", Number );
			printf ( "</th>\n" );
			printf ( "</tr>\n" );
			printf ( "<tr>\n" );
			printf ( "<th>\n" );
			printf ( "<input type='submit' name='submitTest' value='Next'>\n" );
			printf ( "</th>\n" );
			printf ( "</tr>\n" );
			printf ( "</table>\n" );
			break;

		case DISTRACT_ARITHMETIC:
			Operator = random_range ( 1, 4 );
			switch ( Operator )
			{
				case 1:
					Number1 = random_range ( 1, 20 );
					Number2 = random_range ( 1, 20 );
					sprintf ( Equation, "%d + %d =", Number1, Number2 );
					Number = Number1 + Number2;
					break;
				case 2:
					do
					{
						Number1 = random_range ( 2, 20 );
						Number2 = random_range ( 1, 19 );
					} while ( Number1 < Number2 );
					sprintf ( Equation, "%d - %d =", Number1, Number2 );
					Number = Number1 - Number2;
					break;
				case 3:
					Number1 = random_range ( 2, 9 );
					Number2 = random_range ( 2, 9 );
					sprintf ( Equation, "%d * %d =", Number1, Number2 );
					Number = Number1 * Number2;
					break;
				case 4:
					Number1 = random_range ( 2, 9 );
					Number2 = random_range ( 2, 9 );
					sprintf ( Equation, "%d / %d =", Number1 * Number2, Number2 );
					Number = Number1;
					break;

			}

			printf ( "<p>\n" );
			printf ( "<table align='center' cellspacing='15px'>\n" );
			printf ( "<tr>\n" );
			printf ( "<th>\n" );
			printf ( "<h2>%s</h2>", Equation );
			printf ( "</th>\n" );
			printf ( "</tr>\n" );
			printf ( "<tr>\n" );
			printf ( "<th>\n" );
			printf ( "<input name='Test_%d' size='10' autofocus>", Number );
			printf ( "</th>\n" );
			printf ( "</tr>\n" );
			printf ( "<tr>\n" );
			printf ( "<th>\n" );
			printf ( "<input type='submit' name='submitTest' value='Next'>\n" );
			printf ( "</th>\n" );
			printf ( "</tr>\n" );
			printf ( "</table>\n" );
			break;

		case DISTRACT_RANDOM_IMAGE:
			printf ( "<style>\n" );
			printf ( "#container  { position: relative; }\n" );
			printf ( "#containerA { position: relative; height: 85%%; }\n" );
			printf ( "#containerB { position: relative; height: 15%%; padding: 15px; text-align:center; }\n" );
			printf ( "</style>\n" );
			printf ( "<div id ='container'>\n" );

			printf ( "<div id ='containerA'>\n" );
			if ( NoDelay == 0 )
			{
				printf ( "<canvas id='Distract'></canvas>\n" );
			}
			else
			{
				printf ( "<canvas id='Distract' onClick='javascript:TouchMode(\"random\");'></canvas>\n" );
			}
			printf ( "</div>\n" );

			printf ( "<div id ='containerB'>\n" );
#ifdef BEFORE_TOUCH_MODE
			printf ( "<input type='submit' id='submitNoTest' name='submitNoTest' value='Next' autofocus%s>\n",
							NoDelay == 1 ? "" : " disabled" );
#else
			if ( NoDelay == 0 )
			{
				printf ( "<input type='submit' id='submitNoTest' name='submitNoTest' value='Next' autofocus disabled>\n" );
			}
#endif
			printf ( "</div>\n" );

			printf ( "</div>\n" );
			break;

		case DISTRACT_WORD:
			Word = "ABCDE";
			if (( fp = fopen ( "100_5_letter.txt", "r" )) != NULL )
			{
				Number = random_range ( 1, 100 );
				Number1 = 0;
				while ( fgets ( xbuffer, sizeof(xbuffer), fp ) != NULL )
				{
					Number1++;
					if ( Number1 == Number )
					{
						TrimRightAndLeft(xbuffer);
						Word = xbuffer;
						break;
					}
				}
				fclose ( fp );
			}
			printf ( "<p>\n" );
			printf ( "<table align='center' cellspacing='15px'>\n" );
			printf ( "<tr>\n" );
			printf ( "<th>\n" );
			printf ( "<h2>%s</h2>", Word );
			printf ( "</th>\n" );
			printf ( "</tr>\n" );
			printf ( "<tr>\n" );
			printf ( "<th>\n" );
			printf ( "<input name='Word_%s' size='10' autofocus>", Word );
			printf ( "</th>\n" );
			printf ( "</tr>\n" );
			printf ( "<tr>\n" );
			printf ( "<th>\n" );
			printf ( "<input type='submit' name='submitTest' value='Next'>\n" );
			printf ( "</th>\n" );
			printf ( "</tr>\n" );
			printf ( "</table>\n" );
			break;

	}
}
