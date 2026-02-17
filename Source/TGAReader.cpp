#include "../Include/TGAReader.h"
#include "../Include/FileController.h"

ImageInfo* TGAReader::ReadTGA(const std::string& filepath) {
    std::vector<unsigned char> fileData;
    if (!FileController::GetInstance()->ReadFile(filepath, fileData)) {
        return nullptr;
    }

    if (fileData.size() < sizeof(TGAHeader)) {
        std::cerr << "Invalid TGA file: " << filepath << std::endl;
        return nullptr;
    }

    TGAHeader* header = reinterpret_cast<TGAHeader*>(fileData.data());

    // Support uncompressed RGB/RGBA
    if (header->imageType != 2) { // Type 2 = Uncompressed True-color
        std::cerr << "Unsupported TGA image type: " << (int)header->imageType << std::endl;
        return nullptr;
    }

    int width = header->width;
    int height = header->height;
    int bpp = header->bitsPerPixel;

    if (bpp != 24 && bpp != 32) {
        std::cerr << "Unsupported TGA bit depth: " << bpp << std::endl;
        return nullptr;
    }

    int bytesPerPixel = bpp / 8;
    int imageSize = width * height * bytesPerPixel;

    // Skip ID field and color map
    int dataOffset = sizeof(TGAHeader) + header->idLength + 
                     (header->colorMapType ? header->colorMapLength * (header->colorMapDepth / 8) : 0);

    if (fileData.size() < dataOffset + imageSize) {
        std::cerr << "Invalid TGA file size: " << filepath << std::endl;
        return nullptr;
    }

    // Allocate and copy image data (convert BGR to RGB)
    unsigned char* imageData = new unsigned char[imageSize];
    unsigned char* src = fileData.data() + dataOffset;

    for (int i = 0; i < width * height; ++i) {
        int idx = i * bytesPerPixel;
        imageData[idx + 0] = src[idx + 2]; // R
        imageData[idx + 1] = src[idx + 1]; // G
        imageData[idx + 2] = src[idx + 0]; // B
        if (bpp == 32) {
            imageData[idx + 3] = src[idx + 3]; // A
        }
    }

    ImageInfo* info = new ImageInfo();
    info->Width = width;
    info->Height = height;
    info->BitsPerPixel = bpp;
    info->Data = imageData;

    return info;
}
