 #include <stdio.h>

void line125();
void button();
void line(int x, int y, int xr1, int yr1, int xr2, int yr2);
void ball_pos(int x, int y, int xr1, int yr1, int xr2, int yr2, int m);
char wall = '-';
char ball = '*';
char space = ' ';
char wall2 = '#';
char raketka = '|';
char mid = '.';
int countr1 = 1;
int countr2 = 1;
int kn = 32;
int ns = 10;
int gx = 39;
int gy = 1;
int gxr1 = 2;
int gyr1 = 11;
int gxr2 = 79;
int gyr2 = 11;
int moveb = 1;
int gamer1 = 0;
int gamer2 = 0;
int counte = 0;

int main() {
    do {
        if ((kn == 122 || kn == 97 || kn == 107 || kn == 109 || kn == 32 ||
        kn == 65 || kn == 90 || kn == 75 || kn == 77) && ns == 10) {
          counte = 0;
            printf("\033c");
            if (gamer1 == 21) {
                printf("*******************************\n");
                printf("Player #1 WIN! Congratulations!\n");
                printf("*******************************\n");
                return 0;
            } else if (gamer2 == 21) {
                printf("*******************************\n");
                printf("Player #2 WIN! Congratulations!\n");
                printf("*******************************\n");
                return 0;
            }
            line(gx, gy, gxr1, gyr1, gxr2, gyr2);
        } else {
          if (counte == 0) {
            printf("Для продолжения игры введите 2 пробела\n");
            counte++;
          }
            kn = getchar();
            ns = getchar();
        }
    } while (1);
    return 0;
}

void line(int x, int y, int xr1, int yr1, int xr2, int yr2) {
    for (int n = 1; n <= 25; n++) {
        for (int i = 1; i <= 80; i++) {
            // Боковые стены
            if (i == 1 || i == 80) {
                printf("%c", wall2);
            }
            // Позиция пробелов
            if (i > 1 && i < 80 && (n != y || i != x) && (n != yr1 || i != xr1) && (n != yr1+1 || i != xr1)
            && (n != yr1+2 || i != xr1) && (n != yr2 || i != xr2) && (n != yr2+1 || i != xr2)
            && (n != yr2+2 || i != xr2) && (i != 39 && i != 40)) {
                printf(" ");
            }
            // Позиция 1 ракетки
            if (n == yr1 && i == xr1 && countr1 == 1 && i == 2) {
                printf("%c", raketka);
                countr1++;
            }
            if (n == yr1+1 && i == xr1 && countr1 == 2 && i == 2) {
                printf("%c", raketka);
                countr1++;
            }
            if (n == yr1+2 && i == xr1 && countr1 == 3 && i == 2) {
                printf("%c", raketka);
                countr1 = 1;
            }
            // Позиции шарика
            // Позиция шарика, если не попал на 1 ракетку
            if (n == y && i == x && y != yr1 && x != xr1 && i == 2) {
                printf("%c", ball);
            }
            // Позиция шарика в поле от следующего поля обоих ракеток
            if (i > 2 && i < 79 && i == x && n == y) {
                printf("%c", ball);
            }
            // Позиция 2 ракетки
            if (n == yr2 && i == xr2 && countr2 == 1 && i == 79) {
                printf("%c", raketka);
                countr2++;
            }
            if (n == yr2+1 && i == xr2 && countr2 == 2 && i == 79) {
                printf("%c", raketka);
                countr2++;
            }
            if (n == yr2+2 && i == xr2 && countr2 == 3 && i == 79) {
                printf("%c", raketka);
                countr2 = 1;
            }
            // Позиция шарика, если не попал на 2 ракетку
            if (n == y && i == x && y != yr2 && x != xr2 && i == 79) {
                printf("%c", ball);
            }
            if ((i == 39 || i == 40) && (n != y || i != x)) {
                printf("%c", mid);
            }
            // Перенос строки
             if (i == 80) {
                 printf("\n");
             }
        }
    }
    gx = x;
    gy = y;
    gxr1 = xr1;
    gyr1 = yr1;
    gxr2 = xr2;
    gyr2 = yr2;

    for (int i = 1; i <= 80; i++) {
        if (i <37 || i > 41) {
            printf(" ");
        } else if (i == 37) {
            printf("%d -- %d", gamer1, gamer2);
        }
    }
    printf("\n");

    button();
    ball_pos(gx, gy, gxr1, gyr1, gxr2, gyr2, moveb);
}

// Функция чтения кнопок
void button() {
    kn = getchar();
    ns = getchar();

    if ((kn == 97 || kn == 65) && gyr1 != 1) {
        gyr1--;
    }
    if ((kn == 122 || kn == 90) && gyr1 != 23) {
        gyr1++;
    }
    if ((kn == 107 || kn == 75) && gyr2 != 1) {
        gyr2--;
    }
    if ((kn == 109 || kn == 77) && gyr2 != 23) {
        gyr2++;
    }
}

