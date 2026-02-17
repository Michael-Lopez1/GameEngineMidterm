#pragma once

#include "StandardIncludes.h"
#include "Resource.h"
#include "Warrior.h"

class Renderer;

class Level : public Resource {
public:
    Level(int levelNumber);
    virtual ~Level();

    virtual void Initialize() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render(Renderer* renderer) = 0;
    virtual bool ShouldTransition() const = 0;
    virtual bool ShouldQuit() const = 0;

    void SaveToFile(const std::string& filename);
    static Level* LoadFromFile(const std::string& filename, int levelNumber);

    int GetLevelNumber() const { return m_levelNumber; }
    float GetGameTime() const { return m_gameTime; }
    bool IsAutoSaved() const { return m_autoSaved; }
    SDL_Color GetBackgroundColor() const { return m_backgroundColor; }
    const std::vector<Warrior*>& GetWarriors() const { return m_warriors; }

    virtual void Serialize(std::ostream& stream) override;
    virtual void Deserialize(std::istream& stream) override;

protected:
    int m_levelNumber;
    float m_gameTime;
    bool m_autoSaved;
    SDL_Color m_backgroundColor;
    std::vector<Warrior*> m_warriors;
};
