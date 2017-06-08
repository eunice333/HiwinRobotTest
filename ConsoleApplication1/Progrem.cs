using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.IO;

namespace HRSDK
{
	class Program
	{
        static void Main(string[] args)
        {
            int rol = HRobot.Connect("192.168.0.3");
            double[] point = { 0, 0, 0, 0, -90, 0 };
            Console.ReadLine();
        }
	}
}
