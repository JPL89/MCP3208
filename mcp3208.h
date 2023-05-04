// @File		MCP3208.H	 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		BRAZIL
// @Date		02/05/23
//
//
// Copyright (C) 2023 JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
#ifndef MCP3208_H
#define MCP3208_H

#define MCP3208_CLK         PORTCbits.RC0
#define MCP3208_DIN         PORTCbits.RC1
#define MCP3208_DOUT        PORTCbits.RC2
#define MCP3208_CS          PORTCbits.RC3

#define MCP3208_CLK_TRIS     TRISCbits.RC0
#define MCP3208_DIN_TRIS     TRISCbits.RC1
#define MCP3208_DOUT_TRIS    TRISCbits.RC2
#define MCP3208_CS_TRIS      TRISCbits.RC3

unsigned int MCP3208_Init(void)
{  
    MCP3208_CLK_TRIS = 0;
    MCP3208_DIN_TRIS = 0;
    MCP3208_DOUT_TRIS = 1;
    MCP3208_CS_TRIS = 0;
    
    MCP3208_CS = 1;
    MCP3208_CLK = 1;
}

unsigned int MCP3208_Read(unsigned char channel)
{
    unsigned int data = 0;
       
    MCP3208_CS = 0;
    
    // START BIT
    MCP3208_CLK = 1;
    MCP3208_DIN = 1;
    MCP3208_CLK = 0;
    
    // DIFF
    MCP3208_CLK = 1;
    MCP3208_DIN = 1;
    MCP3208_CLK = 0;
    
    // D2
    MCP3208_CLK = 1;
    MCP3208_DIN = (channel & 0x04) >> 2;
    MCP3208_CLK = 0;
    
    // D1
    MCP3208_CLK = 1;
    MCP3208_DIN = (channel & 0x02) >> 1;
    MCP3208_CLK = 0;
    
    // D0
    MCP3208_CLK = 1;
    MCP3208_DIN = (channel & 0x01) >> 0;
    MCP3208_CLK = 0;
            
    // X
    MCP3208_CLK = 1;
    MCP3208_DIN = 0;
    MCP3208_CLK = 0;
    
    // X
    MCP3208_CLK = 1;
    MCP3208_DIN = 0;
    MCP3208_CLK = 0;
    
    for(unsigned char bit = 0; bit < 16; bit++)
    {
        data <<= 1;
        
        MCP3208_CLK = 1;                
        if(MCP3208_DOUT) data |= 1;        
        MCP3208_CLK = 0;
    }
    
    MCP3208_CS = 1;
    
    return ( data & 0x0FFF );
}

#endif
