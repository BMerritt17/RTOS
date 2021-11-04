#include "unity.h"
#include <stdlib.h>
#include "TM4C_spi.h"


void test_TM4C_spi_init_should_initialize_RCGCSSI_Register(void) {
    
    SYSCTL->RCGCSSI = 0x84u; /* Simulate bits 2 and 7 set before,.. */

    TM4C_spi_init(SPI_MOD_0); /* .. after bits 1 and 7 will be set.  */
    TEST_ASSERT_EQUAL_HEX32(0x81u, SYSCTL->RCGCSSI);


    /* Should handle multiple options. */
    TM4C_spi_init((SPI_MOD_1 | SPI_MOD_3)); 
    TEST_ASSERT_EQUAL_HEX32(0x8Au, SYSCTL->RCGCSSI);



}

void test_TM4C_spi_init_should_initialize_RCGCGPIO_Register(void) {
    
    /* Simulate reg. preinitialized. */
    SYSCTL->RCGCGPIO = 0x11111010u; /* Bits 28, 24, 20, 16, 12, and 4 set. */

    TM4C_spi_init(SPI_MOD_0); /* Port A */
    TEST_ASSERT_EQUAL_HEX32(0x11111011u, SYSCTL->RCGCGPIO);


    SYSCTL->RCGCGPIO = 0x11111010u;

    TM4C_spi_init((SPI_MOD_0 | SPI_MOD_2 | SPI_MOD_3)); /* Port A, B, D. */
    TEST_ASSERT_EQUAL_HEX32(0x1111101Bu, SYSCTL->RCGCGPIO);

    /* Test all options. */
    SYSCTL->RCGCGPIO = 0x0u;
    TM4C_spi_init((SPI_MOD_0 | SPI_MOD_1 | SPI_MOD_2 | SPI_MOD_3)); 
    TEST_ASSERT_EQUAL_HEX32(0x2Bu, SYSCTL->RCGCGPIO);



}

void test_TM4C_spi_init_should_initialize_GPIOAFSEL_Register(void) {

}



int main() {
    
    UNITY_BEGIN()

    RUN_TEST(test_TM4C_spi_init_should_initialize_RCGCSSI_Register);
    RUN_TEST(test_TM4C_spi_init_should_initialize_RCGCGPIO_Register);

    return UNITY_END();
}