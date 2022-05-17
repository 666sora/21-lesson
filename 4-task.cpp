#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

enum command {
    LEFT = 1,
    RIGHT = 2,
    TOP = 4,
    BOTTOM = 8
};

struct Player {
    char name_field = 'P';

    std::string name_player = "";

    int health_points = 0;
    int armor_points = 0;
    int damage = 0;

    int x_player_pos = 0;
    int y_player_pos = 0;
};

struct Enemy {
    char name_field = 'E';

    std::string name_enemy = "Enemy#";

    int health_points = 0;
    int armor_points = 0;
    int damage = 0;

    
    int x_enemy_pos = 0;
    int y_enemy_pos = 0;
};

void show_field (char (&field)[40][40]) {
    for (int i = 0; i < 40; i++) {
        std::cout << " ";
        for (int j = 0; j < 40; j++) {
            std::cout << field[i][j];
        }
        std::cout << std::endl;
    }
}

void save (char (&field)[40][40], Player& player, Enemy (&enemy)[5]) {
    std::ofstream save_data("save.txt");
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            save_data << field[i][j];
        }
        save_data << std::endl;
    }
    save_data << player.name_field << " " << player.name_player << " " << player.health_points << " " << player.armor_points << " " 
        << player.damage << " " << player.x_player_pos << " " << player.y_player_pos << std::endl;
    for (int i = 0; i < 5; i++) {
        save_data << enemy[i].name_field << " " << enemy[i].name_enemy << " " << enemy[i].health_points << " " 
            << enemy[i].armor_points << " " << enemy[i].damage << " " << enemy[i].x_enemy_pos << " " << enemy[i].y_enemy_pos;
        if (i != 4) save_data << std::endl;
    }
    save_data.close();
}

void load (char (&field)[40][40], Player& player, Enemy (&enemy)[5]) {
    std::ifstream load_data("save.txt");
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            load_data >> field[i][j];
        }
    }
    load_data >> player.name_field >> player.name_player >> player.health_points >> player.armor_points >> player.damage >> player.x_player_pos >> player.y_player_pos;
    for (int i = 0; i < 5; i++) {
        load_data >> enemy[i].name_field >> enemy[i].name_enemy >> enemy[i].health_points 
            >> enemy[i].armor_points >> enemy[i].damage >> enemy[i].x_enemy_pos >> enemy[i].y_enemy_pos;
    }
    load_data.close();
}

void gen_game (char (&field)[40][40], Player& player, Enemy (&enemy)[5]) {
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            field[i][j] = '.';
        }
    }
    std::cout << "Input character name: ";
    std::cin >> player.name_player;
    std::cout << "Input character HP: ";
    std::cin >> player.health_points;
    std::cout << "Input character AP: ";
    std::cin >> player.armor_points;
    std::cout << "Input character damage: ";
    std::cin >> player.damage;

    std::srand(std::time(nullptr));
    for (int i = 0; i < 5; i++) {
        enemy[i].name_enemy += std::to_string(i + 1);
        enemy[i].health_points = std::rand() % 101 + 50;
        enemy[i].armor_points = std::rand() % 51;
        enemy[i].damage = std::rand() % 16 + 15;
    }

    player.x_player_pos = std::rand() % 40;
    player.y_player_pos = std::rand() % 40;
    field[player.y_player_pos][player.x_player_pos] = player.name_field;

    for (int i = 0; i < 5; i++) {
        enemy[i].x_enemy_pos = std::rand() % 40;
        enemy[i].y_enemy_pos = std::rand() % 40;

        bool no_one_here = false;
        do {
            if (field[enemy[i].y_enemy_pos][enemy[i].x_enemy_pos] == player.name_field
                    || field[enemy[i].y_enemy_pos][enemy[i].x_enemy_pos] == enemy[i].name_field) {
                enemy[i].x_enemy_pos = std::rand() % 40;
                enemy[i].y_enemy_pos = std::rand() % 40;

                no_one_here = false;
            }
            else {
                field[enemy[i].y_enemy_pos][enemy[i].x_enemy_pos] = enemy[i].name_field;

                no_one_here = true;
            }
        } while (!no_one_here);
    }
}

