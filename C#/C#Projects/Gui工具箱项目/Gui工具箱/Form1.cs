using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using 文件夹同步助手;

namespace Gui工具箱
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private void 退出QToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void 文件夹同步助手ToolStripMenuItem1_Click(object sender, EventArgs e)//显示相应工具窗口
        {
            文件夹同步助手.Form1 a = new 文件夹同步助手.Form1();
            a.Show();
        }
    }
}
