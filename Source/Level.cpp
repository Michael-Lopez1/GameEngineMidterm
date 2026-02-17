#include "../Include/Level.h"
#include "../Include/FileController.h"

Level::Level(int levelNumber)
    : m_levelNumber(levelNumber), m_gameTime(0.0f), m_autoSaved(false),
      m_backgroundColor{0, 0, 0, 255} {
}

Level::~Level() {
    // Warriors are managed by pool, don't delete
}

void Level::SaveToFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to save level to: " << filename << std::endl;
        return;
    }

    Serialize(file);
    file.close();

    std::cout << "Level saved to: " << filename << std::endl;
}

Level* Level::LoadFromFile(const std::string& filename, int levelNumber) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to load level from: " << filename << std::endl;
        return nullptr;
    }

    // We can't create level here as it's abstract
    // This will be handled by specific level classes
    file.close();
    return nullptr;
}

void Level::Serialize(std::ostream& stream) {
    stream.write(reinterpret_cast<const char*>(&m_levelNumber), sizeof(int));
    stream.write(reinterpret_cast<const char*>(&m_gameTime), sizeof(float));
    stream.write(reinterpret_cast<const char*>(&m_autoSaved), sizeof(bool));
    stream.write(reinterpret_cast<const char*>(&m_backgroundColor), sizeof(SDL_Color));

    // Serialize warriors
    size_t warriorCount = m_warriors.size();
    stream.write(reinterpret_cast<const char*>(&warriorCount), sizeof(size_t));

    for (Warrior* warrior : m_warriors) {
        warrior->Serialize(stream);
    }
}

void Level::Deserialize(std::istream& stream) {
    stream.read(reinterpret_cast<char*>(&m_levelNumber), sizeof(int));
    stream.read(reinterpret_cast<char*>(&m_gameTime), sizeof(float));
    stream.read(reinterpret_cast<char*>(&m_autoSaved), sizeof(bool));
    stream.read(reinterpret_cast<char*>(&m_backgroundColor), sizeof(SDL_Color));

    // Deserialize warriors
    size_t warriorCount;
    stream.read(reinterpret_cast<char*>(&warriorCount), sizeof(size_t));

    m_warriors.clear();
    for (size_t i = 0; i < warriorCount; ++i) {
        Warrior* warrior = Warrior::Pool->GetResource();
        warrior->Deserialize(stream);
        m_warriors.push_back(warrior);
    }
}
