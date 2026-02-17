#pragma once

#include "StandardIncludes.h"
#include "Resource.h"
#include "Asset.h"
#include "ObjectPool.h"

class Texture : public Resource {
public:
    Texture();
    virtual ~Texture();

    bool Load(const std::string& filepath);
    void Unload();

    ImageInfo* GetImageInfo() const { return m_imageInfo; }
    void* GetData() const { return m_imageInfo ? m_imageInfo->Data : nullptr; }

    virtual void Serialize(std::ostream& stream) override;
    virtual void Deserialize(std::istream& stream) override;

    static ObjectPool<Texture>* Pool;

private:
    ImageInfo* m_imageInfo;
    std::string m_filepath;
};
