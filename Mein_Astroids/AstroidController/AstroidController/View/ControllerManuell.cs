using System;
using System.Threading;
using System.Windows.Forms;

namespace AstroidController.View
{
    public partial class ControllerManuell : Form
    {
        public ControllerManuell()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //Schub = 'I'
            ((Container)MdiParent).Cntr.send(0x44);
            Thread.Sleep(500);
            ((Container)MdiParent).Cntr.send(0x40);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            //links = 'Q'
            ((Container)MdiParent).Cntr.send(0x50);
            Thread.Sleep(500);
            ((Container)MdiParent).Cntr.send(0x40);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            //rechts = 'W'
            ((Container)MdiParent).Cntr.send(0x48);
            Thread.Sleep(500);
            ((Container)MdiParent).Cntr.send(0x40);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            //Hyper = 'SPACE'
            ((Container)MdiParent).Cntr.send(0x41);
            Thread.Sleep(500);
            ((Container)MdiParent).Cntr.send(0x40);
        }

        private void button6_Click(object sender, EventArgs e)
        {
            //Fire = 'O'
            ((Container)MdiParent).Cntr.send(0x42);
            Thread.Sleep(500);
            ((Container)MdiParent).Cntr.send(0x40);
        }

        private void button7_Click(object sender, EventArgs e)
        {
            ((Container)MdiParent).LoadStartPage();
        }
    }
}
