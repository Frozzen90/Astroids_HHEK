namespace AstroidController
{
    public partial class SteuerungManuell : Form
    {
        private MainController mainController;

        public MainController MainController { get => mainController; set => mainController = value; }

        public SteuerungManuell()
        {
            InitializeComponent();
            MainController mainController = new MainController();
        }

        public SteuerungManuell(MainController MC)
        {
            InitializeComponent();
            MainController mainController = MC;

        }

        private void button1_Click(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {

        }

        private void button4_Click(object sender, EventArgs e)
        {

        }

        private void button5_Click(object sender, EventArgs e)
        {

        }

        private void button6_Click(object sender, EventArgs e)
        {

        }

        private void button7_Click(object sender, EventArgs e)
        {

        }

        private void button8_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
    }
}