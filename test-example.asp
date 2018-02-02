<%@ LANGUAGE=VBScript CODEPAGE="65001"%>
<!--#include file="json/JSON.asp" -->
<!--#include file="firedebug.inc" -->
<%
'----------------------------------------------------------------------
'By David Meagor - BooRoo.com 2012 (http://booroo.com)
'
'released under MIT license (http://www.opensource.org/licenses/mit-license.php)
'
'requires json.asp (http://code.google.com/p/aspjson/ )
'----------------------------------------------------------------------

'Functions
'-----------
' log value
' log_type type,label,value
' log_group_start label,collapsed (true/false)
' log_group_end
' log_table array (requires 2 dimensional array)
'----------------------------------------------------------------------


response.write("check firebug console output for debugging info")

'string
log("Testing")


'array
dim hello(5,1)

hello(0,0)="Oranges"
hello(0,1)=1234
hello(0,0)="Oranges"
hello(1,0)="Apples"
hello(1,1)=852
hello(2,0)="Pears"
hello(2,1)=645

log hello 

'log 2 dimensional array as a table
log_table hello


'groups and icon types
log_group_start "My Group",false
	log_type "WARN","Some label","Message"
	log_type "ERROR","Some label","Message"
	log_type "INFO","Some label","Message"
log_group_end

'more complex json object
Dim member

Set details = jsObject()
details("Something") = "rah rah"

Set member = jsObject()
member("name") = "Jim"
member("surname") = "Smith"
member("message") = "Hello World"
set member("details") = details
log member



'uncomment to trigger error report
'a="b"*"c"


%>
