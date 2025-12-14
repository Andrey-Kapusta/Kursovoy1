#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <stdlib.h>



typedef struct {
    double start;
    double finish;
    double step;
    double precision;
} InputParams;


// Прототипы функций
double f(double x);
double sigma(double x, int N);
int build_table(double start, double finish, double step);
double find_x_by_y(double start, double finish, double precision, double y);
int count_x_by_y(double start, double finish, double precision, double y);
double calculate_derivative(double x, double precision);
double calculate_integral(double start, double finish, double precision);
InputParams get_input_params();



int main() {
    setlocale(LC_CTYPE, "RUS");
    int choice;

    // Вывод заголовков программы
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
    printf("                              *          |   1 / (x * tan(x)),              x < -2        *\n");
    printf("                              *   f(x) = |                                                *\n");
    printf("                              *          |   (x^4 - 16) / (x-2),            x >= 2        *\n");
    printf("                              *          |                                                *\n");
    printf("                              *          |    16                                          *\n");
    printf("                              *          |    ___    ((-1)^n * x^(2n+1))                  *\n");
    printf("                              *          |    \\     ______________________, -2 <= x < 2   *\n");
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
        printf("                              *        3. Поиск X по Y                                    *\n");
        printf("                              *        4. Производная в точке                             *\n");
        printf("                              *        5. Вычисление интеграла                            *\n");
        printf("                              *        6. Выход                                           *\n");
        printf("                              *                                                           *\n");
        printf("                              *************************************************************\n");
        printf("\n\n\n");
        printf("Выберите пункт: ");

        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода!\n");
            while (getchar() != '\n');
            continue;
        }

        // Переменные для ввода в main
        double x, y, precision4;
        int result;
        InputParams params;


        switch (choice) {




        case 1: // Значение функции в точке
            printf("Введите x: ");
            if (scanf("%lf", &x) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }
            {

                if (x == 2) {
                    printf("Ошибка! Функция не определена в точке x = %lf\n", x);
                }
                else {
                    printf("f(%lf) = %lf\n", x, f(x));
                }
            }
            break;







        case 2: // Таблица значений
            params = get_input_params();
            if (params.start >= params.finish) {
                printf("Ошибка! Начало должно быть меньше конца.\n");
                break;
            }
            if (params.step < 0) {
                printf("Ошибка! Шаг должен быть больше 0.\n");
                break;
            }
            result = build_table(params.start, params.finish, params.step);
            if (result == 0) {
                printf("В таблице нет ни одного определенного значения функции.\n");
            }
            break;


















        case 3: // Поиск X по Y
            printf("Введите Y: ");
            if (scanf("%lf", &y) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }




            params = get_input_params();
            if (params.start >= params.finish) {
                printf("Ошибка! Начало должно быть меньше конца.\n");
                break;
            }
            if (params.precision <= 0) {
                printf("Ошибка! Точность должна быть положительной.\n");
                break;
            }

            int total_count = count_x_by_y(params.start, params.finish, params.precision, y);
            if (total_count == 0) {
                printf("Не удалось найти значение Х для Y = %lf на отрезке [%lf, %lf]\n", y, params.start, params.finish);
                break;
            }

            printf("\nНайдено %d значений Х для Y = %lf на отрезке [%lf, %lf]\n", total_count, y, params.start, params.finish);
            printf("Первое значение Х для Y = %lf на отрезке [%lf, %lf]:  %lf\n", y, params.start, params.finish, find_x_by_y(params.start, params.finish, params.precision, y));
            printf("\n   Список всех значений Х для Y = %lf на отрезке [%lf, %lf]\n", y, params.start, params.finish);
            printf("=============================================================================================\n");

            double new_start = params.start;
            int found = 0;
            while (found < total_count) {
                double x_solution = find_x_by_y(new_start, params.finish, params.precision, y);
                printf("Решение %d: X = %lf\n", found + 1, x_solution);
                found++;
                new_start = x_solution + params.precision;
                if (new_start > params.finish) break;
            }
            printf("============================================================\n");
            break;




















        case 4: // Производная в точке
            printf("Введите x: ");
            if (scanf("%lf", &x) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }

            printf("Введите точность (Например 0.00001): ");
            if (scanf("%lf", &precision4) != 1 || precision4 <= 0) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }
            if (x != 2 && (x + precision4) != 2) {
                printf("f'(%lf) ~ %lf\n", x, calculate_derivative(x, precision4));
            }
            else {
                printf("Ошибка! Нельзя вычислить производную - функция не определена\n");
            }

            break;







        case 5: // Интеграл

            params = get_input_params();
            if (params.start >= params.finish) {
                printf("Ошибка! Начало интервала должно быть меньше конца.\n");
                break;
            }
            if (params.precision < 0) {
                printf("Ошибка! Точность должна быть больше 0.\n");
                break;
            }
            printf("Интеграл ~ %lf\n", calculate_integral(params.start, params.finish, params.precision));
            break;








        case 6:
            printf("Выход из программы.\n");
            break;

        default:
            printf("Неверный выбор! Попробуйте снова.\n");
            break;
        }
    } while (choice != 6);

    return 0;
}








