var newWordTimer = 0;
var spawnTime = 30;

var wordList = [];

var wordListSize = 0;

var lowestWordIndex;

var wordShouldBeRemoved = false;

var generatedWordList;
var bgMusic;

var currentTyped = "";

var backgroundVar = 0;
var backgroundAscDescSwitch = false;

var fallspeed = 0.3;

var typedWords = 0;

class Word
{
	constructor(displayWord, xPosition, yPosition, nLetters)
	{
		this.displayWord = displayWord;
		this.xPosition = xPosition;
		this.yPosition = yPosition;
		this.nLetters = nLetters;
		
		this.graphics = createGraphics(15 * nLetters, 60);
		//this.graphics.background(200);
		this.graphics.textAlign(LEFT, LEFT);
		this.graphics.textSize(25);
		this.graphics.text(displayWord, xPosition, yPosition);
	}
	
	wordUpdate()
	{
		this.yPosition += fallspeed;
	}
}

function testLoss()
{
	if(wordList[lowestWordIndex])
	{
		if(wordList[lowestWordIndex].yPosition > 260)
		{
			bgMusic.fade(0, 1.5);
			console.log(typedWords);
			noLoop();
		}
	}
}
function updateWords()
{
	for(var i = 0; i < wordListSize; i++)
	{
		wordList[i].wordUpdate();
	}
}

function findLowestWord()
{
	var index = 0;
	for(var i = 0; i < wordListSize; i++)
	{
		if(wordList[i].yPosition >= wordList[index].yPosition)
		{
			index = i;
		}
	}
	return index;
}

function drawWords()
{
	for(var i = 0; i < wordListSize; i++)
	{
		
		wordList[i].graphics.background(backgroundVar, backgroundVar, backgroundVar);

		if(i == lowestWordIndex)
		{
			wordList[i].graphics.fill(0, 100, 255);
			wordList[i].graphics.text(wordList[i].displayWord, 0, 50);
			texture(wordList[i].graphics);
		}
		else
		{
			wordList[i].graphics.fill(0);
			wordList[i].graphics.text(wordList[i].displayWord, 0, 50);
			texture(wordList[i].graphics);
		}
		//tint(255, 100);
		rect(wordList[i].xPosition, wordList[i].yPosition, 200, 50);
	}
}

function destroyWord()
 {
	for(var i = 0; i < wordListSize; i++)
	{
		if(i == lowestWordIndex)
		{
			wordList.splice(i, 1);
			//console.log("Removed word at index ", i);
			break;
		}
	}	
	wordListSize -= 1;
	typedWords++;
}

function generateRandomWord()
{
	var min = -500; 
    var max =  300;  
    
	var newWordString = generatedWordList[Math.floor(Math.random() * generatedWordList.length)];
	var newWord = new Word(newWordString, Math.floor(Math.random() * (+max - +min)) + +min, -300, newWordString.length);
	wordList.push(newWord);
	wordListSize += 1;
	
	return newWord;	
}

function preload()
{
	generatedWordList = loadStrings("Words.txt");
	bgMusic = loadSound("BgMusic.mp3");
}

function setup() 
{
	createCanvas(1000, 600, WEBGL);
	//console.log(generatedWordList);
	generateRandomWord();
	bgMusic.play();
}

function draw()
{
	background(backgroundVar, backgroundVar, backgroundVar);
	if(backgroundAscDescSwitch)
	{
		if(backgroundVar < 255)
			backgroundVar += fallspeed;
		else
			backgroundAscDescSwitch = false;
	}
	else
	{
		if(backgroundVar > 0)
			backgroundVar -= fallspeed;
		else
			backgroundAscDescSwitch = true;
	}
	
	newWordTimer += 0.1;
	if(newWordTimer >= spawnTime && spawnTime > 3)
	{
		generateRandomWord();
		newWordTimer = 0;
		spawnTime -= 0.5;
	}
	
	lowestWordIndex = findLowestWord();
	
	drawWords();
	updateWords();
	if(wordShouldBeRemoved == true)
	{
		destroyWord();
		wordShouldBeRemoved = false;
	}
	
	testLoss();
	
	fallspeed += 0.00015;
}

function keyPressed()
{
	//console.log(String.fromCharCode(keyCode));
	
	if(wordList[lowestWordIndex].displayWord[currentTyped.length].toUpperCase() == String.fromCharCode(keyCode))
	{
		currentTyped += String.fromCharCode(keyCode);
		//console.log(currentTyped);
		
		
		var updateString = "";
		for(var i = 0; i < wordList[lowestWordIndex].displayWord.length; i++)
		{
			if(i < currentTyped.length)
				updateString += ' ';
			else
				updateString += wordList[lowestWordIndex].displayWord[i];
		}
		wordList[lowestWordIndex].displayWord = updateString;
		
		if(currentTyped.length == wordList[lowestWordIndex].displayWord.length)
		{
			destroyWord();
			currentTyped = "";
		}
	}
}