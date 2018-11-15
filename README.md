# MagicaLLight
***Magical light is my first hobby project.***

The main goal of this project was to get acquainted with ESP-01 Wi-Fi module.

My secondary goals were learning:
1. TCP server with sockets;
2. soldering;
3. making PCB using laser ironing technology;

***What this project is actually doing?***

I developed the TCP server and GUI with Qt for windows. 
Server converts chosen .WAV file into PWM duty cycle at every 0.1 seconds
and gradually sends this data to ESP-01, which controls the MOSFET's gate.

Project execution plan:
1. developing TCP server and converting algorithm;
2. writing Lua scripts to operate with incoming data and synсhronizing it with music;
3. creating GUI (not the best frontend developer);
4. soldering 50 LEDs and resistors together (just to practice soldering);
5. developing PCB;
6. designing 3D case (T.A.R.D.I.S. has perfect parallelepiped shape);
7. making PCB;
8. making 3D case;
9. installation.

You can check out short demo [here](https://www.youtube.com/watch?v=hM5m-m5Mo0Q).
