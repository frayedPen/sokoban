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

const WALL = "#",
	BOX = "O",
	SPOT = "+",
	ON_SPOT = "0",
	SPACE = " ";

function replaceChar(origString, replaceChar, index) {
    let firstPart = origString.substr(0, index);
    let lastPart = origString.substr(index + 1);
      
    let newString = firstPart + replaceChar + lastPart;
    return newString;
}

class Game {
	constructor() {
		this.restart();
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
			
			const x = this.player.x + deltaX;
			const y = this.player.y + deltaY;
			const block = this.getBlockAtPosition(x, y);

			console.assert(block != "" && block != " ", "Empty block");

			// Check if wall
			if(block == WALL) throw new error();;

			// Check if box
			if(block == BOX || block == ON_SPOT) {
				// Check if there's empty space in the direction of pushing
				const nextX = this.player.x + deltaX + deltaX;
				const nextY = this.player.y + deltaY + deltaY;

				const nextBlock = this.getBlockAtPosition(nextX, nextY);

				if(nextBlock == SPACE || nextBlock == SPOT) {
					// Move box forward and clear spaces behind it
					this.level[nextY] = replaceChar(this.level[nextY], nextBlock == SPACE ? BOX : ON_SPOT, nextX);
					this.level[y] = replaceChar(this.level[y], block == ON_SPOT ? SPOT : SPACE, x);
				} else {
					throw new error();
				}
			}

			this.player.x = x;
			this.player.y = y;
		} catch(e) {
			
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

	restart() {
		this.level = [...layout];
		this.player = {x: 2, y: 2};
	}
}

const game = new Game();
game.renderResponse();

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

			case "reset":
			case "restart":
				game.restart();
			
			case "exit":
			case "leave":
				r1.close();
				return;
		}
		prompt();
	});
}

prompt();  