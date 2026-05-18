# Tamagotchi
This Tamagotchi is a digital pet that you can raise. It runs off an Xiao Esp32C3 board and has an OLED board that displays the pet's condition at all times, to remind people of the mood of their pet. I added LED lights that correspond to different moods (sad, happy, and neutral).
<img width="485" height="503" alt="Tamagotchi_CaseScreenshot" src="https://github.com/user-attachments/assets/914d0a94-84fd-4877-854e-6d373dcdc462" />
<img width="740" height="851" alt="Tamagotchi PCB screenshot" src="https://github.com/user-attachments/assets/158f2724-aad0-4d2c-a46c-5e5a52f70520" />


# How it's made:
Programs used: KiCad, Fusion, Arduino IDE
I first created the schematic and the PCB using KiCad. I took a lot of inspiration from the guide on the Tamagochi made in the Fallout tutorial. So I used the same processor, which is the XIAO Esp32C3 board. I connected everything to the corresponding parts after looking at the datasheet. This part won't take you very long, especially if you have a bit of experience. The wiring for PCB is quite nice in the sense that since there are not a lot of parts, wiring is not much of a hassle. I did add a ground layer on the front side. For my battery, I added a lithium battery that is outside of the PCB. 

For my case, I went with a pretty simple design since it is my first time making a 3D model. To secure the PCB, I used the holes that the OLED screen has to secure the PCB to the back of the case. Then I also added holes in the sides of the case that make it so that the front and back are connected and won't fall apart. I did threads for the holes except the one for the battery, since the hole was too small. I also added an opening for my usbc charging port as well as the LEDs and the  buttons, which I just used the extrude button to cut.  

For the firmware, I learned a lot from the guide in Fallout since I never used C++ before. I did most of what was suggested to do in the guide, so I would suggest that as the starting point. The main part, I think, is connecting the different parts of the hardware to the software as long the connection is there the rest will go pretty smoothly. For the LEDs, I kept it pretty simple with just one LED corresponding to each mood; I kept it to three. So when a mood change is detected, a new LED light will light up.

# How to use it:
When you connect the Tamagotchi to the USBC cable, it will turn on and show the "Tamagotchi loading..." on the OLED screen for 1 second before your pet starts with it's hunger, happiness, and energy at 80/100. Then every 5 seconds all the stats will drop by 1, so if you leave it alone for too long it will eventally die WHICH YOU DONT WANT. So to avoid that, the three buttons that you can press: left for feed (hunger +10), middle for play (happiness +10 energy -5), right for sleep (energy +15). Buttons have a 200ms debounce time, so double presses are ignored. 

The pet's face and the LEDs also change based on mood:
Happy face and green LED = all stats above 50
Neutral face and yellow LED = stats are between 50 and 30
Sad face and red LED = stats under 30

# Why I made this:
I wanted to challenge myself to do something out of my comfort zone. This project required many different parts combined, so I thought it was a very good learning opportunity to use many different things combined (3d modeling, hardware, and software). I think the project is also very fun, and you can really personalize the end product to whatever you like. This project had many complex parts, but they are small enough that it won't take a massive amount of time. I also wanted to learn how to incorporate an OLED screen in my build, so this was also my other reason for creating this.  

# Zine Page
[Tamagotchi_ZIne.pdf](https://github.com/user-attachments/files/27939778/Tamagotchi_ZIne.pdf)
