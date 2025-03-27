const layout = [
	"  ##### ",
	"###   # ",
	"#+ O  # ",
	"### O+# ",
	"#+##O # ",
	"# # + ##",
	"#O 0OO+#",
	"#   +  #",
	"########",
];

function replaceChar(origString, replaceChar, index) {
    let firstPart = origString.substr(0, index);
    let lastPart = origString.substr(index + 1);
      
    let newString = firstPart + replaceChar + lastPart;
    return newString;
}

class Game {
	constructor() {
		this.level = [...layout];
		this.player = {x: 2, y: 2};
	}

	moveUp() {
		this.move(0, -1);
	}

	moveDown() {
		this.move(0, 1);
	}

	moveLeft() {
		this.move(-1, 0);
	}

	moveRight() {
		this.move(1, 0);
	}

	move(deltaX, deltaY) {
		try {
			const block = this.getBlockAtPosition(this.player.x + deltaX, this.player.y + deltaY);

			console.assert(block != "" && block != " ", "Empty block");

			this.player.x = this.player.x  + deltaX;
			this.player.y = this.player.y  + deltaY;
		} catch(e) {
			console.assert(true, "Out of bounds");
		}

		this.renderResponse();
	}

	getBlockAtPosition(x, y) {
		if(!this.level[y]) throw new error("Doesn't exists");
		if(!this.level[y][x]) throw new error("Doesn't exists");
		
		const c = this.level[y][x];
		// console.assert((typeof c) != "string", "Level not 2D array of string");

		return c;
	}

	renderResponse() {
		this.level.forEach((line, index) => {
			if(index == this.player.y) {
				console.log(replaceChar(line, "P", this.player.x));
			} else {
				console.log(line);
			}
		});
	}
}

const game = new Game();

const readline = require('node:readline');
const rl = readline.createInterface({
	input: process.stdin,
	output: process.stdout,
});

const prompt = () => {
	rl.question(`Action: `, str => {
		switch(str) {
			case "up":
			case "u":
				game.moveUp();
				break;
				
			case "down":
			case "d":
				game.moveDown();
				break;

			case "left":
			case "l":
				game.moveLeft();
				break;

			case "right":
			case "r":
				game.moveRight();
				break;
			
			case "exit":
			case "leave":
				return;
		}
		prompt();
	});
}

prompt();  