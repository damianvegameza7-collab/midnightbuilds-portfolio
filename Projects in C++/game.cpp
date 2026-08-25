#include "rpg.hpp"
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

//Enemy Implementation
Enemy::Enemy(string name, int health, int attackPower, int defense, int expReward, int goldReward, bool isBoss)
    : name(name), health(health), maxHealth(health), attackPower(attackPower),
      defense(defense), expReward(expReward), goldReward(goldReward), isBoss(isBoss) {}

    string Enemy::getName() const { 
    return name; 
    }
    int Enemy::getHealth() const { 
    return health; 
    }
    int Enemy::getMaxHealth() const { 
    return maxHealth; 
    }
    int Enemy::getAttackPower() const {
     return attackPower; 
    }
    int Enemy::getDefense() const { 
    return defense; 
    }
    int Enemy::getExpReward() const { 
    return expReward; 
    }
    int Enemy::getGoldReward() const { 
    return goldReward; 
    }
    bool Enemy::getIsBoss() const {
        return isBoss;
    }

void Enemy::takeDamage(int damage) {
    int actualDamage = max(1, damage - defense);
    health -= actualDamage;
    if (health < 0) health = 0;
}

bool Enemy::isAlive() const { 
    return health > 0; 
    }

void Enemy::printStats() const {
    cout << "\n  Enemy: " << name << "\n";
    cout << "  HP: " << health << "/" << maxHealth
         << "  | ATK: " << attackPower
         << "  | DEF: " << defense << "\n";
}

Player::Player(string name)
    : name(name), health(100), maxHealth(100), attackPower(15),
      defense(5), level(1), experience(0), expToNextLevel(100), gold(50) {
    inventory.push_back({"Health Potion", 30});
    inventory.push_back({"Health Potion", 30});
}

    string Player::getName() const { 
    return name; 
    }
    int Player::getHealth() const { 
    return health; 
    }
    int Player::getMaxHealth() const { 
    return maxHealth; 
    }
    int Player::getAttackPower() const { 
    return attackPower; 
    }
    int Player::getDefense() const { 
    return defense; 
    }
    int Player::getLevel() const { 
    return level; 
    }
    int Player::getGold() const { 
    return gold; 
    }
    int Player::getExperience() const { 
    return experience; 
    }
    int Player::getExpToNextLevel() const { 
    return expToNextLevel; 
    }

void Player::takeDamage(int damage) {
    int actualDamage = max(1, damage - defense);
    health -= actualDamage;
    if (health < 0) health = 0;
}

bool Player::isAlive() const { 
    return health > 0; 
    }

void Player::gainExperience(int exp) {
    experience += exp;
    cout << "  + " << exp << " EXP\n";
    if (experience >= expToNextLevel)
        levelUp();
}

void Player::gainGold(int amount) {
    gold += amount;
    if(amount > 0)
    cout << "  + " << amount << " Gold\n";
}

void Player::levelUp() {
    level++;
    experience -= expToNextLevel;
    expToNextLevel = level * 100;
    maxHealth += 20;
    health = maxHealth;
    attackPower += 5;
    defense += 2;
    cout << "\n You leveled up! You are now level " << level << "!\n";
    cout << "  Max HP +" << 20 << "  | ATK +" << 5 << "  | DEF +" << 2 << "\n";
}

void Player::heal(int amount) {
    health = min(maxHealth, health + amount);
    }

void Player::addItem(Item item) {
    inventory.push_back(item);
    cout << "  Added " << item.name << " to inventory.\n";
    }

bool Player::usePotion() {
    for (int i = 0; i < (int)inventory.size(); i++) {
        if (inventory[i].healAmount > 0) {
            heal(inventory[i].healAmount);
            cout << "  Used " << inventory[i].name
                 << "! Restored " << inventory[i].healAmount << " HP.\n";
            inventory.erase(inventory.begin() + i);
            return true;
        }
    }
    cout << "  No potions left!\n";
    return false;
}

void Player::printStats() const {
    cout << "\n  ╔══════════════════════════════════╗\n";
    cout << "  ║  " << left << setw(32) << ("  " + name + " | LVL " + to_string(level)) << "║\n";
    cout << "  ╠══════════════════════════════════╣\n";
    cout << "  ║  HP:  " << setw(5) << health << "/ " << setw(5) << maxHealth
         << "                   ║\n";
    cout << "  ║  ATK: " << setw(27) << attackPower  << "║\n";
    cout << "  ║  DEF: " << setw(27) << defense      << "║\n";
    cout << "  ║  EXP: " << setw(5) << experience << "/ " << setw(5) << expToNextLevel
         << "                   ║\n";
    cout << "  ║  Gold:" << setw(27) << gold          << "║\n";
    cout << "  ╚══════════════════════════════════╝\n";
}

