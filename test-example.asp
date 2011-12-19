<%@ LANGUAGE=VBScript CODEPAGE="65001"%>
<!--#include file="firedebug.inc" -->
<%
'---------------------------------------
'By David Meagor - BooRoo.com 2011
'
'released under MIT license (http://www.opensource.org/licenses/mit-license.php)
'
'requires json.asp (http://code.google.com/p/aspjson/ )
'
'based on FireASP by Jonathan Dalrymple (https://github.com/veritech/FireASP)
'---------------------------------------

response.write("check firebug console output for debugging info")

'string
log("Testing")


'array
dim hello(5,1)

hello(0,0)="Oranges"
hello(0,1)=1234
hello(1,0)="Apples"
hello(1,1)=852
hello(2,0)="Pears"
hello(2,1)=645

log(hello)




'more complex json object
Dim member

Set details = jsObject()
details("Something") = "rah rah"

Set member = jsObject()
member("name") = "Jim"
member("surname") = "Smith"
member("message") = "Hello World"
set member("details") = details
log(member)



'uncomment to trigger error report
'a="b"*"c"


%>