# CONSTANTS
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

WALL = "#"
BOX = "O"
SPOT = "+"
ON_SPOT = "0"
SPACE = " "
PLAYER = "P"
INVALID = "!"
H = len(LAYOUT)
W = len(LAYOUT[0])

FIRST_STEP_BLOCK = (INVALID, WALL)
SECOND_STEP_BLOCK = (INVALID, WALL, BOX, ON_SPOT)

class Game:
	def __init__(self):
		self.player = {
			"x": 2,
			"y": 2
		}

		self.level = []

		# Make a copy of the level
		for line in LAYOUT:
			arr = []
			for c in line:
				arr.append(c)

			self.level.append(arr)
		pass

	def prompt(self):
		self.render()
		print("")
		input_str = input("Action: ")

		for c in input_str:
			if c == "w":
				self.move(0, -1)
			elif c == "a"
				self.move(-1, 0)
			elif c == "s":
				self.move(0, 1)
			elif c == "d":
				self.move(1, 0)

		self.prompt()
		pass
	
	def getBlock(self, x, y):
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

		if block == BOX or ON_SPOT:
			# Check if can push box over
			nextX = self.player["x"] + deltaX + deltaX
			nextY = self.player["y"] + deltaY + deltaY

			nextBlock = self.getBlock(nextX, nextY)

			if nextBlock in SECOND_STEP_BLOCK:
				pass
			else:
				# Push box over
				self.level[y][x] = SPACE if block == BOX else SPOT
				self.level[nextY][nextX] = ON_SPOT if nextBlock == SPOT else block

		self.player["x"] = x
		self.player["y"] = y
		
		return

	def render(self):
		for i, line in enumerate(self.level):
			outStr = ''

			for j, c in enumerate(line):
				outStr += PLAYER if i == self.player["y"] and j == self.player["x"] else c

			print(outStr)

game = Game()
game.prompt()