void Player::printInventory() const {
    cout << "\n  Inventory:\n";
    if (inventory.empty()) {
        cout << "  (empty)\n";
        return;
    }
        for (const auto& item : inventory)
            cout << "  - " << item.name << " (Heals " << item.healAmount << " HP)\n";
}
    
//Added location block and removed old generateEnemy()
    Location::Location(string name, string description, string enemyDefeatedMsg,
    LocationType type, int diffcultyScaling) : name(name), description(description),
    enemyDefeatedMsg(enemyDefeatedMsg), type(type), difficultyScaling(difficultyScaling) {}

    string Location::getName() const {
        return name;
        }
    string Location::getDescription() const {
        return description;
        }
    string Location::getEnemyDefeatedMsg() const {
        return enemyDefeatedMsg;
        }
    LocationType Location::getType() const {
        return type;
        }
    int Location::getDifficultyScaling() const {
        return difficultyScaling;
        }
    //Implementation of game with added locations feature
Game::Game() : player(nullptr), enemiesDefeated(0), dungeonFloor(1),
bossDefeated(false), currentLocation(LocationType::DARK_FOREST) {
    srand(time(NULL));

    locations.push_back(Location(
        "Dark Forest",
        "An eerie forest filled with shadows and dark trees.\nWeak enemies roam here.",
        "Multiple creature stare at you in the abyss of the forest.",
        LocationType::DARK_FOREST, 1
    ));
    locations.push_back(Location(
        "Cave",
        "A damp, lightless cave echoing with dripping water and screams.\nTougher enemies lurk within.",
        "Monsters collapses and sense your presence near.",
        LocationType::CAVE, 2
    ));
    locations.push_back(Location(
        "Castle",
        "A palatial but dangerous castle filled with guards armed to the bone.\nStrong enemies patrol every hall.",
        "No guard has fallen with a strike of metal.",
        LocationType::CASTLE, 3
    ));
    locations.push_back(Location(
        "Dungeon",
        "A terrifying dungeon beneath the castle.\nThe most damgerous enemies await your welcome — including something strong.",
        "You descend deeper into the dungeon...",
        LocationType::DUNGEON, 4
    ));
}

Game::~Game() {
    delete player;
}

Enemy Game::generateEnemy(LocationType loc) {
     int s = enemiesDefeated / 3;

        if (loc == LocationType::DARK_FOREST) {
        int roll = rand() % 4;
        if (roll == 0) return Enemy("Goblin",    30 + s*3,  8 + s, 2, 20 + s*4, 10 + s*2);
        if (roll == 1) return Enemy("Wolf",       35 + s*3, 10 + s, 1, 22 + s*4, 12 + s*2);
        if (roll == 2) return Enemy("Bandit",     40 + s*4, 12 + s, 3, 25 + s*5, 15 + s*2);
        else           return Enemy("Dark Elf",   38 + s*4, 14 + s, 2, 28 + s*5, 18 + s*2);

    } else if (loc == LocationType::CAVE) {
        int roll = rand() % 4;
        if (roll == 0) return Enemy("Cave Bat",    40 + s*4,  9 + s, 2, 30 + s*5, 15 + s*3);
        if (roll == 1) return Enemy("Troll",        60 + s*6, 13 + s, 5, 40 + s*6, 22 + s*3);
        if (roll == 2) return Enemy("Cave Spider",  45 + s*5, 15 + s, 3, 38 + s*6, 20 + s*3);
        else           return Enemy("Stone Golem",  70 + s*7, 11 + s, 7, 45 + s*7, 25 + s*3);

    } else if (loc == LocationType::CASTLE) {
        int roll = rand() % 4;
        if (roll == 0) return Enemy("Knight",      65 + s*6, 14 + s, 7, 50 + s*7, 28 + s*4);
        if (roll == 1) return Enemy("Archer",       50 + s*5, 18 + s, 4, 48 + s*7, 25 + s*4);
        if (roll == 2) return Enemy("Wizard",       55 + s*5, 20 + s, 3, 52 + s*8, 30 + s*4);
        else           return Enemy("Royal Guard",  75 + s*7, 16 + s, 8, 55 + s*8, 32 + s*4);

    } else {
        int roll = rand() % 4;
        if (roll == 0) return Enemy("Demon",         80 + s*8,  18 + s, 6,  60 + s*8,  35 + s*5);
        if (roll == 1) return Enemy("Skeleton",       70 + s*7,  16 + s, 5,  55 + s*7,  30 + s*5);
        if (roll == 2) return Enemy("Shadow Beast",   90 + s*9,  20 + s, 7,  65 + s*9,  40 + s*5);
        else           return Enemy("Death Knight",  100 + s*10, 22 + s, 8,  70 + s*10, 45 + s*5);
    }
}

    Enemy Game::generateBoss() {
        return Enemy(" The Dark Lord", 300, 35, 15, 500, 200, true);
    }

