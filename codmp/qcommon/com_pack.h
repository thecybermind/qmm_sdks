#pragma once

struct PackedTexCoords 
{                                       
    PackedTexCoords()
    {
        packed = 0;
    }
    PackedTexCoords(unsigned int i)
    {
        packed = i;
    }
    unsigned int packed;
};
