using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace Asteroids_avatar
{
    public partial class Form1 : Form
    {
        private TController Controller;

        public Form1()
        {
            InitializeComponent();
        }

        public Form1(TController value)
        {
            InitializeComponent();
            Controller = value;
        }

        private void button1_Click(object sender, EventArgs e)//rechts
        {
            //Einmal rechts senden
            this.Controller.senden(0x48); //rechts senden
            for (int index = 0; index < 8000000; index++) ;//warten
            this.Controller.senden(0x40); //rechts zurücknehmen
        }

        private void button2_Click(object sender, EventArgs e)//Links
        {
            this.Controller.senden(0x50);
            for (int index = 0; index < 8000000; index++) ;
            this.Controller.senden(0x40);
        }

        private void button3_Click(object sender, EventArgs e)//Feuer
        {
            this.Controller.senden(0x42);
            for (int index = 0; index < 8000000; index++) ;
            this.Controller.senden(0x40);
        }

        private void button4_Click(object sender, EventArgs e)//Schub
        {
            this.Controller.senden(0x44);
            for (int index = 0; index < 8000000; index++) ;
            this.Controller.senden(0x40);
        }
        private void button5_Click(object sender, EventArgs e)//Hyper
        {
            this.Controller.senden(0x41);
            for (int index = 0; index < 8000000; index++) ;
            this.Controller.senden(0x40);
        }
    }
}
