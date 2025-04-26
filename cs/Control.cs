
public static class Control
{
	static private Level Level = new ();
	static public Func<char, Vector2Int>? GetVector;
	static public Action<Level, Vector2Int>? Render;

	private static void Restart()
	{
		Level = new Level();
	}

	public static void Start()
	{
		Console.WriteLine("Type w,a,s,d to move. Can type multiple characters to move. Write reset to restart.");
		
		while(true)
		{
			Console.Write("Action: ");
			var str = Console.ReadLine() ?? "";

			if(str == "exit" || str == "leave") return;

			if(str == "restart" || str == "reset")
			{
				Restart();
				Render?.Invoke(Level, Level.Player);
				continue;
			}

			foreach(char c in str)
			{
				try 
				{
					Vector2Int dir = GetVector?.Invoke(c) ?? new Vector2Int(0, 0);
					var newPos = Level.Player + dir;
					
					var block = Level.GetBlock(newPos);

					// Check if can move
					if(block == Level.WALL) return;

					// Check if can push block
					if(block == Level.BOX || block == Level.ON_SPOT) {
						var nextPos = newPos + dir;

						var nextBlock = Level.GetBlock(nextPos);

						if(nextBlock == Level.SPACE || nextBlock == Level.SPOT) {
							// Move box forward and clear spaces behind it
							Level.SetLocation(nextPos, nextBlock == Level.SPACE ? Level.BOX : Level.ON_SPOT);
							Level.SetLocation(newPos, block == Level.BOX ? Level.SPACE : Level.ON_SPOT);
						} else {
							throw new Exception();
						}
					}

					Level.Player = newPos;

				} 
				catch (System.Exception)
				{
					
				}
			}

			Render?.Invoke(Level, Level.Player);

			if(Level.CheckWin()) {
				Console.WriteLine("You won! Type restart to restart.");
			}
		}
	}
}