/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.4
        Device            :  PIC24FJ128GA705
    The generated drivers are tested against the following:
        Compiler          :  XC16 v2.10
        MPLAB 	          :  MPLAB X v6.05
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/tmr2.h"
#include "mcc_generated_files/pin_manager.h"

/*
                         Main application
 */
struct DISTANCES{
    uint8_t front; //0 - bez odleglosci, 255 - uderzyl (dane od 230 zwracaja info na led_red, ze za blisko))
}distances;

uint32_t time = 0;
uint32_t distance = 0;
uint8_t on = 0;
uint8_t echo = 0;
uint16_t count = 0;

extern uint16_t counter_clocker;


int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    TMR2_Start();
    
    while (1)
    {
        echo = ECHO_GetValue();
        if(echo == 1){
            if(on == 0){
                counter_clocker = 0;
                TMR2_Counter16BitSet(0x00);
                on=1;
            }
            count++;
        }else{
            if(on == 1){
                time = (counter_clocker * 256) + TMR2_Counter16BitGet(); 
                distance = time / 58;
                distances.front = 255 - distance;
                if(distances.front > 200){
                    LED_RED_SetLow();
                }
                else{
                    LED_RED_SetHigh();
                }
                on=0;
            }
        }
    }    

    return 1;
}
/**
 End of File
*/
