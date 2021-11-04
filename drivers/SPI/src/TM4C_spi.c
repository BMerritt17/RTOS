/******************************************************************************
 * DEVICE DRIVER        SPI
 * 
 * File     : TM4C_spi.c
 * Target   : TM4C123GH6PM
 * Author   : Blake Merritt
 * Vesion   : 1.0 - 11/01/21
 * Notes    :
 *   The target features Synchronus Serial Interface (SSI) modules. Each of
 *   which can be set to master or slave for communication with peripherals
 *   that have Freescale SPI, MICROWIRE, or T.I. SSI.
 * 
 *   The purpose of this file is to leverage the available features of the 
 *   SSI module to interact via SPI. 
 *  
 *   There are 4 modules available with the following pin outs (x for module #)
 *      
 * 
 *    Pin Name  |    Pin #    |     Pin Mux     | Pin Type |   Description
 *  (x,0,1,2,3) | (x,0,1,2,3) |   (x,0,1,2,3)   |          |   (x,0,1,2,3)
 *    ==========|=============|=================|==========|================
 *    SSIxClk   | 19,30,58,61 | PA2,PF2,PB4,PD0 |   I/O    | Clock 
 *    SSIxFss   | 20,31,57,62 | PA3,PF3,PB5,PD1 |   I/O    | Frame Signal
 *    SSIxRx    | 21,28,1 ,63 | PA4,PF0,PB6,PD2 |    I     | Recieve
 *    SSIxTx    | 22,29,4 ,64 | PA5,PF1,PB7,PD3 |    O     | Transmit
 * 
 * 
 *   Initialization:
 *      1) Enable SSI with RCGSSI (pg.346) 965
 *      2) Enable the clock on the right GPIO via RCGCGPIO
 *      3) Set GPIO AFSEL bits (pg.671)
 *  
 *****************************************************************************/
#include "TM4C_spi.h"


void TM4C_spi_init(uint32_t SelectOpts) {


    /* Clear then enable run mode for selected SSI modules. */
    SYSCTL->RCGCSSI &= ~(0xFu);
    SYSCTL->RCGCSSI |= SelectOpts;


    if (SelectOpts & (1 << 0)) {/*        SPI_MOD_0 */
        SYSCTL->RCGCGPIO |= (1 << 0); /*  PORT A    */
    }

    if (SelectOpts & (1 << 1)) {/*        SPI_MOD_1 */
        SYSCTL->RCGCGPIO |= (1 << 5); /*  PORT F    */
    } 

    if (SelectOpts & (1 << 2)) {/*        SPI_MOD_2 */
        SYSCTL->RCGCGPIO |= (1 << 1); /*  PORT B    */
    }

    if (SelectOpts & (1 << 3)) {/*        SPI_MOD_3 */
        SYSCTL->RCGCGPIO |= (1 << 3); /*  PORT D    */
    }
  

    

}