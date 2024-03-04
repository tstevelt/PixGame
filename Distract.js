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

var Colors  = [ 'red', 'blue', 'green', 'yellow', 'white' ];
var moveX   = [ 1,  1, 0, -1, -1 ];
var moveY   = [ 1, -1, 0,  1, -1 ];
var startmoveX   = [ 0, 0, 0, 0, 0 ];
var startmoveY   = [ 0, 0, 0, 0, 0 ];
var centermoveX   = [ 0, 0, 0, 0, 0 ];
var centermoveY   = [ 0, 0, 0, 0, 0 ];
var endmoveX   = [ 0, 0, 0, 0, 0 ];
var endmoveY   = [ 0, 0, 0, 0, 0 ];
var startX = [ 0, 0, 0, 0, 0 ];
var startY = [ 0, 0, 0, 0, 0 ];
var endX = [ 0, 0, 0, 0, 0 ];
var endY = [ 0, 0, 0, 0, 0 ];
var centerX = [ 0, 0, 0, 0, 0 ];
var centerY = [ 0, 0, 0, 0, 0 ];
var radius  = [ 0, 0, 0, 0, 0 ];
var Angle  = [ 0, 0, 0, 0, 0 ];
var Length  = [ 0, 0, 0, 0, 0 ];

var ScreenWidth  = window.innerWidth;
var ScreenHeight = window.innerHeight;

async function RandomNumberSpinner ( ctx, Width, Height )
{
	var ClearOrRandom = 'C';
	let t0= performance.now();
	var Numbers = [ 0, 0, 0, 0, 0 ];
	var centerX = [ 0, 0, 0, 0, 0 ];
	var centerY = [ 0, 0, 0, 0, 0 ];
	var Degrees = [ 0.5, -0.6, -0.7, 0.7, -0.8 ];
	var n = 0;
	let Colors = [ 'red', 'blue', 'green', 'black', 'purple' ];

	if ( ClearOrRandom == 'R' )
	{
		for (var i = 0; i < imgData.data.length; i += 4) {
		  imgData.data[i] = randomInt(0, 255); // red
		  imgData.data[i+1] = randomInt(0, 255); // green
		  imgData.data[i+2] = randomInt(0, 255); // blue
		  imgData.data[i+3] = 255; // alpha
		}
	}

	var NumberCount = 5;
	// console.log ( 'dimensions ' + Width + 'x' + Height );
	for ( n = 0; n < NumberCount; n++ )
	{
		Numbers[n] = randomInt ( 10001, 99999 );
		centerX[n] = randomInt ( Width  * 0.45, Width  * 0.55 );
		centerY[n] = randomInt ( Height * 0.45, Height * 0.55 );
		// console.log ( n + ' center ' + centerX[n] + 'x' + centerY[n] );
	}

	var MaxLines = 800;
	var SleepTime = 5;
	ctx.font = '30px Georgia';

	n = -1;
	for ( var k = 0; k < MaxLines; k++ )
	{
		if ( ClearOrRandom == 'R' )
		{
			ctx.putImageData(imgData, 0, 0);
		}
		else if ( ClearOrRandom == 'C' )
		{
			ctx.clearRect ( 0, 0, Width, Height );
		}
		else if ( ClearOrRandom == 'F' )
		{
			ctx.fillStyle = "#cccccc";
			ctx.fillRect ( 0, 0, Width, Height );
		}
		
		if ( k < MaxLines * 0.2 )
		{
			if ( n == -1 ) { console.log ( 'first number ' + Colors[0] ); }
			n = 0;
		}	
		else if ( k >= MaxLines * 0.2 && k < MaxLines * 0.4 )
		{
			if ( n == 0 ) { console.log ( 'second number ' + Colors[1] ); }
			n = 1;
		}
		else if ( k >= MaxLines * 0.4 && k < MaxLines * 0.6 )
		{
			if ( n == 1 ) { console.log ( 'third number ' + Colors[2] ); }
			n = 2;
		}
		else if ( k >= MaxLines * 0.6 && k < MaxLines * 0.8 )
		{
			if ( n == 2 ) { console.log ( 'fourth number ' + Colors[3] ); }
			n = 3;
		}
		else if ( k >= MaxLines * 0.8 )
		{
			if ( n == 3 ) { console.log ( 'fifth number ' + Colors[4] ); }
			n = 4;
		}

		ctx.translate ( centerX[n], centerY[n] );
		ctx.rotate ( Degrees[n] * Math.PI / 180 );
		ctx.translate ( 0 - centerX[n], 0 - centerY[n] );

		WK = ctx.measureText(Numbers[n]).width;
		X = centerX[n] - WK/2;
		Y = centerY[n] - 4;
		ctx.fillStyle = Colors[n];
		ctx.fillText ( Numbers[n], X, Y );

		await sleep ( SleepTime );
	}

	let t1= performance.now();
	console.log('Total time '+ (t1-t0) +' milliseconds');

	var Button = document.getElementById ( 'submitNoTest' ).disabled = false;
}

