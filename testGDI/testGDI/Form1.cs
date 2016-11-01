using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Runtime.InteropServices;

namespace testGDI
{
    public partial class Form1 : Form 
    {
        public Form1()
        {
            InitializeComponent();
        }

 
        public List<float> x1 = new List<float>();
        public List<float> y1 = new List<float>();
        public List<float> x2 = new List<float>();
        public List<float> y2 = new List<float>();
        public List<float> x3 = new List<float>();
        public List<float> y3 = new List<float>();
        public List<float> x4 = new List<float>();
        public List<float> y4 = new List<float>();

        private void button1_Click(object sender, EventArgs e)
        {

            x1.Clear();
            y1.Clear();

            doCAPDecode();
            using (StreamReader reader = new StreamReader("H:\\output.txt"))
            {
                int i = 1;
                string line = reader.ReadLine();
                while (line != "" && line != null)
                {
                    float x = float.Parse(line);
                    y1.Add(x);
                    x1.Add(i);
                    line = reader.ReadLine();
                    i++;
                }                     
            }
            zGraphTest.f_ClearAllPix();
            zGraphTest.f_reXY();
            zGraphTest.f_LoadOnePix(ref x1, ref y1, Color.Blue, 2);
            zGraphTest.f_AddPix(ref x2, ref y2, Color.Red, 1);
            zGraphTest.f_Refresh();
        }
        [DllImport("testCAPDLL1.dll", EntryPoint = "doCAPDecode")]
        private static extern int doCAPDecode(); 
    }
}
