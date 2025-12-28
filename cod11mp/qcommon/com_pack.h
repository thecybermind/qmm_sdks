#pragma once

struct PackedTexCoords // sizeof=0x4
{                                       // ...
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