void getting_damage (Player& player, Enemy& enemy, int who_deal = 1) {
    if (who_deal == 1) {
        std::cout << player.name_player << " deals " << player.damage << " damage to " << enemy.name_enemy << std::endl;
        enemy.armor_points -= player.damage;
        if (enemy.armor_points < 0) {
            enemy.health_points += enemy.armor_points;
            enemy.armor_points = 0;
        }
        std::cout << enemy.name_enemy << " has " << enemy.armor_points << " AP and " << enemy.health_points << " HP" << std::endl;
    }
    else if (who_deal == 2) {
        std::cout << "Enemy deals" << enemy.damage << " damage to " << player.name_player << std::endl;
        player.armor_points -= enemy.damage;
        if (player.armor_points < 0) {
            player.health_points += player.armor_points;
            player.armor_points = 0;
        }
        std::cout << player.name_player << " has " << player.armor_points << " AP and " << player.health_points << " HP" << std::endl;
    }
}

void character_moving (char (&field)[40][40], Player& player, Enemy (&enemy)[5], int& command, int enemyNumber = 0, int who_move = 1) {
    if (command & RIGHT) {
        if (who_move == 1) {
            if (player.x_player_pos + 1 <= 39) {
                if (field[player.y_player_pos][player.x_player_pos + 1] == 'E') {
                    int number;
                    for (int i = 0; i < 5; i++) {
                        if (enemy[i].x_enemy_pos == player.x_player_pos + 1 
                                && enemy[i].y_enemy_pos == player.y_player_pos) {
                            number = i;
                            break;
                        }
                    }
                    getting_damage(player, enemy[number], 1);
                    if (enemy[number].health_points <= 0) {
                        std::swap(field[player.y_player_pos][player.x_player_pos], field[enemy[number].y_enemy_pos][enemy[number].x_enemy_pos]);
                        field[player.y_player_pos][player.x_player_pos] = '.';
                        enemy[number].x_enemy_pos = -1;
                        enemy[number].y_enemy_pos = -1;
                        player.x_player_pos++;
                    }
                }
                else if (field[player.y_player_pos][player.x_player_pos + 1] == '.') {
                    std::swap(field[player.y_player_pos][player.x_player_pos], field[player.y_player_pos][player.x_player_pos + 1]);
                    player.x_player_pos++;
                }
            } 
        }
        else if (who_move == 2) {
            if (enemy[enemyNumber].x_enemy_pos + 1 <= 39) {
                if (field[enemy[enemyNumber].y_enemy_pos][enemy[enemyNumber].x_enemy_pos + 1] == 'P') {
                    getting_damage(player, enemy[enemyNumber], 2);
                }
                else if (field[enemy[enemyNumber].y_enemy_pos][enemy[enemyNumber].x_enemy_pos + 1] == '.') {
                    std::swap(field[enemy[enemyNumber].y_enemy_pos][enemy[enemyNumber].x_enemy_pos], field[enemy[enemyNumber].y_enemy_pos][enemy[enemyNumber].x_enemy_pos + 1]);
                    enemy[enemyNumber].x_enemy_pos++;
                }
            }
        }
    }

    if (command & LEFT) {
        if (who_move == 1) {
            if (player.x_player_pos - 1 >= 0) {
                if (field[player.y_player_pos][player.x_player_pos - 1] == 'E') {
                    int number;
                    for (int i = 0; i < 5; i++) {
                        if (enemy[i].x_enemy_pos == player.x_player_pos - 1 
                                && enemy[i].y_enemy_pos == player.y_player_pos) {
                            number = i;
                            break;
                        }
                    }
                    getting_damage(player, enemy[number], 1);
                    if (enemy[number].health_points <= 0) {
                        std::swap(field[player.y_player_pos][player.x_player_pos], field[enemy[number].y_enemy_pos][enemy[number].x_enemy_pos]);
                        field[player.y_player_pos][player.x_player_pos] = '.';
                        enemy[number].x_enemy_pos = -1;
                        enemy[number].y_enemy_pos = -1;
                        player.x_player_pos--;
                    }
                }
                else if (field[player.y_player_pos][player.x_player_pos - 1] == '.') {
                    std::swap(field[player.y_player_pos][player.x_player_pos], field[player.y_player_pos][player.x_player_pos - 1]);
                    player.x_player_pos--;
                }
            } 
        }
        else if (who_move == 2) {
            if (enemy[enemyNumber].x_enemy_pos - 1 >= 0) {
                if (field[enemy[enemyNumber].y_enemy_pos][enemy[enemyNumber].x_enemy_pos - 1] == 'P') {
                    getting_damage(player, enemy[enemyNumber], 2);
                }
                else if (field[enemy[enemyNumber].y_enemy_pos][enemy[enemyNumber].x_enemy_pos - 1] == '.') {
                    std::swap(field[enemy[enemyNumber].y_enemy_pos][enemy[enemyNumber].x_enemy_pos], field[enemy[enemyNumber].y_enemy_pos][enemy[enemyNumber].x_enemy_pos - 1]);
                    enemy[enemyNumber].x_enemy_pos--;
                }
            }
        }
    }

    if (command & BOTTOM) {
        if (who_move == 1) {
            if (player.y_player_pos + 1 <= 39) {
                if (field[player.y_player_pos + 1][player.x_player_pos] == 'E') {
                    int number;
                    for (int i = 0; i < 5; i++) {
                        if (enemy[i].x_enemy_pos == player.x_player_pos
                                && enemy[i].y_enemy_pos == player.y_player_pos + 1) {
                            number = i;
                            break;
                        }
                    }
                    getting_damage(player, enemy[number], 1);
                    if (enemy[number].health_points <= 0) {
                        std::swap(field[player.y_player_pos][player.x_player_pos], field[enemy[number].y_enemy_pos][enemy[number].x_enemy_pos]);
                        field[player.y_player_pos][player.x_player_pos] = '.';
                        enemy[number].x_enemy_pos = -1;
                        enemy[number].y_enemy_pos = -1;
                        player.y_player_pos++;
                    }
                }
                else if (field[player.y_player_pos + 1][player.x_player_pos] == '.') {
                    std::swap(field[player.y_player_pos][player.x_player_pos], field[player.y_player_pos + 1][player.x_player_pos]);
                    player.y_player_pos++;
                }
            } 
        }
        else if (who_move == 2) {
            if (enemy[enemyNumber].y_enemy_pos + 1 <= 39) {
                if (field[enemy[enemyNumber].y_enemy_pos + 1][enemy[enemyNumber].x_enemy_pos] == 'P') {
                    getting_damage(player, enemy[enemyNumber], 2);
                }
                else if (field[enemy[enemyNumber].y_enemy_pos + 1][enemy[enemyNumber].x_enemy_pos] == '.') {
                    std::swap(field[enemy[enemyNumber].y_enemy_pos][enemy[enemyNumber].x_enemy_pos], field[enemy[enemyNumber].y_enemy_pos + 1][enemy[enemyNumber].x_enemy_pos]);
                    enemy[enemyNumber].y_enemy_pos++;
                }
            }
        }
    }

    if (command & TOP) {
        if (who_move == 1) {
            if (player.y_player_pos - 1 >= 0) {
                if (field[player.y_player_pos - 1][player.x_player_pos] == 'E') {
                    int number;
                    for (int i = 0; i < 5; i++) {
                        if (enemy[i].x_enemy_pos == player.x_player_pos 
                                && enemy[i].y_enemy_pos == player.y_player_pos - 1) {
                            number = i;
                            break;
                        }
                    }
                    getting_damage(player, enemy[number], 1);
                    if (enemy[number].health_points <= 0) {
                        std::swap(field[player.y_player_pos][player.x_player_pos], field[enemy[number].y_enemy_pos][enemy[number].x_enemy_pos]);
                        field[player.y_player_pos][player.x_player_pos] = '.';
                        enemy[number].x_enemy_pos = -1;
                        enemy[number].y_enemy_pos = -1;
                        player.y_player_pos--;
                    }
                }
                else if (field[player.y_player_pos - 1][player.x_player_pos] == '.') {
                    std::swap(field[player.y_player_pos][player.x_player_pos], field[player.y_player_pos - 1][player.x_player_pos]);
                    player.y_player_pos--;
                }
            } 
        }
        else if (who_move == 2) {
            if (enemy[enemyNumber].y_enemy_pos - 1 >= 0) {
                if (field[enemy[enemyNumber].y_enemy_pos - 1][enemy[enemyNumber].x_enemy_pos] == 'P') {
                    getting_damage(player, enemy[enemyNumber], 2);
                }
                else if (field[enemy[enemyNumber].y_enemy_pos - 1][enemy[enemyNumber].x_enemy_pos] == '.') {
                    std::swap(field[enemy[enemyNumber].y_enemy_pos][enemy[enemyNumber].x_enemy_pos], field[enemy[enemyNumber].y_enemy_pos - 1][enemy[enemyNumber].x_enemy_pos]);
                    enemy[enemyNumber].y_enemy_pos--;
                }
            }
        }
    }
}

