/* build.cmd: procedura x la compilazione di eseguibili */

arg debug
"@echo off"
"mode co80,102"
if debug = "" then do
   say;say;say
   say "Includere codice di debugging?"
   pull reply
   if reply = "S" then
      debug = "D"
end
if debug = "D" then do
   say "Il codice di debugging verr… incluso"
   "set debug=1"
   end /* do */
else
   "set debug=0"

call compile
call beep 440, 100
call beep 880, 200
call beep 440, 100

vernum = linein("build.ini") + 1
call lineout "build.ini", vernum, 1
call lineout "build.ini"
exit

compile:
   say
   say "------------------------------------------------------------------"
   "nmake -f attman.mak"
   if rc \= 0 then call tryagain
return   

tryagain:
   call beep 1440, 200
   say
   say "Apportare le opportune modifiche al listato e premere un tasto"
   say "qualsiasi per riprendere la compilazione."
   "PAUSE > nul"
   call compile
return
