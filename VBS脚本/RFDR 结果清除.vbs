'RFDR ������ v1.00
Dim yecg_file_path,yecg_file_path_1,yecg_file_path_2
Msgbox "Welcome To RFDR ������"
'yecg_file_path_1=InputBox("Please input Flex sn")   '��ʾ����RFDR��Flex sn
'yecg_file_path_2=InputBox("Please input module sn") '��ʾ����RFDR��module sn
yecg_file_path_1=123   '����RFDR��Flex sn
yecg_file_path_2=456   '����RFDR��module sn
yecg_file_path=yecg_file_path_1&"+"&yecg_file_path_2
Dim yecg_fs,yecg_1,yecg_2
set yecg_fs=wscript.createobject("scripting.filesystemobject")
'Dim yecg_dk
'Set yecg_dk=CreateObject("WScript.shell")
'yecg_dk.Run "D:\RFDR\"&yecg_file_path
yecg_fs.deletefile "D:\RFDR\"&yecg_file_path&"\Conoscope_Files\*.*" 'ɾ��18������ļ�
'yecg_fs.deletefile "D:\RFDR\"&yecg_file_path&"\Conoscope_Files\*.*" 'ɾ��ͼ���ļ�
Msgbox "RFDR ��������ɣ�"
WScript.Quit '��������