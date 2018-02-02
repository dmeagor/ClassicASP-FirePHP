# Classic ASP debugging made slightly less painful

Debugging legacy Classic ASP scripts is a painful job.  This script will enable
you to use FirePHP (https://github.com/firephp/firephp-for-firefox-devtools) to 
log errors and messages to the Firefox console window.

It's particularly useful for catching errors and problems with AJAX/JSON requests
where outputting to the browser will break the JSON format.

released under MIT license (http://www.opensource.org/licenses/mit-license.php)

requires json.asp (http://code.google.com/p/aspjson/ )

inspired by FireASP by Jonathan Dalrymple's Fire ASP script


## Installation

1. Install FirePHP for FireFox (https://github.com/firephp/firephp-for-firefox-devtools)
2. You may have to first go to about:config and set xpinstall.signatures.required to false
3. Ensure both fireasp and json.asp are included in every page you wish to debug

## How it works

When you call the various log methods the script will attach additional headers to the 
response which will be interperated by the FirePHP extension and then displayed in
the firefox console.

If you are using ajax/json calls then you can log debugging into without breaking your 
front end.

## Use with sql queries

There is no built in support for SQL however we recommend you create some helper functions to store details of your ASP SQL queries into an array along with query times and success/fail status as they are called.  Then add some code into the class termination function to log out these results into an SQL log group.

## Group log entries functions

    log "hellow world" to output to the console
    
    log_group_start( label, collapsed )
        log "Some grouped text"
        log "Bla bla bla"
       log "and so on..."
    log_group_end()
    
    log_type( logtype,label, obj )
    ' logtype : "INFO", "ERROR", "LOG" or "WARN" for different colours/icons.
    ' label : add label to the variable/object you are about to output on the same line.
    ' obj : array, string, json object


## Disclaimer
This source was developed over a decade ago by BooRoo Limited, now known as [Shout.com](https://Shout.com).  We have long since migrated away to the C# .NET platform so this script is not maintained.  
