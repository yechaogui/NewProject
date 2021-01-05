'RFDR 结果清除 v1.00
Dim yecg_file_path,yecg_file_path_1,yecg_file_path_2
Msgbox "Welcome To RFDR 结果清除"
'yecg_file_path_1=InputBox("Please input Flex sn")   '提示输入RFDR的Flex sn
'yecg_file_path_2=InputBox("Please input module sn") '提示输入RFDR的module sn
yecg_file_path_1=123   '输入RFDR的Flex sn
yecg_file_path_2=456   '输入RFDR的module sn
yecg_file_path=yecg_file_path_1&"+"&yecg_file_path_2
Dim yecg_fs,yecg_1,yecg_2
set yecg_fs=wscript.createobject("scripting.filesystemobject")
'Dim yecg_dk
'Set yecg_dk=CreateObject("WScript.shell")
'yecg_dk.Run "D:\RFDR\"&yecg_file_path
yecg_fs.deletefile "D:\RFDR\"&yecg_file_path&"\Conoscope_Files\*.*" '删除18个结果文件
'yecg_fs.deletefile "D:\RFDR\"&yecg_file_path&"\Conoscope_Files\*.*" '删除图像文件
Msgbox "RFDR 结果清除完成！"
WScript.Quit '结束运行