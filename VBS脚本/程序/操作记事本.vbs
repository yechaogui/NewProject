Dim WshShell
Set WshShell=WScript.CreateObject("WScript.Shell")
WshShell.Run "notepad"
WScript.Sleep 2000   
WshShell.AppActivate "�ޱ��� - ���±�"
WshShell.SendKeys "hello, welcome to cfan"
'WshShell.SendKeys "%{f4}"