print("magic")

music = {}

read_counter = 20
write_counter = 1
max_counter = 0
print("max_counter"..max_counter)
first_time = 0
time = 0

function smth()
    sk:send("0")
end

function play()
    if(first_time == 0) then
        --print(tmr.now()/1000000)  
        first_time = 1 
    end
    
    if(max_counter == 0) then
        if(read_counter<300) then
            if(music[read_counter] == nil) then 
                print(read_counter)
            else
                pwm.setduty(_G["pin"],music[read_counter])
            end
            read_counter = read_counter + 1
            --на 290 элементе запустить посылку сообщений
            if(read_counter == 290) then 
                if(write_counter <= 301) then
                    tmr.alarm(0,8,tmr.ALARM_AUTO,smth)
                end
            end
        else
            --если мы дошли до конца, а запись не идет
            --тогда останавливаемся.
            if(write_counter >= 301) then 
                tmr.stop(1)
                print(tmr.now()/1000000)
                print("light stop")
                dofile("command_center.lua")
            end
            print("300")
            read_counter = 1
            --print(tmr.now()/1000000)
        end
    else--если max_counter !=0
        --если данные ещё есть
        if(read_counter<max_counter) then
            if(music[read_counter] == nil) then 
                print(read_counter)
            else
                pwm.setduty(_G["pin"],music[read_counter])
            end
            read_counter = read_counter + 1
        else
            tmr.stop(1)
            print(tmr.now()/1000000)
            print("light stop")
            dofile("command_center.lua")
            --print(tmr.now()/1000000)
        end
    end
end

sk:on("receive", function(sk, c)
                    --print("received "..c)
                    --if(_G["first_message"]==false) then
                        if(c == "stop0") then--Если нажали кнопку стоп
                            print("stopped")
                            tmr.stop(0)--остановить таймеры
                            tmr.stop(1)
                            pwm.stop(_G["pin"])--отключить шим
                            dofile("command_center.lua")--перейти в командный центр
                        else
                            --print(c)
                            if(tonumber(c) == nil) then--если пришло не число
                                --sk:send("start")
                                print("stop")
                                if(write_counter == 1) then
                                    max_counter = 300
                                else
                                    max_counter = write_counter
                                end
                                print("Max counter "..max_counter)
                                tmr.stop(0)
                                print(tmr.now()/1000000)
                                write_counter = 301
                            else
                                music[write_counter] = tonumber(c)
                                write_counter = write_counter + 1
                                if(write_counter == 300) then
                                    tmr.stop(0)
                                    write_counter = 1
                                end
                            end
                        end
                    --else
                    --    _G["first_message"]=false;
                   -- end
                end)

                
pwm.setup(_G["pin"],1000,1)
pwm.start(_G["pin"])
--dofile("command_center.lua")
--через 1 секунду таймер запускает отсыл сообщений
tmr.alarm(2,1000,tmr.ALARM_SINGLE,function()
                                    tmr.alarm(0,8,tmr.ALARM_AUTO,smth)
                                    print("write start")
                                    print(tmr.now()/1000000)
                                    tmr.stop(2)
                                end)
--print(tmr.now()/1000000)
--через 3 секунды таймер запускает свет
tmr.alarm(3,3000,tmr.ALARM_SINGLE, function() 
                                        tmr.alarm(1,100,tmr.ALARM_AUTO,play)
                                        print("read start")
                                        print(tmr.now()/1000000)
                                        tmr.stop(3)
                                    end)
