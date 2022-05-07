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
    public partial class Container : Form
    {
        private MainController _cntr;

        public MainController Cntr { get => _cntr; set => _cntr = value; }

        public Container()
        {
            InitializeComponent();
            Cntr = new MainController();
        }

        public Container(MainController cntr)
        {
            InitializeComponent();
            Cntr = cntr;
        }

        private void Container_Load(object sender, EventArgs e)
        {
            LoadStartPage();
        }

        private void CloseActiveMdiChild()
        {
            while (this.MdiChildren.Length > 0)
            {
                this.ActiveMdiChild.Close();
            }
        }

        public void LoadStartPage()
        {
            CloseActiveMdiChild();
            Startfenster SP = new Startfenster();
            SP.MdiParent = this;
            SP.Dock = DockStyle.Fill;
            SP.Show();
            this.Text = SP.Text;
        }

        public void LoadManuellPage()
        {
            CloseActiveMdiChild();
            this.IsMdiContainer = true;
            ControllerManuell CM = new ControllerManuell();
            CM.MdiParent = this;
            CM.Dock = DockStyle.Fill;
            CM.Show();
            this.Text = CM.Text;
        }

        public void LoadAutomaticPage()
        {
            CloseActiveMdiChild();
            this.IsMdiContainer = true;
            ControllerAutomatisch CA = new ControllerAutomatisch();
            CA.MdiParent = this;
            CA.Dock = DockStyle.Fill;
            CA.Show();
            this.Text = CA.Text;
        }
    }
}