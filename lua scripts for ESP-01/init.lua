--Yo, this is init file. LET'S MAKE IT BRIGHT IN HERE.
table = {}
_G["pin"] = 4
_G["init"] = true
dofile("wifi.lua")

--dofile("wifi.lua")
tmr.alarm(0,10000,tmr.ALARM_SINGLE,function()  
                                        dofile("command_center.lua") 
                                        end)
--dofile("command_center.lua")
print("init")
