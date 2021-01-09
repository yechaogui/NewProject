using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Text;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using FunctionClassLibrary;
using System.IO;
using System.Collections;

namespace 常用电脑路径
{
    public partial class 常用电脑路径 : Form
    {
        public 常用电脑路径()
        {
            InitializeComponent();
        }
        /*#region 文件框提示
        Boolean textboxHasText = false;//判断输入框是否有文本
        //textBox获得焦点
        private void Textbox_Enter(object sender, EventArgs e)
        {
            if (textboxHasText == false)
            {
                tB_OpenPath.Text = "";
                tB_OpenPath.ForeColor = Color.Black;
            }
        }
        //textBox失去焦点
        private void Textbox_Leave(object sender, EventArgs e)
        {
            if (tB_OpenPath.Text == "")
            {
                tB_OpenPath.Text = "打开多个路径，使用英文\",\"隔开";
                tB_OpenPath.ForeColor = Color.LightGray;
                textboxHasText = false;
            }
            else
                textboxHasText = true;
        }
        #endregion*/
        private void bt_OpenPath_Click(object sender, EventArgs e)
        {
            ArrayList OpenPath_ArrayList = new ArrayList();//获取选中状态的路径
            if (OpenPath_cB1.Checked) OpenPath_ArrayList.Add(OpenPath_tB1.Text);
            if (OpenPath_cB2.Checked) OpenPath_ArrayList.Add(OpenPath_tB2.Text);
            if (OpenPath_cB3.Checked) OpenPath_ArrayList.Add(OpenPath_tB3.Text);
            if (OpenPath_cB4.Checked) OpenPath_ArrayList.Add(OpenPath_tB4.Text);
            if (OpenPath_cB5.Checked) OpenPath_ArrayList.Add(OpenPath_tB5.Text);
            if (OpenPath_cB6.Checked) OpenPath_ArrayList.Add(OpenPath_tB6.Text);
            if (OpenPath_cB7.Checked) OpenPath_ArrayList.Add(OpenPath_tB7.Text);
            if (OpenPath_cB8.Checked) OpenPath_ArrayList.Add(OpenPath_tB8.Text);
            if (OpenPath_cB9.Checked) OpenPath_ArrayList.Add(OpenPath_tB9.Text);
            if (OpenPath_cB10.Checked) OpenPath_ArrayList.Add(OpenPath_tB10.Text);
            string Error_Path = "";
            //string[] OpenPath_Array = tB_OpenPath.Text.Split(',');
            foreach (string OpenPath in OpenPath_ArrayList)
            {
                if (Directory.Exists(OpenPath))
                    System.Diagnostics.Process.Start(OpenPath);
                else
                {
                    DialogResult dialogResult = MessageBox.Show("当前路径" + OpenPath + "不存在!", "错误", MessageBoxButtons.OKCancel, MessageBoxIcon.Error);
                    if (dialogResult == DialogResult.OK)
                    {
                        Error_Path += OpenPath + "\n";
                        MessageBox.Show(Error_Path, "如下路径还未打开：", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                }
            }
        }
        private void 系统常用_TSMt_Click(object sender, EventArgs e)
        {
            系统常用 系统常用 = new 系统常用();
            系统常用.Show();
        }

        private void 软件常用_TSMt_Click(object sender, EventArgs e)
        {
            软件常用 软件常用 = new 软件常用();
            软件常用.Show();
        }
    }
}
