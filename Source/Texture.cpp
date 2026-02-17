#include "../Include/Texture.h"
#include "../Include/TGAReader.h"

ObjectPool<Texture>* Texture::Pool = nullptr;

Texture::Texture() : m_imageInfo(nullptr) {
}

Texture::~Texture() {
    Unload();
}

bool Texture::Load(const std::string& filepath) {
    m_filepath = filepath;
    m_imageInfo = TGAReader::ReadTGA(filepath);
    return m_imageInfo != nullptr;
}

void Texture::Unload() {
    if (m_imageInfo) {
        if (m_imageInfo->Data) {
            delete[] m_imageInfo->Data;
        }
        delete m_imageInfo;
        m_imageInfo = nullptr;
    }
}

void Texture::Serialize(std::ostream& stream) {
    size_t pathLen = m_filepath.length();
    stream.write(reinterpret_cast<const char*>(&pathLen), sizeof(size_t));
    stream.write(m_filepath.c_str(), pathLen);
}

void Texture::Deserialize(std::istream& stream) {
    size_t pathLen;
    stream.read(reinterpret_cast<char*>(&pathLen), sizeof(size_t));
    char* pathBuffer = new char[pathLen + 1];
    stream.read(pathBuffer, pathLen);
    pathBuffer[pathLen] = '\0';
    m_filepath = pathBuffer;
    delete[] pathBuffer;

    // Reload texture
    Load(m_filepath);
}
