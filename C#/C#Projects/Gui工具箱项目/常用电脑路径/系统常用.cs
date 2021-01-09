using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace 常用电脑路径
{
    public partial class 系统常用 : Form
    {
        public 系统常用()
        {
            InitializeComponent();
        }
        private void Fonts_bt_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start(Fonts_tB.Text);
        }
        private void StartMenu_bt_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start(StartMenu_tB.Text);
        }

        private void Programs_bt_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start(Programs_tB.Text);
        }

        private void Startup_bt_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start(Startup_tB.Text);
        }

        private void hosts_bt_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start(hosts_tB.Text);
        }
    }
}
