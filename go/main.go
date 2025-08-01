package main

import "fmt"

const W int8 = 8
const H int8 = 9

const WALL string = "#"
const BOX string = "O"
const SPOT string = "+"
const ON_SPOT string = "0"
const SPACE string = " "
const PLAYER string = "P"
const INVALID string = "!"

var LAYOUT = [W * H]string{" ", " ", "#", "#", "#", "#", "#", " ", "#", "#", "#", " ", " ", " ", "#", " ", "#", "+", " ", "O", " ", " ", "#", " ", "#", "#", "#", " ", "O", "+", "#", " ", "#", "+", "#", "#", "O", " ", "#", " ", "#", " ", "#", " ", "+", " ", "#", "#", "#", "O", " ", "0", "O", "O", "+", "#", "#", " ", " ", " ", "+", " ", " ", "#", "#", "#", "#", "#", "#", "#", "#", "#"}

func main() {
	player := [2]int8{2, 2}
	var level = LAYOUT

	fmt.Println("Type w,a,s,d to move. Can type multiple characters to move. Write reset to restart.")

	// Game loop
	for {
		render(level, player)
		checkWin(level)

		fmt.Println("")
		fmt.Print("Action: ")

		var inputStr string
		fmt.Scanln(&inputStr)

		if inputStr == "exit" || inputStr == "leave" {
			// Leave the program
			break
		}

		if inputStr == "reset" || inputStr == "restart" {
			// Reset level
			player[0] = 2
			player[1] = 2
			level = LAYOUT
			continue
		}

		// Loop over each character in the input string
		for i := 0; i < len(inputStr); i++ {
			switch inputStr[i] {
			case 'w':
				movePlayer(&player, &level, 0, -1)
			case 'a':
				movePlayer(&player, &level, -1, 0)
			case 's':
				movePlayer(&player, &level, 0, 1)
			case 'd':
				movePlayer(&player, &level, 1, 0)
			}
		}
	}
}

func render(level [W * H]string, player [2]int8) {
	playerIndex := player[1]*W + player[0]
	var i int8 = 0

	// Draw level in a grid
	for ; i < W*H; i++ {
		if playerIndex == i {
			fmt.Print(PLAYER)
		} else {
			fmt.Print(level[i])
		}

		if i%W == W-1 {
			fmt.Println("")
		}
	}
}

func movePlayer(player *[2]int8, level *[72]string, deltaX int8, deltaY int8) {
	x := player[0] + deltaX
	y := player[1] + deltaY

	block := getBlock(level, x, y)

	// Check if player can move
	if block == INVALID || block == WALL {
		return
	}

	// Check if player is trying to push a box
	if block == BOX || block == ON_SPOT {
		nextX := x + deltaX
		nextY := y + deltaY

		nextBlock := getBlock(level, nextX, nextY)

		// Move the box if there's an empty space over
		switch nextBlock {
		case SPACE:
			switch block {
			case BOX:
				level[y*W+x] = SPACE
			case ON_SPOT:
				level[y*W+x] = SPOT
			}
			level[nextY*W+nextX] = BOX
		case SPOT:
			switch block {
			case BOX:
				level[y*W+x] = SPACE
			case ON_SPOT:
				level[y*W+x] = SPOT
			}

			level[nextY*W+nextX] = ON_SPOT
		default:
			return
		}
	}

	// Move player
	player[0] = x
	player[1] = y
}

func getBlock(level *[72]string, x int8, y int8) string {
	if x < 0 || y < 0 || x >= W || y >= H {
		return INVALID
	}

	return level[y*W+x]
}

func checkWin(level [72]string) {
	if level[2*W+1] == ON_SPOT &&
		level[3*W+5] == ON_SPOT &&
		level[4*W+1] == ON_SPOT &&
		level[5*W+4] == ON_SPOT &&
		level[6*W+3] == ON_SPOT &&
		level[6*W+6] == ON_SPOT &&
		level[7*W+4] == ON_SPOT {
		fmt.Println("You won! Type restart to restart.")
	}
}
