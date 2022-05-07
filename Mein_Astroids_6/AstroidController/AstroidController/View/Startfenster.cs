namespace AstroidController
{
    public partial class Startfenster : Form
    {
        private MainController mainController;

        public MainController MainController { get => mainController; set => mainController = value; }

        public Startfenster()
        {
            InitializeComponent();
            MainController = new MainController();
        }

        public Startfenster(MainController MC)
        {
            InitializeComponent();
            MainController = MC;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            
        }

        private void button2_Click(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
    }
}
