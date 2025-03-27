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
	SPACE = " ",
	PLAYER = "P";

function replaceChar(origString, replaceChar, index) {
    const firstPart = origString.substr(0, index);
    const lastPart = origString.substr(index + 1);
    return `${firstPart}${replaceChar}${lastPart}`;
}

class Game {
	constructor() {
		this.wins = [
			{x:1, y:2},
			{x:5, y:3},
			{x:1, y:4},
			{x:4, y:5},
			{x:3, y:6},
			{x:6, y:6},
			{x:4, y:7},
		];
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
		const x = this.player.x + deltaX;
		const y = this.player.y + deltaY;

		try {
			const block = this.getBlockAtPosition(x, y);

			console.assert(block != "", "Empty block");

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
			console.assert(this.player.x == x || this.player.y == y, "Player moved when it shouldn't haved");
		}

		this.renderResponse();
	}

	getBlockAtPosition(x, y) {
		if(!this.level[y]) throw new error("Doesn't exists");
		if(!this.level[y][x]) throw new error("Doesn't exists");
		
		const c = this.level[y][x];
		console.assert(y >= 0 && y <= 8, "y out of bounds");
		console.assert(x >= 0 && x <= 7, "x out of bounds");

		return c;
	}

	renderResponse() {
		this.level.forEach((line, index) => {
			if(index == this.player.y) {
				console.log(replaceChar(line, PLAYER, this.player.x));
			} else {
				console.log(line);
			}
		});

		if(this.checkWin()) {
			console.log("You won!!!");
		}
		
		console.log("");
	}

	restart() {
		this.level = [...layout];
		this.player = {x: 2, y: 2};
	}

	checkWin() {
		return !this.wins.some(win => {
			if(this.level[win.y][win.x] != ON_SPOT) return true;
			return false;
		});
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
		if(str == "r" || str == "restart") {
			game.restart();
			prompt();
			return;
		}

		if(str == "exit" || str == "leave") {
			r1.close();
			return;
		}

		str.split("").some(c => {
			switch(c) {
				case "w":
					game.moveUp();
					break;
					
				case "s":
					game.moveDown();
					break;

				case "a":
					game.moveLeft();
					break;

				case "d":
					game.moveRight();
					break;
			}
		});
		prompt();
	});
}

prompt();  