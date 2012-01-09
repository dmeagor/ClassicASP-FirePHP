----------------------------------------------------------------------------------

Install Firebug and FirePHP before running and check firebug console for output
__________________________________________________________________________________

By David Meagor - BooRoo.com 2012 (http://booroo.com)

We use this for internal testing since clasic ASP's one debugging is so terrible.
It's particularly useful for catching errors and problems with AJAX/JSON requests
where outputting to the browser will break the JSON format.

released under MIT license (http://www.opensource.org/licenses/mit-license.php)

requires json.asp (http://code.google.com/p/aspjson/ )

inspired by FireASP by Jonathan Dalrymple's Fire ASP script
----------------------------------------------------------------------------------

Updated 09/01/2012

Improvement: 
All ASP system collections are now grouped (collapsed by default) so they only
take up one line on the console.

Added:

Group log entries functions
log_group_start( label, collapsed )
log_group_end()

log_type( logtype,label, obj )
logtype = "INFO", "ERROR", "LOG" or "WARN" for different colours/icons.
label = add label to the variable/object you are about to output on the same line.
obj = array, string, json object


Initial release: Dec 2011

Use log "some text" to output to the console