void ball_pos(int x, int y, int xr1, int yr1, int xr2, int yr2, int m) {
    // Движение мяча вниз влево
    if (m == 1 && y != 25 && xr1 != x - 1 && x != 2) {
        gx--;
        gy++;
    // Движение мяча в угол
    } else if (m == 1 && y == 25 && x -1 == xr1 && yr1 == 23) {
        moveb = 3;
        gx++;
        gy--;
    // Движение мяча в угол без ракетки
    } else if (m == 1 && y == 25 && x - 1 == xr1 && yr1 != 23) {
        gamer2++;
        gx = 40;
        gy = 1;
        gxr1 = 2;
        gyr1 = 11;
        gxr2 = 79;
        gyr2 = 11;
        moveb = 2;
    // Движение мяча от нижней стенки
    } else if (m == 1 && y == 25 && xr1 != x) {
        moveb = 4;
        gx--;
        gy--;
    // Движение мяча от ракетки сверху влево отлетает вниз вправо
    } else if (m == 1 && xr1 == x-1 && (yr1 == y || y == yr1+1 || y == yr1+2)) {
        moveb = 2;
        gx++;
        gy++;
    // Пропуск мяча
    } else if (m == 1 && x == 3) {
        gamer2++;
        gx = 40;
        gy = 1;
        gxr1 = 2;
        gyr1 = 11;
        gxr2 = 79;
        gyr2 = 11;
        moveb = 2;
    }
    // Движение мяча вниз вправо
    if (m == 2 && y != 25 && xr2 != x + 1 && x != 79) {
        gx++;
        gy++;
    // Движение мяча в угол
    } else if (m == 2 && y == 25 && x + 1 == xr2 && yr2 == 23) {
        moveb = 4;
        gx--;
        gy--;
    // Движение мяча в угол без ракетки
    } else if (m == 2 && y == 25 && x + 1 == xr2 && yr2 != 23) {
        gamer1++;
        gx = 39;
        gy = 1;
        gxr1 = 2;
        gyr1 = 11;
        gxr2 = 79;
        gyr2 = 11;
        moveb = 1;
    // Движение мяча от нижней стенки
    } else if (m == 2 && y == 25 && xr2 != x) {
        moveb = 3;
        gx++;
        gy--;
    // Движение мяча от ракетки 2 снизу вправо отлетает наверх влево
    } else if (m == 2 && xr2 == x + 1 && (yr2 == y || y == yr2+1 || y == yr2+2)) {
        moveb = 1;
        gx--;
        gy++;
    // Пропуск мяча 2 игроком
    } else if (m == 2 && x == 78) {
        gamer1++;
        gx = 39;
        gy = 1;
        gxr1 = 2;
        gyr1 = 11;
        gxr2 = 79;
        gyr2 = 11;
        moveb = 1;
    }
    // Движение мяча вправо вверх
    if (m == 3 && y != 1 && xr2 != x + 1 && x != 79) {
        gx++;
        gy--;
    // Движение мяча в угол + ракетка
    } else if (m == 3 && y == 1 && x + 1 == xr2 && yr2 == 1) {
        moveb = 1;
        gx--;
        gy++;
    // Движение мяча в угол без ракетки
    } else if (m == 3 && y == 1 && x + 1 == xr2 && yr2 != 1) {
        gamer1++;
        gx = 39;
        gy = 1;
        gxr1 = 2;
        gyr1 = 11;
        gxr2 = 79;
        gyr2 = 11;
        moveb = 1;
    // Движение мяча от верхней стенки
    } else if (m == 3 && y == 1 && xr2 != x) {
        moveb = 2;
        gx++;
        gy++;
    // Движение мяча от ракетки 2 снизу вправо отлетает наверх влево
    } else if (m == 3 && xr2 == x + 1 && (yr2 == y || y == yr2+1 || y == yr2+2)) {
        moveb = 4;
        gx--;
        gy--;
    // Пропуск мяча 2 игроком
    } else if (m == 3 && x == 78) {
        gamer1++;
        gx = 39;
        gy = 1;
        gxr1 = 2;
        gyr1 = 11;
        gxr2 = 79;
        gyr2 = 11;
        moveb = 1;
    }
    // Движение мяча вверх влево
    if (m == 4 && y != 1 && xr1 != x - 1 && x != 2) {
        gx--;
        gy--;
    // Движение мяча в угол + ракетка
    } else if (m == 4 && y == 1 && x - 1 == xr1 && yr1 == 1) {
        moveb = 2;
        gx++;
        gy++;
    // Движение мяча от верхней стенки (отлетает вниз влево)
    } else if (m == 4 && y == 1 && x - 1 == xr1 && yr1 != 1) {
        gamer2++;
        gx = 40;
        gy = 1;
        gxr1 = 2;
        gyr1 = 11;
        gxr2 = 79;
        gyr2 = 11;
        moveb = 2;
    // Движение мяча от верхней стенки
    } else if (m == 4 && y == 1 && xr1 != x) {
        moveb = 1;
        gx--;
        gy++;
    // Движение мяча при столкновении с 1 ракеткой (отлетает вверх вправо)
    } else if (m == 4 && xr1 == x-1 && (yr1 == y || y == yr1+1 || y == yr1+2)) {
        moveb = 3;
        gx++;
        gy--;
    } else if (m == 4 && x == 3) {
        gamer2++;
        gx = 40;
        gy = 1;
        gxr1 = 2;
        gyr1 = 11;
        gxr2 = 79;
        gyr2 = 11;
        moveb = 2;
    }
}
