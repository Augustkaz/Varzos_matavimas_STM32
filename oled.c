#include "oled.h"
#include <stdio.h>
#include <string.h>

extern I2C_HandleTypeDef hi2c1;
#define OLED_ADDR 0x78

const uint8_t font5x7[][5] = {
    {0x3E,0x51,0x49,0x45,0x3E}, // 0
    {0x00,0x42,0x7F,0x40,0x00}, // 1
    {0x42,0x61,0x51,0x49,0x46}, // 2
    {0x21,0x41,0x45,0x4B,0x31}, // 3
    {0x18,0x14,0x12,0x7F,0x10}, // 4
    {0x27,0x45,0x45,0x45,0x39}, // 5
    {0x3C,0x4A,0x49,0x49,0x30}, // 6
    {0x01,0x71,0x09,0x05,0x03}, // 7
    {0x36,0x49,0x49,0x49,0x36}, // 8
    {0x06,0x49,0x49,0x29,0x1E}, // 9
    {0x7F,0x09,0x19,0x29,0x46}, 
    {0x14,0x14,0x14,0x14,0x14},  
		{0x1F,0x20,0x40,0x20,0x1F},
		{0x2C, 0x32, 0x02, 0x32, 0x2C}		
};

void OLED_Command(uint8_t cmd) {
    uint8_t data[2] = {0x00, cmd};
    HAL_I2C_Master_Transmit(&hi2c1, OLED_ADDR, data, 2, 100);
}

void OLED_Init(void)
{
    HAL_Delay(100); 

    OLED_Command(0xAE); 

    
    OLED_Command(0xA8); 
    OLED_Command(0x1F); 

    OLED_Command(0xD3); 
    OLED_Command(0x00); 

    OLED_Command(0x40); 

    
    OLED_Command(0xA1); 
    OLED_Command(0xC8); 

    OLED_Command(0xDA); 
    OLED_Command(0x02); 

    OLED_Command(0x81); 
    OLED_Command(0x7F); 

    OLED_Command(0x20); 
    OLED_Command(0x02); 

    OLED_Command(0x8D); 
    OLED_Command(0x14); 

    OLED_Command(0xAF); 
    
    HAL_Delay(50);
}

void OLED_ClearPage(uint8_t page) {
    uint8_t buf[129] = {0x40};
    OLED_Command(0xB0 + page);
    OLED_Command(0x00); OLED_Command(0x10);
    HAL_I2C_Master_Transmit(&hi2c1, OLED_ADDR, buf, 129, 100);
}

void OLED_PrintRes(uint8_t page, uint8_t id, float val) {
    uint8_t buf[129] = {0x40};
    int pos = 1;

    
    for(int i=0; i<5; i++) buf[pos++] = font5x7[10][i]; pos++; 
    for(int i=0; i<5; i++) buf[pos++] = font5x7[id][i]; pos++; 
    for(int i=0; i<5; i++) buf[pos++] = font5x7[11][i]; pos++; 
    
    
    char s[10];
    sprintf(s, "%.1f", val);
    for(int k=0; s[k]; k++) {
        if(s[k]=='.') { buf[pos++]=0x40; pos++; continue; }
        int d = s[k]-'0';
        if(d>=0 && d<=9) {
            for(int i=0; i<5; i++) buf[pos++] = font5x7[d][i];
            pos++;
        }
    }

    pos += 2;
    for(int i = 0; i < 5; i++) {
        if (pos < 128) {
            buf[pos++] = font5x7[13][i]; 
        }
    }
    OLED_Command(0xB0 + page);
    OLED_Command(0x00); 
    OLED_Command(0x10);
    HAL_I2C_Master_Transmit(&hi2c1, 0x78, buf, 129, 100);
}

void OLED_PrintOL(uint8_t page, uint8_t id) {
    uint8_t buf[129] = {0x40};
    int pos = 1;
    for(int i=0; i<5; i++) buf[pos++] = font5x7[10][i]; pos++;
    for(int i=0; i<5; i++) buf[pos++] = font5x7[id][i]; pos++;
    for(int i=0; i<5; i++) buf[pos++] = font5x7[11][i]; pos += 2;
    // "OL"
    uint8_t O[5]={0x3E,0x41,0x41,0x41,0x3E}, L[5]={0x7F,0x40,0x40,0x40,0x40};
    for(int i=0; i<5; i++) buf[pos++] = O[i]; pos++;
    for(int i=0; i<5; i++) buf[pos++] = L[i];
    OLED_Command(0xB0 + page);
    OLED_Command(0x00); OLED_Command(0x10);
    HAL_I2C_Master_Transmit(&hi2c1, OLED_ADDR, buf, 129, 100);
}