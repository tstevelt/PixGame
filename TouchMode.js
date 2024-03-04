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

function TouchMode ( Request )
{
	// alert ( Request );

	var b = document.getElementById ( 'ButtonName' );

	if ( Request ==  'big' )
	{
		ButtonName.value = 'submitBig';
		document.PixGame.submit();
	}
	else if ( Request.substring(0,3) ==  'rp_' )
	{
		ButtonName.value = 'submitLittle_' + Request;
		document.PixGame.submit();
	}
	else if ( Request ==  'random' )
	{
		ButtonName.value = 'submitNoTest';
		document.PixGame.submit();
	}
}