void Game::combat(Enemy& enemy) {
    cout << "\n  A wild " << enemy.getName() << " appears\n";
    enemy.printStats();

    while (player->isAlive() && enemy.isAlive()) {
        cout << "\n  Your HP: " << player->getHealth() << "/" << player->getMaxHealth()
             << "  |  " << enemy.getName() << " HP: "
             << enemy.getHealth() << "/" << enemy.getMaxHealth() << "\n";

        cout << "\n  What will you do?\n";
        cout << "  1. Attack\n";
        cout << "  2. Use Potion\n";
        cout << "  3. Run\n";
        cout << "  Choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            int damage = player->getAttackPower() + (rand() % 5);
            enemy.takeDamage(damage);
            cout << "  You attack " << enemy.getName()
                 << " for " << max(1, damage - enemy.getDefense()) << " damage!\n";

            if (!enemy.isAlive()) {
                cout << "\n  You defeated " << enemy.getName() << "!\n";
                player->gainExperience(enemy.getExpReward());
                player->gainGold(enemy.getGoldReward());
                enemiesDefeated++;
                if (enemy.getIsBoss()) {   // ✔ has ()
                    bossDefeated = true;
                    cout << "\n  YOU DEFEATED THE FINAL BOSS!\n";
                    cout << "  The kingdom is saved, or is it?\n";
                }
                return;
            }

        } else if (choice == 2) {
            player->usePotion();

        } else if (choice == 3) {
            if (enemy.getIsBoss()) {
                cout << "  You cannot run from the boss\n";
            } else if (rand() % 2 == 0) {
                cout << "  You successfully ran away!\n";
                return;
            } else {
                cout << "  You failed to run!\n";
            }

        } else {
            cout << "  Invalid choice.\n";
            continue;
        }

        // ✔ Enemy attack is outside all choice blocks
        if (enemy.isAlive()) {
            int enemyDamage = enemy.getAttackPower() + (rand() % 4);
            player->takeDamage(enemyDamage);
            cout << "  " << enemy.getName() << " attacks you for "
                 << max(1, enemyDamage - player->getDefense()) << " damage\n";

            if (!player->isAlive()) {
                cout << "\n  You were defeated by " << enemy.getName() << "...\n";
                return;
            }
        }
    }
}

void Game::visitShop() {
    cout << "\n  ╔══════════════════════════════╗\n";
    cout << "  ║             SHOP            ║\n";
    cout << "  ╠══════════════════════════════╣\n";
    cout << "  ║  1. Health Potion    (20g)   ║\n";
    cout << "  ║  2. Large Potion     (40g)   ║\n";
    cout << "  ║  3. Leave shop               ║\n";
    cout << "  ╚══════════════════════════════╝\n";
    cout << "  Gold: " << player->getGold() << "\n";
    cout << "  Choice: ";

    int choice;
    cin >> choice;

    if (choice == 1) {
        if (player->getGold() >= 20) {
            player->gainGold(-20);
            player->addItem({"Health Potion", 30});
        } else {
            cout << "  Not enough gold\n";
        }
    } else if (choice == 2) {
        if (player->getGold() >= 40) {
            player->gainGold(-40);
            player->addItem({"Large Potion", 60});
        } else {
            cout << "  Not enough gold\n";
        }
    } else {
        cout << "  Leaving shop...\n";
    }
}

void Game::printWorldMap() {
    cout << "\n  ╔══════════════════════════════════════╗\n";
    cout << "  ║              WORLD MAP              ║\n";
    cout << "  ╠══════════════════════════════════════╣\n";
    cout << "  ║  1. Dark Forest  (Recruit)           ║\n";
    cout << "  ║  2. Cave         (Regular)         ║\n";
    cout << "  ║  3. Castle       (Hardened)           ║\n";
    cout << "  ║  4. Dungeon      (Veteran)      ║\n";
    cout << "  ║  5. Back                             ║\n";
    cout << "  ╚══════════════════════════════════════╝\n";

    string locName;
    if      (currentLocation == LocationType::DARK_FOREST) locName = "Dark Forest";
    else if (currentLocation == LocationType::CAVE)        locName = "Cave";
    else if (currentLocation == LocationType::CASTLE)      locName = "Castle";
    else                                                    locName = "Dungeon";
    cout << "  Current location: " << locName << "\n";
    cout << "  Choice: ";
}

