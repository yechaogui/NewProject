'Function ShowDriveType(drvpath)    
Dim fso, d, t    
Set fso = CreateObject("Scripting.FileSystemObject")    
'Set d = fso.GetDrive(drvpath)
Set d = fso.Drives    
Select Case d.DriveType        
Case 0: t = "δ֪"        
Case 1: t = "���ƶ�"        
Case 2: t = "�̶�"        
Case 3: t = "����"        
Case 4: t = "CD-ROM"        
Case 5: t = "RAM ����"    
End Select    
ShowDriveType = "������ " & d.DriveLetter & ": - " & t
'End Function