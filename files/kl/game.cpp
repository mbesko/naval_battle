#include "Game.h"

// Конструктор
Game::Game() {
    
}

// Реализация метода start
void Game::start() {
        cout << "Sea battle 3.0 \n";
        while (true) {
            try {
            cout << "Do you want to play again? (0/any number = no/yes)\n";
            int val;
            cin >> val;
            if (val) {
                startNewGame();
            } else {
                break;
            }
            } catch (const exception& e) {
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
        }
        

    
}

// Реализация метода startNewGame
void Game::startNewGame() {
    cout << "Do you want to load a previous save? (0/ any number)\n";
    int num;
    while (!(cin >> num)) {
            // Если ввод не корректный
            cout << "Invalid input. Please enter a valid number.\n";
            cin.clear(); // Сбрасываем флаг ошибки
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорируем некорректные данные
            continue;
        }
    GameBoard playerBoard(9,9), enemyBoard(9,9);
    vector<Ship> enemyShips;
    ShipManager playerManager(0,enemyShips), enemyManager(0, enemyShips);
    AbilitiesManager abilitiesManager(playerBoard,playerManager);
    Game_State state("saves/enemy","saves/player");
    try
    {
        if(num) {
            state.loadData(playerBoard, enemyBoard, playerManager, enemyManager, abilitiesManager);
        } else {
        int w = 9, h = 9;
        vector<int> numOfShips(4,1);
        vector<Ship> enemyShips;
        int k1;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < numOfShips[i]; j++) {
                Ship* ship = enemyBoard.createRandomShip(i + 1, 1);
                if (ship != nullptr) {
                    enemyShips.push_back(*ship);
                }
            }
        }
        k1 = enemyShips.size();
        ShipManager startEnemyManager(k1, enemyShips);
        AbilitiesManager startAbilitiesManager(enemyBoard, enemyManager);
        vector<Ship> playerShips;
        int k2 = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < numOfShips[i]; j++) {
                Ship* ship = playerBoard.createRandomShip(i + 1, 2);
                if (ship != nullptr) {
                   playerShips.push_back(*ship);
                }
            }
        }
        ShipManager startPlayerManager(k2, playerShips);
        playerManager = startPlayerManager;
        enemyManager = startEnemyManager;
        abilitiesManager.update(enemyBoard,enemyManager);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    int k = enemyManager.getNumAliveShips(), k0 = k;
    Enemy enemy(playerBoard,playerManager);
    while (k != 0 && k0 != 0) {
        try {
        enemyBoard.printBoard(false);
        playerBoard.printBoard(true);
        cout << "There are only " << k << " living enemy ships.\n";
        cout << "Enter the action number:\n1 - Attack the cell.\n2 - Apply the ability.\n3 - Save the game and exit\n";
        int num;
        if (!(cin >> num)) {
                // Если ввод не корректный
                cout << "Invalid input. Please enter a valid number.\n";
                cin.clear(); // Сбрасываем флаг ошибки
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорируем некорректные данные
                continue;
        }
        if (num == 1) {
            cout << "Enter the coordinates of the attacked cell: 'x' 'y'.\n";
            int x, y;
            cin >> x >> y;
            enemyBoard.attackCell(x, y, false);
            int ind = enemyManager.getShipInd(x, y);
            if (ind != -1) {
                enemyManager.takeDamageByIndex(ind, x, y);
            }
        } else if (num == 2) {
            abilitiesManager.popAndUse();
        } else if (num == 3) {
            state.saveData(playerBoard, enemyBoard, playerManager, enemyManager, abilitiesManager);
            break;
        } else if(num == 1928) {
            cout << "The cheat code is activated!\n";
            enemyManager.printAllShipsCoordinates();
        } else {
            cout << "Invalid number\n";
            continue;
        }
        int kNew = enemyManager.getNumAliveShips();
        if (kNew != k) {
            abilitiesManager.pushAbilityByIndex(abilitiesManager.getRandomIndex());
            k = kNew;
            cout << "A new ability has been obtained!\n";
        }
        k0 = playerManager.getNumAliveShips();
        enemy.enemyAttack();
        k = enemyManager.getNumAliveShips();
        } catch (const exception& e) {
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
    }
    if(k == 0) {
        cout << "WINNER!!!\n";
        state.saveData(playerBoard, enemyBoard, playerManager, enemyManager, abilitiesManager);
    } else if (k0 == 0) {
        cout << "LOSER!!!\n";
    }
}
