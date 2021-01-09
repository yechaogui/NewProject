using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;

namespace FunctionClassLibrary
{
    public class FunctionClassLibrary
    {
        private string _folderPath;
        public string FolderPath//访问器/封装字段
        {
            get
            {
                return _folderPath;
            }
            set
            {
                if (value != "")//限定取值
                {
                    _folderPath = value;
                }
                else
                {
                    _folderPath = "空值";
                }
            }
        }
        private string _onoff;
        public string Onoff//自动封装字段
        {
            get;
            set;
        }
        public FunctionClassLibrary()//不带参数的构造函数(重写系统自动添加的构造函数)
        {

        }
        public FunctionClassLibrary(string 参数1, string 参数2)//带参数的构造函数
        {
            this.FolderPath = 参数1;
            this.Onoff = 参数2;
        }
        ~FunctionClassLibrary()//析构函数，释放对象
        {
            Console.WriteLine("我是析构函数,看我什么时候调用！");
            //在使用完当前类的时候会调用它
        }

        public Boolean 判断文件夹是否存在(string 文件夹路径)
        {
            if (Directory.Exists(文件夹路径))
            {
                Console.WriteLine("路径存在！");
                return true;
            }
            else
            {
                Console.WriteLine("路径不存在！");
                return false;
            }
        }
        public void 文件路径去最后斜杠(string 文件夹路径)
        {

        }
/*        public string textBox_name提示文字(string textBox_name,out string 提示内容)
        {
            Boolean textboxHasText = false;//判断输入框是否有文本

            //textBox_name获得焦点
            private void Textbox_Enter(object sender, EventArgs e)
            {
                if (textboxHasText == false)
                    textBox_name.Text = "";

                textBox_name.ForeColor = Color.Black;
            }
            //textBox_name失去焦点
            private void Textbox_Leave(object sender, EventArgs e)
            {
                if (textBox_name.Text == "")
                {
                    textBox_name.Text = 提示内容;
                    textBox_name.ForeColor = Color.LightGray;
                    textboxHasText = false;
                }
                else
                    textboxHasText = true;
            }
        }*/
    }


}