'msgbox "Hello World!"
'msgbox "Hello World!" , , "ϵͳ��ʾ"
'==========================================
'Dim name
'name=inputbox("�������������:","����")
'msgbox name,,"����������"
'==========================================
'Dim objShell
'Set objShell = CreateObject("Wscript.Shell")
'objShell.Run "notepad"

'Set objShell = CreateObject("Wscript.Shell")
'objShell.Run "notepad"
'objShell.Run "calc"

'Set objShell = CreateObject("Wscript.Shell")
'objShell.Run "notepad" ,,true
'objShell.Run "calc"
'==========================================
on error resume next 
a=11 
b=0 
c=a/b 
if err.number<>0 then 
wscript.echo err.number & err.description & err.source 
end if
 
