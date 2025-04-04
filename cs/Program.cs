const string PLAYER = "P";

Func<char, Vector2Int> charToVector = (c) => {
	if(c == 'w') return new Vector2Int(0, -1);
	else if(c == 'a') return new Vector2Int(-1, 0);
	else if(c == 's') return new Vector2Int(0, 1);
	else if(c == 'd') return new Vector2Int(1, 0);
	else throw new Exception();
};

Action<Level, Vector2Int> renderLevel = (level, vector) => {
	for(int i=0;i<level.GetHeight();i++)
	{
		var arr = level.GetLine(i);
		for(int j=0;j<arr.Length;j++) {
			if(i == vector.Y && j == vector.X) Console.Write(PLAYER);
			else Console.Write(arr[j]);
		}
		Console.WriteLine("");
	}
	Console.WriteLine("");
};

Control.GetVector = charToVector;
Control.Render = renderLevel;

Control.Start();