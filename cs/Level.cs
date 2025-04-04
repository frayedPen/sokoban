public class Level
{
	private char[][] Layout = new char[9][];

	public Vector2Int Player = new (2 ,2);

	public readonly char WALL = '#';
	public readonly char BOX = 'O';
	public readonly char SPOT = '+';
	public readonly char ON_SPOT = '0';
	public readonly char SPACE = ' ';
	public readonly Vector2Int[] Wins = new Vector2Int[7];

	public Level()
	{
		Layout = [
			[' ',' ','#','#','#','#','#',' ',],
			['#','#','#',' ',' ',' ','#',' ',],
			['#','+',' ','O',' ',' ','#',' ',],
			['#','#','#',' ','O','+','#',' ',],
			['#','+','#','#','O',' ','#',' ',],
			['#',' ','#',' ','+',' ','#','#',],
			['#','O',' ','0','O','O','+','#',],
			['#',' ',' ',' ','+',' ',' ','#',],
			['#','#','#','#','#','#','#','#',],
		];

		Wins = [
			new Vector2Int(1, 2),
			new Vector2Int(5, 3),
			new Vector2Int(1, 4),
			new Vector2Int(4, 5),
			new Vector2Int(3, 6),
			new Vector2Int(6, 6),
			new Vector2Int(4, 7),
		];
	}

	public char GetBlock(Vector2Int vector)
	{
		if(vector.Y < 0 || vector.Y >= 9 || vector.X < 0 || vector.X >= 8)
		{
			throw new Exception();
		}

		return Layout[vector.Y][vector.X];
	}

	public int GetHeight()
	{
		return Layout.Length;
	}

	public char[] GetLine(int i)
	{
		return Layout[i];
	}

	public void SetLocation(Vector2Int pos, char block)
	{
		Layout[pos.Y][pos.X] = block;
	}

	public bool CheckWin()
	{
		foreach (var win in Wins)
		{
			if(Layout[win.Y][win.X] == ON_SPOT) return true;
		}
		return false;
	}
}