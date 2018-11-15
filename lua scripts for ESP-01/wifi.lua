--WiFi Settup
wifi.setmode(wifi.STATION)
local cfg={}
cfg.ssid="Olegs2"
cfg.pwd="11112222"
cfg.save = false
wifi.sta.config(cfg)
collectgarbage()
print("wi-fi ready")
