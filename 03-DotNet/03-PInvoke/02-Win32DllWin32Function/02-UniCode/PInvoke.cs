using System;
using System.Runtime.InteropServices;

public class PInvoke
{

    [DllImport("User32.dll",CharSet = CharSet.Unicode)]    //attribute
    public static extern int MessageBoxW(int Handle, String Message, String Caption, int Type);

    public static void Main()
    {
        MessageBoxW(0, "This is UniCode MessageBox Via Interop", "Message", 0);
    }
}
