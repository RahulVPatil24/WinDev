using System;
using System.Runtime.InteropServices;
using AutomationServerTypeLibForDotNet;

public class CSharpAutomation
{
    public static void Main()
    {   
        //code 
        CMyMathClass objCMyMathClass = new CMyMathClass();
        IMyMath objIMyMath  = (IMyMath)objCMyMathClass;

        int num1, num2, sum, subtract;

        num1 = 175;
        num2 = 135;

        sum = objIMyMath.SumOfTwoIntegers(num1, num2);
        Console.WriteLine("Sum Of "+num1+" And "+num2+" is "+sum);

        subtract = objIMyMath.SubtractionOfTwoIntegers(num1, num2);
        Console.WriteLine("Sum Of "+num1+" And "+num2+" is "+subtract);
    }
}
