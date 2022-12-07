using System;
using System.Runtime.InteropServices;

public class PInvoke
{

    [DllImport("User32.dll")]    //attribute
    public static extern int MessageBoxA(int Handle, String Message, String Caption, int Type);

    public static void Main()
    {
        MessageBoxA(0, "This is Ansi MessageBox Via Interop", "Message", 0);
    }
}
