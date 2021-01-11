using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace 注册表修改工具
{
    public partial class 注册表修改工具 : Form
    {
        public 注册表修改工具()
        {
            InitializeComponent();
        }

        private void OpenReg_bt_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start(RegPath_tB.Text);
        }

    }
}
