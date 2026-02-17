#pragma once

#include "StandardIncludes.h"
#include "Asset.h"

class TGAReader {
public:
    static ImageInfo* ReadTGA(const std::string& filepath);

private:
    #pragma pack(push, 1)
    struct TGAHeader {
        unsigned char idLength;
        unsigned char colorMapType;
        unsigned char imageType;
        unsigned short colorMapOrigin;
        unsigned short colorMapLength;
        unsigned char colorMapDepth;
        unsigned short xOrigin;
        unsigned short yOrigin;
        unsigned short width;
        unsigned short height;
        unsigned char bitsPerPixel;
        unsigned char imageDescriptor;
    };
    #pragma pack(pop)
};
