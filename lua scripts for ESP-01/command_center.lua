--Here is the command center
stop = false
                    
if( _G["init"] == true) then
    sk = net.createConnection(net.TCP,0)
    sk:connect(1080,"192.168.1.10")
    print("connection")
    _G["init"] = false;
end

sk:on("connection", function(sk, c) 
                print("Connected")
                
            end)               
sk:on("receive", function(sk, c) 
                    if(c == "breathing") then
                        dofile("breathing.lua")
                        --print("breathing")
                    else 
                        if(c == "blinking") then
                            dofile("blinking.lua")
                            --print("blinking")
                        else 
                            if(c == "magic") then
                                dofile("magic.lua")
                                --print("magic")
                            end
                        end
                    end
                end)
_G["first_message"]=true;
print("command")