int main() {
    char field[40][40];

    Player player;
    Enemy enemy[5];

    std::string answer;
    std::cout << "Use save?(y/n): ";
    std::cin >> answer;
    if (answer == "y") {
        load(field, player, enemy);
    }
    else if (answer == "n") {
        gen_game(field, player, enemy);
    }

    bool win = false;

    while(!win) {
        show_field(field);
        std::cout << std::endl;

        std::cout << "Input your command(w/a/s/d, you can use load/save): ";
        std::cin >> answer;

        if (answer == "load") {
            load(field, player, enemy);
            continue;
        }
        else if (answer == "save") {
            save(field, player, enemy);
            continue;
        }

        int command = 0;
        if (answer == "d") {
            command |= RIGHT;
        }
        else if (answer == "a") {
            command |= LEFT;
        }
        else if (answer == "w") {
            command |= TOP;
        }
        else if (answer == "s") {
            command |= BOTTOM;
        }
        character_moving(field, player, enemy, command);

        bool all_enemy_died = true;
        for (auto& e: enemy) {
            if (e.health_points > 0) {
                all_enemy_died = false;
                break;
            }
        }

        if (all_enemy_died) {
            win = true;
            continue;
        }

        std::srand(std::time(nullptr));
        for (int i = 0; i < 5; i++) {
            command = 0;
            int temp = std::rand() % 4;
            if (temp == 0) {
                command |= RIGHT; 
            }
            else if (temp == 1) {
                command |= LEFT;
            }
            else if (temp == 2) {
                command |= TOP;
            }
            else if (temp == 3) {
                command |= BOTTOM;
            }
            character_moving(field, player, enemy, command, i, 2);

            std::cout << std::endl;
        }
        if (player.health_points <= 0) {
            break;
        }
    }
    if (win) {
        std::cout << "You win!";
    }
    else {
        std::cout << "You lose!";
    }
}

