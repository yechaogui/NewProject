'msgbox "Hello World!"
'msgbox "Hello World!" , , "系统提示"
'==========================================
'Dim name
'name=inputbox("请输入你的名字:","名称")
'msgbox name,,"您的名字是"
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
 
