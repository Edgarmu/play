#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <stdbool.h>

int kbhit();

char kbin[256];

void kbget();

bool key(char k) {
    return (kbin[0] == k && !kbin[1]);
}
struct timeval time1;

void delay(int ms);

uint64_t timems() {
    gettimeofday(&time1, NULL);
    return time1.tv_sec * 1000 + time1.tv_usec / 1000;
}

int main(void) {
    char arr[25][81];
    int i;
    int x = 40, y = 12;
    int p11 = 11, p12 = 12, p13 = 13;
    int p21 = 11, p22 = 12, p23 = 13;
    int dy = 1, dx = -1;
    int score11 = 0, score12 = 0;
    int score21 = 0, score22 = 0;
    do {
        delay(100);
        system("clear");
        sprintf(arr[0], "  ############################################################################");
        for (i = 1; i < 24; i++) {
        sprintf(arr[i], "I                                                                              I");
        }
        sprintf(arr[24], "################################################################################");
        if (arr[y][x - 1] == 'I') {
            score22++;
            if (score22 >= 10) {
                score22 = 0;
                score21++;
            }
            dx *= -1;
            x = 40; y = 12;
           // continue;
        }
        if (arr[y][x + 1] == 'I') {
            score12++;
            if (score12 >= 10) {
              score12 = 0;
              score11++;
            }
            dx *= -1;
            x = 40; y = 12;
           // continue;
        }
        if (score11 == 2 && score12 == 1) {
            system("clear");
            printf("CONGRATULATIONS PLAYER 1 WIN");
            break;
        }
        if (score21 == 2 && score22 == 1) {
            system("clear");
            printf("CONGRATULATIONS PLAYER 2 WIN");
            break;
        }
        char c11 = score11 +'0';
        arr[0][0] = c11;
        char c12 = score12 +'0';
        arr[0][1] = c12;
        char c21 = score21 +'0';
        arr[0][78] = c21;
        char c22 = score22 +'0';
        arr[0][79] = c22;
        arr[p11][1] = '|';
        arr[p12][1] = '|';
        arr[p13][1] = '|';
        arr[p21][78] = '|';
        arr[p22][78] = '|';
        arr[p23][78] = '|';
        if (arr[y + 1][x] == '#' || arr[y - 1][x] == '#') {
            dy = dy * -1;
            y = (y + dy);
        } else {
            y = (y + dy);
        }
        if (arr[y][x + 1] == '|' || arr[y][x - 1] == '|') {
            dx *= -1;
        }
        x = x + dx;

        arr[y][x] = '@';

        for (i = 0; i < 25; i++) {
        printf("%s\n", arr[i]);
        }
        kbget();
        if (key('a') && p11 != 1) { p11--; p12--; p13--;
        }
        if (key('z') && p13 != 23) { p11++; p12++; p13++;
        }
        if (key('k') && p21 != 1) { p21--; p22--; p23--;
        }
        if (key('m') && p23 != 23) { p21++; p22++; p23++;
        }
        if (key('e')) { break;
        }
    } while (1);
        return 0;
}
int kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;
    if (!initialized) {
        struct termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }
    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}
void kbget() {
    int tmp;
    kbin[0] = 0;
    if (!(tmp = kbhit())) return;
    int obp = 0;
    while (obp < tmp) {
        kbin[obp] = 0;
        kbin[obp] = getchar();
        if (kbin[obp] == 0) {break;}
        obp++;
    }
    kbin[obp] = 0;
}
void delay(int ms) {
    uint64_t cms = 0;
    gettimeofday(&time1, NULL);
    uint64_t bms = cms = time1.tv_sec * 1000 + time1.tv_usec / 1000;
    while (cms < bms + ms) {
        gettimeofday(&time1, NULL);
        cms = time1.tv_sec * 1000 + time1.tv_usec / 1000;
    }
}
