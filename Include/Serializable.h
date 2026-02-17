#pragma once

#include <iostream>

class Serializable {
public:
    virtual ~Serializable() {}

    virtual void Serialize(std::ostream& stream) = 0;
    virtual void Deserialize(std::istream& stream) = 0;
};
