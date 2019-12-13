var sequence = [];
var displayed = [];
var delay = 2;
var delayTimer = 0.0;
var displayIndex = 0;
var secondDelay = false;
var secondDelayTimer = 0.0;
var showSequence = true;
var trianglesDisplayed = 0;
var trianglesToDisplay = 4;


var awaitingInput = false;

function preload()
{
	//generatedWordList = loadStrings("Words.txt");
	//bgMusic = loadSound("BgMusic.mp3");
}

function setup() 
{
	createCanvas(1000, 1000, WEBGL);	
	
	for(var i = 0; i < 100; i++)
	{
		sequence.push(floor(random(0, 4)));
	}
	displayed.push(sequence[0]);
}

function draw()
{
	background(50, 50, 50);
	drawOpaqueTriangles();
	
	if(showSequence)
	{
		if(!secondDelay)
		{
			drawTriangles(displayed[0]);
			delayTimer += 0.03;
			if(delayTimer >= delay)
			{
				displayed.unshift(sequence[displayIndex]);
				trianglesDisplayed++;
				displayIndex++;
				delayTimer = 0.0;
				
				secondDelay = true;
			}
		}
		else
		{
			secondDelayTimer += 0.03;
			if(secondDelayTimer >= 0.6)
			{
				secondDelay = false;
				secondDelayTimer = 0.0;
			}
		}
		
		if(trianglesDisplayed >= trianglesToDisplay)
		{
			showSequence = false;
			displayIndex = 0;
			trianglesDisplayed = 0;
			awaitingInput = true;
		}
	}
}

function keyPressed()
{
	if(awaitingInput)
	{
		switch(keyCode)
		{
			case 87: //KeyW
			break;
			
			case 68: //KeyD
			break;
			
			case 83: //KeyS
			break;
			
			case 65: //KeyA
			break;
		}
	}
	//currentTyped += String.fromCharCode(keyCode);

}

function drawOpaqueTriangles()
{
	
	noStroke();
	
	//Triangle 0
	fill(255, 0, 0, 30);
	beginShape();
	vertex(0, -250);
	vertex(125, -125);
	vertex(-125, -125);
	endShape();
	
	//Triangle 1
	fill(0, 255, 0, 30);
	beginShape();
	vertex(125, -125);
	vertex(250, 0);
	vertex(125, 125);
	endShape();
	
	//Triangle 2
	fill(0, 0, 255, 30);
	beginShape();
	vertex(125, 125);
	vertex(0, 250);
	vertex(-125, 125);
	endShape();
	
	//Triangle 3
	fill(255, 255, 0, 30);
	beginShape();
	vertex(-125, 125);
	vertex(-250, 0);
	vertex(-125, -125);
	endShape();
	noFill();
}

function drawTriangles(triangleIndex)
{
	
	noStroke();
	
	if(triangleIndex == 0)
	{
	//Triangle 0
	fill(255, 0, 0);
	beginShape();
	vertex(0, -250);
	vertex(125, -125);
	vertex(-125, -125);
	endShape();
	}
	
	if(triangleIndex == 1)
	{
	//Triangle 1
	fill(0, 255, 0);
	beginShape();
	vertex(125, -125);
	vertex(250, 0);
	vertex(125, 125);
	endShape();
	}
	
	if(triangleIndex == 2)
	{
	//Triangle 2
	fill(0, 0, 255);
	beginShape();
	vertex(125, 125);
	vertex(0, 250);
	vertex(-125, 125);
	endShape();
	}
	
	if(triangleIndex == 3)
	{
	//Triangle 3
	fill(255, 255, 0);
	beginShape();
	vertex(-125, 125);
	vertex(-250, 0);
	vertex(-125, -125);
	endShape();
	}
}
