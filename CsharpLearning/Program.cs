﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CsharpLearning
{
    class Program
    {
        static void Main(string[] args)
        {
            // 输出到屏幕
			double firstNumber, secondNumber;
			string userName;
			Console.WriteLine("Enter your name:");
			userName = Console.ReadLine();
			Console.WriteLine("Welcome {0}!", userName);
			Console.WriteLine("Now give me a number:");
			firstNumber =  Convert.ToDouble(Console.ReadLine());
			Console.WriteLine("Now give me another number:");
			secondNumber = Convert.ToDouble(Console.ReadLine());
			Console.WriteLine("The sum of {0} and {1} is {2}.", firstNumber, secondNumber, firstNumber + secondNumber);
			Console.WriteLine("The result of subtracting {0} from {1} is {2}.", secondNumber, firstNumber, firstNumber - secondNumber);
			Console.WriteLine("The product of {0} and {1} is {2}.", firstNumber, secondNumber, firstNumber * secondNumber);
			Console.ReadLine();
        }
    }
}