async function RandomStarWars ( ctx, Width, Height )
{
	let myPromise = new Promise(function(myResolve, myReject) 
	{
		let req = new XMLHttpRequest();
		req.open('GET', '500_3plus.txt');
		req.onload = function() 
		{
			if (req.status == 200) 
			{
				myResolve(req.response);
			}
			else 
			{
				myReject('File not Found');
			}
		};
		req.send();
	});

	myPromise.then
	(
		function(value) 
		{
			myDisplayer(value);
		},
		function(error) 
		{
			myError(error);
		}
	);

	function myError ( Error )
	{
		console.log ( 'error ', Error );
	}

	var ClearOrRandom = 'C';
	// var Horizon = [ 0.3, 0.4, 0.7 ]
	var Horizon = [ 0.35, 0.3, 0.65 ]

	function DrawBackground ( ctx )
	{
		if ( ClearOrRandom == 'R' )
		{
			ctx.putImageData(imgData, 0, 0);
		}
		else
		{
			var grd = ctx.createLinearGradient(Width*0.5,0,Width*0.5,Height*0.2);
			grd.addColorStop(0,"steelblue");
			grd.addColorStop(1,"azure");
			// Fill with gradient
			ctx.fillStyle = grd;
			ctx.fillRect ( 0, 0, Width, Height * 0.2 );

			var grd = ctx.createLinearGradient(Width*0.5,Height,Width*0.5,Height*0.2);
			grd.addColorStop(0,"#000000");
			grd.addColorStop(1,"Indigo");
			// Fill with gradient
			ctx.fillStyle = grd;
			ctx.fillRect ( 0, Height * 0.2, Width, Height );
		}

		ctx.beginPath();
		ctx.strokeStyle = '#bbbbbb';
		ctx.lineWidth = 3;
		ctx.moveTo(0,Height);
		ctx.lineTo(Width*Horizon[0],Height*0.2);
		ctx.stroke();

		ctx.beginPath();
		ctx.strokeStyle = '#bbbbbb';
		ctx.lineWidth = 3;
		ctx.moveTo(Width,Height);
		ctx.lineTo(Width*Horizon[2],Height*0.2);
		ctx.stroke();
	}

	function CalcAlpha ( yy, Height )
	{
		var a = (Height - yy) / Height * 0.8;
		a = 1.0 - a;
		return a;
	}

	async function myDisplayer ( some )
	{
		var MaxLines = 20;
		var KeepGoing = 0;

		let t0= performance.now(); //start time

		try
		{
			var textArray = some.split('\n');
			// console.log ( textArray );
			// console.log ( 'length ' + textArray.length );
		}
		catch // ( Exception e )
		{
			return;
		}
		let t1= performance.now(); //end time
		// console.log('Time taken to load shit '+ (t1-t0) +' milliseconds');

		var LongSentence = GenerateSentences ( textArray, 6, MaxLines );
		// console.log ( LongSentence );

		var Sentences = LongSentence.split(',');
		var Positions = Array(MaxLines).fill(0);
		// console.log ( Sentences );

		if ( ClearOrRandom == 'R' )
		{
			for (var i = 0; i < imgData.data.length; i += 4) {
			  imgData.data[i] = randomInt(0, 255); // red
			  imgData.data[i+1] = randomInt(0, 255); // green
			  imgData.data[i+2] = randomInt(0, 255); // blue
			  imgData.data[i+3] = 255; // alpha
			}
		}

		// find longest sentence
		ctx.font = '30px Verdana';
		var MaxLength = 0;
		var MaxIndex = 0;
		for ( var k = 0; k < MaxLines; k++  )
		{
			xx = ctx.measureText(Sentences[k]).width;	
			if ( MaxLength < xx )
			{
				MaxLength = xx;
				MaxIndex = k;
			}
		}
		// console.log ( 'max length ' + MaxLength + ' at ' + MaxIndex );


		// find largest font that fits bottom of screen
		MaxFontSize = CalcFontSize ( ctx, Sentences[MaxIndex], Width );
		// console.log ( 'best fit max ' + ctx.font );
		MinFontSize = CalcFontSize ( ctx, Sentences[MaxIndex], Width * Horizon[1] );
		// console.log ( 'best fit min ' + ctx.font );

		// ml = (Height*0.8) / (Width*0.3);
		// mr = (0-Height*0.8) / (Width*0.3);

		var LineSpace = Height*0.8 / MaxLines;

		// calculate initial positions
		// first sentence will be at bottom of screen
		// remainder will be spaced correctly, but below bottom
		// display routine will not write sentence if below bottom or above horizon
		for ( var k = 0; k < MaxLines * 2; k++ )
		{
			Positions[k] = Height - LineSpace + k * LineSpace;
		}

		var SleepTime = 20;
		var PositionIncrement = 2.0 * (Height * 0.8) / (5000/SleepTime);
		
		while ( Positions[MaxLines-1] > Height * 0.1 )
		{
			// draw background
			DrawBackground ( ctx );

			// paint visible sentence
			for ( var p = 0; p < MaxLines; p++ )
			{
				yy = Positions[p];

				if ( yy > Height || yy < Height * 0.2 )
				{
					continue;
				}

				// where is this line located between Height and Height * 0.2?
				var Dist = (Height - yy) / (Height * 0.8);
				var FontSize = MaxFontSize - Dist * (MaxFontSize - MinFontSize);
				ctx.font = FontSize + 'px Verdana';

				xx = ctx.measureText(Sentences[p]).width;	
				xx = (Width-xx) / 2;

				ctx.globalAlpha = CalcAlpha ( yy, Height );
				ctx.fillStyle = '#ffff33'
				ctx.fillText ( Sentences[p], xx, yy );
			}

			// update position array
			for ( var p = 0; p < MaxLines; p++ )
			{
				Positions[p] = Positions[p] - PositionIncrement;
			}

			// sleep
			await sleep ( SleepTime );
		}

		let t2= performance.now(); //end time
		console.log('Time taken to drawshit '+ (t2-t1) +' milliseconds');
		console.log('Total time '+ (t2-t0) +' milliseconds');

		try
		{
			var Button = document.getElementById ( 'submitNoTest' ).disabled = false;
		}
		catch
		{
			// nothing to do
		}
	}
}

