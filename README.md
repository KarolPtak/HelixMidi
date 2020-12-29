# HelixMidi

## This is a DIY midi footswitch controller for the line6 helix / hx stomp (or actually any midi device).

Short demo: https://youtu.be/-W3b5MKsnIc

![Controller](controller.jpg?raw=true "Controller")


I did it when it's turned out that I neeed more than 3 footswitches ;-) , and the price of stock midi controllers was too high. More likely I'd sell the stomp and buy helix lt instead, if I had to pay for the controller.

It offers 6 different pages (modes), and covers nearly everything that the hx stomp can accept through the midi :)
It is powered directly from USB, works fine with hx stomp, no buzz/hum

- basic - 4 'classic' switches
- basic+ - 3 'classic' switches + tap/tempo
- preset change - Fs4,5 emulation + 1 'classic' + tap/tempo
- snapshot change - 3 snapshot switches + tap/tempo
- looper 1 - record/overdub, play/stop, undo/redo, tap/tempo
- looper 2 - record/overdub, play, stop, undo/redo

- tuner on/off always available when long pressing fs2

## Brief user manual :) :

You can cycle between basic, basic+, preset and snapshot change by long pressing fs1 and fs2 simultaneously.
Clycle between basic, looper 1, looper 2 by long pressing fs3 and fs4 simultaneously.
Each page has it's own color set - I've tried to reflect hx stomp colors as closely as possible :).

Current page is saved in memory, so next time you turn on the controller, it will go back to it.


Footswitch functions in particular page:
- Basic : fs1-4 - 'classic switches' (midi cc codes 100-103)
- Basic+ : fs1-3 - 'classic switches' (midi cc codes 100-102), fs4 - tap/tempo
- Preset change: fs1 - Fs4 emulation, fs2 - 'classic switch' (midi cc code 101), fs3 - Fs5 emulation, fs4 - tap/tempo
- Snapshot change: fs1-3 - snapshot 1-3, fs4 - tap/tempo
- Looper 1 - fs1: play/stop, fs2 - undo/redo, fs3 - record/overdub, fs4 - tap/tempo
- Looper 2 - fs1: stop, fs2 - undo/redo, fs3 - play, fs4 - record/overdub

In the looper modes leds function is a bit different, and it displays if the looper is active, and if record/overdub is in progres.
So eg. after hitting record/overdub (first time) leds indicating looper and record activation will be lit, and then, if You hit the play switch, the record led will be shut. However it's not 100% accurate - (eg. undo/redo hit just after recording is started for the first time seems to turn the looper in the hx stomp off, but it's the best I could do ;-)


Tap tempo blinking - sadly my led blinking implementation did not keep up the same tempo as the stomp. Probably it was implemented too naive way ;), or just a real time clock is needed to do it? hmm...

## Programming

3 external libraries are used for midi, ledstrip and button handling. You can add them via Arduino IDE -> Tools -> Manage Libraries...

Add:
- MIDI Library (by Francois Best, lathoub)
- Freenove WS2812B RGBLED Controller
- ezButton

Sketch uses 8194 bytes (26%) of program storage space. Maximum is 30720 bytes.
Global variables use 740 bytes (36%) of dynamic memory, leaving 1308 bytes for local variables. Maximum is 2048 bytes.


## Elements used

- Arduino nano - https://www.ebay.com/itm/ATmega328P-Micro-Controller-CH340G-Driver-For-Arduino-5V-16MHz-Nano-V3-0-USB/283932008665
- 4 Footswitches - https://www.ebay.com/itm/2Pin-SPST-Momentary-Touch-Push-Button-Stomp-Foot-Pedal-Electric-Guitar-Switch-SC/163157135937
- Ledstrip WS2812B - 8 leds in series, 2 per one switch - like these, just cut it to single leds (they are ready for this): https://www.ebay.com/itm/WS2812B-5V-5050-RGB-LED-Strip-1-5M-30-60-144-150-300-Leds-Individual-Addressable/254700428516
- Case (any, actually) - I used that: https://www.thomann.de/pl/lead_foot_fs2.htm
- Midi cable / socket - I used that: https://www.thomann.de/pl/the_sssnake_sk366-1_blk_midi_kabel.htm and soldered its wires to arduino

Total cost of elements (except the case) was c.a. 23$.

## Wiring
![Diagram](diagram.jpg?raw=true "Diagram")

In my case (huh, 'case' ;D) the wiring looks like this - pretty simple (only on the photo it looks like hundreds of wires :P ), the arduino is in a heat shrink tubing, and attached to the case with double sided tape

![Wiring](under_the_hood.jpg?raw=true "Wiring")

## Misc

- If you wonder what is the correct order of pins in the midi socket/plug, this image should solve Your problems (helped me a lot)

  ![Midi plug](midiplug.jpg?raw=true "Midi plug")
  
  it comes from http://www.philrees.co.uk/midiplug.htm 
  
- It looks like this together with the hx stomp

  ![Together with hx stomp](with_stomp.jpg?raw=true "With hx stomp")

## TODO

- [ ] Tap/tempo and looper mode
- [ ] Install single leds next to the stomp when they arrive ;) And fill their holes with some transparent, or opaline resin to disperse the led light gently.


## Info from hx stomp instruction

CC message ids restricted by line6 (special purpose):

```
0	n/a Bank MSB (unused, but reserved)
1	0-127 Emulates EXP 1 Pedal
2	0-127 Emulates EXP 2 Pedal
3	0-127 Additional global MIDI commands
32	n/a Bank LSB (unused, but reserved)
49	0-127 Emulates FS1
50	0-127 Emulates FS2
51	0-127 Emulates FS3
52	0-127 Emulates FS4
53	0-127 Emulates FS5
54	0-127 Additional global MIDI commands
55	0-127 Additional global MIDI commands
56	0-127 Additional global MIDI commands
57	0-127 Additional global MIDI commands
58	0-127 Additional global MIDI commands
59	0-127 Additional global MIDI commands
60	0-63: Overdub;64-127: Record 1 Switch Looper Record/Overdub
61	0-63: Stop;64-127: Play 1 Switch Looper Play/Stop
62	64-127 1 Switch Looper Play Once
63	64-127 1 Switch Looper Undo/Redo
64	64-127 Tap Tempo
65	0-63: Forward; 64-127: Reverse 1 Switch Looper Forward/Reverse
66	0-63: Full; 64-127: Half 1 Switch Looper Full/Half Speed
67	0-127 Additional global MIDI commands
68	0-127 Tuner screen on/off
69	0-2, 8 and 9 Snapshot select (0=Snapshot 1, 1=Snapshot 2, 2=Snapshot 3, 8=Next snapshot, 9=Previous snapshot)
70	0-63: Bypass; 64-127: On All Bypass
71	0-5 Footswitch Mode (0=Stomp, 1=Scroll, 2=Preset, 3=Snapshot, 4=Next footswitch mode, 5=Previous footswitch mode)
72	0-127 Additional global MIDI commands
73	0-127 Additional global MIDI commands
74	0-127 Additional global MIDI commands
75	0-127 Additional global MIDI commands
76	0-127 Additional global MIDI commands
128	 0-63: Jealous;  64-127: Codependent HX Stomp sends late-night texts to all of your exsignificant others, professing your undying love to them and their cats
```

Values for block bypass
```
Incoming CC values 0-63 turn the block off; values 64-127 turn the block on. Note
that some MIDI CCs are reserved for global functions and cannot be selected 
```
