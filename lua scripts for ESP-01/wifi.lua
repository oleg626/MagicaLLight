--WiFi Settup
wifi.setmode(wifi.STATION)
local cfg={}
cfg.ssid="lnajdngjdnlgjdsng"
cfg.pwd="schauma551"
wifi.sta.config(cfg)
collectgarbage()
print("wi-fi ready")
