namespace AstroidController
{
    public partial class SteuerungAutomatisch : Form
    {
        private MainController mainController;

        public MainController MainController { get => mainController; set => mainController = value; }

        public SteuerungAutomatisch()
        {
            InitializeComponent();
        }
    }
}
