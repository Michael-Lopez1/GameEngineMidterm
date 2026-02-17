#pragma once

#include "Level.h"
#include "Rock.h"

class Level2 : public Level {
public:
    Level2(std::vector<Warrior*> warriors);
    virtual ~Level2();

    virtual void Initialize() override;
    virtual void Update(float deltaTime) override;
    virtual void Render(Renderer* renderer) override;
    virtual bool ShouldTransition() const override { return false; }
    virtual bool ShouldQuit() const override;

    virtual void Serialize(std::ostream& stream) override;
    virtual void Deserialize(std::istream& stream) override;

private:
    std::vector<Rock*> m_rocks;

    void CheckAutoSave();
    void CheckCollisions();
    bool CheckAABBCollision(Warrior* w, Rock* r);
};
