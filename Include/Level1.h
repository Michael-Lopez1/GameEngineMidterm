#pragma once

#include "Level.h"

class Level1 : public Level {
public:
    Level1();
    virtual ~Level1();

    virtual void Initialize() override;
    virtual void Update(float deltaTime) override;
    virtual void Render(Renderer* renderer) override;
    virtual bool ShouldTransition() const override;
    virtual bool ShouldQuit() const override { return false; }

    virtual void Serialize(std::ostream& stream) override;
    virtual void Deserialize(std::istream& stream) override;

private:
    void CheckAutoSave();
};
