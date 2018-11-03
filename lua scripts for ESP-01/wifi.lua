--WiFi Settup
wifi.setmode(wifi.STATION)
local cfg={}
cfg.ssid="Olegs2"
cfg.pwd="1312847569"
wifi.sta.config(cfg)
collectgarbage()
print("wi-fi ready")
