'RFDR Test File Maker v1.00
Dim yecg_file_path,yecg_file_path_1,yecg_file_path_2
Msgbox "Welcome To RFDR Test File Maker"
'yecg_file_path_1=InputBox("Please input Flex sn")   '��ʾ����RFDR��Flex sn
'yecg_file_path_2=InputBox("Please input module sn") '��ʾ����RFDR��module sn
yecg_file_path_1=123   '����RFDR��Flex sn
yecg_file_path_2=456   '����RFDR��module sn
yecg_file_path=yecg_file_path_1&"+"&yecg_file_path_2
Dim yecg_fs,yecg_1,yecg_2
set yecg_fs=wscript.createobject("scripting.filesystemobject")
if yecg_fs.folderexists("D:\RFDR") then                 '�ж�Ҫ�������ļ����Ƿ����
	yecg_1="is available"
'	MsgBox "RFDR�ļ����Ѿ����ڣ�"
else 
	yecg_2="not exist"
	yecg_fs.createfolder("D:\RFDR")                     '�������򴴽�RFDR�ļ���
end If
if yecg_fs.folderexists("D:\RFDR\"&yecg_file_path) then '�ж�Ҫ�������ļ����Ƿ����
	yecg_1="is available"
'	MsgBox "��Ҫ������"&yecg_file_path&"�ļ����Ѿ����ڣ�"
else 
	yecg_2="not exist"
	yecg_fs.createfolder("D:\RFDR\"&yecg_file_path) '����������Flex sn+module sn�����ļ���
end If
Dim yecg_dk
Set yecg_dk=CreateObject("WScript.shell")
yecg_dk.Run "D:\RFDR\"&yecg_file_path
Msgbox "�����Ѿ��򿪵Ĵ����п�����ͻ��ṩ��RFDR�ļ������������ȷ��������һ��"
if (yecg_fs.folderexists("D:\RFDR\"&yecg_file_path&"\Conoscope_Files")) then               '�ж�Conoscope_Files�ļ����Ƿ����
yecg_1="is available"
yecg_fs.CopyFile "D:\images\RftdrMap\*.*","D:\RFDR\"&yecg_file_path&"\Conoscope_Files"     '����.cmx�ļ���ָ��Ŀ¼,ǿ�Ƹ��Ǽ�",True"
else 
yecg_2="not exist"
Msgbox "δ����Conoscope_Files�ļ��У���ȷ�Ͽ��������RFDR�ļ��Ƿ���ȷ��"
yecg_fs.deletefolder("D:\RFDR\"&yecg_file_path) 'ɾ��֮ǰ����������ļ���
WScript.Quit '�������� 
end If
'---------------��ȡ�ļ����µ�.cmx�ļ���д�뵽Traceability_Log.csv�ļ���---------------
'ָ���ļ���·��
Dim yecg_sFolder
yecg_sFolder = "D:\RFDR\"&yecg_file_path&"\Conoscope_Files"
Dim yecg_oFolder,yecg_oFiles,yecg_file,yecg_files
set yecg_oFolder = yecg_fs.GetFolder(yecg_sFolder)          '��ȡ�ļ���
'set oSubFolders = oFolder.SubFolders                       '��ȡ��Ŀ¼����
set yecg_oFiles = yecg_oFolder.Files                        '��ȡ�ļ�����
'��Traceability_Log.csv�ļ�
Dim yecg_objExcel
Set yecg_objExcel = CreateObject("Excel.Application")
yecg_objExcel.Visible = True
yecg_objExcel.Workbooks.Open ("D:\RFDR\"&yecg_file_path&"\Traceability_Log.csv")
yecg_objExcel.Worksheets("Traceability_Log").Activate
'��Traceability_Log.csv�ļ�д��9���ļ���
yecg_i=2
for each yecg_file in yecg_oFiles
	yecg_files=yecg_file.Name                               '��ȡ�ļ���չ��
	yecg_sExt=yecg_fs.GetExtensionName(yecg_file)           '��ȡ�ļ���չ��
'	yecg_sExt = LCase(sExt)                                 'ת����Сд
	If yecg_sExt="cmx" then
	    yecg_objExcel.Cells(yecg_i,2)=yecg_files      
	    yecg_i=yecg_i+1
	End If
Next
Dim yecg_WshShell
Set yecg_WshShell=WScript.CreateObject("WScript.Shell")
yecg_WshShell.SendKeys "^s"
'WScript.Sleep 50
yecg_WshShell.SendKeys "y"
'WScript.Sleep 50
yecg_WshShell.SendKeys "%{f4}"
'WScript.Sleep 50
yecg_WshShell.SendKeys "n"
'yecg_objExcel.ActiveWorkbook.Save
'yecg_objExcel.ActiveWorkbook.Close
yecg_objExcel.Quit
'---------------��ȡ�ļ����µ�.cmx�ļ���д�뵽Traceability_Log.csv�ļ���---------------

'---------------���н���������---------------
'yecg_fs.CopyFile "D:\RFDR\"&yecg_file_path&"\Traceability_Log.csv"
'yecg_WshShell.Run "���"
'yecg_WshShell.SendKeys "^v"