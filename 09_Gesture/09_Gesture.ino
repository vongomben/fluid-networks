#include <Wire.h>
#include "paj7620.h"


/* 
Notice: When you want to recognize the Forward/Backward gestures, your gestures' reaction time must less than GES_ENTRY_TIME(0.8s). 
        You also can adjust the reaction time according to the actual circumstance.
*/
#define GES_REACTION_TIME       500             // You can adjust the reaction time according to the actual circumstance.
#define GES_ENTRY_TIME          800             // When you want to recognize the Forward/Backward gestures, your gestures' reaction time must less than GES_ENTRY_TIME(0.8s). 
#define GES_QUIT_TIME           1000
 
void setup()
{
    uint8_t error = 0;
 
    Serial.begin(9600);
    Serial.println("\nPAJ7620U2 TEST DEMO: Recognize 9 gestures.");
 
    error = paj7620Init();          // initialize Paj7620 registers
    if (error) 
    {
        Serial.print("INIT ERROR,CODE:");
        Serial.println(error);
    }
    else
    {
        Serial.println("INIT OK");
    }
    Serial.println("Please input your gestures:\n");
}
 
void loop()
{
    uint8_t data = 0, data1 = 0, error;
 
    error = paj7620ReadReg(0x43, 1, &data);             // Read Bank_0_Reg_0x43/0x44 for gesture result.
    if (!error) 
    {
        switch (data)                                   // When different gestures be detected, the variable 'data' will be set to different values by paj7620ReadReg(0x43, 1, &data).
        {
            case GES_RIGHT_FLAG:
                delay(GES_ENTRY_TIME);
                paj7620ReadReg(0x43, 1, &data);
                if(data == GES_FORWARD_FLAG) 
                {
                    Serial.println("Forward");
                    delay(GES_QUIT_TIME);
                }
                else if(data == GES_BACKWARD_FLAG) 
                {
                    Serial.println("Backward");
                    delay(GES_QUIT_TIME);
                }
                else
                {
                    Serial.println("Right");
                }          
                break;
            case GES_LEFT_FLAG: 
                delay(GES_ENTRY_TIME);
                paj7620ReadReg(0x43, 1, &data);
                if(data == GES_FORWARD_FLAG) 
                {
                    Serial.println("Forward");
                    delay(GES_QUIT_TIME);
                }
                else if(data == GES_BACKWARD_FLAG) 
                {
                    Serial.println("Backward");
                    delay(GES_QUIT_TIME);
                }
                else
                {
                    Serial.println("Left");
                }          
                break;
            case GES_UP_FLAG:
                delay(GES_ENTRY_TIME);
                paj7620ReadReg(0x43, 1, &data);
                if(data == GES_FORWARD_FLAG) 
                {
                    Serial.println("Forward");
                    delay(GES_QUIT_TIME);
                }
                else if(data == GES_BACKWARD_FLAG) 
                {
                    Serial.println("Backward");
                    delay(GES_QUIT_TIME);
                }
                else
                {
                    Serial.println("Up");
                }          
                break;
            case GES_DOWN_FLAG:
                delay(GES_ENTRY_TIME);
                paj7620ReadReg(0x43, 1, &data);
                if(data == GES_FORWARD_FLAG) 
                {
                    Serial.println("Forward");
                    delay(GES_QUIT_TIME);
                }
                else if(data == GES_BACKWARD_FLAG) 
                {
                    Serial.println("Backward");
                    delay(GES_QUIT_TIME);
                }
                else
                {
                    Serial.println("Down");
                }          
                break;
            case GES_FORWARD_FLAG:
                Serial.println("Forward");
                delay(GES_QUIT_TIME);
                break;
            case GES_BACKWARD_FLAG:       
                Serial.println("Backward");
                delay(GES_QUIT_TIME);
                break;
            case GES_CLOCKWISE_FLAG:
                Serial.println("Clockwise");
                break;
            case GES_COUNT_CLOCKWISE_FLAG:
                Serial.println("anti-clockwise");
                break;  
            default:
                paj7620ReadReg(0x44, 1, &data1);
                if (data1 == GES_WAVE_FLAG) 
                {
                    Serial.println("wave");
                }
                break;
        }
    }
    delay(100);
}
