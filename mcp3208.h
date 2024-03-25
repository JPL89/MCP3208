// @File		MCP3208.H		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		BRAZIL
// @Date		21/03/24
//
//
// Copyright (C) 2024 JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
#ifndef MCP3208_H
#define MCP3208_H

#define MCP3208_SCK PORTCbits.RC0
#define MCP3208_SDI PORTCbits.RC1
#define MCP3208_SDO PORTCbits.RC2
#define MCP3208_CS PORTCbits.RC3

#define MCP3208_SCK_TRIS TRISCbits.RC0
#define MCP3208_SDI_TRIS TRISCbits.RC1
#define MCP3208_SDO_TRIS TRISCbits.RC2
#define MCP3208_CS_TRIS TRISCbits.RC3

void SPI_write(unsigned char data)
{
    for(unsigned char mask = 0x80; mask; mask >>=1)
    {
        if(data & mask) MCP3208_SDI = 1; else MCP3208_SDI = 0;
        
        MCP3208_SCK = 1;
        __asm__ __volatile__("nop");
        MCP3208_SCK = 0;        
        __asm__ __volatile__("nop");
    }
}

unsigned char SPI_read(void)
{
    unsigned char data = 0;
    
    for(unsigned char mask = 0x80; mask; mask >>=1)
    {
        data <<= 1;
        if(MCP3208_SDO) data |= 1;
        
        MCP3208_SCK = 1;
        __asm__ __volatile__("nop");
        MCP3208_SCK = 0;        
        __asm__ __volatile__("nop");
    }
    
    return ((unsigned char) data);
}

// BYTE CHANNEL 
// MSB FIRST: 0, START, DIFF, D2, D1, D0, NULL, NULL
unsigned short MCP3208_read(unsigned char ch)
{
    unsigned char msb  = 0;
    unsigned char lsb  = 0;
    
    ch |= (unsigned char) (0x60 | (ch << 2));
    
    MCP3208_CS = 0;
    SPI_write(ch);  
    msb = SPI_read();
    lsb = SPI_read();
    MCP3208_CS = 1;
    
    unsigned short data = (unsigned short) (((msb << 8) | lsb));    
    data = (unsigned short) (data >> 4);    
    return ( (unsigned short) (data));
}

void MCP3208_init(void)
{
    MCP3208_SCK_TRIS = 0;
    MCP3208_SDI_TRIS = 0;
    MCP3208_SDO_TRIS = 1;
    MCP3208_CS_TRIS = 0;
    
    MCP3208_CS = 1;
}


#endif
