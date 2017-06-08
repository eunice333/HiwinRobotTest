using System;

using System.Runtime.InteropServices;

namespace HRSDK
{
	class HRobot
	{
        [DllImport("HRSDK.dll")]
        public static extern int Connect(String a);
        [DllImport("HRSDK.dll",EntryPoint = "ptp_axis")]
        public static extern int ptp_joint(int robot, double[] point);
	}
}
