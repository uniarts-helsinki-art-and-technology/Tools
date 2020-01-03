# Setup for multi-channel video player

## Background

The project was developed to create a versatile system for multi-channel video installations. The general idea is to have a low cost video players (Raspberry Pi) that can be easily extended for various setups. This solution makes use of the existing omxplayer to play video content but extends the usability by controlling it from Processing app. The idea to use Processing makes it very easy to implement custom solutions (such as DMX control, various sensors and other tracking devices, online data etc) to be synched with the video playback.

## Hardware

You'll need one Raspberry Pi 3 B+ for each video channel. For synching you will also need LAN cable to connect the Raspberries and a router if you connect more than two.

## Software

Raspberries should have the operating system(*) installed and updated. The project uses omxplayer so please make sure you have it installed. Type ... to test it. You should also install Processing (www.processing.org) and for comfortable work flow also netatalk.

## Video content

Export your files as .mp4. The video files should be compatible with omxplayer. See list of supported codecs here. All videos should have exactly the same lenght and have at least 10 seconds of extra footage(**) in the end.


------------------------------------------------------------

*) Tested on the following operating systems: Rasbian GNU/LINUX 9 (stretch)
**)This footage will not be visible, it's only needed for technical purpose. In other words, video file should always be 10 sec. longer that the video that you will show. Timecode for looping is defined separately.

------------------------------------------------------------


## Setup

The following instructions will guide through installing video players.

For general guidelines to setup Raspberries, please follow the instructions here: https://www.raspberrypi.org/documentation/installation/installing-images/README.md
You should have all Raspberries installed before continuing the installation to the following steps.


## Setup Client player:

1. Start up Raspberry

1. Download files from Github

    1.1. Save "rpMessage-rcv_client.py" file to Desktop

    1.2. Save "dbuscontrol.sh" file to Desktop

    1.3 Download and Install pytone/pyOsc from: https://github.com/ptone/pyosc

2. Check the ip address for client player:

   2.1. Open Terminal (Accesories > Terminal)

    2.2. Type "hostname -I" to terminal and read the ip address

    2.3. You will need the ip address in the step 5.2.3.

3. Copy your video file to each pi's home "/home/pi" folder and rename it "video.mp4".



## Setup Master player

5. Start up Raspberry

    5.1. Setup the Processing code

        5.1.1. Download files from Github

        5.1.2. Save "rpMessage-rcv_master.py" file to Desktop

    5.2. Setup Processing code (Processing is required for the next steps)

        5.2.1. Copy "rpSendOscToPythonScriptManyClients" folder to Desktop

        5.2.2. Open Processing sketch "rpSendOscToPythonScriptManyClients.pde"
        
        5.2.3. Install libraries: CountdownTimer, oscP5, controlP5

        5.2.3. Check the client ip address (step 2.) and type the correct address to Processing sketch. If you use multiple client players write all the ip addresses to the array.

        5.2.4. Check the video length (in seconds) and type it to Processing sketch. Make sure that you type the length of the content that wish to be visible and have approx. 10 sec. of extra footage in the video file.
        
        5.2.5. Export Processing application

6. Make sure that you have all players connected via LAN cable (turn off wifi, bluetooth etc.).

7. Start the client player(s)

    7.1. Start by typing:

8. Start the master player

    8.1. Start by typing:

9. When master is started all videos should jump to the end of the video and then start looping in sync.



## Setting up the autostart

To create a standalone system for exhibition purpose, it is a good idea to make video players start automatically when they are powered.

Note! You can't exit from the client's video player without having the master able to control it. Please make sure that you have tested the whole system before setting up the autostart.

Note! use arm6h on RasPi

1. To modify the autostart, you should copy /etc/xdg/ to ~/.config/lxsession/LXDE-pi/autostart
(The version in the home directory will be used instead of the one in /etc/xdg/...)
2. modify the autostart file for client (see example "autostart_client" in the Github)
3. modify the autostart file for master (see example "autostart_master" in the Github)

*********************************************************************************************
*********************************************************************************************
<!--CAN WE ADD DISABLE WIFI AND BLUETOOTH IN THE AUTOSTART FILE????-->




## Setting up the netatalk

Install netatalk for convenience:

1. Start up Raspberry
2. Install netatalk
2.1. Open Terminal (Accesories > Terminal)
2.2. Type: sudo apt-get install netatalk
3. Check the ip address:
3.1. Open Terminal (Accesories > Terminal)
3.2. Type "hostname -I" to terminal and read the ip address
4. Connect from other computer (MAC)
4.1 Select: Finder —> Go to.. —> Connect to server
4.2. Type the ip address of the Raspberry Pi ( e.g afp://195.148.109.234)



## Instructions

Prepare videos:
1. include 10 seconds of extra footage in the end of all videos
2. use Handbrake with preset "Fast 1080p 30" to convert videos


To stop player:
1. Click with mouse to center of the screen on master player
2. press esc to exit

Exit client players
1. open terminal in startup
2. write "pkill omxplayer" (blindfold)


default video path
/home/pi/video.mp4

default processing app path
/
