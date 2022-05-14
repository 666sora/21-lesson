#include <iostream>
#include <vector>

struct Room {
    std::string type_room = "";

    int area_room = 0;
};

struct Floor {
    std::vector<Room> v_room = {};

    int height = 0;
    int count_room = 0;
};


struct Home {
    std::vector<Floor> v_floor = {};

    int area_home = 0;
    int count_floor = 0;

    bool furnace_home = false;
};

struct Barn {
    int area_barn = 0;
};

struct Bathhouse {
    int area_bathhouse = 0;

    bool furnace_bathhouse = false;
};

struct Garage {
    int area_garage = 0;
};

struct District {
    std::vector<Home> v_home = {};
    std::vector<Barn> v_barn = {};
    std::vector<Bathhouse> v_bathhouse = {};
    std::vector<Garage> v_garage = {};

    int count_garage = 0;
    int count_bathhouse = 0;
    int count_barn = 0;
    int count_home = 0;

    std::string ID_name = "";
};

struct Settlement {
    std::vector<District> v_district = {};

    int count_district = 0;

    int area_settlement = 0;
};

int main() {
    Settlement settlement;
    int count;
    std::cout << "Input count of districts: ";
    std::cin >> settlement.count_district;
    settlement.v_district.resize(settlement.count_district);
    for (int i = 0; i < settlement.count_district; i++) {
        std::cout << "Input count of houses for " << i + 1 << " district: ";
        std::cin >> settlement.v_district[i].count_home;
        settlement.v_district[i].v_home.resize(settlement.v_district[i].count_home);
    }
    for (int i = 0; i < settlement.count_district; i++) {
        for (int j = 0; j < settlement.v_district[i].count_home; j++) {
            std::cout << "Input count of floors for " << i + 1 << " district, " << j + 1 << " home: ";
            std::cin >> settlement.v_district[i].v_home[j].count_floor;
            settlement.v_district[i].v_home[j].v_floor.resize(settlement.v_district[i].v_home[j].count_floor);
        }
    }
    for (int i = 0; i < settlement.count_district; i++) {
        for (int j = 0; j < settlement.v_district[i].count_home; j++) {
            for (int k = 0; k < settlement.v_district[i].v_home[j].count_floor; k++) {
                std::cout << "Input count of rooms for " << i + 1 << " district, " << j + 1 << " home, " << k + 1 << " floor: ";
                std::cin >> settlement.v_district[i].v_home[j].v_floor[k].count_room;
                settlement.v_district[i].v_home[j].v_floor[k].v_room.resize(settlement.v_district[i].v_home[j].v_floor[k].count_room);
            }
        }
    }
    for (int i = 0; i < settlement.count_district; i++) {
        std::cout << "Input count of barns for " << i + 1 << " district: ";
        std::cin >> settlement.v_district[i].count_barn;
        settlement.v_district[i].v_barn.resize(settlement.v_district[i].count_barn);
    }
    for (int i = 0; i < settlement.count_district; i++) {
        std::cout << "Input count of bathhouses for " << i + 1 << " district: ";
        std::cin >> settlement.v_district[i].count_bathhouse;
        settlement.v_district[i].v_bathhouse.resize(settlement.v_district[i].count_bathhouse);
    }
    for (int i = 0; i < settlement.count_district; i++) {
        std::cout << "Input count of garages for " << i + 1 << " district: ";
        std::cin >> settlement.v_district[i].count_garage;
        settlement.v_district[i].v_garage.resize(settlement.v_district[i].count_garage);
    }

    std::cout << "Input area of settlement: ";
    std::cin >> settlement.area_settlement;

    for (int i = 0; i < settlement.count_district; i++) {
        std::cout << "Input name of district " << i + 1 << ": ";
        std::cin >> settlement.v_district[i].ID_name;
    }

    int sum_struct_area = 0;

    for (int i = 0; i < settlement.count_district; i++) {
        for (int j = 0; j < settlement.v_district[i].count_home; j++) {
            std::cout << "Input area of home for " << i + 1 << " district, " << j + 1 << " home: ";
            std::cin >> settlement.v_district[i].v_home[j].area_home;
            sum_struct_area += settlement.v_district[i].v_home[j].area_home;

            std::cout << "Have " << i + 1 << " district, " << j + 1 << " home furnace(1/0): ";
            std::cin >> settlement.v_district[i].v_home[j].furnace_home;
        }
    }
    for (int i = 0; i < settlement.count_district; i++) {
        for (int j = 0; j < settlement.v_district[i].count_home; j++) {
            for (int k = 0; k < settlement.v_district[i].v_home[j].count_floor; k++) {
                std::cout << "Input height of floor for " << i + 1 << " district, " << j + 1 << " home, " << k + 1 << " floor: ";
                std::cin >> settlement.v_district[i].v_home[j].v_floor[k].height;
            }
        }
    }
    for (int i = 0; i < settlement.count_district; i++) {
        for (int j = 0; j < settlement.v_district[i].count_home; j++) {
            for (int k = 0; k < settlement.v_district[i].v_home[j].count_floor; k++) {
                for (int l = 0; l < settlement.v_district[i].v_home[j].v_floor[k].count_room; l++) {
                    std::cout << "Input type of room for " << i + 1 << " district, " << j + 1 << " home, " << k + 1 << " floor, " << l + 1  << " room: ";
                    std::cin >> settlement.v_district[i].v_home[j].v_floor[k].v_room[l].type_room;
                    std::cout << "Input area of room for " << i + 1 << " district, " << j + 1 << " home, " << k + 1 << " floor, " << l + 1  << " room: ";
                    std::cin >> settlement.v_district[i].v_home[j].v_floor[k].v_room[l].area_room;
                }
            }
        }
    }
    for (int i = 0; i < settlement.count_district; i++) {
        for (int j = 0; j < settlement.v_district[i].count_barn; j++) {
            std::cout << "Input area of barn for " << i + 1 << " district, " << j + 1 << " barn: ";
            std::cin >> settlement.v_district[i].v_barn[j].area_barn;
            sum_struct_area += settlement.v_district[i].v_barn[j].area_barn; 
        }
    }
    for (int i = 0; i < settlement.count_district; i++) {
        for (int j = 0; j < settlement.v_district[i].count_bathhouse; j++) {
            std::cout << "Input area of bathhouse for " << i + 1 << " district, " << j + 1 << " bathhouse: ";
            std::cin >> settlement.v_district[i].v_bathhouse[j].area_bathhouse;
            sum_struct_area += settlement.v_district[i].v_bathhouse[j].area_bathhouse;

            std::cout << "Have " << i + 1 << " district, " << j + 1 << " bathhouse furnace(1/0): ";
            std::cin >> settlement.v_district[i].v_bathhouse[j].furnace_bathhouse;  
        }
    }
    for (int i = 0; i < settlement.count_district; i++) {
        for (int j = 0; j < settlement.v_district[i].count_garage; j++) {
            std::cout << "Input area of garage for " << i + 1 << " district, " << j + 1 << " garage: ";
            std::cin >> settlement.v_district[i].v_garage[j].area_garage;
            sum_struct_area += settlement.v_district[i].v_garage[j].area_garage; 
        }
    }

    std::cout << "Total sum of area buildings is " << sum_struct_area << std::endl;
    std::cout << "Total percent occupied by buildings is " << float(sum_struct_area) / float(settlement.area_settlement) * 100.0f << "%";
}

