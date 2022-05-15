#include <iostream>
#include <cmath>

struct Vector {
    float v_a_1 = 0.0f;
    float v_a_2 = 0.0f;

    float v_b_1 = 0.0f;
    float v_b_2 = 0.0f;

    float v_c_1 = 0.0f;
    float v_c_2 = 0.0f;
};

void add(Vector& vector) {
    vector.v_c_1 = vector.v_a_1 + vector.v_b_1;
    vector.v_c_2 = vector.v_a_2 + vector.v_b_2;
}

void subtract(Vector& vector) {
    vector.v_c_1 = vector.v_a_1 - vector.v_b_1;
    vector.v_c_2 = vector.v_a_2 - vector.v_b_2;
}

void scale (Vector& vector, float& d) {
    vector.v_a_1 *= d;
    vector.v_a_2 *= d;
}

float length (Vector& vector) {
    return sqrt(pow(vector.v_a_1, 2) + pow(vector.v_a_2, 2));
}

void normalize (Vector& vector) {
    float dvdr = length(vector);
    vector.v_a_1 = vector.v_a_1 / dvdr;
    vector.v_a_2 = vector.v_a_2 / dvdr;
}

int main() {
    Vector vector;
    std::string answer = "";
    std::cout << "Input command: ";
    std::cin >> answer;
    if (answer == "add") {
        std::cout << "Input vector A: ";
        std::cin >> vector.v_a_1 >> vector.v_a_2;
        std::cout << "Input vector B: ";
        std::cin >> vector.v_b_1 >> vector.v_b_2;
        add(vector);
        std::cout << "Vector C: (" << vector.v_c_1 << ", " << vector.v_c_2 << ")";
    }
    else if (answer == "subtract") {
        std::cout << "Input vector A: ";
        std::cin >> vector.v_a_1 >> vector.v_a_2;
        std::cout << "Input vector B: ";
        std::cin >> vector.v_b_1 >> vector.v_b_2;
        subtract(vector);
        std::cout << "Vector C: (" << vector.v_c_1 << ", " << vector.v_c_2 << ")";
    }
    else if (answer == "scale") {
        std::cout << "Input vector A: ";
        std::cin >> vector.v_a_1 >> vector.v_a_2;
        float scalar_d;
        std::cout << "Input scalar: ";
        std::cin >> scalar_d;
        scale(vector, scalar_d);
        std::cout << "A new vector: (" << vector.v_a_1 << ", " << vector.v_a_2 << ")";
    }
    else if (answer == "length") {
        std::cout << "Input vector A: ";
        std::cin >> vector.v_a_1 >> vector.v_a_2;
        std::cout << "Length of vector A: " << length(vector);
    }
    else if (answer == "normalize") {
        std::cout << "Input vector A: ";
        std::cin >> vector.v_a_1 >> vector.v_a_2;
        normalize(vector);
        std::cout << "A normalize vector A: (" << vector.v_a_1 << ", " << vector.v_a_2 << ")";
    }
}

/*
Реализуйте структуру двумерного математического вектора и основные операции над ним. 
Обе координаты вектора (x и y) должны быть вещественными числами.
Вначале программы пользователь вводит команду, которая соответствует требуемой операции. 
Далее, в зависимости от операции, пользователь вводит её аргументы. Это могут быть как вектора, 
так и обычные, скалярные значения. В результате в стандартный вывод помещается результат. 
Это тоже может быть или вектор, или скаляр.
Реализуйте следующие операции в виде отдельных функций:
Сложение двух векторов — команда add.
Вычитание двух векторов — команда subtract.
Умножение вектора на скаляр — команда scale.
Нахождение длины вектора — команда length.
Нормализация вектора — команда normalize.
*/