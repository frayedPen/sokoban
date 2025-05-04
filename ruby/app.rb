module BLOCK
    WALL = "#"
    BOX = "O"
    SPOT = "+"
    ON_SPOT = "0"
    SPACE = " "
end

PLAYER = "P"

LAYOUT = [
    [' ', ' ', '#', '#', '#', '#', '#', ' ', ],
    ['#', '#', '#', ' ', ' ', ' ', '#', ' ', ],
    ['#', '+', ' ', 'O', ' ', ' ', '#', ' ', ],
    ['#', '#', '#', ' ', 'O', '+', '#', ' ', ],
    ['#', '+', '#', '#', 'O', ' ', '#', ' ', ],
    ['#', ' ', '#', ' ', '+', ' ', '#', '#', ],
    ['#', 'O', ' ', '0', 'O', 'O', '+', '#', ],
    ['#', ' ', ' ', ' ', '+', ' ', ' ', '#', ],
    ['#', '#', '#', '#', '#', '#', '#', '#', ],
]

Point = Struct.new(:x, :y) do
	def +(other)
		Point.new(other.x + self.x, other.y + self.y)
	end
end

DELTAS = {"w" => Point.new(0, -1), "a" => Point.new(-1, 0), "s" => Point.new(0, 1), "d" => Point.new(1, 0)}

class Game
	@player
	@level

	def initialize
		@player = Point.new(2, 2)
		@level = Marshal.load(Marshal.dump(LAYOUT))
	end

	def start
		puts "Type w,a,s,d to move. Can type multiple characters to move. Write reset to restart."

		while true
			renderLevel

			print "Action: "
			inputStr = gets.chomp

			if inputStr == "exit" or inputStr == "leave"
				return
			end

			if inputStr == "restart" or inputStr == "reset"
				@player = Point.new(2, 2)
				@level = Marshal.load(Marshal.dump(LAYOUT))
				next
			end

			inputStr.chars.each do |c|
				delta = DELTAS[c]
				if delta == nil
					next
				end

				movePlayer(delta)
			end
		end
	end

	def movePlayer(delta)
		pos = delta + @player

		# Check if player can move
		block = getBlock(pos)

		if block == nil or block == BLOCK::WALL
			return
		end

		# Check if player is trying to push block
		if block == BLOCK::BOX or block == BLOCK::ON_SPOT
			nextPos = pos + delta

			nextBlock = getBlock(nextPos)

			if nextBlock == BLOCK::SPACE or nextBlock == BLOCK::SPOT
				# Push block over
				@level[pos.y][pos.x] = block == BLOCK::BOX ? BLOCK::SPACE : BLOCK::SPOT
            	@level[nextPos.y][nextPos.x] = nextBlock == BLOCK::SPACE ? BLOCK::BOX : BLOCK::ON_SPOT
			else
				return
			end
		end

		@player.x = pos.x
		@player.y = pos.y

	end

	def getBlock(pos)
		if pos.x < 0 or pos.y < 0 or pos.y >= @level.length or pos.x >= @level[0].length
			nil
		end

		@level[pos.y][pos.x]
	end

	def renderLevel
		for i in 0...@level.length do
			for j in 0...@level[i].length do
				if i == @player.y and j == @player.x
					print PLAYER
				else
					print @level[i][j]
				end
			end

			puts ""
		end

		if checkWin
			puts "You won! Type restart to restart."
		end

		puts ""
	end

	def checkWin
		if @level[2][1] == BLOCK::ON_SPOT and
			@level[3][5] == BLOCK::ON_SPOT and
			@level[4][1] == BLOCK::ON_SPOT and
			@level[5][4] == BLOCK::ON_SPOT and
			@level[6][3] == BLOCK::ON_SPOT and
			@level[6][6] == BLOCK::ON_SPOT and
			@level[7][4] == BLOCK::ON_SPOT then
			return true
		end

		return false
	end
end

game = Game.new
game.start