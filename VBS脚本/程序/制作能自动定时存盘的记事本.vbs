'��һ���֣���������Ͷ���
Dim WshShell, AutoSaveTime, TXTFileName
 AutoSaveTime=300
 Set WshShell=WScript.CreateObject("WScript.Shell")
 TXTFileName=InputBox("��������Ҫ�������ļ���(���������ĺʹ�����)��")
 '�ڶ����֣��򿪲�������±�
WshShell.Run "notepad"
 WScript.Sleep 200
 WshShell.AppActivate "�ޱ��� - ���±�"
 '�������֣���������ļ�������
WshShell.SendKeys "^s"
 WScript.Sleep 300
 WshShell.SendKeys TXTFileName
 WScript.Sleep 300
 WshShell.SendKeys "%s"
 WScript.Sleep AutoSaveTime
 '���Ĳ��֣��Զ���ʱ����
While WshShell.AppActivate (TXTFileName)=True
 WshShell.SendKeys "^s"
 WScript.Sleep AutoSaveTime
 Wend
 WScript.Quit