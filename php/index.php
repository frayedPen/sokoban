<?php
	const WALL = "#";
	const BOX = "O";
	const SPOT = "+";
	const ON_SPOT = "0";
	const SPACE = " ";
	const PLAYER = "P";
	const INVALID = "#";

	const LAYOUT = [
		[' ', ' ', '#', '#', '#', '#', '#', ' ', ],
		['#', '#', '#', ' ', ' ', ' ', '#', ' ', ],
		['#', '+', ' ', 'O', ' ', ' ', '#', ' ', ],
		['#', '#', '#', ' ', 'O', '+', '#', ' ', ],
		['#', '+', '#', '#', 'O', ' ', '#', ' ', ],
		['#', ' ', '#', ' ', '+', ' ', '#', '#', ],
		['#', 'O', ' ', '0', 'O', 'O', '+', '#', ],
		['#', ' ', ' ', ' ', '+', ' ', ' ', '#', ],
		['#', '#', '#', '#', '#', '#', '#', '#', ],
	];

	class Point {
		public $x;
		public $y;

		function __construct($x, $y) {
			$this->x = $x;
			$this->y = $y;
		}
	}

	class Game {
		private $player;
		private $level;

		function __construct() {
			$this->reset();
		}

		private function reset() {
			$this->player = new Point(2, 2);
			$this->level = LAYOUT;
		}

		public function start() {
			print("Type w,a,s,d to move. Can type multiple characters to move. Write reset to restart.\n");

			while (true) {
				$this->render();

				$inputStr = readline('Action: ');

				if($inputStr == "exit" || $inputStr == "leave") return;

				if($inputStr == "reset" || $inputStr == "restart") {
					$this->reset();
					continue;
				}

				$chars = str_split($inputStr);

				// Loop over each command
				foreach($chars as $c) {
					switch($c) {
						case 'w':
							$this->movePlayer(0, -1);
							break;
						
						case 'a':
							$this->movePlayer(-1, 0);
							break;

						case 's':
							$this->movePlayer(0, 1);
							break;

						case 'd':
							$this->movePlayer(1, 0);
							break;
					}
				}
			}
		}

		private function movePlayer($deltaX, $deltaY) {
			$x = $this->player->x + $deltaX;
			$y = $this->player->y + $deltaY;

			// Check if the player can move
			$block = $this->getBlock($x, $y);

			if($block == INVALID || $block == WALL) return;

			// Check if the player is trying to push a block
			if($block == BOX || $block == ON_SPOT) {
				$nextX = $x + $deltaX;
				$nextY = $y + $deltaY;

				$nextBlock = $this->getBlock($nextX, $nextY);

				if($nextBlock == SPACE || $nextBlock == SPOT) {
					// Push block over
					$this->level[$y][$x] = $block == BOX ? SPACE : SPOT;
					$this->level[$nextY][$nextX] = $nextBlock == SPACE ? BOX : ON_SPOT;
				} else {
					return;
				}
			}

			// Move player if move was valid
			$this->player->x = $x;
			$this->player->y = $y;
		}

		private function checkWin() {
			if($this->level[2][1] == ON_SPOT &&
				$this->level[3][5] == ON_SPOT &&
				$this->level[4][1] == ON_SPOT &&
				$this->level[5][4] == ON_SPOT &&
				$this->level[6][3] == ON_SPOT &&
				$this->level[6][6] == ON_SPOT &&
				$this->level[7][4] == ON_SPOT) return true;

			return false;
		}

		private function getBlock($x, $y) {
			// Check if coordinates are out of bounds
			if($x < 0 || $y < 0 || $y >= sizeof($this->level) || $x >= sizeof($this->level[0])) return;

			return $this->level[$y][$x];
		}

		private function render() {
			// Print out level and player
			for($i=0;$i<sizeof($this->level);$i++) {
				for($j=0;$j<sizeof($this->level[$i]);$j++) {
					if($i == $this->player->y && $j == $this->player->x) print(PLAYER);
					else print($this->level[$i][$j]);
				}

				print("\n");
			}

			if($this->checkWin()) {
				print("You won! Type restart to restart.\n");
			}

			print("\n");
		}
	}

	$game = new Game();
	$game->start();
?>