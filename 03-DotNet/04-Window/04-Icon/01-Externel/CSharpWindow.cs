using System;
using System.Drawing;
using System.Windows.Forms; //For Windows UI Component

public class CSharpWindow:Form
{
    public CSharpWindow()
    {
        Icon = new Icon("MyIcon.ico");
        Text = "CSharp Window"; //Text == caption CreateWindows's 3rd parameter in win32
        BackColor = Color.Black; //hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH)
        ResizeRedraw = true; //CS_HREDRAW | CS_VREDRAW;
        Width = 800;
        Height = 600;

        this.KeyDown += new KeyEventHandler(MyKeyDown);
        this.MouseDown += new MouseEventHandler(MyMouseDown);   
    }

    protected override void OnPaint(PaintEventArgs pea)
    {
        Graphics grfx = pea.Graphics;

        StringFormat strfmt = new StringFormat();

        strfmt.Alignment = StringAlignment.Center;

        strfmt.LineAlignment = StringAlignment.Center;
        grfx.DrawString("Hello World !!!", Font, new SolidBrush(System.Drawing.Color.Cyan), ClientRectangle, strfmt);
    }

    void MyKeyDown(Object Sender, KeyEventArgs e)
    {
        MessageBox.Show("A Key Is Pressed");
    }

    void MyMouseDown(object Sender, MouseEventArgs e)
    {
        MessageBox.Show("Mouse is Clicked");
    }

    public static void Main()
    {
        Application.Run(new CSharpWindow());
    }
}
