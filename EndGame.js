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


var imageArray = []; // array for the images

async function LoadImages ( imageUrlArray)
{
	const promiseArray = []; // create an array for promises

	for (let imageUrl of imageUrlArray) 
	{
		promiseArray.push(new Promise(resolve => 
		{
			const img = new Image();
			img.onload = resolve;
			img.src = imageUrl;
			imageArray.push(img);
		}));
	}

	await Promise.all(promiseArray); // wait for all the images to be loaded
}


async function EndGame ()
{
	// alert ("End Game");

	var ScreenWidth = window.innerWidth;
	var ScreenHeight = window.innerHeight;
	// alert ( 'Width' + ScreenWidth + ' Height' + ScreenHeight );

	var canvas = document.getElementById('EndGame');
	canvas.width = ScreenWidth - 20;
	canvas.height = ScreenHeight - 20;
	CanvasSize = canvas.width * canvas.height;

	var Score = 'You scored ' + document.getElementById ( 'Score' ).value + '!';

	var ctx = canvas.getContext('2d');
	var imgData = ctx.getImageData(0, 0, canvas.width, canvas.height);

	// alert ( 'imgLength' + imgData.data.length + ' CanvasSize' + CanvasSize );

	var x = 0;
	for (var row = 0; row < canvas.height * 4; row += 4 )
	{
		for (var col = 0; col < canvas.width * 4; col += 4) 
		{
			x = row * canvas.width;
			imgData.data[x+col]   = 255 * row / (canvas.height * 4); // red
			imgData.data[x+col+1] = 127; // green
			imgData.data[x+col+2] = 127; // blue
			imgData.data[x+col+3] = 255; // alpha
		}
	}

	// ctx.putImageData(imgData, 0, 0);

	var LineStart = 10; 
	var LineEnd   = Math.min(canvas.width, canvas.height);

	var UrlArray = [ 'balloons-25737_640.png', 'balloon-25734_640.png', 'balloon-25739_640.png' ];
	LoadImages (  UrlArray );

	var Steps = 200;
	var Sleeps = 25;
	var Increment = canvas.height / Steps;
	var DelayStart = [ 0, 10, 20, 30, 50, 100 ];
	var y = [ canvas.height, canvas.height, canvas.height, canvas.height, canvas.height, canvas.height ];

	var xs = [  canvas.width * 0.10 + randomDbl ( 0.0, canvas.width * 0.7), 
				canvas.width * 0.12 + randomDbl ( 0.0, canvas.width * 0.7), 
				canvas.width * 0.14 + randomDbl ( 0.0, canvas.width * 0.7), 
				canvas.width * 0.16 + randomDbl ( 0.0, canvas.width * 0.7), 
				canvas.width * 0.18 + randomDbl ( 0.0, canvas.width * 0.7), 
				canvas.width * 0.20 + randomDbl ( 0.0, canvas.width * 0.7) ];

	var xe = [  canvas.width * 0.40 + randomDbl ( 0.0 - canvas.width * 0.2, canvas.width * 0.5 ), 
				canvas.width * 0.50 + randomDbl ( 0.0 - canvas.width * 0.3, canvas.width * 0.4 ), 
				canvas.width * 0.60 + randomDbl ( 0.0 - canvas.width * 0.4, canvas.width * 0.3 ), 
				canvas.width * 0.70 + randomDbl ( 0.0 - canvas.width * 0.5, canvas.width * 0.2 ), 
				canvas.width * 0.80 + randomDbl ( 0.0 - canvas.width * 0.6, canvas.width * 0.1 ), 
				canvas.width * 0.90 + randomDbl ( 0.0 - canvas.width * 0.7, 0.0 ) ];

	var x = [];
	var moveX = [];
	for ( j = 0; j < 6; j++ )
	{
		Slope = canvas.height / (xe[j] - xs[j]);
		moveX[j] = Increment / Slope;

		// moveX[j] = (xe[j] - xs[j]) / canvas.height;


		x[j] = xs[j];
	}

	var Fonts = [ 
		'36px Georgia', 
		'33px Georgia',
		'30px Georgia', 
		'27px Georgia', 
		'24px Georgia', 
		'21px Georgia', 
		'18px Georgia', 
		'15px Georgia' ];

	Font = Fonts[0];
	var LineLength = 0;
	for ( j = 0; j < Fonts.length; j++ )
	{
		ctx.font = Fonts[j];
		LineLength = ctx.measureText(Score).width;
		if ( LineLength < canvas.width * 0.8 )
		{
			Font = Fonts[j];
			break;
		}
	}
	
	var imgX = 0;
	var offset = 0;
	var angle = 0;
	var amplitude = Math.min(50,canvas.width * 0.1);
	var factor = canvas.height / 7.5;
	var FirstLine = canvas.height * 0.25;

	for ( var j = 0; ;  j++ )
	{
		ctx.putImageData(imgData, 0, 0);
		
		ctx.font = Font;
		ctx.fillStyle = "#FFFF00";
		ctx.fillText ( Score, canvas.width * 0.1, FirstLine );

		for ( var zz = 0; zz < 6; zz++ )
		{
			if ( j > DelayStart[zz] )
			{
				offset = amplitude * Math.sin(y[zz]/factor);
				angle = offset / 3.0;
				angle = angle * Math.PI/180;

				if ( y[zz] > 1 )
				{
					y[zz] = y[zz] - Increment;
				}
				else
				{
					moveX[zz] = 0;
				}
				imgX = zz % 3;
				ctx.rotate(angle);
				ctx.drawImage(imageArray[imgX],x[zz]+offset,y[zz]);
				ctx.rotate(0-angle);
				x[zz] = x[zz] + moveX[zz];
			}
		}

		await sleep ( Sleeps );

		if ( y[5] <= 1 )
		{
			break;
		}
	}

	rectX = (canvas.width - 200) / 2;
	rectY = canvas.height * 0.5;
	var rect = {
	    x:rectX,
		y:rectY,
		width:200,
		height:75
		};

	ctx.fillStyle = '#999999';
	ctx.fillRect(rect.x, rect.y, rect.width, rect.height );

	ctx.beginPath();
	ctx.lineWidth = 5;
	ctx.moveTo(rect.x,rect.y);
	ctx.strokeStyle = '#d3d3d3'
	ctx.lineTo(rect.x+rect.width,rect.y);
	ctx.lineTo(rect.x+rect.width,rect.y+rect.height);
	ctx.stroke();
	ctx.beginPath();
	ctx.lineWidth = 5;
	ctx.strokeStyle = '#3d3d3d'
	ctx.moveTo(rect.x+rect.width,rect.y+rect.height);
	ctx.lineTo(rect.x,rect.y+rect.height);
	ctx.lineTo(rect.x,rect.y);
	ctx.stroke();

	ctx.font = '30px Georgia';
	ctx.fillStyle = 'black'
	var Text = 'Play Again';
	LineLength = ctx.measureText(Text).width;
	var textX = rect.x + ( rect.width - LineLength) / 2;
	var textY = rect.y + 10 + rect.height /2;
	ctx.fillText ( Text , textX, textY );

	// click button from: https://stackoverflow.com/questions/24384368/simple-button-in-html5-canvas
	//Function to get the mouse position
	function getMousePos(canvas, event) {
		var rect = canvas.getBoundingClientRect();
		return {
			x: event.clientX - rect.left,
			y: event.clientY - rect.top
		};
	}

	//Function to check whether a point is inside a rectangle
	function isInside(pos, rect){
		return pos.x > rect.x && pos.x < rect.x+rect.width && pos.y < rect.y+rect.height && pos.y > rect.y
	}

	//Binding the click event on the canvas
	canvas.addEventListener('click', function(evt) {
		var mousePos = getMousePos(canvas, evt);

		if (isInside(mousePos,rect)) 
		{
			// alert('clicked inside rect');
			document.getElementById ( 'NewGame' ).value = 'Y';
			window.document.PixGame.submit();
		}
		else
		{
			// alert('clicked outside rect');
		}   

	}, false);
}
