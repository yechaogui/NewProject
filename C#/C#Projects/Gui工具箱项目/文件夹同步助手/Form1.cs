using System;
using System.IO;
using System.Security.Cryptography.X509Certificates;
using System.Windows.Forms;
using Microsoft.Office.Interop.Excel;
using System.Threading;
using System.Linq;

namespace 文件夹同步助手
{

    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            //文件夹同步助手.Form1.Text = "文件夹同步助手 v1.0";//软件标题
            this.Text = "文件夹同步助手 v3.1";//软件标题

        }
        //public class 公用字段
        //{
        //    //int ycg_ii, ycg_jj;
        //    //float ycg_计时器;
        //    public string ycg_本地文件夹路径 = @"E:\yechaogui\Desktop\计算机\程序\C#\C#Projects\文件夹资料更新\本地文件夹\待同步文件夹";
        //    public string ycg_服务器文件夹路径 = @"E:\yechaogui\Desktop\计算机\程序\C#\C#Projects\文件夹资料更新\服务器文件夹\待同步文件夹";
        //    //Console.WriteLine(ycg_本地文件夹路径);
        //    //Console.WriteLine(ycg_服务器文件夹路径);
        //    //MessageBox.Show(ycg_本地文件夹路径, "弹窗提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
        //    //MessageBox.Show(ycg_服务器文件夹路径, "弹窗提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
        //}
        private void button1_Click(object sender, EventArgs e)//本地与服务器同步
        {
            string ycg_功能选择 = "同步";//功能选择
            触发进度条();
            //string ycg_本地文件夹路径 = @"E:\yechaogui\Desktop\计算机\程序\C#\C#Projects\文件夹资料更新\本地文件夹\待同步文件夹";
            //string ycg_服务器文件夹路径 = @"E:\yechaogui\Desktop\计算机\程序\C#\C#Projects\文件夹资料更新\服务器文件夹\待同步文件夹";
            DateTime ycg_BeforTime = System.DateTime.Now;
            string ycg_本地文件夹路径 = 文件夹路径最后去斜杠(textBox2.Text);
            textBox2.Text = ycg_本地文件夹路径;//修正路径
            string ycg_服务器文件夹路径 = 文件夹路径最后去斜杠(textBox3.Text);
            textBox3.Text = ycg_服务器文件夹路径;//修正路径
            文件夹是否存在(ycg_本地文件夹路径);
            文件夹是否存在(ycg_服务器文件夹路径);
            textBox1.Text = "";//清空操作记录内容
            //Console.WriteLine(ycg_本地文件夹路径);
            //Console.WriteLine(ycg_服务器文件夹路径);
            //MessageBox.Show(ycg_本地文件夹路径, "弹窗提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
            //MessageBox.Show(ycg_服务器文件夹路径, "弹窗提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
            //string 功能反馈1 = 当前文件夹下文件同步(ycg_本地文件夹路径);//调用功能
            //MessageBox.Show(功能反馈1, "弹窗提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
            //string 功能反馈2 = 当前文件夹下文件夹同步(ycg_本地文件夹路径);//调用功能
            //MessageBox.Show(功能反馈2, "弹窗提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
            当前文件夹下文件夹同步(ycg_本地文件夹路径, ycg_功能选择);//同步父层
            当前文件夹下文件同步(ycg_本地文件夹路径, ycg_功能选择);//同步父层
            Console.WriteLine(递归遍历子文件夹(ycg_本地文件夹路径, ycg_功能选择, "文件夹+文件"));//递归调用
            DateTime ycg_AfterTime = System.DateTime.Now;
            TimeSpan ycg_Time = ycg_AfterTime - ycg_BeforTime;
            progressBar1.PerformStep();//填充最后一次进度条
            textBox1.Text += "\r\n" + "同步完成！" + "\r\n" + "耗时：" + ycg_Time + "\r\n";
            MessageBox.Show("同步完成！" + "\n" + "耗时：" + ycg_Time, "完成", MessageBoxButtons.OKCancel, MessageBoxIcon.Asterisk);
        }
        private void button2_Click(object sender, EventArgs e)//本地上传至服务器
        {
            string ycg_功能选择 = "上传";//功能选择
            触发进度条();
            //string ycg_本地文件夹路径 = @"E:\yechaogui\Desktop\计算机\程序\C#\C#Projects\文件夹资料更新\本地文件夹\待同步文件夹";
            //string ycg_服务器文件夹路径 = @"E:\yechaogui\Desktop\计算机\程序\C#\C#Projects\文件夹资料更新\服务器文件夹\待同步文件夹";
            DateTime ycg_BeforTime = System.DateTime.Now;
            string ycg_本地文件夹路径 = 文件夹路径最后去斜杠(textBox2.Text);
            textBox2.Text = ycg_本地文件夹路径;//修正路径
            string ycg_服务器文件夹路径 = 文件夹路径最后去斜杠(textBox3.Text);
            textBox3.Text = ycg_服务器文件夹路径;//修正路径
            文件夹是否存在(ycg_本地文件夹路径);
            文件夹是否存在(ycg_服务器文件夹路径);
            textBox1.Text = "";//清空操作记录内
            //Console.WriteLine(ycg_本地文件夹路径);
            //Console.WriteLine(ycg_服务器文件夹路径);
            //MessageBox.Show(ycg_本地文件夹路径, "弹窗提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
            //MessageBox.Show(ycg_服务器文件夹路径, "弹窗提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
            //string 功能反馈1 = 当前文件夹下文件同步(ycg_本地文件夹路径);//调用功能
            //MessageBox.Show(功能反馈1, "弹窗提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
            //string 功能反馈2 = 当前文件夹下文件夹同步(ycg_本地文件夹路径);//调用功能
            //MessageBox.Show(功能反馈2, "弹窗提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
            当前文件夹下文件夹同步(ycg_本地文件夹路径, ycg_功能选择);//同步父层
            当前文件夹下文件同步(ycg_本地文件夹路径, ycg_功能选择);//同步父层
            Console.WriteLine(递归遍历子文件夹(ycg_本地文件夹路径, ycg_功能选择, "文件夹+文件"));//递归调用
            DateTime ycg_AfterTime = System.DateTime.Now;
            TimeSpan ycg_Time = ycg_AfterTime - ycg_BeforTime;
            progressBar1.PerformStep();//填充最后一次进度条
            textBox1.Text += "\r\n" + "同步完成！" + "\r\n" + "耗时：" + ycg_Time + "\r\n";
            MessageBox.Show("同步完成！" + "\n" + "耗时：" + ycg_Time, "完成", MessageBoxButtons.OKCancel, MessageBoxIcon.Asterisk);
        }
        private void button3_Click(object sender, EventArgs e)//服务器下载至本地
        {
            string ycg_功能选择 = "下载";//功能选择
            触发进度条();
            //string ycg_本地文件夹路径 = @"E:\yechaogui\Desktop\计算机\程序\C#\C#Projects\文件夹资料更新\本地文件夹\待同步文件夹";
            //string ycg_服务器文件夹路径 = @"E:\yechaogui\Desktop\计算机\程序\C#\C#Projects\文件夹资料更新\服务器文件夹\待同步文件夹";
            DateTime ycg_BeforTime = System.DateTime.Now;
            string ycg_本地文件夹路径 = 文件夹路径最后去斜杠(textBox2.Text);
            textBox2.Text = ycg_本地文件夹路径;//修正路径
            string ycg_服务器文件夹路径 = 文件夹路径最后去斜杠(textBox3.Text);
            textBox3.Text = ycg_服务器文件夹路径;//修正路径
            文件夹是否存在(ycg_本地文件夹路径);
            文件夹是否存在(ycg_服务器文件夹路径);
            textBox1.Text = "";//清空操作记录内
            //Console.WriteLine(ycg_本地文件夹路径);
            //Console.WriteLine(ycg_服务器文件夹路径);
            //MessageBox.Show(ycg_本地文件夹路径, "弹窗提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
            //MessageBox.Show(ycg_服务器文件夹路径, "弹窗提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
            //string 功能反馈1 = 当前文件夹下文件同步(ycg_本地文件夹路径);//调用功能
            //MessageBox.Show(功能反馈1, "弹窗提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
            //string 功能反馈2 = 当前文件夹下文件夹同步(ycg_本地文件夹路径);//调用功能
            //MessageBox.Show(功能反馈2, "弹窗提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
            当前文件夹下文件夹同步(ycg_本地文件夹路径, ycg_功能选择);//同步父层
            当前文件夹下文件同步(ycg_本地文件夹路径, ycg_功能选择);//同步父层
            Console.WriteLine(递归遍历子文件夹(ycg_本地文件夹路径, ycg_功能选择, "文件夹+文件"));//递归调用
            DateTime ycg_AfterTime = System.DateTime.Now;
            TimeSpan ycg_Time = ycg_AfterTime - ycg_BeforTime;
            progressBar1.PerformStep();//填充最后一次进度条
            textBox1.Text += "\r\n" + "同步完成！" + "\r\n" + "耗时：" + ycg_Time + "\r\n";
            MessageBox.Show("同步完成！" + "\n" + "耗时：" + ycg_Time, "完成", MessageBoxButtons.OKCancel, MessageBoxIcon.Asterisk);
        }
        private void button4_Click(object sender, EventArgs e)//选择本地文件夹
        {
            #region 启用文件夹选择
            ///*
            FolderBrowserDialog folderBrowserDialog = new FolderBrowserDialog();
            folderBrowserDialog.Description = "请选择本地文件夹";
            //folderBrowserDialog.RootFolder = textBox2.Text;
            folderBrowserDialog.SelectedPath = textBox2.Text;//设置起始目录
            folderBrowserDialog.ShowNewFolderButton = true;
            if (folderBrowserDialog.ShowDialog() == DialogResult.OK)
            {
                textBox2.Text = folderBrowserDialog.SelectedPath;
            }
            //*/
            #endregion
            #region 使用Office库插件实现(需要调入Microsoft Office 15.0 Object Library，Microsoft.Office.Interop.Excel这俩库)
            /*
            Microsoft.Office.Interop.Excel.Application app = new Microsoft.Office.Interop.Excel.Application();
            Microsoft.Office.Core.FileDialog fileDialog = app.get_FileDialog(Microsoft.Office.Core.MsoFileDialogType.msoFileDialogFolderPicker);
            fileDialog.InitialFileName = textBox2.Text; //选择初始路径
            int nres = fileDialog.Show();
            if (nres == -1) //ok
            {
                Microsoft.Office.Core.FileDialogSelectedItems selectedItems = fileDialog.SelectedItems;
                string[] selectedFolders = selectedItems.Cast<string>().ToArray();
                if (selectedFolders.Length > 0)
                {
                    textBox2.Text = selectedFolders[0];
                }
            }
            */
            #endregion
        }
        private void button5_Click(object sender, EventArgs e)//选择服务器文件夹
        {
            #region 启用文件夹选择
            ///*
            FolderBrowserDialog folderBrowserDialog = new FolderBrowserDialog();
            folderBrowserDialog.Description = "请选择服务器文件夹";
            //folderBrowserDialog.RootFolder = textBox3.Text;
            folderBrowserDialog.SelectedPath = textBox3.Text;//设置起始目录
            folderBrowserDialog.ShowNewFolderButton = true;
            if (folderBrowserDialog.ShowDialog() == DialogResult.OK)
            {
                textBox3.Text = folderBrowserDialog.SelectedPath;
            }
            //*/
            #endregion
            #region 使用Office库插件实现(需要调入Microsoft Office 15.0 Object Library，Microsoft.Office.Interop.Excel这俩库)
            /*
            Microsoft.Office.Interop.Excel.Application app = new Microsoft.Office.Interop.Excel.Application();
            Microsoft.Office.Core.FileDialog fileDialog = app.get_FileDialog(Microsoft.Office.Core.MsoFileDialogType.msoFileDialogFolderPicker);
            fileDialog.InitialFileName = textBox3.Text; //选择初始路径
            int nres = fileDialog.Show();
            if (nres == -1) //ok
            {
                Microsoft.Office.Core.FileDialogSelectedItems selectedItems = fileDialog.SelectedItems;
                string[] selectedFolders = selectedItems.Cast<string>().ToArray();
                if (selectedFolders.Length > 0)
                {
                    textBox3.Text = selectedFolders[0];
                }
            }
            */
            #endregion
        }
        private void button6_Click(object sender, EventArgs e)
        {
            string ycg_功能选择 = "同步";//功能选择
            触发进度条();
            //string ycg_本地文件夹路径 = @"E:\yechaogui\Desktop\计算机\程序\C#\C#Projects\文件夹资料更新\本地文件夹\待同步文件夹";
            //string ycg_服务器文件夹路径 = @"E:\yechaogui\Desktop\计算机\程序\C#\C#Projects\文件夹资料更新\服务器文件夹\待同步文件夹";
            DateTime ycg_BeforTime = System.DateTime.Now;
            string ycg_本地文件夹路径 = 文件夹路径最后去斜杠(textBox2.Text);
            textBox2.Text = ycg_本地文件夹路径;//修正路径
            string ycg_服务器文件夹路径 = 文件夹路径最后去斜杠(textBox3.Text);
            textBox3.Text = ycg_服务器文件夹路径;//修正路径
            文件夹是否存在(ycg_本地文件夹路径);
            文件夹是否存在(ycg_服务器文件夹路径);
            textBox1.Text = "";//清空操作记录内容
            //Console.WriteLine(ycg_本地文件夹路径);
            //Console.WriteLine(ycg_服务器文件夹路径);
            //MessageBox.Show(ycg_本地文件夹路径, "弹窗提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
            //MessageBox.Show(ycg_服务器文件夹路径, "弹窗提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
            //string 功能反馈1 = 当前文件夹下文件同步(ycg_本地文件夹路径);//调用功能
            //MessageBox.Show(功能反馈1, "弹窗提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
            //string 功能反馈2 = 当前文件夹下文件夹同步(ycg_本地文件夹路径);//调用功能
            //MessageBox.Show(功能反馈2, "弹窗提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
            当前文件夹下文件夹同步(ycg_本地文件夹路径, ycg_功能选择);//同步父层
            //当前文件夹下文件同步(ycg_本地文件夹路径, ycg_功能选择);//同步父层
            Console.WriteLine(递归遍历子文件夹(ycg_本地文件夹路径, ycg_功能选择, "文件夹"));//递归调用
            DateTime ycg_AfterTime = System.DateTime.Now;
            TimeSpan ycg_Time = ycg_AfterTime - ycg_BeforTime;
            progressBar1.PerformStep();//填充最后一次进度条
            textBox1.Text += "\r\n" + "同步完成！" + "\r\n" + "耗时：" + ycg_Time + "\r\n";
            MessageBox.Show("同步完成！" + "\n" + "耗时：" + ycg_Time, "完成", MessageBoxButtons.OKCancel, MessageBoxIcon.Asterisk);
        }
        #region 功能方法
        private void 文件夹是否存在(string 文件夹路径_形参)
        {
            string 文件夹路径_功能 = 文件夹路径_形参;
            if (Directory.Exists(文件夹路径_功能) == false)
            {
                MessageBox.Show("本地或服务器文件夹不存在，请确认后重试！", "错误提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Warning);
                System.Environment.Exit(0);//退出所有进程和窗口
            }
        }
        private string 文件夹路径最后去斜杠(string 文件夹路径_形参)
        {
            #region 判断路径最后一个字符是否为"\"
            string 文件夹路径_功能 = 文件夹路径_形参;
            Console.WriteLine(文件夹路径_功能.EndsWith("\\"));
            while (文件夹路径_功能.EndsWith("\\") == true)
            {
                文件夹路径_功能 = 文件夹路径_功能.Remove(文件夹路径_功能.Length - 1);//删除最后一个字符
                //MessageBox.Show(ycg_本地文件夹路径, "弹窗提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
            }
            return 文件夹路径_功能;
            #endregion
        }
        private string 计算服务器文件夹路径(string ycg_本地文件夹路径_形参)
        {
            string ycg_本地文件夹路径_功能 = ycg_本地文件夹路径_形参;
            string ycg_本地文件夹路径 = 文件夹路径最后去斜杠(textBox2.Text);
            string 服务器文件夹路径_功能 = 文件夹路径最后去斜杠(textBox3.Text);
            //MessageBox.Show(ycg_本地文件夹路径.Length, "回显", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
            if (ycg_本地文件夹路径_功能.Length - ycg_本地文件夹路径.Length == 0)
            {
                //服务器文件夹路径_功能 = 服务器文件夹路径_功能;
            }
            else
            {
                string ycg_子文件夹段 = ycg_本地文件夹路径_功能.Substring(ycg_本地文件夹路径.Length);//Right函数功能
                服务器文件夹路径_功能 = 服务器文件夹路径_功能 + ycg_子文件夹段;
                //MessageBox.Show(服务器文件夹路径_功能, "计算后的服务器文件夹路径", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
                Console.WriteLine("计算后的服务器文件夹路径：" + 服务器文件夹路径_功能);
            }
            return 服务器文件夹路径_功能;
        }
        private string 当前文件夹下文件同步(string ycg_本地文件夹路径_形参, string ycg_功能选择_形参)
        {
            string ycg_本地文件夹路径_功能 = ycg_本地文件夹路径_形参;
            string ycg_服务器文件夹路径_功能 = 计算服务器文件夹路径(ycg_本地文件夹路径_功能);
            //MessageBox.Show("开始调用 当前文件夹下文件同步 功能！", "功能提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
            //MessageBox.Show(ycg_本地文件夹路径_功能 + "\n" + ycg_服务器文件夹路径_功能, "准备要执行同步的文件夹路径", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
            //var file;
            string[] 本地_files = Directory.GetFiles(ycg_本地文件夹路径_功能);
            if (Directory.Exists(ycg_服务器文件夹路径_功能) == false)//判断服务器是否存在本地同名文件夹
            {
                return "服务器不存在相应的本地文件夹！";
            }
            string[] 服务器_files = Directory.GetFiles(ycg_服务器文件夹路径_功能);
            #region 文件夹下无文件
            Console.WriteLine(本地_files.GetUpperBound(0));
            Console.WriteLine(服务器_files.GetUpperBound(0));
            if (本地_files.GetUpperBound(0) == -1 && 服务器_files.GetUpperBound(0) != -1)
            {
                if (ycg_功能选择_形参 == "同步" || ycg_功能选择_形参 == "下载")
                {
                    foreach (string 服务器_file in 服务器_files)
                    {
                        if (textBox4.Text.ToLower().Contains(Path.GetExtension(服务器_file).ToLower().Remove(0, 1)) == false)//文件过滤器
                        {
                            Console.WriteLine("即将要复制的文件为：" + Path.GetFileName(服务器_file));//回显
                            File.Copy(服务器_file, ycg_本地文件夹路径_功能 + "\\" + Path.GetFileName(服务器_file), true);
                            Console.WriteLine("服务器文件 " + Path.GetFileName(服务器_file) + " 下载成功！");
                            textBox1.Text += "服务器文件 " + Path.GetFileName(服务器_file) + " 下载成功！" + "\r\n";
                        }
                    }
                }
            }
            else if (服务器_files.GetUpperBound(0) == -1 && 本地_files.GetUpperBound(0) != -1)
            {
                if (ycg_功能选择_形参 == "同步" || ycg_功能选择_形参 == "上传")
                {
                    foreach (string 本地_file in 本地_files)
                    {
                        if (textBox4.Text.ToLower().Contains(Path.GetExtension(本地_file).ToLower().Remove(0, 1)) == false)//文件过滤器
                        {
                            Console.WriteLine("即将要复制的文件为：" + Path.GetFileName(本地_file));//回显
                            File.Copy(本地_file, ycg_服务器文件夹路径_功能 + "\\" + Path.GetFileName(本地_file), true);
                            Console.WriteLine("本地文件 " + Path.GetFileName(本地_file) + " 上传成功！");
                            textBox1.Text += "本地文件 " + Path.GetFileName(本地_file) + " 上传成功！" + "\r\n";
                        }
                    }
                }
            }
            else if (本地_files.GetUpperBound(0) == -1 && 服务器_files.GetUpperBound(0) == -1)
            {
                return "文件夹下无文件！";
            }
            #endregion
            #region 文件同步
            foreach (string 本地_file in 本地_files)//file带路径
            {
                int ycg_j = 0;
                if (textBox4.Text.ToLower().Contains(Path.GetExtension(本地_file).ToLower().Remove(0, 1)) == false)//文件过滤器
                {
                    foreach (string 服务器_file in 服务器_files)//file带路径
                    {
                        if (Path.GetFileName(本地_file) == Path.GetFileName(服务器_file))
                        {
                            //Console.WriteLine(Path.GetFileName(本地_file));
                            //MessageBox.Show(Path.GetFileName(本地_file));
                            //MessageBox.Show(Path.GetFileName(服务器_file));

                            if (Directory.GetLastWriteTime(本地_file) == Directory.GetLastWriteTime(服务器_file))
                            {
                                break;
                            }
                            else if (Directory.GetLastWriteTime(本地_file) > Directory.GetLastWriteTime(服务器_file))
                            {
                                if (ycg_功能选择_形参 == "同步" || ycg_功能选择_形参 == "上传")
                                {
                                    Console.WriteLine("即将要复制的文件为：" + Path.GetFileName(本地_file));//回显
                                    File.SetAttributes(服务器_file, FileAttributes.Normal);//即将覆盖的文件属性设计成正常
                                    File.Copy(本地_file, 服务器_file, true);//本地覆盖服务器同名文件,不能对只读属性文件进行覆盖！
                                    Console.WriteLine("本地文件 " + Path.GetFileName(本地_file) + " 上传成功！");
                                    textBox1.Text += "本地文件 " + Path.GetFileName(本地_file) + " 上传成功！" + "\r\n";
                                    break;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            else if (Directory.GetLastWriteTime(本地_file) < Directory.GetLastWriteTime(服务器_file))
                            {
                                if (ycg_功能选择_形参 == "同步" || ycg_功能选择_形参 == "下载")
                                {
                                    Console.WriteLine("即将要复制的文件为：" + Path.GetFileName(服务器_file));//回显
                                    File.SetAttributes(本地_file, FileAttributes.Normal);//即将覆盖的文件属性设计成正常
                                    File.Copy(服务器_file, 本地_file, true);//服务器覆盖本地同名文件，不能对只读属性文件进行覆盖！
                                    Console.WriteLine("服务器文件 " + Path.GetFileName(服务器_file) + " 下载成功！");
                                    textBox1.Text += "服务器文件 " + Path.GetFileName(服务器_file) + " 下载成功！" + "\r\n";
                                    break;
                                }
                                else
                                {
                                    break;
                                }
                            }
                        }
                        else if (ycg_j == 服务器_files.GetUpperBound(0))//本地文件未在服务器中找到
                        {
                            if (ycg_功能选择_形参 == "同步" || ycg_功能选择_形参 == "上传")
                            {
                                Console.WriteLine("即将要复制的文件为：" + Path.GetFileName(本地_file));//回显
                                File.Copy(本地_file, ycg_服务器文件夹路径_功能 + "\\" + Path.GetFileName(本地_file), true);
                                Console.WriteLine("本地文件 " + Path.GetFileName(本地_file) + " 上传成功！");
                                textBox1.Text += "本地文件 " + Path.GetFileName(本地_file) + " 上传成功！" + "\r\n";
                                break;
                            }
                            else
                            {
                                break;
                            }
                        }
                        ycg_j = ycg_j + 1;
                    }
                }
            }
            #endregion

            #region 文件下载
            if (ycg_功能选择_形参 == "同步" || ycg_功能选择_形参 == "下载")
            {
                foreach (string 服务器_file in 服务器_files)
                {
                    int ycg_i = 0;
                    if (textBox4.Text.ToLower().Contains(Path.GetExtension(服务器_file).ToLower().Remove(0, 1)) == false)//文件过滤器
                    {
                        foreach (string 本地_file in 本地_files)
                        {
                            if (Path.GetFileName(服务器_file) == Path.GetFileName(本地_file))
                            {
                                break;
                            }
                            else if (ycg_i == 本地_files.GetUpperBound(0))
                            {
                                Console.WriteLine("即将有复制的文件为：" + Path.GetFileName(服务器_file));//回显
                                File.Copy(服务器_file, ycg_本地文件夹路径_功能 + "\\" + Path.GetFileName(服务器_file), true);
                                Console.WriteLine("服务器文件 " + Path.GetFileName(服务器_file) + " 下载成功！");
                                textBox1.Text += "服务器文件 " + Path.GetFileName(服务器_file) + " 下载成功！" + "\r\n";
                                break;
                            }
                            ycg_i = ycg_i + 1;
                        }
                    }
                }
            }
            #endregion
            return "调用 当前文件夹下文件同步 方法成功！";
        }
        private string 当前文件夹下文件夹同步(string ycg_本地文件夹路径_形参, string ycg_功能选择_形参)
        {
            string ycg_本地文件夹路径_功能 = ycg_本地文件夹路径_形参;
            string ycg_服务器文件夹路径_功能 = 计算服务器文件夹路径(ycg_本地文件夹路径_功能);
            //MessageBox.Show("开始调用 当前文件夹下文件夹同步 功能！", "功能提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
            //MessageBox.Show(ycg_本地文件夹路径_功能 + "\n" + ycg_服务器文件夹路径_功能, "准备要执行同步的文件夹路径", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
            Console.WriteLine("准备要执行同步的文件夹路径" + "\n" + ycg_本地文件夹路径_功能 + "\n" + ycg_服务器文件夹路径_功能);
            string[] 本地_folders = Directory.GetDirectories(ycg_本地文件夹路径_功能);
            if (Directory.Exists(ycg_服务器文件夹路径_功能) == false)//判断服务器是否存在本地同名文件夹
            {
                return "服务器不存在相应的本地文件夹！";
            }
            string[] 服务器_folders = Directory.GetDirectories(ycg_服务器文件夹路径_功能);
            #region 文件夹下无子文件夹
            Console.WriteLine(本地_folders.GetUpperBound(0));
            Console.WriteLine(服务器_folders.GetUpperBound(0));
            if (本地_folders.GetUpperBound(0) == -1 && 服务器_folders.GetUpperBound(0) != -1)
            {
                if (ycg_功能选择_形参 == "同步" || ycg_功能选择_形参 == "下载")
                {
                    foreach (string 服务器_folder in 服务器_folders)
                    {
                        string[] 子文件夹段数组 = 服务器_folder.Split('\\');
                        string 子文件夹段 = 子文件夹段数组[子文件夹段数组.GetUpperBound(0)];
                        Console.WriteLine("即将有创建的文件夹：" + 子文件夹段);
                        //Directory.CreateDirectory(ycg_本地文件夹路径_功能 + "\\" + Path.GetFileNameWithoutExtension(服务器_folder));//创建文件夹，路径过长，需要解决
                        Directory.CreateDirectory(ycg_本地文件夹路径_功能 + "\\" + 子文件夹段);//创建文件夹
                        Console.WriteLine("服务器文件夹 " + 子文件夹段 + " 下载成功！");
                        textBox1.Text += "服务器文件夹 " + 子文件夹段 + " 下载成功！" + "\r\n";
                    }
                }
            }
            else if (服务器_folders.GetUpperBound(0) == -1 && 本地_folders.GetUpperBound(0) != -1)
            {
                if (ycg_功能选择_形参 == "同步" || ycg_功能选择_形参 == "上传")
                {
                    foreach (string 本地_folder in 本地_folders)
                    {
                        string[] 子文件夹段数组 = 本地_folder.Split('\\');
                        string 子文件夹段 = 子文件夹段数组[子文件夹段数组.GetUpperBound(0)];
                        Console.WriteLine("即将有创建的文件夹：" + 子文件夹段);
                        //Directory.CreateDirectory(ycg_服务器文件夹路径_功能 + "\\" + Path.GetFileNameWithoutExtension(本地_folder));////创建文件夹，路径过长，需要解决
                        Directory.CreateDirectory(ycg_服务器文件夹路径_功能 + "\\" + 子文件夹段);//创建文件夹
                        Console.WriteLine("本地文件夹 " + 子文件夹段 + " 上传成功！");
                        textBox1.Text += "本地文件夹 " + 子文件夹段 + " 上传成功！" + "\r\n";
                    }
                }
            }
            else if (本地_folders.GetUpperBound(0) == -1 && 服务器_folders.GetUpperBound(0) == -1)
            {
                return "文件夹下无子文件夹！";
            }
            #endregion
            #region 本地文件夹上传
            if (ycg_功能选择_形参 == "同步" || ycg_功能选择_形参 == "上传")
            {
                foreach (string 本地_folder in 本地_folders)
                {
                    int ycg_j = 0;
                    foreach (string 服务器_folder in 服务器_folders)
                    {
                        if (Path.GetFileNameWithoutExtension(本地_folder) == Path.GetFileNameWithoutExtension(服务器_folder))
                        {
                            break;
                        }
                        else if (ycg_j == 服务器_folders.GetUpperBound(0))
                        {
                            string 子文件夹段 = 获取路径中最后一个文件或文件夹名(本地_folder);
                            Console.WriteLine("即将有创建的文件夹：" + 子文件夹段);
                            Directory.CreateDirectory(ycg_服务器文件夹路径_功能 + "\\" + 子文件夹段);//创建文件夹
                            //Directory.CreateDirectory(ycg_服务器文件夹路径_功能 + "\\" + Path.GetFileNameWithoutExtension(本地_folder));//创建文件夹
                            Console.WriteLine("本地文件夹 " + 子文件夹段 + " 上传成功！");
                            textBox1.Text += "本地文件夹 " + 子文件夹段 + " 上传成功！" + "\r\n";
                            break;
                        }
                        ycg_j++;
                    }
                }
            }
            #endregion
            #region 服务器文件夹下载
            if (ycg_功能选择_形参 == "同步" || ycg_功能选择_形参 == "下载")
            {
                foreach (string 服务器_folder in 服务器_folders)
                {
                    int ycg_i = 0;
                    foreach (string 本地_folder in 本地_folders)
                    {
                        if (Path.GetFileNameWithoutExtension(服务器_folder) == Path.GetFileNameWithoutExtension(本地_folder))
                        {
                            break;
                        }
                        else if (ycg_i == 本地_folders.GetUpperBound(0))
                        {
                            string 子文件夹段 = 获取路径中最后一个文件或文件夹名(服务器_folder);
                            Console.WriteLine("即将有创建的文件夹：" + 子文件夹段);
                            Directory.CreateDirectory(ycg_本地文件夹路径_功能 + "\\" + 子文件夹段);//创建文件夹
                            //Directory.CreateDirectory(ycg_本地文件夹路径_功能 + Path.GetFileNameWithoutExtension(服务器_folder));//创建文件夹
                            Console.WriteLine("服务器文件夹 " + 子文件夹段 + " 下载成功！");
                            textBox1.Text += "服务器文件夹 " + 子文件夹段 + " 下载成功！" + "\r\n";
                            break;
                        }
                        ycg_i++;
                    }
                }
            }
            #endregion
            return "调用 当前文件夹下文件夹同步 方法成功！";
        }
        private string 递归遍历子文件夹(string 文件夹路径, string ycg_功能选择_形参, string ycg_文件夹_文件)//递归调用
        {
            #region 递归调用实现遍历文件夹下的子文件夹
            string[] folders = Directory.GetDirectories(文件夹路径);
            foreach (string folder in folders)
            {
                if (ycg_文件夹_文件 == "文件夹")
                {
                    当前文件夹下文件夹同步(folder, ycg_功能选择_形参);
                }
                //else if(ycg_文件夹_文件 == "文件")
                //{
                //    当前文件夹下文件同步(folder, ycg_功能选择_形参);
                //}
                else if (ycg_文件夹_文件 == "文件夹+文件")
                {
                    当前文件夹下文件夹同步(folder, ycg_功能选择_形参);
                    当前文件夹下文件同步(folder, ycg_功能选择_形参);
                }
                递归遍历子文件夹(folder, ycg_功能选择_形参, ycg_文件夹_文件);//递归调用
            }
            return "递归调用成功！";
            #endregion
        }
        private void 触发进度条()
        {
            // 显示进度条控件.
            progressBar1.Visible = true;
            // 设置进度条最小值.
            progressBar1.Minimum = 0;
            // 设置进度条最大值.
            progressBar1.Maximum = 100;
            // 设置进度条初始值
            progressBar1.Value = 10;
            // 设置每次增加的步长
            progressBar1.Step = 10;

            // 循环执行
            for (int x = 1; x <= 10; x++)
            {
                // 每次循环让程序休眠300毫秒
                System.Threading.Thread.Sleep(100);
                // 执行PerformStep()函数
                progressBar1.PerformStep();
            }
            //progressBar1.Visible = false;
            //MessageBox.Show("success!");
        }
        /*
        public string 同步文件夹及文件(string 源文件夹路径, string 目标文件夹路径)
        {
            try
            {
                //如果目标路径不存在,则创建目标路径
                if (!Directory.Exists(目标文件夹路径))
                {
                    Directory.CreateDirectory(目标文件夹路径);
                }
                //得到原文件根目录下的所有文件
                string[] files = Directory.GetFiles(源文件夹路径);
                foreach (string file in files)
                {
                    string name = Path.GetFileName(file);
                    string dest = Path.Combine(目标文件夹路径, name);
                    File.Copy(file, dest);//复制文件
                }
                //得到原文件根目录下的所有文件夹
                string[] folders = Directory.GetDirectories(源文件夹路径);
                foreach (string folder in folders)
                {
                    string name = Path.GetFileName(folder);
                    string dest = Path.Combine(目标文件夹路径, name);
                    同步文件夹及文件(folder, dest);//构建目标路径,递归实现
                }
                return "文件夹复制操作成功！";
            }
            catch (Exception e)
            {
                //MessageBox.Show(e.Message);
                return "文件夹复制操作失败！";
            }

        }
        */
        #endregion

        #region 子功能方法
        private string 获取路径中最后一个文件或文件夹名(string 文件夹路径)
        {
            string[] 文件夹数组 = 文件夹路径.Split('\\');
            string 最后一个文件或文件夹名 = 文件夹数组[文件夹数组.GetUpperBound(0)];
            return 最后一个文件或文件夹名;
        }


        #endregion


    }



}

