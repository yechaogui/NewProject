'第一部分：定义变量和对象
Dim WshShell, AutoSaveTime, TXTFileName
 AutoSaveTime=300
 Set WshShell=WScript.CreateObject("WScript.Shell")
 TXTFileName=InputBox("请输入你要创建的文件名(不能用中文和纯数字)：")
 '第二部分：打开并激活记事本
WshShell.Run "notepad"
 WScript.Sleep 200
 WshShell.AppActivate "无标题 - 记事本"
 '第三部分：用输入的文件名存盘
WshShell.SendKeys "^s"
 WScript.Sleep 300
 WshShell.SendKeys TXTFileName
 WScript.Sleep 300
 WshShell.SendKeys "%s"
 WScript.Sleep AutoSaveTime
 '第四部分：自动定时存盘
While WshShell.AppActivate (TXTFileName)=True
 WshShell.SendKeys "^s"
 WScript.Sleep AutoSaveTime
 Wend
 WScript.Quit