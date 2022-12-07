using System;
using System.Drawing;
using System.Windows.Forms; //For Windows UI Component

public class CSharpWindow:Form
{
    public CSharpWindow()
    {
        Text = "CSharp Window"; //Text == caption CreateWindows's 3rd parameter in win32
        BackColor = Color.Black; //hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH)
        ResizeRedraw = true; //CS_HREDRAW | CS_VREDRAW;
    }

    public static void Main()
    {
        Application.Run(new CSharpWindow());
    }
}
