'Function ShowDriveType(drvpath)    
Dim fso, d, t    
Set fso = CreateObject("Scripting.FileSystemObject")    
'Set d = fso.GetDrive(drvpath)
Set d = fso.Drives    
Select Case d.DriveType        
Case 0: t = "未知"        
Case 1: t = "可移动"        
Case 2: t = "固定"        
Case 3: t = "网络"        
Case 4: t = "CD-ROM"        
Case 5: t = "RAM 磁盘"    
End Select    
ShowDriveType = "驱动器 " & d.DriveLetter & ": - " & t
'End Function