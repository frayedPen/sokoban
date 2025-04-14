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
		Game() {
			reset();
		};
};

void Game::renderResponse() 
{
	for(int i=0;i<H;i++) {
		for(int j=0;j<W;j++) {
			cout << level[i][j];
        }
		cout << endl;
	}

	cout << end1;
}

void Game::reset() 
{
	player.x = 2;
	player.y = 2;

	for(int i=0;i<H;i++) {
		for(int j=0;j<W;j++) {
			level[i][j] = LAYOUT[i][j];
		}
	}
}

int main()
{
    Game game;
	string inputStr = "";

	cout << "Type w,a,s,d to move. Can type multiple characters to move. Write reset to restart." << endl;

    cout << game.level[1][1];

    return 0;
}
