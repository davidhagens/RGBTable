So this is my code which is powering my LED Matrix Table.
The table is coffee table futering a LED matrix on top of it with 36 * 18 WS2812b LEDs (NeoPixel).

Used Hardware:
- 3 * Ardunio Uno (2 of them are powering the LEDs and the other one does other stuff which is explained later)
- 648 * WS2812b LED Controller & RGB LED
- 2 * Nintendo Entertainment System Controller Jack (which are from a NES 4Play Adapter (which I got from Ebay))
- 1 * 5V 20A Power Supply (100W), which is powering the LEDs, the Arduinos are powered over USB
- 2 * IR Reciever (which I got from analogue LED Strips)
- 1 additional WS2812b LED which is used to provide status information (like no WIFI connection, etc.)
- 1 USB Hub to provide power and Serial connections to the Arduinos
- several cables
- Wood to build the actual table

I will probably publish pictures of the table & of the building process somewhere, a link to this will be added on time.

So I use two Arduinos two power the LEDs (which are two becaus one had not enough RAM to get all the pixel 
information over the Serial connection. The third Arduino powers the two NES controller, the IR reciever 
(which recieve the IR codes from an Remote of the analogue LED strip where I get the Reciever from) and 
the status LED. It is also connected to a currently unused relaycard, which should switch off the connection
between the power supply and the LEDs, but which is currently not working and I haven't figured out why it's not working...

Since I use the windows API a lot, the Code is only working on windows devices.
I may upload the arduino code here or somewhere else.

If you're interested in stuff about this table or want to build one by yourself, feel free and ask me anything.
