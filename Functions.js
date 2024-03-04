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


function sleep(ms) 
{
	return new Promise(resolve => setTimeout(resolve, ms));
}

function flip ()
{
	var x = Math.random();

	if ( x < 0.5 )
	{
		return ( 0 );
	}
	return ( 1 );
}

function randomDbl(min, max)
{
	var range = max - min;
	if ( range < 0.0 )
	{
		range = 0.0 - range;
	}
	return Math.random() * ( range ) + min;
}

function randomInt(min, max) 
{
	return Math.floor(Math.random() * (max - min + 1)) + min;
}

function CalcSine ( zz, offset, frequency, amplitude )
{
	var y = amplitude * Math.sin((zz-offset*3)*frequency/2500);
	return y;
}

function CalcLine ( x, m, b )
{
	var y = m * x + b;
	return y;
}

function CalcEndPoint ( Circle, Angle, centerX, centerY, Width, Height )
{
	if ( Angle > 89 && Angle < 91 )
	{
		xEnd = centerX;
		yEnd = Height;
	}
	else if ( Angle > 269 && Angle < 271 )
	{
		xEnd = centerX;
		yEnd = 0;
	}
	else
	{
		Tangent = Math.tan(Angle*Math.PI/180);
		if ( Angle < 90 || Angle > 270 )
		{
			xEnd = Width;
			yEnd = centerY + centerX * Tangent;
		}
		else
		{
			xEnd = 0;
			yEnd = centerY - centerX * Tangent;
		}
	}

	// console.log ( 'circle ' + Circle + ' angle ' + Angle + ' X ' + xEnd + ' Y ' + yEnd )

	return [ xEnd, yEnd ];
}

function GenerateSentences ( WordArray, PerLine, Lines )
{
	// console.log ( WordArray );
	// console.log ( PerLine );
	// console.log ( Lines );

	var sentence = new String('');
	for ( let xl = 0; xl < Lines; xl++ )
	{
		if ( xl > 0 )
		{
			sentence = sentence + ',';
		}
		for ( let xw = 0; xw < PerLine; xw++ )
		{
			Word = WordArray[randomInt(0,WordArray.length-1)];
			// console.log ( 'line ' + xl + ' word ' + xw + ' ' + Word );
			sentence = sentence + ' ' + Word;
		}
	}

	// console.log ( sentence );

	return sentence;
}


function CalcFontSize ( ctx, Sentence, Width )
{
	var minS = 6;
	var maxS = 50;
	var minL = 0;
	var maxL = 0;
	var midL = 0;

	while ( minS < maxS )
	{
		ctx.font = minS + 'px Verdana';
		minL = ctx.measureText(Sentence).width;
		// console.log ( ctx.font + ' ' + minL );

		ctx.font = maxS + 'px Verdana';
		maxL = ctx.measureText(Sentence).width;
		// console.log ( ctx.font + ' ' + maxL );

		midL = (minL + maxL) / 2;
		midS = (minS + maxS) / 2;

		if ( midL > Width )
		{
			maxS = midS - 0.5;
			// console.log ( 'setting max to ' + maxS );
		}
		else
		{
			minS = midS + 0.5;
			// console.log ( 'setting min to ' + minS );
		}

		// console.log ( ' width ' + Width + ' min ' + minL + ' mid ' + minL + ' max ' + maxL );
	}

	return midS;
}
