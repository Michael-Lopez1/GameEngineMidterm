#pragma once

#include "Serializable.h"

class Asset;

class Resource : public Serializable {
public:
    Resource() {}
    virtual ~Resource() {}

    virtual void Serialize(std::ostream& stream) override {}
    virtual void Deserialize(std::istream& stream) override {}

    // Helper methods for asset serialization
    static void SerializeAsset(std::ostream& stream, const void* data, size_t size) {
        stream.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
        stream.write(reinterpret_cast<const char*>(data), size);
    }

    static void DeserializeAsset(std::istream& stream, void*& data, size_t& size) {
        stream.read(reinterpret_cast<char*>(&size), sizeof(size_t));
        data = malloc(size);
        stream.read(reinterpret_cast<char*>(data), size);
    }
};
