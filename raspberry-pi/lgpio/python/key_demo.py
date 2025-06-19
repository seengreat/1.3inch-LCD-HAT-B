# Seengreat 1.3 Inch LCD Display demo
# Author(s):Andy Li from Seengreat

import lcd_1inch3
from PIL import ImageDraw, Image, ImageFont
# import wiringpi as wpi
from gpiozero import *
import time

# define the key button pin in BCM number
K1_PIN    = 17
K2_PIN    = 18
K3_PIN    = 22
K4_PIN    = 23
R_PIN     = 20
L_PIN     = 21
UP_PIN    = 13
LEFT_PIN  = 5
DOWN_PIN  = 26
RIGHT_PIN = 19
CENTER_PIN= 6


if __name__ == '__main__':
    lcd = lcd_1inch3.LCD_1Inch3()

    K1 = DigitalInputDevice(K1_PIN,pull_up=True,active_state=None)
    K2 = DigitalInputDevice(K2_PIN,pull_up=True,active_state=None)
    K3 = DigitalInputDevice(K3_PIN,pull_up=True,active_state=None)
    K4 = DigitalInputDevice(K4_PIN,pull_up=True,active_state=None)
    L = DigitalInputDevice(L_PIN,pull_up=True,active_state=None)
    R = DigitalInputDevice(R_PIN,pull_up=True,active_state=None)
    UP = DigitalInputDevice(UP_PIN,pull_up=True,active_state=None)
    LEFT = DigitalInputDevice(LEFT_PIN,pull_up=True,active_state=None)
    RIGHT = DigitalInputDevice(RIGHT_PIN,pull_up=True,active_state=None)
    DOWN = DigitalInputDevice(DOWN_PIN,pull_up=True,active_state=None)
    CENTER = DigitalInputDevice(CENTER_PIN,pull_up=True,active_state=None)

    lcd.lcd_init()
    lcd.clear()
    img0 = Image.new("RGB", (lcd.w, lcd.h), "WHITE")
    lcd_draw = ImageDraw.Draw(img0)
    k1_flag = 0
    k2_flag = 0
    k3_flag = 0
    k4_flag = 0
    l_flag = 0
    r_flag = 0
    up_flag = 0
    left_flag = 0
    right_flag = 0
    down_flag = 0
    center_flag = 0
    lcd_draw.rectangle([(170,60),(210,80)],outline=255, fill = 0) # K1
    lcd_draw.rectangle([(150,100),(170,140)],outline=255, fill = 0) # K2
    lcd_draw.rectangle([(210,100),(230,140)],outline=255, fill = 0) # K3
    lcd_draw.rectangle([(170,160),(210,180)],outline=255, fill = 0) # K4
    lcd_draw.rectangle([(30,10),(70,30)],outline=255, fill = 0) # L
    lcd_draw.rectangle([(170,10),(210,30)],outline=255, fill = 0) # R
    lcd_draw.rectangle([(40,70),(80,90)],outline=255, fill = 0) # up
    lcd_draw.rectangle([(10,100),(30,140)],outline=255, fill = 0) # left
    lcd_draw.rectangle([(90,100),(110,140)],outline=255, fill = 0) # right 
    lcd_draw.rectangle([(40,150),(80,170)],outline=255, fill = 0) # down  
    lcd_draw.rectangle([(40,100),(80,140)],outline=255, fill = 0) # center
    lcd.img_show(img0.rotate(180)) 
    while True:
        if K1.value == 1 and k1_flag == 0:
            time.sleep(0.01)
            if K1.value == 1: # make sure the button has been pressed
                k1_flag = 1
                lcd_draw.rectangle([(170,60),(210,80)],outline=255, fill = 0XFF00)
                lcd.img_show(img0.rotate(180)) 
                print("K1 Press")
        elif K1.value == 0 and k1_flag == 1: # key has been released
            k1_flag = 0
            lcd_draw.rectangle([(170,60),(210,80)],outline=255, fill = 0)
            lcd.img_show(img0.rotate(180)) 
                
        if K2.value == 1 and k2_flag == 0:
            time.sleep(0.01)
            if K2.value == 1: # make sure the button has been pressed
                k2_flag = 1
                lcd_draw.rectangle([(150,100),(170,140)],outline=255, fill = 0XFF00)
                lcd.img_show(img0.rotate(180)) 
                print("K2 Press")
        elif K2.value == 0 and k2_flag == 1: # key has been released
            k2_flag = 0
            lcd_draw.rectangle([(150,100),(170,140)],outline=255, fill = 0)
            lcd.img_show(img0.rotate(180)) 

        if K3.value == 1 and k3_flag == 0:
            time.sleep(0.01)
            if K3.value == 1: # make sure the button has been pressed
                k3_flag = 1
                lcd_draw.rectangle([(210,100),(230,140)],outline=255, fill = 0XFF00)
                lcd.img_show(img0.rotate(180)) 
                print("K3 Press")
        elif K3.value == 0 and k3_flag == 1: # key has been released
            k3_flag = 0
            lcd_draw.rectangle([(210,100),(230,140)],outline=255, fill = 0)
            lcd.img_show(img0.rotate(180)) 

        if K4.value == 1 and k4_flag == 0:
            time.sleep(0.01)
            if K4.value == 1: # make sure the button has been pressed
                k4_flag = 1
                lcd_draw.rectangle([(170,160),(210,180)],outline=255, fill = 0XFF00)
                lcd.img_show(img0.rotate(180)) 
                print("K4 Press")
        elif K4.value == 0 and k4_flag == 1: # key has been released
            k4_flag = 0
            lcd_draw.rectangle([(170,160),(210,180)],outline=255, fill = 0)
            lcd.img_show(img0.rotate(180))

        if L.value == 1 and l_flag == 0:
            time.sleep(0.01)
            if L.value == 1: # make sure the button has been pressed
                l_flag = 1
                lcd_draw.rectangle([(30,10),(70,30)],outline=255, fill = 0XFF00)
                lcd.img_show(img0.rotate(180)) 
                print("L Press")
        elif L.value == 0 and l_flag == 1: # key has been released
            l_flag = 0
            lcd_draw.rectangle([(30,10),(70,30)],outline=255, fill = 0)
            lcd.img_show(img0.rotate(180))

        if R.value == 1 and r_flag == 0:
            time.sleep(0.01)
            if R.value == 1: # make sure the button has been pressed
                r_flag = 1
                lcd_draw.rectangle([(170,10),(210,30)],outline=255, fill = 0XFF00)
                lcd.img_show(img0.rotate(180)) 
                print("R Press")
        elif R.value == 0 and r_flag == 1: # key has been released
            r_flag = 0
            lcd_draw.rectangle([(170,10),(210,30)],outline=255, fill = 0)
            lcd.img_show(img0.rotate(180))
            
        if UP.value == 1 and up_flag == 0:
            time.sleep(0.01)
            if UP.value == 1: # make sure the button has been presse
                up_flag = 1
                lcd_draw.rectangle([(40,70),(80,90)],outline=255, fill = 0XFF00)
                lcd.img_show(img0.rotate(180)) 
                print("UP Press")
        elif UP.value == 0 and up_flag == 1: # key has been released
            up_flag = 0
            lcd_draw.rectangle([(40,70),(80,90)],outline=255, fill = 0)
            lcd.img_show(img0.rotate(180)) 

        if LEFT.value == 1 and left_flag == 0:
            time.sleep(0.01)
            if LEFT.value == 1: # make sure the button has been pressed
                left_flag = 1
                lcd_draw.rectangle([(10,100),(30,140)],outline=255, fill = 0XFF00)
                lcd.img_show(img0.rotate(180)) 
                print("LEFT Press")
        elif LEFT.value == 0 and left_flag == 1: # key has been released
            left_flag = 0
            lcd_draw.rectangle([(10,100),(30,140)],outline=255, fill = 0)
            lcd.img_show(img0.rotate(180)) 

        if RIGHT.value == 1 and right_flag == 0:
            time.sleep(0.01)
            if RIGHT.value == 1: # make sure the button has been pressed
                right_flag = 1
                lcd_draw.rectangle([(90,100),(110,140)],outline=255, fill = 0XFF00)
                lcd.img_show(img0.rotate(180)) 
                print("RIGHT Press")
        elif RIGHT.value == 0 and right_flag == 1: # key has been released
            right_flag = 0
            lcd_draw.rectangle([(90,100),(110,140)],outline=255, fill = 0)
            lcd.img_show(img0.rotate(180)) 

        if DOWN.value == 1 and down_flag == 0:
            time.sleep(0.01)
            if DOWN.value == 1: # make sure the button has been pressed
                down_flag = 1
                lcd_draw.rectangle([(40,150),(80,170)],outline=255, fill = 0XFF00)
                lcd.img_show(img0.rotate(180)) 
                print("DOWN Press")
        elif DOWN.value == 0 and down_flag == 1: # key has been released
            down_flag = 0
            lcd_draw.rectangle([(40,150),(80,170)],outline=255, fill = 0)
            lcd.img_show(img0.rotate(180)) 

        if CENTER.value == 1 and center_flag == 0:
            time.sleep(0.01)
            if CENTER.value == 1: # make sure the button has been pressed
                center_flag = 1
                lcd_draw.rectangle([(40,100),(80,140)],outline=255, fill = 0XFF00)
                lcd.img_show(img0.rotate(180)) 
                print("CENTER Press")
        elif CENTER.value == 0 and center_flag == 1: # key has been released
            center_flag = 0
            lcd_draw.rectangle([(40,100),(80,140)],outline=255, fill = 0)
            lcd.img_show(img0.rotate(180))        

                