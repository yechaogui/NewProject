Dim WshShell
Set WshShell=WScript.CreateObject("WScript.Shell")
WshShell.Run "notepad"
WScript.Sleep 2000   
WshShell.AppActivate "无标题 - 记事本"
WshShell.SendKeys "hello, welcome to cfan"
'WshShell.SendKeys "%{f4}"