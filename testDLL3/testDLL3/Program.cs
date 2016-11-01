using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace testDLL3
{
    class Program
    {
        static void Main(string[] args)
        {
            doCAPDecode();         
        }
        [DllImport("testCAPDLL1.dll", EntryPoint = "doCAPDecode")]
        private static extern int doCAPDecode(); 

    }
}
