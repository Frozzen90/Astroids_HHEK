using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AstroidController.View
{
    public partial class Startfenster : Form
    {
        public Startfenster()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.IsMdiContainer = true;
            ControllerManuell CM = new ControllerManuell();
            CM.MdiParent = this;
            CM.Show();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.IsMdiContainer = true;
            ControllerAutomatisch CA = new ControllerAutomatisch();
            CA.MdiParent = this;
            CA.Show();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
    }
}
