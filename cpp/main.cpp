#include <iostream>

using namespace std;

const char LAYOUT[9][8] = {
	{' ',' ','#','#','#','#','#',' '},
	{'#','#','#',' ',' ',' ','#',' '},
	{'#','+',' ','O',' ',' ','#',' '},
	{'#','#','#',' ','O','+','#',' '},
	{'#','+','#','#','O',' ','#',' '},
	{'#',' ','#',' ','+',' ','#','#'},
	{'#','O',' ','0','O','O','+','#'},
	{'#',' ',' ',' ','+',' ',' ','#'},
	{'#','#','#','#','#','#','#','#'}
};

const char WALL = '#';
const char BOX = 'O';
const char SPOT = '+';
const char ON_SPOT = '0';
const char SPACE = ' ';
const char PLAYER = 'P';
const char INVALID = '!';

const int H = 9;
const int W = 8;

struct vector2
{
	int x;
	int y;
};

class Game
{
	public:
		struct vector2 player;
		char level[9][8];
		void renderResponse();
		void reset();
		void move(int deltaX, int deltaY);
		char getBlock(int x, int y);
		bool checkWin();
		Game();
};

Game::Game()
{
	reset();
}

void Game::renderResponse()
{
	// Output level and player
	for(int i=0;i<H;i++) {
		for(int j=0;j<W;j++) {
            if(i == player.y && j == player.x) {
                cout << PLAYER;
            } else {
                cout << level[i][j];
            }
        }
		cout << endl;
	}

	if(checkWin()) {
		cout << "You won! Type restart to restart" << endl;
	}

	cout << endl;
}

void Game::reset()
{
	// Reset player position and level
	player.x = 2;
	player.y = 2;

	for(int i=0;i<H;i++) {
		for(int j=0;j<W;j++) {
			level[i][j] = LAYOUT[i][j];
		}
	}
}

void Game::move(int deltaX, int deltaY)
{
    int x = player.x + deltaX;
    int y = player.y + deltaY;

    // Check if player can move
    char block = getBlock(x, y);

    if(block == INVALID || block == WALL) {
        return;
    }

    // Check if player is attempting to push a block
    if(block == BOX || block == ON_SPOT) {
        int nextX = x + deltaX;
        int nextY = y + deltaY;

        char nextBlock = getBlock(nextX, nextY);

        if(nextBlock == INVALID || nextBlock == WALL || nextBlock == ON_SPOT || nextBlock == BOX) {
            // To place to move to
            return;
        }

        // Push the box over
        if(block == BOX) {
            level[y][x] = SPACE;
        } else if(block == ON_SPOT) {
            level[y][x] = SPOT;
        }

        if(nextBlock == SPACE) {
            level[nextY][nextX] = BOX;
        } else if(nextBlock == SPOT) {
            level[nextY][nextX] = ON_SPOT;
        }
    }

	// Commit player position
    player.x = x;
    player.y = y;
}

char Game::getBlock(int x, int y)
{
	// Check of coordinates is out of bounds
	if(x < 0 || x >= W || y < 0 || y >= H) {
		return INVALID;
	}

	return level[y][x];
}

bool Game::checkWin()
{
	// Check if every box is in their spots
	if(level[2][1] == ON_SPOT &&
		level[3][5] == ON_SPOT &&
		level[4][1] == ON_SPOT &&
		level[5][4] == ON_SPOT &&
		level[6][3] == ON_SPOT &&
		level[6][6] == ON_SPOT &&
		level[7][4] == ON_SPOT )
	{
		return true;
	}

	return false;
}

int main()
{
    Game game;
	string inputStr = "";

	cout << "Type w,a,s,d to move. Can type multiple characters to move. Write reset to restart." << endl;

	while (true) {
        game.renderResponse();

        cout << "Action: ";
        cin >> inputStr;

        if(inputStr == "leave" || inputStr == "exit") {
            return 0;
        }

        if(inputStr == "reset" || inputStr == "restart") {
            game.reset();
            continue;
        }

		// Loop over each character and make the player move
        for(int i=0;i<inputStr.length();i++) {
            char c = inputStr.at(i);

            switch (c) {
                case 'w':
                    game.move(0, -1);
                    break;
                case 'a':
                    game.move(-1, 0);
                    break;
                case 's':
                    game.move(0, 1);
                    break;
                case 'd':
                    game.move(1, 0);
                    break;
            }
        }
    }

    return 0;
}
