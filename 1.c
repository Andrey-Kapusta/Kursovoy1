#define _CRT_SECURE_NO_DEPREKATE
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <locale.h>

void calculate_value();
double f(double x);
void calculate_value();
void build_table();
void find_extremum();
void find_x_by_y();
void calculate_derivative();
void calculate_integral();







int main() {


    setlocale(LC_CTYPE, "RUS");
    int choice;


    printf("\n");
    printf("                              *************************************************************\n");
    printf("                              *                                                           *\n");
    printf("                              *                      Курсовой проект                      *\n");
    printf("                              *          Конструирование программы анализа функции        *\n");
    printf("                              *                  Выполнил: Капустин А. И.                 *\n");
    printf("                              *              Руководитель: Минакова О. В.                 *\n");
    printf("                              *                    Группа: бИЦ-252                        *\n");
    printf("                              *                                                           *\n");
    printf("                              *************************************************************\n");
    printf("\n\n\n");




    printf("                              *************************************************************\n");
    printf("                              *                      АНАЛИЗ ФУНКЦИИ                       *\n");
    printf("                              *           __                                              *\n");
    printf("                              *          |  (tan^-1 (x)) / x,               x < -2        *\n");
    printf("                              *   f(x) = |                                                *\n");
    printf("                              *          |   (x^4 - 16) / (x-2),            x >= 2        *\n");
    printf("                              *          |                                                *\n");
    printf("                              *          |    16                                          *\n");
    printf("                              *          |    ___    ((-1)^n * x^(2n+1))                  *\n");
    printf("                              *          |    \\     ______________________, -2 <= x < 2  *\n");
    printf("                              *          |    /__    ((2n+1) * sqrt(n+2))                 *\n");
    printf("                              *          |__  n = 0                                       *\n");
    printf("                              *                                                           *\n");
    printf("                              *************************************************************\n");
    printf("\n\n\n");


    do {
        printf("\n\n\n");
        printf("                              *************************************************************\n");
        printf("                              *                                                           *\n");
        printf("                              *                       ГЛАВНОЕ МЕНЮ                        *\n");
        printf("                              *                                                           *\n");
        printf("                              *        1. Значение функции в точке                        *\n");
        printf("                              *        2. Таблица значений                                *\n");
        printf("                              *        3. Поиск минимального/максимального значения       *\n");
        printf("                              *        4. Поиск X по Y                                    *\n");
        printf("                              *        5. Производная в точке                             *\n");
        printf("                              *        6. Вычисление интеграла                            *\n");
        printf("                              *        7. Выход                                           *\n");
        printf("                              *                                                           *\n");
        printf("                              *************************************************************\n");
        printf("\n\n\n");
        printf("Выберите пункт: ");

        if (scanf_s("%d", &choice) != 1) {
            printf("Ошибка ввода!\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
        case 1:
            calculate_value();
            break;
        case 2:
            build_table();
            break;
        case 3:
            find_extremum();
            break;
        case 4:
            find_x_by_y();
            break;
        case 5:
            calculate_derivative();
            break;
        case 6:
            calculate_integral();
            break;
        case 7:
            printf("Выход из программы.\n");
            break;
        default:
            printf("Неверный выбор! Попробуйте снова.\n");
            break;
        }
    } while (choice != 7);

    return 0;
}



// Функция Сигмы
double sigma(double x) {
    double sumx = 0.0;
    for (int n = 0; n <= 16; n++) {
        sumx += (pow(-1, n) * pow(x, 2 * n + 1)) / ((2 * n + 1) * sqrt(n + 2));
    }
    return sumx;
}




// Функция вычисления f(x)
double f(double x) {
    if (x < -2.0) {
        return (1.0 / x * (tan(x)));
    }
    if (-2.0 <= x < 2.0) {
        return sigma(x);
    }
    if (x >= 2.0) {
        return (pow(x, 4) - 16.0) / (x - 2.0);
    }
}



// 1 Значение функции в точке
void calculate_value() {
    double x;
    printf("Введите x: ");
    if (scanf_s("%lf", &x) != 1) {
        printf("Ошибка ввода!\n");
        while (getchar() != '\n');
        return;
    }

    double result = f(x);
    if (isnan(result)) {
        printf("Ошибка! Функция не определена в точке x = %.2lf\n", x);
    }
    else {
        printf("f(%.2lf) = %.6lf\n", x, result);
    }
}

// 2 Таблица значений
void build_table() {
    double start, step;
    int count;

    printf("Введите начало отсчета: ");
    if (scanf_s("%lf", &start) != 1) {
        printf("Ошибка ввода!\n");
        while (getchar() != '\n');
        return;
    }

    printf("Введите шаг: ");
    if (scanf_s("%lf", &step) != 1) {
        printf("Ошибка ввода!\n");
        while (getchar() != '\n');
        return;
    }

    printf("Введите количество отсчетов: ");
    if (scanf_s("%d", &count) != 1 || count <= 0) {
        printf("Ошибка ввода!\n");
        while (getchar() != '\n');
        return;
    }

    printf("\n| %-10s | %-15s |\n", "x", "f(x)");
    printf("|%-12s|%-17s|\n", "------------", "-----------------");

    double x = start;
    for (int i = 0; i < count; i++) {
        double result = f(x);
        if (isnan(result)) {
            printf("| %-10.2lf | %-15s |\n", x, "не определена");
        }
        else {
            printf("| %-10.2lf | %-15.6lf |\n", x, result);
        }
        x += step;
    }
    printf("\n");
}

// 3 Поиск минимума/максимума на отрезке
void find_extremum() {
    double start, finish, step;

    printf("Введите начало отрезка: ");
    if (scanf_s("%lf", &start) != 1) {
        printf("Ошибка ввода!\n");
        while (getchar() != '\n');
        return;
    }

    printf("Введите конец отрезка: ");
    if (scanf_s("%lf", &finish) != 1) {
        printf("Ошибка ввода!\n");
        while (getchar() != '\n');
        return;
    }

    if (start >= finish) {
        printf("Ошибка! Начало отрезка должно быть меньше конца.\n");
        return;
    }

    printf("Введите шаг поиска: ");
    if (scanf_s("%lf", &step) != 1 || step <= 0) {
        printf("Ошибка ввода!\n");
        while (getchar() != '\n');
        return;
    }

    double min_val = DBL_MAX;
    double max_val = -DBL_MAX;
    double min_x = start;
    double max_x = start;
    int found_valid = 0;

    for (double x = start; x <= finish; x += step) {
        double result = f(x);
        if (!isnan(result)) {
            found_valid = 1;
            if (result < min_val) {
                min_val = result;
                min_x = x;
            }
            if (result > max_val) {
                max_val = result;
                max_x = x;
            }
        }
    }

    if (!found_valid) {
        printf("На отрезке [%.2lf, %.2lf] функция не определена\n", start, finish);
    }
    else {
        printf("Минимум: f(%.6lf) = %.6lf\n", min_x, min_val);
        printf("Максимум: f(%.6lf) = %.6lf\n", max_x, max_val);
    }
}

// 4 Поиск X по Y
void find_x_by_y() {
    double y, precision;

    printf("Введите Y: ");
    if (scanf_s("%lf", &y) != 1) {
        printf("Ошибка ввода!\n");
        while (getchar() != '\n');
        return;
    }

    printf("Введите точность (Например 0.001): ");
    if (scanf_s("%lf", &precision) != 1 || precision <= 0) {
        printf("Ошибка ввода!\n");
        while (getchar() != '\n');
        return;
    }

    // Поиск на интервале [-10, 10] с шагом 0.001
    int found = 0;
    for (double x = -10.0; x <= 10.0; x += 0.001) {
        double result = f(x);
        if (!isnan(result) && fabs(result - y) < precision) {
            printf("Найдено: f(%.6lf) ? %.6lf (разница: %.6lf)\n",
                x, result, fabs(result - y));
            found = 1;
        }
    }

    if (!found) {
        printf("Не удалось найти x такой, что f(x) ? %.6lf с точностью %.6lf\n",
            y, precision);
    }
}

// 5 Производная в точке
void calculate_derivative() {
    double x;
    double h = 1e-7; // Малое приращение

    printf("Введите x: ");
    if (scanf_s("%lf", &x) != 1) {
        printf("Ошибка ввода!\n");
        while (getchar() != '\n');
        return;
    }

    // Проверяем, определена ли функция в точке и в соседних точках
    double fx = f(x);
    double fx_plus_h = f(x + h);

    if (isnan(fx) || isnan(fx_plus_h)) {
        printf("Ошибка! Нельзя вычислить производную - функция не определена\n");
        return;
    }

    double derivative = (fx_plus_h - fx) / h;
    printf("f'(%.2lf) ? %.6lf\n", x, derivative);
}

// 6 Вычисление определенного интеграла методом прямоугольников
void calculate_integral() {
    double a, b;
    int n;

    printf("Введите начало интервала: ");
    if (scanf_s("%lf", &a) != 1) {
        printf("Ошибка ввода!\n");
        while (getchar() != '\n');
        return;
    }

    printf("Введите конец интервала: ");
    if (scanf_s("%lf", &b) != 1) {
        printf("Ошибка ввода!\n");
        while (getchar() != '\n');
        return;
    }

    if (a >= b) {
        printf("Ошибка! Начало интервала должно быть меньше конца.\n");
        return;
    }

    printf("Введите количество разбиений: ");
    if (scanf_s("%d", &n) != 1 || n <= 0) {
        printf("Ошибка ввода!\n");
        while (getchar() != '\n');
        return;
    }

    double h = (b - a) / n;
    double sum = 0.0;
    int valid_points = 0;

    for (int i = 0; i < n; i++) {
        double x = a + (i + 0.5) * h; // Метод средних прямоугольников
        double result = f(x);
        if (!isnan(result)) {
            sum += result;
            valid_points++;
        }
    }

    if (valid_points == 0) {
        printf("Функция не определена на интервале [%.2lf, %.2lf]\n", a, b);
    }
    else if (valid_points < n) {
        printf("Внимание: функция не определена в некоторых точках интервала\n");
        printf("Интеграл ? %.6lf (вычислен по %d из %d точек)\n",
            sum * h, valid_points, n);
    }
    else {
        printf("Интеграл ? %.6lf\n", sum * h);
    }
}