async function RandomWordCloud ( ctx, Width, Height )
{
	let Colors  = [ 'red', 'blue', 'green', 'black', 'cyan' ];
	let myPromise = new Promise(function(myResolve, myReject) 
	{
		let req = new XMLHttpRequest();
		req.open('GET', '500_3plus.txt');
		req.onload = function() 
		{
			if (req.status == 200) 
			{
				myResolve(req.response);
			}
			else 
			{
				myReject('File not Found');
			}
		};
		req.send();
	});

	myPromise.then
	(
		function(value) 
		{
			myDisplayer(value);
		},
		function(error) 
		{
			myError(error);
		}
	);

	function myError ( Error )
	{
		console.log ( 'error ', Error );
	}

	async function myDisplayer ( some )
	{
		var ClearOrRandom = 'C';
		var W = [ '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '' ];
		var X = [ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ];
		var Y = [ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ];
		var C = [ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ];
		var MaxWords = W.length;
		var WordCount = 0;

		let t0= performance.now(); //start time

		try
		{
			var textArray = some.split('\n');
			// console.log ( textArray );
			// console.log ( 'length ' + textArray.length );
		}
		catch // ( Exception e )
		{
			return;
		}

		ctx.font = '30px Georgia';

		for ( var k = 0; k < MaxWords;  )
		{
			var isDupe = 0; 
			do
			{
				isDupe = 0; 
				W[k] = textArray [ randomInt(0,textArray.length-1) ];
				for ( var m = 0; m < k && isDupe == 0; m++ )
				{
					if ( W[k] == W[m] )
					{
						isDupe = 1;
					}
				}
			} while ( isDupe == 1  );
			
			WK = ctx.measureText(W[k]).width;
			if ( 1 == 2 )
			{
				X[k] = randomInt(2,Width - WK );
				Y[k] = randomInt(20,Height-20);
			}
			else
			{
				var tooClose = 0; 
				do
				{
					tooClose = 0; 
					X[k] = randomInt(2,Width - WK );
					Y[k] = randomInt(20,Height-20);
					for ( var m = 0; m < k && tooClose == 0; m++ )
					{
						WM = ctx.measureText(W[m]).width;
						if ( Math.abs(Y[k]-Y[m]) < 20 && Math.abs(X[k]-X[m]) < Math.max(WK,WM) )
						{
							tooClose = 1;
							// console.log ( 'too close: WK ' + WK + ' X ' + X[k] + ' ' + X[m] + ' Y ' + Y[k] + ' ' + Y[m]  )
						}
					}
				} while ( tooClose == 1 );
			}

			C[k] = Colors[k%5];
			k++;
		}
		WordCount = 1;

		var SleepTime = 5000 / MaxWords;

		for ( var k = 0; k < MaxWords; k++ )
		{
			if ( ClearOrRandom == 'R' )
			{
				ctx.putImageData(imgData, 0, 0);
			}
			else
			{
				// ctx.clearRect(0, 0, Width, Height);
				ctx.fillStyle = "#cccccc";
				ctx.fillRect ( 0, 0, Width, Height );
			}

			for ( xw = 0; xw < WordCount; xw++ )
			{
				ctx.fillStyle = C[xw];
				ctx.fillText ( W[xw], X[xw], Y[xw] );
			}

			WordCount++;

			await sleep ( SleepTime );
		}

		let t1= performance.now(); //end time
		console.log('Total time '+ (t1-t0) +' milliseconds');

		var Button = document.getElementById ( 'submitNoTest' ).disabled = false;
	}

}

async function RandomFastBars ( ctx, Width, Height )
{
	var MinDimension = Math.min(Width,Height);
	let t0= performance.now();

	for ( var j = 0; j < 50; j++ )
	{
		ctx.putImageData(imgData, 0, 0);

		var LineStart = 10; 
		var LineEnd   = MinDimension - 10;

		for ( var zz = 0; zz < 5; zz++ )
		{
			ctx.beginPath();
			ctx.strokeStyle = Colors[zz];
			ctx.lineWidth = 3+zz*2;
			if ( 1 == 2 )
			{
				xs = randomInt(LineStart,LineEnd);
				ys = randomInt(LineStart,LineEnd);
				ctx.moveTo(xs,ys);
				xe = randomInt(LineStart,LineEnd);
				ye = randomInt(LineStart,LineEnd);
				ctx.lineTo(xe,ye);
			}
			xs = randomInt(10,Width);
			ys = randomInt(10,Height);
			ctx.moveTo(xs,ys);
			xe = randomInt(10,Width);
			ye = randomInt(10,Height);
			ctx.lineTo(xe,ye);
			ctx.stroke();
		}

		await sleep ( 100 );
	}

	let t1= performance.now();
	console.log('Total time '+ (t1-t0) +' milliseconds');

	var Button = document.getElementById ( 'submitNoTest' ).disabled = false;
}

async function RandomCenterBezier ( ctx, Width, Height )
{
	let t0= performance.now();

	for ( var zz = 0; zz < 5; zz++ )
	{
		startX[zz]  = Width / 2; // randomInt ( 5, 395 );
		startY[zz]  = Height / 2; // randomInt ( 5, 395 );
		endX[zz]    = randomInt ( 5, 395 );
		endY[zz]    = randomInt ( 5, 395 );
		centerX[zz] = startX[zz] + (startX[zz] - endX[zz]) / 2 + randomInt ( 3, 6 );
		centerY[zz] = startY[zz] + (startY[zz] - endY[zz]) / 2 + randomInt ( 3, 6 );
		startmoveX[zz] = randomInt ( 0, 6 ) - 3;
		startmoveY[zz] = randomInt ( 0, 6 ) - 3;
		centermoveX[zz]= randomInt ( 0, 10 ) - 5;
		centermoveY[zz]= randomInt ( 0, 10 ) - 5;
		endmoveX[zz]   = randomInt ( 0, 6 ) - 3;
		endmoveY[zz]   = randomInt ( 0, 6 ) - 3;
	}

	var Sign = 0;

	for ( var j = 0; j < 250; j++ )
	{
		ctx.putImageData(imgData, 0, 0);

		for ( var zz = 0; zz < 5; zz++ )
		{
			ctx.beginPath();
			ctx.strokeStyle = Colors[4-zz];
			ctx.lineWidth = 5;

			ctx.moveTo ( startX[zz], startY[zz] );
			ctx.quadraticCurveTo ( centerX[zz], centerY[zz], endX[zz], endY[zz] );
			ctx.stroke();

			endX[zz]    = endX[zz]    + endmoveX[zz];
			endY[zz]    = endY[zz]    + endmoveY[zz];
			if ( j % 50 == 0 )
			{
				Sign = flip();
			}

			if ( Sign == 1 )
			{
				centerX[zz] = centerX[zz] + centermoveX[zz];
				centerY[zz] = centerY[zz] + centermoveY[zz];
			}
			else
			{
				centerX[zz] = centerX[zz] - centermoveX[zz];
				centerY[zz] = centerY[zz] - centermoveY[zz];
			}

			if (  startX[zz] < 10 ||  startX[zz] > Width - 10 )
			{
				startmoveX[zz] = 0 - startmoveX[zz];
				centermoveX[zz] = 0 - centermoveX[zz];
			}
			if (  startY[zz] < 10 ||  startY[zz] > Height - 10 )
			{
				startmoveY[zz] = 0 - startmoveY[zz];
				centermoveY[zz] = 0 - centermoveY[zz];
			}
			if (  endX[zz] < 10 ||  endX[zz] > Width - 10 )
			{
				endmoveX[zz] = 0 - endmoveX[zz];
				centermoveX[zz] = 0 - centermoveX[zz];
			}
			if (  endY[zz] < 10 ||  endY[zz] > Height - 10 )
			{
				endmoveY[zz] = 0 - endmoveY[zz];
				centermoveY[zz] = 0 - centermoveY[zz];
			}
		}

		await sleep ( 20 );
	}

	let t1= performance.now();
	console.log('Total time '+ (t1-t0) +' milliseconds');

	var Button = document.getElementById ( 'submitNoTest' ).disabled = false;
}

async function RandomSineSurfer ( ctx, Width, Height )
{
	var MaxBarLength = Height - 70;
	var HorizSpace = Width / 5;
	let t0= performance.now();

	for ( var zz = 0; zz < 5; zz++ )
	{
		Length[zz] = randomInt ( 100, MaxBarLength );
		centerX[zz] = HorizSpace/2 + zz * HorizSpace;
	}

	for ( var j = 0; j < 250; j++ )
	{
		ctx.putImageData(imgData, 0, 0);

		for ( var zz = 0; zz < 5; zz++ )
		{
			centerY[zz] = 50 * Math.sin ( (j + zz * 80) / 30 ) + 60;

			ctx.beginPath();
			ctx.strokeStyle = Colors[4-zz];
			ctx.lineWidth = 5 + zz*2;

			ctx.moveTo(centerX[zz],centerY[zz]);
			ctx.lineTo(centerX[zz],centerY[zz] + Length[zz] );
			ctx.stroke();
		}

		await sleep ( 20 );
	}

	let t1= performance.now();
	console.log('Total time '+ (t1-t0) +' milliseconds');

	var Button = document.getElementById ( 'submitNoTest' ).disabled = false;
}

async function RandomSpinSticks ( ctx, Width, Height )
{
	let t0= performance.now();
	var MinDimension = Math.min(Width,Height);

	for ( var zz = 0; zz < 5; zz++ )
	{
		Angle[zz]   = randomDbl ( 0.0, 1.0 * Math.PI );
		Length[zz]  = randomInt ( 100, MinDimension / 2 );
		centerX[zz] = Width / 2 + randomInt(-50,50);
		centerY[zz] = Height / 2 + randomInt(-50,50);
		moveX[zz]   = randomDbl(-2.0,2.0);
		moveY[zz]   = randomDbl(-2.0,2.0);
	}

	// do 250 times * 0.02 second = 5 seconds
	for ( var j = 0; j < 250; j++ )
	{
		ctx.putImageData(imgData, 0, 0);

		for ( var zz = 0; zz < 5; zz++ )
		{
			Angle[zz] += 0.035;
			if ( Angle[zz] >= 2 * Math.PI )
			{
				Angle[zz] = 0.0;
			}
			Vert = (Length[zz]/2.0) * Math.sin(Angle[zz]);
			Horiz = Math.sqrt((Length[zz]/2)*(Length[zz]/2)-Vert*Vert);
			if ( Angle[zz] > 0.5 * Math.PI && Angle[zz] < 1.5 * Math.PI )
			{
				Horiz = 0 - Horiz;
			}

			ctx.beginPath();
			ctx.strokeStyle = Colors[4-zz];
			ctx.lineWidth = 5 + zz*2;

			xs = centerX[zz] - Horiz;
			ys = centerY[zz] - Vert;
			ctx.moveTo(xs,ys);
			xe = centerX[zz] + Horiz;
			ye = centerY[zz] + Vert;
			ctx.lineTo(xe,ye);
			ctx.stroke();

			if ( centerX[zz] - Length[zz]/2.0 < 2 || centerX[zz] + Length[zz]/2.0 > Width - 2 )
			{
				moveX[zz] = 0.0 - moveX[zz];
			}
			if ( centerY[zz] - Length[zz]/2.0 < 2 || centerY[zz] + Length[zz]/2.0 > Height - 2 )
			{
				moveY[zz] = 0.0 - moveY[zz];
			}

			centerX[zz] = centerX[zz] + moveX[zz];
			centerY[zz] = centerY[zz] + moveY[zz];
		}

		await sleep ( 20 );
	}

	let t1= performance.now();
	console.log('Total time '+ (t1-t0) +' milliseconds');

	var Button = document.getElementById ( 'submitNoTest' ).disabled = false;
}

async function RandomCircles ( ctx, Width, Height )
{
	var	GrowShrink = 1;
	let t0= performance.now();

	for ( var zz = 0; zz < 5; zz++ )
	{
		radius[zz]  = randomInt(10,30);
		centerX[zz] = Width / 2 + randomInt(-50,50);
		centerY[zz] = Height / 2 + randomInt(-50,50);
		moveX[zz] = randomDbl(-2.0,2.0);
		moveY[zz] = randomDbl(-2.0,2.0);
	}

	for ( var j = 0; j < 250; j++ )
	{
		ctx.putImageData(imgData, 0, 0);

		// draw five circles
		for ( var zz = 0; zz < 5; zz++ )
		{
			if ( radius[zz] > 100 )
			{
				GrowShrink = -1;
			}
			else if ( radius[zz] < 10 )
			{
				GrowShrink = 1;
			}
			radius[zz] += GrowShrink;

			ctx.beginPath();
			ctx.strokeStyle = Colors[zz];
			ctx.lineWidth = 3;
			ctx.arc ( centerX[zz], centerY[zz], radius[zz], 0, 2 * Math.PI );
			ctx.stroke();

			if ( moveX[zz] > 0.0 && centerX[zz] + radius[zz] > Width - 10 )
			{
				moveX[zz] = 0.0 - moveX[zz];
			}
			else if ( moveX[zz] < 0.0 && centerX[zz] - radius[zz] < 10 )
			{
				moveX[zz] = 0.0 - moveX[zz];
			}

			if ( moveY[zz] > 0.0 && centerY[zz] + radius[zz] > Height - 10 )
			{
				moveY[zz] = 0.0 - moveY[zz];
			}
			else if ( moveY[zz] < 0.0 && centerY[zz] - radius[zz] < 10 )
			{
				moveY[zz] = 0.0 - moveY[zz];
			}

			centerX[zz] = centerX[zz] + moveX[zz];
			centerY[zz] = centerY[zz] + moveY[zz];

		}	

		if ( 1 == 2 )
		{
			// draw a bezier cubic curve using centers of first four
			ctx.beginPath();
			ctx.strokeStyle = 'black';
			ctx.lineWidth = 5;
			ctx.moveTo( centerX[0], centerY[0])
			ctx.bezierCurveTo( centerX[1], centerY[1], centerX[2], centerY[2], centerX[3], centerY[3] )
			ctx.stroke();
		}

		await sleep ( 20 );
	}

	let t1= performance.now();
	console.log('Total time '+ (t1-t0) +' milliseconds');

	var Button = document.getElementById ( 'submitNoTest' ).disabled = false;
}

async function RandomSines ( ctx, Width, Height )
{
	var xx = 0;
	var yS = 0;
	var yL = 0;
	var y = 0;
	var LineStart = 1; 
	var LineEnd = Width - 1;
	var m = -1.0 / (LineEnd - LineStart);
	var b = 1.0;
	var Freq = 0;
	var Amp  = Height * 0.09;
	var Space = (Height - 5 * Amp * 2) / 6;
	var HeightStart = Amp + Space;
	let t0= performance.now();

	for ( var k = 0; k < 250; k++ )
	{
		Freq = 100;

		LineHeight = HeightStart;

		ctx.putImageData(imgData, 0, 0);

		for ( var j = 0; j < 5; j++ )
		{
			ctx.beginPath();
			ctx.strokeStyle = Colors[j];
			ctx.lineWidth = 3;

			yS = CalcSine( LineStart, k,  Freq, Amp );

			yL = CalcLine ( LineStart, m, b );

			y = yS * yL;

			xx = LineStart;
			y = y + LineHeight;
			ctx.moveTo(xx,y);
			for ( zz = LineStart + 1; zz <= LineEnd; zz++ )
			{
				yS  = CalcSine( zz, k, Freq, Amp );
				
				yL = CalcLine ( zz, m, b );

				y = yS * yL;

				xx = zz;
				y = y + LineHeight;
				ctx.lineTo(xx,y);
			}
			ctx.stroke();

			Freq = Freq + 50;

			LineHeight = LineHeight + 2 * Amp + Space;

		}

		await sleep ( 5 );
	}

	let t1= performance.now();
	console.log('Total time '+ (t1-t0) +' milliseconds');

	var Button = document.getElementById ( 'submitNoTest' ).disabled = false;
}

async function RandomSpinCirclesLines ( ctx, Width, Height )
{
	var StartRadius = 10;
	var CircleArray = [ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ];
	var MaxCircles = CircleArray.length;
	var CircleCount = 0;
	var NewCircleAt = 30;
	var AngleArray = [ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ];
	var AngleX     = [ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ];
	var AngleY     = [ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ];
	var increment = 2;
	var distance = Math.sqrt((Width/2)**2, (Height/2)**2);
	var ThisColor = Colors[1];
	var PrevIndex = 0;
	var StartColor = 1;
	var ColorIndex = 1;
	var DoRotate = 1;
	var ClearOrRandom = 'R';
	let centerX = Width / 2;
	let centerY = Height / 2;
	let t0= performance.now();

	for ( var j = 0; j < MaxCircles; j++ )
	{
		AngleArray[j] = j * 360.0 / MaxCircles;
		var endPoint = CalcEndPoint ( j, AngleArray[j], centerX, centerY, Width, Height );
		AngleX[j] = endPoint[0];
		AngleY[j] = endPoint[1];
	}

	// run long enough for last circle grow 50%
	for ( var k = 0; k < 800; k++ )
	{
		if ( ClearOrRandom == 'R' )
		{
			ctx.putImageData(imgData, 0, 0);
		}
		else
		{
			ctx.clearRect(0, 0, Width, Height );
		}

		if ( CircleCount == 0 || ( CircleArray[CircleCount-1] > NewCircleAt && CircleCount < MaxCircles ))
		{
			// add another circle
			CircleArray[CircleCount] = StartRadius;
			CircleCount = CircleCount + 1;

			// console.log ( 'added circle ' + CircleCount );

			// if this is the last circle, then turn on line rotation
			if ( CircleCount == MaxCircles )
			{
				DoRotate = 1;
			}
		}

		if ( DoRotate == 1 )
		{
			for ( xc = 0; xc < MaxCircles; xc++ )
			{
				AngleArray[xc] = AngleArray[xc] + 0.25;
				if ( AngleArray[xc] >= 360 )
				{
					AngleArray[xc] = AngleArray[xc] - 360;
				}
				var endPoint = CalcEndPoint ( xc, AngleArray[xc], centerX, centerY, Width, Height );
				AngleX[xc] = endPoint[0];
				AngleY[xc] = endPoint[1];
			}
		}

		for ( xc = 0; xc < CircleCount; xc++ )
		{
			// paint circle
			radius = CircleArray[xc];
			ctx.beginPath();
			ctx.strokeStyle = Colors[xc%5];
			ctx.lineWidth = 3;
			ctx.arc ( centerX, centerY, radius, 0, 2 * Math.PI );
			ctx.stroke();

			yStart = centerY;
			xStart = centerX;

			// paint line
			ctx.beginPath();
			ctx.strokeStyle = Colors[xc%5];
			ctx.moveTo ( xStart, yStart );
			ctx.lineTo ( AngleX[xc], AngleY[xc] );
			ctx.stroke();

			// now update this circle's radius
			// CircleArray[xc] = CircleArray[xc] + increment;

			// plus sign speeds them up and they all get catch up
			// CircleArray[xc] = CircleArray[xc] + increment * ( 1 + xc/50);

			// minus sign slows them down
			CircleArray[xc] = CircleArray[xc] + increment * ( 1 - xc/25);

		}

		await sleep ( 4 );
	}

	let t1= performance.now();
	console.log('Total time '+ (t1-t0) +' milliseconds');

	var Button = document.getElementById ( 'submitNoTest' ).disabled = false;
}

function DrawDistraction ()
{
	var Stage = document.getElementById('GameStage').value;

	var canvas = document.getElementById('Distract');
	canvas.width = ScreenWidth - 20;
	canvas.height = ScreenHeight * 0.85 - 20;
	var MinDimension = Math.min(canvas.width,canvas.height);

	var ctx = canvas.getContext('2d');
	imgData = ctx.getImageData(0, 0, canvas.width, canvas.height);

	for (var i = 0; i < imgData.data.length; i += 4) 
	{
		imgData.data[i]   = randomInt(0, 255); // red
		imgData.data[i+1] = randomInt(0, 255); // green
		imgData.data[i+2] = randomInt(0, 255); // blue
		imgData.data[i+3] = 255; // alpha
	}

	var WhichDistraction = Stage % 10;
	if ( WhichDistraction == 0 )
	{
		// graphic
		RandomCircles ( ctx, canvas.width, canvas.height );
	}
	else if ( WhichDistraction == 1 )
	{
		// graphic
		RandomFastBars ( ctx, canvas.width, canvas.height );
	}
	else if ( WhichDistraction == 2 )
	{
		// graphic
		RandomSpinSticks ( ctx, canvas.width, canvas.height );
	}
	else if ( WhichDistraction == 3 )
	{
		// text
		RandomNumberSpinner ( ctx, canvas.width, canvas.height );
	}
	else if ( WhichDistraction == 4 )
	{
		// graphic
		RandomSineSurfer ( ctx, canvas.width, canvas.height );
	}
	else if ( WhichDistraction == 5 )
	{
		// graphic
		RandomCenterBezier ( ctx, canvas.width, canvas.height );
	}
	else if ( WhichDistraction == 6 )
	{
		// text
		RandomWordCloud ( ctx, canvas.width, canvas.height );
	}
	else if ( WhichDistraction == 7 )
	{
		// graphic
		RandomSines ( ctx, canvas.width, canvas.height );
	}
	else if ( WhichDistraction == 8 )
	{
		// graphic
		RandomSpinCirclesLines ( ctx, canvas.width, canvas.height );
	}
	else if ( WhichDistraction == 9 )
	{
		// text
		RandomStarWars ( ctx, canvas.width, canvas.height );
	}
	else
	{
		alert ( 'stage ' + Stage + ' which ' + WhichDistraction );
	}
}
