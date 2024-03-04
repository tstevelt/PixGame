/*----------------------------------------------------------------------------
	Program : LogGame.c
	Author  : Tom Stevelt
	Date    : 2022
	Synopsis: Write game results to log file
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

void LogGame ()
{
	FILE		*fp;
	DATETIMEVAL	Now;
	char		*RemoteAddr;

	if ( access ( LOGFILE, (F_OK|R_OK|W_OK) ) != 0 )
	{
		printf ( "%s missing or restricted permissions<br>\n", LOGFILE );
		return;
	}

	if (( fp = fopen ( LOGFILE, "a" )) == NULL )
	{
		printf ( "Could not open %s for append<br>\n", LOGFILE );
		return;
	}

	if (( RemoteAddr = getenv ( "REMOTE_ADDR" )) == NULL )
	{
		RemoteAddr = "TERMINAL";
	}
	fprintf ( fp, "%-15.15s", RemoteAddr );

	CurrentDateTime ( &Now );
	fprintf ( fp, " %4d-%02d-%02d %02d:%02d",
		Now.year4, Now.month, Now.day, Now.hour, Now.minute);

	fprintf ( fp, " %-10.10s", Game.ImageSet );
	fprintf ( fp, " %6d", Game.PlayerID );
	fprintf ( fp, " %3d", Game.Score );
	fprintf ( fp, " %3d", Game.Stage );
	fprintf ( fp, "\n" );

	fclose ( fp );
}
