#ifndef RPG_CPP
#define RPG_CPP
#include <iostream>
#include <vector>
using namespace std;
    //Item class
struct Item{
    string name;
    int healAmount;
};
    //Enemy class
    class Enemy {
        private:
        string name;
        int health;
        int maxHealth;
        int attackPower;
        int defense;
        int expReward;
        int goldReward;
        bool isBoss;

    public:
        Enemy(string name, int health, int attackPower, int defense, 
            int expReward, int goldReward, bool isBoss = false);

        string getName() const;
        int getHealth() const;
        int getMaxHealth() const;
        int getAttackPower() const;
        int getDefense() const;
        int getExpReward() const;
        int getGoldReward() const;
        bool getIsBoss() const;

        void takeDamage(int damage);
        bool isAlive() const;
        void printStats() const;
    };
    //Player class, all player functions inside Player
    class Player {
        private:
        string name;
        int health;
        int maxHealth;
        int attackPower;
        int defense;
        int level;
        int experience;
        int expToNextLevel;
        int gold;
        vector<Item> inventory;
    public:
    Player(string name);
        string getName()const;
        int getHealth() const;
        int getMaxHealth() const;
        int getAttackPower() const;
        int getDefense() const;
        int getLevel() const;
        int getGold() const;
        int getExperience() const;
        int getExpToNextLevel() const;

        void takeDamage(int damage);
        bool isAlive() const;
        void gainExperience(int exp);
        void gainGold(int amount);
        void levelUp();
        void heal(int amount);
        void addItem(Item item);
        bool usePotion();
        void printStats() const;
        void printInventory() const;
    };
    //Location class, added location feature
    enum class LocationType {
        DARK_FOREST, CAVE, CASTLE, DUNGEON
    };

    class Location{
        private:
        string name;
        string description;
        string enemyDefeatedMsg;
        LocationType type;
        int difficultyScaling;

        public:
        Location(string name, string description, string enemyDefeatedMsg,
        LocationType type, int diffcultyScaling);

        string getName() const;
        string getDescription() const;
        string getEnemyDefeatedMsg() const;
        LocationType getType() const;
        int getDifficultyScaling() const;
    };

    class Game {
        private:
        Player* player;
        int enemiesDefeated;
    //Added location functions
        int dungeonFloor;
        bool bossDefeated;
        vector<Location> locations;
        LocationType currentLocation;

        Enemy generateEnemy(LocationType loc);
        Enemy generateBoss();
        void combat(Enemy& enemy);
        void visitShop();
        void exploreLocation(LocationType loc);
        void printLocationMenu();
        void printWorldMap();

    public:
    Game();
    ~Game();
    void start();
    void printMainMenu();
    };
    #endif
