#!/usr/bin/env python3
from OSC import OSCServer
import sys
from time import sleep
import subprocess
from subprocess import Popen
#from subprocess import run
import os
import time

# you can type hostname -I in the terminal to discover the Ip address of the Pi
port = 1234
server = OSCServer( ("0.0.0.0", port) )
server.timeout = 0
runB = True

# path of the dbuscontrol.sh script    
dBus_scriptPath = "/home/pi/Desktop/dbuscontrol.sh"

os.system("hostname -I")
print("started python script to receive OSC commands on port " + str(port))
processingAppPath = "/home/pi/sketchbook/rpSendOscToPythonScriptManyClients/application.linux-arm64/rpSendOscToPythonScriptManyClients"
# using os impedes the execution of the rest of the program
#os.system("bash " + processingAppPath)

videoPath = "/home/pi/video.mp4" 
#os.system("omxplayer --loop --win '0 0 400 300' " + videoPath)       
subprocess.Popen("omxplayer --loop --no-osd " + videoPath, shell=True)
time.sleep(3)
subprocess.call([dBus_scriptPath + ' setvideopos 100 100 740 460'], shell=True)
time.sleep(1)
subprocess.call([dBus_scriptPath + ' setposition 0'], shell=True)

# omxplayer starts in play and get a seek message from processing
# in this way the order of booting of the client pi do not matter
#subprocess.call([dBus_scriptPath + " pause"], shell=True)

subprocess.Popen("bash " + processingAppPath, shell=True)

# this method of reporting timeouts only works by convention
# that before calling handle_request() field .timed_out is 
# set to False
def handle_timeout(self):
    self.timed_out = True

# funny python's way to add a method to an instance of a class
import types
server.handle_timeout = types.MethodType(handle_timeout, server)

def user_callback(path, tags, args, source):
    # which user will be determined by path:
    # we just throw away all slashes and join together what's left
    #user = ''.join(path.split("/"))
    # tags will contain 'fff'
    # args is a OSCMessage with data
    # source is where the message came from (in case you need to reply)
    if path == '/setposition':
        #print("received /setposition")
        subprocess.call([dBus_scriptPath + ' setposition ' + str(args[0])], shell=True)
    if path == '/setalpha':
        #print("received /setalpha")
        subprocess.call([dBus_scriptPath + ' setalpha ' + str(args[0]*255)], shell=True)
    if path == '/smallWindow':
        print("received /smallWindow")
         #os.system("omxplayer --win '0 0 400 300' " + videoPath)
        subprocess.call([dBus_scriptPath + ' setvideopos 100 100 740 460'], shell=True)
    if path == '/fullScreen':
        print("received /fullScreen")        
        subprocess.call([dBus_scriptPath + ' setvideopos 0 0 1920 1080'], shell=True)
    if path == '/pause':
        print("python script received /pause")
        subprocess.call([dBus_scriptPath + ' pause'], shell=True)        
    if path == '/stop':
        print("python script received /stop")
        subprocess.call([dBus_scriptPath + ' stop'], shell=True)         
    if path == '/restart':
        print("python script received /command")
        #os.system("bash " + dBus_scriptPath + " setposition 0")
        subprocess.call([dBus_scriptPath + ' setposition 0'], shell=True)
    # print ("Now do something with", user,args[2],args[0],1-args[1]) 

def quit_callback(path, tags, args, source):
    # don't do this at home (or it'll quit blender)
    global runB
    runB = False

server.addMsgHandler( "/smallWindow", user_callback )
server.addMsgHandler( "/pause", user_callback )
server.addMsgHandler( "/restart", user_callback )
server.addMsgHandler( "/stop", user_callback )
server.addMsgHandler( "/fullScreen", user_callback )
server.addMsgHandler( "/setalpha", user_callback )
server.addMsgHandler( "/setposition", user_callback )
server.addMsgHandler( "/quit", quit_callback )

# user script that's called by the game engine every frame
def each_frame():
    # clear timed_out flag
    server.timed_out = False
    # handle all pending requests then return
    while not server.timed_out:
        server.handle_request()

# simulate a "game engine"
while runB:
    # do the game stuff:
    #sleep(0.1)
    # call user script
    each_frame()

server.close()
