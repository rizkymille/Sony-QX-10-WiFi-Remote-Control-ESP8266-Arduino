Credit to kuzcy for the original QX-10 Arduino code  

# Pixhawk QX-10 Wifi Trigger
Software for turning ESP32 into wifi based camera remote that can be triggered from pixhawk. This software was tested with Sony DSC QX-10, but you can try it with another Sony camera (as long as it has WiFi feature and included in Sony Camera Remote API beta).  

Versions:  
* ArduPlane 4.0.6  
* Sony QX-10 Firmware 3.0  

For adding wider features, please look into Sony Camera Remote API beta 2.40. Do not use the newer Camera Remote SDK because Sony hasn't included the wifi features.  

## Setup ##  
Please replace the camera SSID "DIRECT-dUQ0:DSC-QX10" and password "NE8oHWt5" with your own QX-10 camera SSID and Password. If you found difficulties when searching your camera SSID and Password, just look into the back battery cover.

### Pixhawk Parameters Settings ###
#### Camera shutter pin: ###  
SERVO5 (MAIN 5)  

#### PWM states: ####  
Servo limits  
Min 1000  
Max 1700  

#### Shutter: ####  
Pushed 1700  
Not Pushed 1000  
Duration 1 (0,1 s)  

### ESP32 Pinouts ###  
SERVO5 (MAIN 5)  
SIGNAL -> GPIO13 (D13)    

### Pre Flight Setup ###
1. Turn on the pixhawk  
2. Turn on the safety switch to ensure pixhawk sends PWM to servo rail  
3. Press EN at ESP32  
4. Click "Trigger Camera NOW" at Mission Planner (or else if you using another GCS program)  
5. Ensure the camera triggers. If not, please reboot the ESP32

## Known Issues ##  
This software was already tested at KRTI (National Flying Robot Competition) 2020 with Team Cygnus, Universitas Indonesia. The QX-10 is used as aerial mapping camera for our fixed wing UAV. These listed issues will less problematic if you use a copter type UAV or make a vibration damper for the QX-10. Some issues we have found in field such as:  
* *Fast shooting, blurred images*  
  This is ocurring because there's no manual focus control in QX-10. So, if you delete the HalfPressShutter feature, you will get much more accurate images with pixhawk but with blurred quality.  
* *Focused images, slow shooting*  
  I added HalfPressShutter feature so you will get better image quality, but the camera will shutter less faster so you will get less accurate image with pixhawk.  
