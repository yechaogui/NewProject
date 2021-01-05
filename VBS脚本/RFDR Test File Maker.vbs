'RFDR Test File Maker v1.00
Dim yecg_file_path,yecg_file_path_1,yecg_file_path_2
Msgbox "Welcome To RFDR Test File Maker"
'yecg_file_path_1=InputBox("Please input Flex sn")   '提示输入RFDR的Flex sn
'yecg_file_path_2=InputBox("Please input module sn") '提示输入RFDR的module sn
yecg_file_path_1=123   '输入RFDR的Flex sn
yecg_file_path_2=456   '输入RFDR的module sn
yecg_file_path=yecg_file_path_1&"+"&yecg_file_path_2
Dim yecg_fs,yecg_1,yecg_2
set yecg_fs=wscript.createobject("scripting.filesystemobject")
if yecg_fs.folderexists("D:\RFDR") then                 '判断要建立的文件夹是否存在
	yecg_1="is available"
'	MsgBox "RFDR文件夹已经存在！"
else 
	yecg_2="not exist"
	yecg_fs.createfolder("D:\RFDR")                     '不存在则创建RFDR文件夹
end If
if yecg_fs.folderexists("D:\RFDR\"&yecg_file_path) then '判断要建立的文件夹是否存在
	yecg_1="is available"
'	MsgBox "需要建立的"&yecg_file_path&"文件夹已经存在！"
else 
	yecg_2="not exist"
	yecg_fs.createfolder("D:\RFDR\"&yecg_file_path) '不存在则以Flex sn+module sn创建文件夹
end If
Dim yecg_dk
Set yecg_dk=CreateObject("WScript.shell")
yecg_dk.Run "D:\RFDR\"&yecg_file_path
Msgbox "请在已经打开的窗口中拷贝入客户提供的RFDR文件，拷贝完后点击确定进入下一步"
if (yecg_fs.folderexists("D:\RFDR\"&yecg_file_path&"\Conoscope_Files")) then               '判断Conoscope_Files文件夹是否存在
yecg_1="is available"
yecg_fs.CopyFile "D:\images\RftdrMap\*.*","D:\RFDR\"&yecg_file_path&"\Conoscope_Files"     '复制.cmx文件到指定目录,强制覆盖加",True"
else 
yecg_2="not exist"
Msgbox "未发现Conoscope_Files文件夹，请确认拷贝进入的RFDR文件是否正确！"
yecg_fs.deletefolder("D:\RFDR\"&yecg_file_path) '删除之前错误操作的文件夹
WScript.Quit '结束运行 
end If
'---------------获取文件夹下的.cmx文件名写入到Traceability_Log.csv文件中---------------
'指定文件夹路径
Dim yecg_sFolder
yecg_sFolder = "D:\RFDR\"&yecg_file_path&"\Conoscope_Files"
Dim yecg_oFolder,yecg_oFiles,yecg_file,yecg_files
set yecg_oFolder = yecg_fs.GetFolder(yecg_sFolder)          '获取文件夹
'set oSubFolders = oFolder.SubFolders                       '获取子目录集合
set yecg_oFiles = yecg_oFolder.Files                        '获取文件集合
'打开Traceability_Log.csv文件
Dim yecg_objExcel
Set yecg_objExcel = CreateObject("Excel.Application")
yecg_objExcel.Visible = True
yecg_objExcel.Workbooks.Open ("D:\RFDR\"&yecg_file_path&"\Traceability_Log.csv")
yecg_objExcel.Worksheets("Traceability_Log").Activate
'向Traceability_Log.csv文件写入9个文件名
yecg_i=2
for each yecg_file in yecg_oFiles
	yecg_files=yecg_file.Name                               '获取文件扩展名
	yecg_sExt=yecg_fs.GetExtensionName(yecg_file)           '获取文件扩展名
'	yecg_sExt = LCase(sExt)                                 '转换成小写
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
'---------------获取文件夹下的.cmx文件名写入到Traceability_Log.csv文件中---------------

'---------------运行结果分析软件---------------
'yecg_fs.CopyFile "D:\RFDR\"&yecg_file_path&"\Traceability_Log.csv"
'yecg_WshShell.Run "软件"
'yecg_WshShell.SendKeys "^v"