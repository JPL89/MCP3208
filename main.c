// @File		MAIN.C		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		BRAZIL
// @Date		01/05/23
//
//
// Copyright (C) 2023 JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
#include "config.h"
#include "ks0066.h"
#include "mcp3208.h"

void main(void)
{
    __delay_ms(500);
    
    PIC18F2520();
    
    KS0066_Init();
    
    KS0066_Clear(0);
    
    KS0066_Clear(1);
    
    KS0066_Goto(0, 0);
    
    MCP3208_Init(); 
    
    unsigned int data = 0;
    
    while(1)
    {
        data = MCP3208_Read( 4 );
    
        KS0066_Clear(0);
    
        KS0066_Clear(1);
    
        KS0066_Goto(0, 0);
        
        KS0066_Int( data );
    
        __delay_ms( 500 );
    }
    
    return;
}