/*
С помощью структур данных создайте подробную модель посёлка.
В посёлке есть множество участков. Каждый из них имеет свой уникальный номер. 
На каждом из участков должен быть расположен как минимум один жилой дом, но 
возможны и другие сооружения, такие как гараж, сарай (бытовка) и баня. Для каждого 
здания предусмотрена информация о площади, которую он занимает на участке.
В жилом доме может быть 1–3 этажа. На каждом из этажей может быть 2–4 комнаты. 
Каждая комната при этом может быть разных типов: спальня, кухня, ванная, детская, 
гостиная. Для каждой комнаты предусмотрены данные о её площади. Для каждого этажа 
также есть данные о высоте потолка. В жилом доме и бане может быть печь с трубой, 
информация об этом также должна быть предусмотрена в данных.
Для всех упомянутых сущностей надо объявить соответствующие структуры данных.
Вначале работы программы пользователь заполняет данные о посёлке: вводит общее 
количество участков и далее начинает детализировать каждый из участков.
Для каждого участка сначала заполняется общее количество построек, а затем
детализируется каждая постройка, этажи, комнаты на этажах.
По итогам введённых данных вы можете рассчитать некий суммарный параметр,
например, процент земли, занимаемой постройками, к общей площади всего посёлка.
Главное в этой задаче не сама операция подсчёта, а структуры данных.
*/