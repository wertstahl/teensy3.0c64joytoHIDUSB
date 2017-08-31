    /*
    
       Teensy C64 Wiring scheme
       
       Joystick 1
    
       IO    DB9         Function
          (C64 Side)
       1   <--- 1        Forward
       0   <--- 2        Back
       2   <--- 3        Left
       3   <--- 4        Right
           <--- 5        not connected (POT Y)
       4   <--- 6        Button1
       5V  <--- 7        +5V  ( only needed if the joystick contains circuits like autofire,.. )
       GND <--- 8        Ground
       6   <--- 9        Button2 (optional)
    
       Joystick 2
    
       IO DB9  Function
    
       14  1   Forward
       15  2   Back
       16  3   Left
       17  4   Right
           5   not connected
       19  6   Button1
           7   +5V
       AGND 8   Ground
       18  9   Button2 (optional)
    
    */

    //---------------------------------------------------------------------------------------------------

    uint8_t Firstrun = true;
    uint8_t Joy;
    uint8_t MemoJoy1 ;
    uint8_t MemoJoy2 ;
    
    uint16_t xaxis1 = 512;  // range 0-1023, 512 is resting position
    uint16_t yaxis1 = 512;  // range 0-1023, 512 is resting position
    uint8_t fbutton1 = 0;   // firebutton, 0 unpressed, 1 pressed

    uint16_t xaxis2 = 512;  // range 0-1023, 512 is resting position
    uint16_t yaxis2 = 512;  // range 0-1023, 512 is resting position
    uint8_t fbutton2 = 0;   // firebutton, 0 unpressed, 1 pressed

    // Pin 13: Teensy 3.0 has the LED on pin 13
    const int ledPin =  13;      // the number of the LED pin
  
    // player 1 bank
    const int P1_DOWN = 0;
    const int P1_UP = 1;
    const int P1_LEFT = 2;
    const int P1_RIGHT = 3;
    const int P1_FIER = 4;
 
    // player 2 bank
    const int P2_UP = 14;
    const int P2_DOWN = 15;
    const int P2_LEFT = 16;
    const int P2_RIGHT = 17;
    const int P2_FIER = 19;

    // Visual Debugging
    boolean ledOn = false;

    // Cycling
    unsigned long lastTime = 0;

   
void setup()
{
    pinMode(ledPin, OUTPUT);

    pinMode(P1_FIER, INPUT_PULLUP);
    pinMode(P1_LEFT, INPUT_PULLUP);
    pinMode(P1_RIGHT, INPUT_PULLUP);
    pinMode(P1_DOWN, INPUT_PULLUP);
    pinMode(P1_UP, INPUT_PULLUP);

    pinMode(P2_FIER, INPUT_PULLUP);
    pinMode(P2_UP, INPUT_PULLUP);
    pinMode(P2_DOWN, INPUT_PULLUP);
    pinMode(P2_LEFT, INPUT_PULLUP);
    pinMode(P2_RIGHT, INPUT_PULLUP);

    // initialize serial and wait for port to open:
    Serial.begin(9600);
    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
    }
    
   
}

   void loop()
{
    unsigned long time = millis();
    // run at 50 Hz 
    if(time - lastTime >= 20)
    {
        lastTime = time;
      
        // read the data of all our "buttons"

         Joy = ~PIND & 0b10011111;     // read Port D, invert logic, mask relevant bits
         if (Joy != MemoJoy1) {        // state changed?


                            //-unfired----------------------------------------

                            if (Joy == 128) { // 0 position
                              xaxis1 = 512;
                              yaxis1 = 512;
                              fbutton1 = 0;
                            }

                            if (Joy == 130) { // up position
                              xaxis1 = 512;
                              yaxis1 = 0;
                              fbutton1 = 0;
                            }

                            if (Joy == 138) { // up right position
                              xaxis1 = 1023;
                              yaxis1 = 0;
                              fbutton1 = 0;
                            }

                            if (Joy == 136) { // right position
                              xaxis1 = 1023;
                              yaxis1 = 512;
                              fbutton1 = 0;
                            }
                            

                            if (Joy == 137) { // down right position
                              xaxis1 = 1023;
                              yaxis1 = 1023;
                              fbutton1 = 0;
                            }

                            if (Joy == 129) { // down position
                              xaxis1 = 512;
                              yaxis1 = 1023;
                              fbutton1 = 0;
                            }

                            if (Joy == 133) { // down left position
                              xaxis1 = 0;
                              yaxis1 = 1023;
                              fbutton1 = 0;
                            }

                            if (Joy == 132) { // left position
                              xaxis1 = 0;
                              yaxis1 = 512;
                              fbutton1 = 0;
                            }

                            if (Joy == 134) { // up left position
                              xaxis1 = 0;
                              yaxis1 = 0;
                              fbutton1 = 0;
                            }



                                //--firebutton---------------------------------------
    
                                if (Joy == 144) { // 0 position + fire
                                  xaxis1 = 512;
                                  yaxis1 = 512;
                                  fbutton1 = 1;
                                }
    
                                if (Joy == 146) { // up position + fire
                                  xaxis1 = 512;
                                  yaxis1 = 0;
                                  fbutton1 = 1;
                                }
    
                                if (Joy == 154) { // up right position + fire
                                  xaxis1 = 1023;
                                  yaxis1 = 0;
                                  fbutton1 = 1;
                                }
    
                                if (Joy == 152) { // right position + fire
                                  xaxis1 = 1023;
                                  yaxis1 = 512;
                                  fbutton1 = 1;
                                }
                                
    
                                if (Joy == 153) { // down right position + fire
                                  xaxis1 = 1023;
                                  yaxis1 = 1023;
                                  fbutton1 = 1;
                                }
    
                                if (Joy == 145) { // down position + fire
                                  xaxis1 = 512;
                                  yaxis1 = 1023;
                                  fbutton1 = 1;
                                }
    
                                if (Joy == 149) { // down left position + fire
                                  xaxis1 = 0;
                                  yaxis1 = 1023;
                                  fbutton1 = 1;
                                }
    
                                if (Joy == 148) { // left position + fire
                                  xaxis1 = 0;
                                  yaxis1 = 512;
                                  fbutton1 = 1;
                                }

                                if (Joy == 150) { // left position + fire
                                  xaxis1 = 0;
                                  yaxis1 = 0;
                                  fbutton1 = 1;
                                }

                            //-----------------------------------------

                                
                              //  Alter Values Accordingly
                              Serial.print("  JOY:");
                              Serial.print(Joy);
                              Serial.print("  X:");
                              Serial.print(xaxis1);
                              Serial.print("  Y:");
                              Serial.print(yaxis1);
                              Serial.print("  FB:");
                              Serial.println(fbutton1);

                              // Update Joystick
                              Joystick.button (1,fbutton1);
                              Joystick.X(xaxis1);
                              Joystick.Y(yaxis1);

                              //  debounce                               
                              MemoJoy1 = Joy;             // save last state
                                 
                              // toggle our led
                              ledOn = !ledOn;
                              digitalWrite(ledPin, ledOn);
                      
                              }

    
    }
}
