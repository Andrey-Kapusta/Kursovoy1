#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <locale.h>


// Прототипы функций
double f(double x);
double sigma(double x, int N);
int build_table(double start, double finish, double step);
double find_x_by_y(double start, double finish, double y, double precision);
int count_x_by_y(double start, double finish, double y, double precision);
double calculate_derivative(double x, double h);
double calculate_integral(double start, double finish, int n);




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
    printf("                              *          |  (atan(x)) / x,                 x < -2         *\n");
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
        double x, start, step, finish, y, precision;
        int n, result;

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
                    printf("f(%lf) = %.6lf\n", x, f(x));
                }
            }
            break;







        case 2: // Таблица значений
            printf("Введите начало отсчёта: ");
            if (scanf("%lf", &start) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }
            printf("Введите конец отсчёта: ");
            if (scanf("%lf", &finish) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }
            if (start >= finish) {
                printf("Ошибка! Начало должно быть меньше конца.\n");
                break;
            }
            printf("Введите шаг: ");
            if (scanf("%lf", &step) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }

            result = build_table(start, finish, step);
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
            printf("Введите точность (Например 0.001): ");
            if (scanf("%lf", &precision) != 1 || precision <= 0) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }

            printf("Введите начало отсчёта: ");
            if (scanf("%lf", &start) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }
            printf("Введите конец отсчёта: ");
            if (scanf("%lf", &finish) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }
            if (start >= finish) {
                printf("Ошибка! Начало должно быть меньше конца.\n");
                break;
            }



            int total_count = count_x_by_y(start, finish, y, precision);

            if (total_count == 0) {
                printf("Не удалось найти значение Х для Y = %lf на отрезке [%lf, %lf]\n", y, start, finish);
                return;
            }

            printf("\nНайдено %d значений Х для Y = %lf на отрезке [%lf, %lf]\n", total_count, y, start, finish);
            printf("Первое значение Х для Y = %lf на отрезке [%lf, %lf]:  %lf\n", y, start, finish, find_x_by_y(start, finish, y, precision));
            printf("\n   Список всхе значений Х для Y = %lf на отрезке [%lf, %lf]\n", y, start, finish);
            printf("=============================================================================================\n");

            double new_start = start;
            int found = 0;

            while (found < total_count) {

                double x_solution = find_x_by_y(new_start, finish, y, precision);

                printf("Решение %d: X = %lf\n", found + 1, x_solution);
                found++;

                new_start = x_solution + precision;

                if (new_start > finish) {
                    break;
                }
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
            {
                double h = 1e-7;
                if (x != 2 && (x + h) != 2) {
                    printf("f'(%lf) ~ %.5lf\n", x, calculate_derivative(x, h));
                }
                else {
                    printf("Ошибка! Нельзя вычислить производную - функция не определена\n");
                }
            }
            break;







        case 5: // Интеграл
            printf("Введите начало интервала: ");
            if (scanf("%lf", &start) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }
            printf("Введите конец интервала: ");
            if (scanf("%lf", &finish) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }
            if (start >= finish) {
                printf("Ошибка! Начало интервала должно быть меньше конца.\n");
                break;
            }
            printf("Введите количество разбиений: ");
            if (scanf("%d", &n) != 1 || n <= 0) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }

            printf("Интеграл = %.6lf\n", calculate_integral(start, finish, n));

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
        return 1.0 / (x * tan(x));
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
double find_x_by_y(double start, double finish, double y, double precision) {
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
int count_x_by_y(double start, double finish, double y, double precision) {
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
double calculate_derivative(double x, double h) {
    double fx = f(x);
    double fx_plus_h = f(x + h);

    if (x == 2 || (x + h) == 2) {
        return 0;
    }

    double derivative = (fx_plus_h - fx) / h;
    return derivative;
}







// 5 Вычисление определенного интеграла методом прямоугольников
double calculate_integral(double start, double finish, int n) {
    double h = (finish - start) / n;
    double sum = 0.0;
    int valid_points = 0;

    for (int i = 0; i < n; i++) {
        double x = start + (i + 0.5) * h; // Метод средних прямоугольников
        double result = f(x);
        if (x != 2) {
            sum += result;
            valid_points++;
        }
    }


    double integral = sum * h;
    return integral;
}