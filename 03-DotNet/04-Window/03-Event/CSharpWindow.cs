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
        Width = 800;
        Height = 600;
    }

    protected override void OnPaint(PaintEventArgs pea)
    {
        Graphics grfx = pea.Graphics;

        StringFormat strfmt = new StringFormat();

        strfmt.Alignment = StringAlignment.Center;

        strfmt.LineAlignment = StringAlignment.Center;
        grfx.DrawString("Hello World !!!", Font, new SolidBrush(System.Drawing.Color.Cyan), ClientRectangle, strfmt);
    }

    public static void Main()
    {
        Application.Run(new CSharpWindow());
    }
}
