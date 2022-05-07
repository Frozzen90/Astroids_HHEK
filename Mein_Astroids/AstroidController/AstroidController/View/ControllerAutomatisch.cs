using System;
using System.ComponentModel;
using System.Windows.Forms;

namespace AstroidController.View
{
    public partial class ControllerAutomatisch : Form
    {
        private BackgroundWorker worker;
        public ControllerAutomatisch()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //Automatik starten
            button1.Enabled = false;
            button2.Enabled = true;
            if (worker == null)
            {
                worker = new BackgroundWorker();
                worker.WorkerSupportsCancellation = true;
                worker.DoWork += new DoWorkEventHandler((state, args) =>
                {
                    while (true)
                    {
                        if (worker.CancellationPending)
                        {
                            break;
                        }
                        //Run Automatic
                        ((Container)MdiParent).Cntr.RunAutomatic();
                    }; 
                });
            }
            else
            {
                //nichts
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            button1.Enabled = true;
            button2.Enabled = false;
            CancelWorker();
        }

        private void CancelWorker()
        {
            if (worker != null)
            {
                worker.CancelAsync();
                worker = null;
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            CancelWorker();
            ((Container)MdiParent).LoadStartPage();
        }
    }
}
