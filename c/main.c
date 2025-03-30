#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct pos {
    int x;
    int y;
};

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

const struct pos wins[7] = {
    {1,2},
    {5,3},
    {1,4},
    {4,5},
    {3,6},
    {6,6},
    {4,7}
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
    // Get block at location and prevent player from going out of bounds
	if(x < 0 || x >= W || y < 0 || y >= H) {
		return INVALID;
	}

	return level[y][x];
}

void render(int x, int y, char level[9][8])
{
    // Draw level and player
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

bool checkWon(char level[9][8])
{
    // Check if every box is in their position
    for(int i=0;i<7;i++) {
        const struct pos win = wins[i];

        if(level[win.y][win.x] != ON_SPOT) {
            return false;
        }
    }

    return true;
}

/*
  * https://alexandra-zaharia.github.io/posts/how-to-read-safely-from-stdin-in-c/
  */
// Read at most `n` characters (newline included) into `str`.
// If present, the newline is removed (replaced by the null terminator).
void s_gets(char* str, int n)
{
    char* str_read = fgets(str, n, stdin);
    if (!str_read)
        return;

    int i = 0;
    while (str[i] != '\n' && str[i] != '\0')
        i++;

    if (str[i] == '\n')
        str[i] = '\0';
}


int main()
{
	char level[9][8];
	struct pos player;
	char inputStr[50];

	printf("Type w,a,s,d to move. Can type multiple characters to move. Write reset to restart.\n");

reset:

	player.x = 2;
	player.y = 2;

	// Make a copy of the layout into the level
	for(int i=0;i<H;i++) {
		for(int j=0;j<W;j++) {
			level[i][j] = LAYOUT[i][j];
		}
	}

	render(player.x, player.y, level);

gameplay:

    printf("Action: ");
    s_gets(inputStr, 50);

	if(strncmp(inputStr, "exit", 4) == 0 || strncmp(inputStr, "leave", 5) == 0) {
        printf("wa");
        return 0;
    }

    if(strncmp(inputStr, "reset", 5) == 0 || inputStr[0] == 'r') {
        goto reset;
    }

	int i = -1;

checkInput:
    i += 1;

    char deltaX = 0;
    char deltaY = 0;

    if(inputStr[i] == 'w') {
        deltaY = -1;
    } else if(inputStr[i] == 'a') {
        deltaX = -1;
    } else if(inputStr[i] == 's') {
        deltaY = 1;
    } else if(inputStr[i] == 'd') {
        deltaX = 1;
    } else if(inputStr[i]== ' ' || inputStr[i]== '\n') {
        render(player.x, player.y, level);
        goto gameplay;
    } else {
        render(player.x, player.y, level);
        goto gameplay;
    }

    char block = getBlock(player.x + deltaX, player.y + deltaY, level);

    // If player trying to walk into a wall, do not move it
    if(block == INVALID || block == WALL) {
        //render(player.x, player.y, level);
        goto checkInput;
    }

    if(block == BOX || block == ON_SPOT) {

        // Player trying to push block
        // Check if there's space to push block over
        int nextX = player.x + deltaX + deltaX;
        int nextY = player.y + deltaY + deltaY;
        const char nextBlock = getBlock(nextX, nextY, level);

        if(nextBlock == INVALID || nextBlock == WALL || nextBlock == BOX || nextBlock == ON_SPOT) {
            // No space to move
            render(player.x, player.y, level);
            goto checkInput;
        }

        if(nextBlock == SPACE) {
            level[nextY][nextX] = BOX;
        }

        if(nextBlock == SPOT) {
            level[nextY][nextX] = ON_SPOT;
        }

        if(block == BOX) {
            level[player.y + deltaY][player.x + deltaX] = SPACE;

        } else if(block == ON_SPOT) {
            level[player.y + deltaY][player.x + deltaX] = SPOT;
        }
    }

    // Move player
    player.x += deltaX;
    player.y += deltaY;

    goto checkInput;

	render(player.x, player.y, level);

	const bool won = checkWon(level);

	if(won) {
        printf("You won\n");
	} else {
        goto gameplay;
	}

	return 0;
}


