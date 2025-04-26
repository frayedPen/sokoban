import java.util.Scanner;
import java.text.CharacterIterator;
import java.text.StringCharacterIterator;

class Vector2 {
	public int x;
	public int y;

	public Vector2(int x, int y) {
		this.x = x;
		this.y = y;
	}
}

class Main
{
	private static final char[][] LAYOUT = {
		{' ', ' ', '#', '#', '#', '#', '#', ' '},
		{'#', '#', '#', ' ', ' ', ' ', '#', ' '},
		{'#', '+', ' ', 'O', ' ', ' ', '#', ' '},
		{'#', '#', '#', ' ', 'O', '+', '#', ' '},
		{'#', '+', '#', '#', 'O', ' ', '#', ' '},
		{'#', ' ', '#', ' ', '+', ' ', '#', '#'},
		{'#', 'O', ' ', '0', 'O', 'O', '+', '#'},
		{'#', ' ', ' ', ' ', '+', ' ', ' ', '#'},
		{'#', '#', '#', '#', '#', '#', '#', '#'}
	};

	private static char[][] level;

	public static Vector2 player = new Vector2(2 ,2);

	private static final char WALL = '#';
	private static final char BOX = 'O';
	private static final char SPOT = '+';
	private static final char ON_SPOT = '0';
	private static final char SPACE = ' ';
	private static final char INVALID = '!';
	private static final char PLAYER = 'P';

	public static void main(String[] args)
	{
		Scanner s = new Scanner(System.in);
		restart();

		System.out.println("Type w,a,s,d to move. Can type multiple characters to move. Write reset to restart.");

		while (true) {
			renderLevel();

			System.out.print("Action: ");
			String inputStr = s.nextLine();

			if(inputStr.equals("exit") || inputStr.equals("leave")) {
				break;
			}

			if(inputStr.equals("reset") || inputStr.equals("restart")) {
				restart();
				continue;
			}
			
			CharacterIterator it = new StringCharacterIterator(inputStr);
			
			while (it.current() != CharacterIterator.DONE) {
				char c = it.current();

				move(c);

				it.next();
			}
		}

		s.close();
	}

	private static void restart()
	{
		// Player staring position
		player = new Vector2(2, 2);

		// Make a copy of the level
		level = new char[LAYOUT.length][LAYOUT[0].length];

		for(int i=0;i<LAYOUT.length;i++) 
		{
			char[] arr = LAYOUT[i].clone();
			level[i] = arr;
		}
	}

	private static void move(char c) 
	{
		
		Vector2 delta = getDelta(c);
		int x = player.x + delta.x;
		int y = player.y + delta.y;

		char block = getBlock(x, y);

		// Check if player can move
		if(block == INVALID || block == WALL) return;

		if (block == BOX || block == ON_SPOT) {
			// Check if player can push box
			int nextX = x + delta.x;
			int nextY = y + delta.y;
			char nextBlock = getBlock(nextX, nextY);

			if(nextBlock == INVALID || nextBlock == WALL || nextBlock == BOX || nextBlock == ON_SPOT) return;

			// Push box over
			level[nextY][nextX] = nextBlock == SPACE ? BOX : ON_SPOT;
			level[y][x] = block == ON_SPOT ? SPOT : SPACE;
		}


		player.x = x;
		player.y = y;
	}

	private static char getBlock(int x, int y)
	{
		if(y < 0 || y >= level.length || x < 0 || x > level[0].length) return INVALID;

		return level[y][x];
	}

	private static Vector2 getDelta(char c)
	{
		int deltaX = 0;
		int deltaY = 0;

		switch (c) {
			case 'w':
				deltaY = -1;
				break;

			case 'a':
				deltaX = -1;
				break;

			case 's':
				deltaY = 1;
				break;

			case 'd':
				deltaX = 1;
				break;
		
			default:
				break;
		}

		return new Vector2(deltaX, deltaY);
	}

	private static void renderLevel()
	{
		for(int i=0;i<level.length;i++) 
		{
			for(int j=0;j<level[0].length;j++) 
			{
				if(i == player.y && j == player.x) System.out.print(PLAYER);
				else System.out.print(level[i][j]);
			}
			System.out.println("");
		}

		if(checkWin())
		{
			System.out.println("You won! Type restart to restart.");
		}

		System.out.println("");
	}
	
	private static boolean checkWin()
	{
		if(level[2][1] == ON_SPOT &&
			level[3][5] == ON_SPOT &&
			level[4][1] == ON_SPOT &&
			level[5][4] == ON_SPOT &&
			level[6][3] == ON_SPOT &&
			level[6][6] == ON_SPOT &&
			level[7][4] == ON_SPOT) return true;
		return false;
	}
}