void Game::exploreLocation(LocationType loc) {
    for (const auto& l : locations) {
        if (l.getType() == loc) {
            cout << "\n  " << string(42, '=') << "\n";
            cout << "  " << l.getName() << "\n";
            cout << "  " << l.getDescription() << "\n";
            cout << "  " << string(42, '=') << "\n";
            break;
        }
    }

    if (loc == LocationType::DUNGEON) {
        cout << "\n  Dungeon Floor: " << dungeonFloor << "\n";
        cout << "  1. Fight enemy\n";
        cout << "  2. Fight Final Boss\n";
        cout << "  3. Leave dungeon\n";
        cout << "  Choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            Enemy enemy = generateEnemy(loc);
            combat(enemy);
            if (!player->isAlive()) return;
            dungeonFloor++;
        } else if (choice == 2) {
            if (bossDefeated) {
                cout << "  You have already defeated the Dark Lord\n";
            } else {
                Enemy boss = generateBoss();
                combat(boss);
            }
        } else {
            cout << "  You leave the dungeon.\n";
        }
    } else {
        cout << "\n  1. Explore (find enemy)\n";
        cout << "  2. Leave\n";
        cout << "  Choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            Enemy enemy = generateEnemy(loc);
            combat(enemy);
        } else {
            cout << "  You leave the area.\n";
        }
    }
}

void Game::printMainMenu() {
    cout << "\n  ╔══════════════════════════════╗\n";
    cout << "  ║          Journey   ║\n";
    cout << "  ╠══════════════════════════════╣\n";
    cout << "  ║  1. Travel (World Map)       ║\n";
    cout << "  ║  2. Explore (find enemy)     ║\n";
    cout << "  ║  3. View Stats               ║\n";
    cout << "  ║  4. View Inventory           ║\n";
    cout << "  ║  5. Visit Shop               ║\n";
    cout << "  ║  6. Rest (restore 20 HP)     ║\n";
    cout << "  ║  7. Quit                     ║\n";
    cout << "  ╚══════════════════════════════╝\n";
    cout << "  Choice: ";
}

void Game::start() {
    cout << "\n  ╔══════════════════════════════╗\n";
    cout << "  ║     Welcome to Journey!    ║\n";
    cout << "  ╚══════════════════════════════╝\n";
    cout << "\n  Enter your character name: ";

    string name;
    cin.ignore();
    getline(cin, name);

    player = new Player(name);
    cout << "\n  Welcome, " << name << "! Your adventure begins...\n";
    cout << "  You start with 2 Health Potions and 50 Gold.\n";

    int option;
        while (true) {
        printMainMenu();
        cin >> option;

        if (option == 1) {
            printWorldMap();
            int dest;
            cin >> dest;
            if      (dest == 1) { currentLocation = LocationType::DARK_FOREST; cout << "  You travel to the Dark Forest.\n"; }
            else if (dest == 2) { currentLocation = LocationType::CAVE;         cout << "  You travel to the Cave.\n"; }
            else if (dest == 3) { currentLocation = LocationType::CASTLE;       cout << "  You travel to the Castle.\n"; }
            else if (dest == 4) { currentLocation = LocationType::DUNGEON;      cout << "  You travel to the Dungeon.\n"; }
            else                { cout << "  Staying put.\n"; }

        } else if (option == 2) {
            exploreLocation(currentLocation);
            if (!player->isAlive()) {
                cout << "\n  Game Over! You were defeated after killing "
                     << enemiesDefeated << " enemies.\n";
                break;
            }
            if (bossDefeated) {
                cout << "\n Congratulations! You completed the game!\n";
                cout << "  Enemies defeated: " << enemiesDefeated << "\n";
                break;
            }

        } else if (option == 3) {
            player->printStats();

        } else if (option == 4) {
            player->printInventory();

        } else if (option == 5) {
            visitShop();

        } else if (option == 6) {
            player->heal(20);
            cout << "  You rest and restore 20 HP. Current HP: "
                 << player->getHealth() << "/" << player->getMaxHealth() << "\n";

        } else if (option == 7) {
            cout << "\n  Thanks for playing! You defeated "
                 << enemiesDefeated << " enemies.\n\n";
            break;

        } else {
            cout << "  Invalid option. Choose 1-7.\n";
        }
    }
}