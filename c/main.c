#include <stdio.h>
#include <stdlib.h>

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

char getBlock(int x, int y, char level[9][8])
{
	if(x < 0 || x >= W || y < 0 || y >= H) {
		return INVALID;
	}

	return level[y][x];
}

void render(int x, int y, char level[9][8])
{
    for(int i=0;i<H;i++) {
        for(int j=0;j<W;j++) {
            if(y == i && x == j) {
                printf("%c", PLAYER);
            } else {
                printf("%c", level[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
	char level[9][8];
	int playerX = 2;
	int playerY = 2;
	char inputStr[50];

	// Make a copy of the layout into the level
	for(int i=0;i<H;i++) {
		for(int j=0;j<W;j++) {
			level[i][j] = LAYOUT[i][j];
		}
	}

	render(playerX, playerY, level);

gameplay:

    printf("Action: ");
	scanf("%s", inputStr);

	char deltaX = 0;
	char deltaY = 0;

	if(inputStr[0] == 'w') {
	    deltaY = -1;
	} else if(inputStr[0] == 'a') {
	    deltaX = -1;
	} else if(inputStr[0] == 's') {
	    deltaY = 1;
	} else if(inputStr[0] == 'd') {
	    deltaX = 1;
	} else {
	    goto gameplay;
	}

    char block = getBlock(playerX + deltaX, playerY + deltaY, level);

    // If player trying to walk into a wall, do not move it
    if(block == INVALID || block == WALL) {
        render(playerX, playerY, level);
        goto gameplay;
    }

    if(block == BOX || block == ON_SPOT) {

        // Player trying to push block
        // Check if there's space to push block over
        int nextX = playerX + deltaX + deltaX;
        int nextY = playerY + deltaY + deltaY;
        const nextBlock = getBlock(nextX, nextY, level);

        if(nextBlock == INVALID || nextBlock == WALL || nextBlock == BOX || nextBlock == ON_SPOT) {
            // No space to move
            render(playerX, playerY, level);
            goto gameplay;
        }

        if(nextBlock == SPACE) {
            level[nextY][nextX] = BOX;
        }

        if(nextBlock == SPOT) {
            level[nextY][nextX] = ON_SPOT;
        }

        if(block == BOX) {
            level[playerY + deltaY][playerX + deltaX] = SPACE;

        } else if(block == ON_SPOT) {
            level[playerY + deltaY][playerX + deltaX] = SPOT;
        }
    }

    playerY += deltaY;
    playerX += deltaX;


	//printf("%c", level[1][1]);
	render(playerX, playerY, level);

	goto gameplay;

	return 0;
}


