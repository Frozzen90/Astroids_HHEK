using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace Asteroids_avatar
{
    static class Program
    {
        /// <summary>
        /// Der Haupteinstiegspunkt für die Anwendung.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            TController Controller = new TController();

            Application.Run(new Form1(Controller));
        }
    }
}
