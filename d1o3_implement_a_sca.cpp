#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Forward declarations
class Game;
class GamePrototype;
class Integrator;

// Game Prototype class
class GamePrototype {
public:
    virtual ~GamePrototype() {}
    virtual void initialize() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual std::string getName() = 0;
};

// Game class
class Game : public GamePrototype {
private:
    std::string name;
public:
    Game(const std::string& name) : name(name) {}
    void initialize() override { std::cout << "Initializing " << name << std::endl; }
    void update() override { std::cout << "Updating " << name << std::endl; }
    void render() override { std::cout << "Rendering " << name << std::endl; }
    std::string getName() override { return name; }
};

// Integrator class
class Integrator {
private:
    std::vector<std::unique_ptr<GamePrototype>> games;
public:
    void addGame(std::unique_ptr<GamePrototype> game) { games.push_back(std::move(game)); }
    void integrate() {
        for (auto& game : games) {
            game->initialize();
            game->update();
            game->render();
        }
    }
};

int main() {
    Integrator integrator;
    integrator.addGame(std::make_unique<Game>("Game 1"));
    integrator.addGame(std::make_unique<Game>("Game 2"));
    integrator.integrate();
    return 0;
}