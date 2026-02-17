#include "../Include/AssetController.h"
#include "../Include/FileController.h"

AssetController::AssetController() : m_allocator(nullptr) {
}

AssetController::~AssetController() {
    Shutdown();
}

void AssetController::Initialize(size_t stackSize) {
    m_allocator = new StackAllocator(stackSize);
}

void AssetController::Shutdown() {
    for (auto& pair : m_assets) {
        delete pair.second;
    }
    m_assets.clear();

    if (m_allocator) {
        delete m_allocator;
        m_allocator = nullptr;
    }
}

Asset* AssetController::LoadAsset(const std::string& filepath) {
    // Check if already loaded
    auto it = m_assets.find(filepath);
    if (it != m_assets.end()) {
        return it->second;
    }

    // Load new asset
    std::vector<unsigned char> data;
    if (!FileController::GetInstance()->ReadFile(filepath, data)) {
        return nullptr;
    }

    // Allocate from stack
    void* memory = m_allocator->Allocate(data.size());
    if (!memory) {
        std::cerr << "Stack allocator out of memory!" << std::endl;
        return nullptr;
    }

    memcpy(memory, data.data(), data.size());

    Asset* asset = new Asset();
    asset->SetData(memory, data.size());
    m_assets[filepath] = asset;

    return asset;
}

void AssetController::UnloadAsset(const std::string& filepath) {
    auto it = m_assets.find(filepath);
    if (it != m_assets.end()) {
        delete it->second;
        m_assets.erase(it);
    }
}
