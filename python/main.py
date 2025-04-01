# CONSTANTS
# Starting level layout
LAYOUT = (
	(' ',' ','#','#','#','#','#',' '),
	('#','#','#',' ',' ',' ','#',' '),
	('#','+',' ','O',' ',' ','#',' '),
	('#','#','#',' ','O','+','#',' '),
	('#','+','#','#','O',' ','#',' '),
	('#',' ','#',' ','+',' ','#','#'),
	('#','O',' ','0','O','O','+','#'),
	('#',' ',' ',' ','+',' ',' ','#'),
	('#','#','#','#','#','#','#','#')
)

# Final destination of boxes
WINS = (
	(1, 2),
	(5, 3),
	(1, 4),
	(4, 5),
	(3, 6),
	(6, 6),
	(4, 7)
)

WALL = "#"
BOX = "O"
SPOT = "+"
ON_SPOT = "0"
SPACE = " "
PLAYER = "P"
INVALID = "!"
H = len(LAYOUT)
W = len(LAYOUT[0])

seq = ''

FIRST_STEP_BLOCK = (INVALID, WALL)
SECOND_STEP_BLOCK = (INVALID, WALL, BOX, ON_SPOT)

class Game:
	def __init__(self):
		self.reset()
		pass

	def reset(self):
		self.player = {
			"x": 2,
			"y": 2
		}

		self.level = []

		self.playing = True

		# Make a copy of the level
		for line in LAYOUT:
			arr = []
			for c in line:
				arr.append(c)

			self.level.append(arr)

		pass

	def start(self):
		print("Type w,a,s,d to move. Can type multiple characters to move. Write reset to restart.")

		while(True):
			self.render()
			print("")
			input_str = input("Action: ")

			if input_str == "reset" or input_str == "restart":
				self.reset()
				continue

			if input_str == "exit" or input_str == "leave":
				break

			if self.playing: # Don't take any input if the game is over
				for c in input_str:
					if c == "w":
						self.move(0, -1)
					elif c == "a":
						self.move(-1, 0)
					elif c == "s":
						self.move(0, 1)
					elif c == "d":
						self.move(1, 0)

					global seq
					seq += c

		pass
	
	def getBlock(self, x, y):
		# Check if coordinates are out of bounds
		if x < 0 or x >= W or y < 0 or y >= H:
			return INVALID

		return self.level[y][x]

	def move(self, deltaX, deltaY):
		x = self.player["x"] + deltaX
		y = self.player["y"] + deltaY

		block = self.getBlock(x, y)

		# Check if there's space to move to
		if block in FIRST_STEP_BLOCK:
			return

		if block == BOX or block == ON_SPOT:
			# Check if can push box over
			nextX = self.player["x"] + deltaX + deltaX
			nextY = self.player["y"] + deltaY + deltaY

			nextBlock = self.getBlock(nextX, nextY)

			if nextBlock in SECOND_STEP_BLOCK:
				return
			
			# Push box over
			self.level[y][x] = SPACE if block == BOX else SPOT
			self.level[nextY][nextX] = ON_SPOT if nextBlock == SPOT else block

		self.player["x"] = x
		self.player["y"] = y
		
		return

	def render(self):
		# Output level and player
		for i, line in enumerate(self.level):
			outStr = ''

			for j, c in enumerate(line):
				outStr += PLAYER if i == self.player["y"] and j == self.player["x"] else c

			print(outStr)
		
		if self.checkWin():
			self.playing = False
			print("You won!")

	def checkWin(self):
		# Check if every box is in it's spot
		for win in WINS:
			if self.level[win[1]][win[0]] != ON_SPOT:
				return False
		
		print(seq)
		return True


game = Game()
game.start()