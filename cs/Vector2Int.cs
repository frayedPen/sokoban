public struct Vector2Int {
    public int X;
    public int Y;

    public Vector2Int(int x, int y)
    {
        this.X = x;
        this.Y = y;
    }

    public static Vector2Int operator +(Vector2Int a, Vector2Int b)
    {
        Vector2Int res = new (a.X + b.X, a.Y + b.Y);
        return res;
    }
}