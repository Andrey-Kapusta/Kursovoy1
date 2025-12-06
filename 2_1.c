#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <locale.h>

// Прототипы функций
double f(double x);
double sigma(double x);
int build_table(double start, double step, int count);
int find_extremum(double start, double finish, double step, double* min_x, double* min_val, double* max_x, double* max_val);
int find_x_by_y(double y, double precision, double found_x[], int max_results, int* found_count);
int calculate_derivative(double x, double h, double* derivative);
int calculate_integral(double a, double b, int n, double* integral);

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
    printf("                              *          |  (atan(x)) / x,                 x <= -2         *\n");
    printf("                              *   f(x) = |                                                *\n");
    printf("                              *          |   (x^4 - 16) / (x-2),            x >= 2        *\n");
    printf("                              *          |                                                *\n");
    printf("                              *          |    16                                          *\n");
    printf("                              *          |    ___    ((-1)^n * x^(2n+1))                  *\n");
    printf("                              *          |    \\     ______________________, -2 = x < 2  *\n");
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

        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода!\n");
            while (getchar() != '\n');
            continue;
        }

        // Переменные для ввода в main
        double x, start, step, finish, y, precision, a, b;
        int count, n;
        double min_x, min_val, max_x, max_val;
        int result;

        switch (choice) {




        case 1: // Значение функции в точке
            printf("Введите x: ");
            if (scanf("%lf", &x) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }
            {
                double result_val = f(x);
                if (isnan(result_val)) {
                    printf("Ошибка! Функция не определена в точке x = %.2lf\n", x);
                }
                else {
                    printf("f(%.2lf) = %.6lf\n", x, result_val);
                }
            }
            break;







        case 2: // Таблица значений
            printf("Введите начало отсчета: ");
            if (scanf("%lf", &start) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }
            printf("Введите шаг: ");
            if (scanf("%lf", &step) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }
            printf("Введите количество отсчетов: ");
            if (scanf("%d", &count) != 1 || count <= 0) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }
            result = build_table(start, step, count);
            if (result == 0) {
                printf("В таблице нет ни одного определенного значения функции.\n");
            }
            break;






        case 3: // Поиск минимума/максимума
            printf("Введите начало отрезка: ");
            if (scanf("%lf", &start) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }
            printf("Введите конец отрезка: ");
            if (scanf("%lf", &finish) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }
            if (start >= finish) {
                printf("Ошибка! Начало отрезка должно быть меньше конца.\n");
                break;
            }
            printf("Введите шаг поиска: ");
            if (scanf("%lf", &step) != 1 || step <= 0) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }
            if (find_extremum(start, finish, step, &min_x, &min_val, &max_x, &max_val) == 1) {
                printf("Минимум: f(%.6lf) = %.6lf\n", min_x, min_val);
                printf("Максимум: f(%.6lf) = %.6lf\n", max_x, max_val);
            }
            else {
                printf("На отрезке [%.2lf, %.2lf] функция не определена\n", start, finish);
            }
            break;






        case 4: // Поиск X по Y
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
            {
#define MAX_RESULTS 100
                double found_x[MAX_RESULTS];
                int found_count = 0;

                result = find_x_by_y(y, precision, found_x, MAX_RESULTS, &found_count);
                if (result == 1 && found_count > 0) {
                    printf("Найдено %d значений x:\n", found_count);
                    for (int i = 0; i < found_count && i < 10; i++) {
                        printf("  x = %.6lf\n", found_x[i]);
                    }
                    if (found_count > 10) {
                        printf("  ... и еще %d значений\n", found_count - 10);
                    }
                }
                else {
                    printf("Не удалось найти x такой, что f(x) = %.6lf с точностью %.6lf\n", y, precision);
                }
            }
            break;







        case 5: // Производная в точке
            printf("Введите x: ");
            if (scanf("%lf", &x) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }
            {
                double h = 1e-7;
                double derivative;
                result = calculate_derivative(x, h, &derivative);
                if (result == 1) {
                    printf("f'(%.2lf) = %.6lf\n", x, derivative);
                }
                else {
                    printf("Ошибка! Нельзя вычислить производную - функция не определена\n");
                }
            }
            break;







        case 6: // Интеграл
            printf("Введите начало интервала: ");
            if (scanf("%lf", &a) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }
            printf("Введите конец интервала: ");
            if (scanf("%lf", &b) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }
            if (a >= b) {
                printf("Ошибка! Начало интервала должно быть меньше конца.\n");
                break;
            }
            printf("Введите количество разбиений: ");
            if (scanf("%d", &n) != 1 || n <= 0) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }
            {
                double integral;
                result = calculate_integral(a, b, n, &integral);
                if (result == 1) {
                    printf("Интеграл = %.6lf\n", integral);
                }
                else {
                    printf("Функция не определена на интервале [%.2lf, %.2lf]\n", a, b);
                }
            }
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






// 1 Функция вычисления f(x) 
double f(double x) {
    if (x <= (-2.0)) {
        return 1.0 / (x * tan(x));
    }
    else if (x > (-2.0) && x < (2.0)) {
        return sigma(x);
    }
    else if (x > (2.0)) {
        return (pow(x, 4.0) - (16.0)) / (x - (2.0));
    }
    else {
        return NAN; // x == 2.0 или другие случаи
    }
}






// 2 Таблица значений
int build_table(double start, double step, int count) {
    int valid_count = 0;

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
            valid_count++;
        }
        x += step;
    }
    printf("\n");

    return (valid_count > 0) ? 1 : 0;
}

// 3 Поиск минимума/максимума на отрезке
int find_extremum(double start, double finish, double step, double* min_x, double* min_val, double* max_x, double* max_val) {
    *min_val = DBL_MAX;
    *max_val = -DBL_MAX;
    int found_valid = 0;

    for (double x = start; x <= finish; x += step) {
        double result = f(x);
        if (!isnan(result)) {
            found_valid = 1;
            if (result < *min_val) {
                *min_val = result;
                *min_x = x;
            }
            if (result > *max_val) {
                *max_val = result;
                *max_x = x;
            }
        }
    }

    return found_valid ? 1 : 0;
}





// 4 Поиск X по Y
int find_x_by_y(double y, double precision, double found_x[], int max_results, int* found_count) {
    *found_count = 0;

    // Поиск на интервале [-10, 10] с шагом 0.001
    for (double x = -10.0; x <= 10.0 && *found_count < max_results; x += 0.001) {
        double result = f(x);
        if (!isnan(result) && fabs(result - y) < precision) {
            found_x[*found_count] = x;
            (*found_count)++;
        }
    }

    return (*found_count > 0) ? 1 : 0;
}





// 5 Производная в точке
int calculate_derivative(double x, double h, double* derivative) {
    double fx = f(x);
    double fx_plus_h = f(x + h);

    if (isnan(fx) || isnan(fx_plus_h)) {
        return 0;
    }

    *derivative = (fx_plus_h - fx) / h;
    return 1;
}







// 6 Вычисление определенного интеграла методом прямоугольников
int calculate_integral(double a, double b, int n, double* integral) {
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
        return 0;
    }

    *integral = sum * h;
    return 1;
}