#include <iostream>
#include <fstream>
#include <string>

struct statement {
    std::string name = "unknown";
    std::string surname = "unknown";
    std::string date = "dd.mm.yyyy";
    int amount = 0;
};

void add(std::ofstream& file, statement& payment) {
    file << payment.name << " " << payment.surname << " " << payment.date << " " << payment.amount << std::endl;
}

void read(std::ifstream& file, statement& payment) {
    file >> payment.name >> payment.surname >> payment.date >> payment.amount;
    if (payment.name != "0") {
        std::cout << payment.name << " " << payment.surname << " " << payment.date << " " << payment.amount << std::endl;
    }
    else {
        std::cout << "End of file" << std::endl;
    }
}

int main() {
    std::string answer = "0";
    while (answer != "-1") {
        statement payment;
        std::cout << "Choose which command you want to use: ";
        std::cin >> answer;
        if (answer == "add") {
            std::cout << "Input name: ";
            std::cin >> payment.name;
            std::cout << "Input surname: ";
            std::cin >> payment.surname;
            std::cout << "Input date: ";
            std::cin >> payment.date;
            std::cout << "Input amount of payment: ";
            std::cin >> payment.amount;
            std::ofstream file("statement.txt", std::ios::app);
            add(file, payment);
            file.close();
        }
        else if (answer == "read") {
            std::ifstream file("statement.txt");
            while (!file.eof()) {
                payment.name = "0";
                read(file, payment);
            }
        }
    }
}

/*
Вы уже создавали программу чтения и записи ведомости. Теперь её надо будет обобщить и дополнить использованием структур.
Формат ведомости прежний. Сначала идёт имя и фамилия получателя денежных средств, далее — дата выдачи в формате ДД.ММ.ГГГГ.,
затем — сумма выплаты в рублях. Данные разделяются между собой пробелами. В конце каждой записи должен быть перевод строки.
Структура данных записи должна соответствовать указанному формату.
При старте программы пользователь указывает команду, которую следует осуществить:
list или add. Команда read осуществляет чтение из файла ведомости как и прежде, только уже в структуры данных и отображает их на экране.
Команда add добавляет новую запись в конец ведомости.
*/