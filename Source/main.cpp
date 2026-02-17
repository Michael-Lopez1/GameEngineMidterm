#include "../Include/GameController.h"

int main(int argc, char* argv[]) {
    GameController* game = GameController::GetInstance();
    game->RunGame();
    GameController::DestroyInstance();

    return 0;
}
