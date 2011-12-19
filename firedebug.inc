<!--#include file="json/json.asp" -->
<%
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


		Public function firebugDump()

			dim str,lasterr
			

			log(".")
			log("----------------------------------------------------------------------------------------------------------------------------------------------------------------")	

			log("- Page terminated (time: "&timer-pageStartTime&")")
						
			set objErr=Server.GetLastError()
			if objErr.Number<>0 or err.number<>0 then 
				log("********************************************************")


				log("- "&err.Source)
				log("- File: "&objErr.file)						
				log("- Error: "&objErr.Description &" on line: "&objErr.line)
				if objErr.column>1 then log("- Column: "&objErr.column)						
				if objErr.ASPDescription<>"" then log("- Description: "&objErr.ASPDescription)
				log("********************************************************")

			end if

			log("----------------------------------------------------------------------------------------------------------------------------------------------------------------")	

			'SESSION
			log("Session Values")	
			Set member = jsObject()
			for each str in session.contents
				member(str) = Session.Contents(str)
			next
			log(member)
			log(".")


			'POST
			log("POST - Form")
			Set member = jsObject()	
			for each str in request.form
				member(str) = request.form(str)
			next
			log(member)
			log(".")


			'GET
			log("GET - Querystring")
			Set member = jsObject()
			for each str in request.querystring
				member(str) = request.querystring(str)
			next
			log(member)
			log(".")

			'Application
			log("Application Values")	
			Set member = jsObject()	
			for each str in Application.Contents
				'response.write(vartype(application(str))&",")
				if vartype(application(str))<>8204 then
					member(str) = application.contents(str)
				else		
					member(str) = "Not shown"
				end if
			next
			log(member)
			log(".")

			'SERVER
			log("Server values")
			Set member = jsObject()
			for each str in Request.ServerVariables
				member(str) = request.ServerVariables(str)
			next
			log(member)

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
	
	Function log( ByRef msg )
		
		FIRE_ASP.log( msg )
		
	End Function




%>