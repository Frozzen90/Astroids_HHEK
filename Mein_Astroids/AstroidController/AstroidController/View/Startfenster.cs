using System;
using System.Windows.Forms;

namespace AstroidController.View
{
    public partial class Startfenster : Form
    {
        public Startfenster()
        {
            InitializeComponent();
        }

        public Startfenster(MainController cntr)
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            ((Container)MdiParent).LoadManuellPage();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            ((Container)MdiParent).LoadAutomaticPage();
        }

        private void btnExit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
    }
}
