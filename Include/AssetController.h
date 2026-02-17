#pragma once

#include "StandardIncludes.h"
#include "Singleton.h"
#include "StackAllocator.h"
#include "Asset.h"
#include <map>

class AssetController : public Singleton<AssetController> {
public:
    AssetController();
    virtual ~AssetController();

    void Initialize(size_t stackSize);
    void Shutdown();

    Asset* LoadAsset(const std::string& filepath);
    void UnloadAsset(const std::string& filepath);

private:
    StackAllocator* m_allocator;
    std::map<std::string, Asset*> m_assets;
};
