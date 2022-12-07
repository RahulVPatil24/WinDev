using System;
using System.Runtime.InteropServices;

public class PInvoke
{

    [DllImport("MyMathTwo.dll")]    //attribute
    public static extern int MakeCube(int Num);

    public static void Main()
    {
        int num1 = 5;
        int num2 = MakeCube(num1);
        Console.WriteLine("Cube of "+num1+" is "+num2);
    }
}
