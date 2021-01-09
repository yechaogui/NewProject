using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace 文件夹同步助手
{
    static class Program
    {
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());

            #region test使用
            //public struct Student//结构体
            //{
            //    //声明变量
            //    //将此处的变量声明为public
            //    public string name;
            //    public int age;
            //    public string department;
            //    public char gender;

            //}

            //public class Program
            //{
            //    static void Main(string[] args)
            //    {
            //        Student abc = new Student();

            //    }
            //}
            #endregion
        }


    }
}
