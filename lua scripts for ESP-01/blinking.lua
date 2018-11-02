print("in blinking")
sk:on("receive", function(sk, c) 
                    if(c == "stop") then
                        dofile("command_center.lua")
                        pwm.stop(_G["pin"])
                    end
                end)
pwm.setup(_G["pin"],1,512)
pwm.start(_G["pin"])



--dofile("command_center.lua")