InputParams get_input_params() {
    InputParams params;

    printf("Введите начало отсчёта: ");
    scanf("%lf", &params.start);

    printf("Введите конец отсчёта: ");
    scanf("%lf", &params.finish);

    printf("Введите шаг (если он не нужен введите 0): ");
    scanf("%lf", &params.step);

    printf("Введите точность (Например 0.0001): ");
    scanf("%lf", &params.precision);

    return params;
}












// Функция Сигмы
double sigma(double x, int N) {
    double sumx = 0.0;
    for (int n = 0; n <= N; n++) {
        sumx += (pow(-1, n) * pow(x, 2 * n + 1)) / ((2 * n + 1) * sqrt(n + 2));
    }
    return sumx;
}






// 1 Функция вычисления f(x) 
double f(double x) {
    if (x < (-2.0)) {
        return (1.0 / (x * tan(x)));
    }
    else if ((-2.0) <= x && x < (2.0)) {
        return sigma(x, 16);
    }
    else if (x > (2.0)) {
        return (pow(x, 4.0) - (16.0)) / (x - (2.0));
    }
    else {
        return NAN; // x == 2.0 или другие случаи
    }
}






// 2 Таблица значений
int build_table(double start, double finish, double step) {
    int valid_count = 0;

    printf("\n| %-10s | %-15s |\n", "x", "f(x)");
    printf("|%-12s|%-17s|\n", "------------", "-----------------");


    for (double x = start; x <= finish; x += step) {
        double result = f(x);
        if (x == 2) {
            printf("| %-10.2lf | %-15s |\n", x, "не определена");
        }
        else {
            printf("| %-10.2lf | %-15.6lg |\n", x, result);
            valid_count++;
        }
    }
    printf("\n");


    if (valid_count > 0) {
        return 1;
    }
    else
    {
        return 0;
    }

}








// 3_1 Поиск X по Y
double find_x_by_y(double start, double finish, double precision, double y) {
    double found_x = 0;


    for (double x = start; x <= finish; x += precision) {
        double result = f(x);
        if (x != 2 && fabs(result - y) < precision) {
            found_x = x;
            break;
        }
    }

    return found_x;
}

// 3_2 поиск количества Х
int count_x_by_y(double start, double finish, double precision, double y) {
    int count = 0;


    for (double x = start; x <= finish; x += precision) {
        double result = f(x);

        // Проверяем, равно ли значение функции Y с заданной точностью
        if (x != 2 && fabs(result - y) < precision) {
            count++;
        }
    }

    return count;
}






// 4 Производная в точке
double calculate_derivative(double x, double precision) {
    double fx = f(x);
    double fx_plus_h = f(x + precision);

    if (x == 2 || (x + precision) == 2) {
        return 0;
    }

    double derivative = (fx_plus_h - fx) / precision;
    return derivative;
}







// 5 Вычисление определенного интеграла методом прямоугольников
double calculate_integral(double start, double finish, double precision) {
    double h = (finish - start) * precision;
    double sum = 0.0;

    for (int i = 0; i < pow(precision, (-1.0)); i++) {
        double x = start + (h / 2) + i * h; // Метод средних прямоугольников
        double result = f(x);
        if (x != 2) {
            sum += result;
        }
    }


    double integral = sum * h;
    return integral;
}








