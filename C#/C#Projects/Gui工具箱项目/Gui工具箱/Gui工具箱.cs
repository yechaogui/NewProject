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
    public partial class Gui工具箱_Form : Form
    {
        public Gui工具箱_Form()
        {
            InitializeComponent();
        }
        private void 退出QToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void 文件夹同步助手ToolStripMenuItem1_Click(object sender, EventArgs e)//显示相应工具窗口
        {
            文件夹同步助手.Form1 文件夹同步助手 = new 文件夹同步助手.Form1();//创建对象
            文件夹同步助手.Show();//显示对象
        }
    }
}
