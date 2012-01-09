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

	Class FireASP
		
		'Private variables 
		Private headerPrefix
		Private headerCounter
		Private protocolHeaderKeys(3)
		Private protocolHeaderVals(3)
		Private pageStartTime
		
		'Singleton Instance
		Private instance
		
		Private Sub Class_Initialize()
			pageStartTime = timer
			'Set the header prefix
			headerPrefix = "X-Wf-"
			
			headerCounter = 0
			
			protocolHeaderKeys(0) = "Protocol-1"
			protocolHeaderKeys(1) = "1-Plugin-1"
			protocolHeaderKeys(2) = "1-Structure-1"
			
			protocolHeaderVals(0) = "http://meta.wildfirehq.org/Protocol/JsonStream/0.2"
			protocolHeaderVals(1) = "http://meta.firephp.org/Wildfire/Plugin/FirePHP/Library-FirePHPCore/0.3"
			protocolHeaderVals(2) = "http://meta.firephp.org/Wildfire/Structure/FirePHP/FirebugConsole/0.1"
			
			'Turn on Page buffering
			Response.Buffer = True
			
			For i = 0 to 2
				
				'Response.Write protocolHeaders(i)
				Response.addHeader headerPrefix & protocolHeaderKeys(i), protocolHeaderVals(i) 
				
			next
			
		End Sub

		Private Sub Class_Terminate()
			firebugDump()

		end sub
		
		

		Public Function log( ByRef obj )
			dim str
			
			headerCounter= headerCounter + 1
			
			str= "|[{""Type"":""LOG""},"&toJson(obj)&"]|"
			msgLength = len(str) - 2
			str=msgLength&str						
			Response.addHeader headerPrefix & "1-1-1-" & headerCounter , str
		End Function

		Public Function log_type( logtype,label,ByRef obj )
			dim str
			
			headerCounter= headerCounter + 1
				      
			str= "|[{""Type"":"""&logtype&""",""Label"":"""&label&"""},"&toJson(obj)&"]|"
			msgLength = len(str) - 2
			str=msgLength&str						
			Response.addHeader headerPrefix & "1-1-1-" & headerCounter , str
		End Function

		Public Function log_group_start( label,Collapsed )
			dim str
			
			if Collapsed=true then Collapsed="true" else Collapsed="false"

			headerCounter= headerCounter + 1
				      
			str= "|[{""Type"":""GROUP_START"",""Label"":"""&label&""",""Collapsed"":"""&Collapsed&"""},"&toJson(obj)&"]|"
			msgLength = len(str) - 2
			str=msgLength&str						
			Response.addHeader headerPrefix & "1-1-1-" & headerCounter , str
		End Function

		Public Function log_group_end()
			dim str
			
			headerCounter= headerCounter + 1
				      
			str= "|[{""Type"":""GROUP_END""}]|"
			msgLength = len(str) - 2
			str=msgLength&str						
			Response.addHeader headerPrefix & "1-1-1-" & headerCounter , str
		End Function


		Public function firebugDump()

			dim str,lasterr
			
			

						
			set objErr=Server.GetLastError()
			if objErr.Number<>0 then 
				
				log_type "ERROR","","objErr.Number: "&objErr.Number
				log_type "ERROR","","err.Number: "&err.Number
				log_type "ERROR","","ERROR ON PAGE: "&objErr.file										
				log_type "ERROR","",err.Source
				log_type "ERROR","","Error: "&objErr.Description &" on line: "&objErr.line
				if objErr.column>1 then log_type "ERROR","","Column: "&objErr.column					
				if objErr.ASPDescription<>"" then log_type "ERROR","","Description: "&objErr.ASPDescription
			else
				log_type "INFO","SUCCESS","(Time taken: "&formatnumber((timer-pageStartTime)*1000,2)&"ms)"


			end if


			log_group_start "ASP System Collections",true


			'SESSION
			Set member = jsObject()
			for each str in session.contents
				member(str) = Session.Contents(str)
			next
			log_type "INFO","SESSION",member

			'POST
			Set member = jsObject()	
			for each str in request.form
				member(str) = request.form(str)
			next
			log_type "INFO","POST",member


			'GET
			Set member = jsObject()
			for each str in request.querystring
				member(str) = request.querystring(str)
			next
			log_type "INFO","GET",member

			'Application
			Set member = jsObject()	
			for each str in Application.Contents
				'response.write(vartype(application(str))&",")
				if vartype(application(str))<>8204 then
					member(str) = application.contents(str)
				else		
					member(str) = "Not shown"
				end if
			next
			log_type "INFO","APPLICATION",member

			'SERVER
			Set member = jsObject()
			for each str in Request.ServerVariables
				member(str) = request.ServerVariables(str)
			next
			log_type "INFO","SERVER",member

			log_group_end()


		end function
		


		'Get singleton instance
		Public Function getInstance
			
			If IsNull( instance ) then
				set instance = new FireASP
			End if
			
			getInstance = instance
			
		End Function
		
	End Class
	Set FIRE_ASP = new FireASP
	
	sub log( ByRef msg )		
		call FIRE_ASP.log(msg)
	end sub


	sub log_type( logtype,label,ByRef obj )		
		call FIRE_ASP.log_type(logtype,label,obj)
	end sub


	sub log_group_start( label,collapsed )
		call FIRE_ASP.log_group_start(label,collapsed)
	end sub

	sub log_group_end()
		call FIRE_ASP.log_group_end()
	end sub

	sub log_table(ByRef obj)
		call FIRE_ASP.log_type("TABLE","Array",obj)
	end sub



%>