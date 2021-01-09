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
using System.Collections;

namespace 常用电脑路径
{
    public partial class 软件常用 : Form
    {
        public 软件常用()
        {
            InitializeComponent();
        }

        private void Adobe_bt_Click(object sender, EventArgs e)
        {
            ArrayList Adobe_ArrayList = new ArrayList();
            if (Adobe_cB1.Checked) Adobe_ArrayList.Add(Adobe_tB1.Text);
            if (Adobe_cB2.Checked) Adobe_ArrayList.Add(Adobe_tB2.Text);
            if (Adobe_cB3.Checked) Adobe_ArrayList.Add(Adobe_tB3.Text);
            if (Adobe_cB4.Checked) Adobe_ArrayList.Add(Adobe_tB4.Text);
            string Error_Path = "";
            //string[] Adobe_Array = tB_Adobe.Text.Split(',');
            foreach (string Adobe in Adobe_ArrayList)
            {
                if (Directory.Exists(Adobe))
                    System.Diagnostics.Process.Start(Adobe);
                else
                {
                    DialogResult dialogResult = MessageBox.Show("当前路径" + Adobe + "不存在!", "错误", MessageBoxButtons.OKCancel, MessageBoxIcon.Error);
                    if (dialogResult == DialogResult.OK)
                    {
                        Error_Path += Adobe + "\n";
                        MessageBox.Show(Error_Path, "如下路径还未打开：", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                }
            }
        }
    }
}