/*
Реализуйте сильно упрощённую версию ролевой пошаговой игры:
Игра происходит на карте размером 40 на 40 клеток. По клеткам перемещаются враги и персонаж игрока.
После каждого хода игрока карта показывается вновь со всеми врагами на ней. 
Игрок помечается буквой P. Враги буквой E. Пустые места — точкой.
Каждый персонаж игры представлен в виде структуры с полями: имя, жизни, броня, урон.
Вначале игры создаются 5 случайных врагов в случайных клетках карты. 
Имена врагам задаются в формате “Enemy #N”, где N — это порядковый номер врага. 
Уровень жизней врагам задаётся случайно, от 50 до 150. Уровень брони варьируется 
от 0 до 50. Урон тоже выбирается случайно от 15 до 30 единиц.
Игрок конструирует своего персонажа самостоятельно. Задаёт все его параметры, включая имя.
Все персонажи появляются в случайных местах карты.
Игрок осуществляет ход с помощью команд: left, right, top, bottom. 
В зависимости от команды и выбирается направление перемещения персонажа: влево, вправо, вверх, вниз.
Враги перемещаются в случайном направлении.
Если персонаж (враг или игрок) перемещается в сторону, где уже находится какой-то персонаж, 
то он бьёт этого персонажа с помощью своего урона. Враги при этом никогда не бьют врагов, 
а просто пропускают ход и остаются на своём месте. За пределы карты (40 на 40 клеток) 
ходить нельзя никому. Если кто-то выбрал направление за гранью дозволенного, ход пропускается.
Формула для расчёта урона совпадает с той, что была в самом уроке. Жизни уменьшаются на 
оставшийся после брони урон. При этом сама броня тоже сокращается на приведённый урон.
Игра заканчивается тогда, когда либо умирают все враги, либо персонаж игрока. В первом 
случае на экран выводится сообщение о поражении, во втором — победа.
Если в начале хода игрок вводит команду save или load вместо направления перемещения, 
то игра либо делает сохранение своего состояния в файл, либо загружает это состояние из файла соответственно.
*/