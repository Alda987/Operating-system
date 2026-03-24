#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 50

// generate random pages (0–9)
void gen(int p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i] = rand() % 10;
    }
}

// check if page is present
int check(int f[], int size, int page) {
    for (int i = 0; i < size; i++) {
        if (f[i] == page)
            return 1;
    }
    return 0;
}

// FIFO
int fifo(int p[], int n, int size) {
    int f[10], faults = 0, pos = 0;

    for (int i = 0; i < size; i++) f[i] = -1;

    for (int i = 0; i < n; i++) {
        if (!check(f, size, p[i])) {
            f[pos] = p[i];
            pos = (pos + 1) % size;
            faults++;
        }
    }
    return faults;
}

// LRU
int lru(int p[], int n, int size) {
    int f[10], used[10];
    int faults = 0, time = 0;

    for (int i = 0; i < size; i++) {
        f[i] = -1;
        used[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < size; j++) {
            if (f[j] == p[i]) {
                time++;
                used[j] = time;
                found = 1;
                break;
            }
        }

        if (!found) {
            int min = used[0], pos = 0;

            for (int j = 1; j < size; j++) {
                if (used[j] < min) {
                    min = used[j];
                    pos = j;
                }
            }

            time++;
            f[pos] = p[i];
            used[pos] = time;
            faults++;
        }
    }
    return faults;
}

// OPTIMAL
int optimal(int p[], int n, int size) {
    int f[10];
    int faults = 0;

    for (int i = 0; i < size; i++) f[i] = -1;

    for (int i = 0; i < n; i++) {

        if (check(f, size, p[i])) continue;

        int pos = -1, far = i + 1;

        for (int j = 0; j < size; j++) {
            int k;

            for (k = i + 1; k < n; k++) {
                if (f[j] == p[k]) break;
            }

            if (k == n) {
                pos = j;
                break;
            }

            if (k > far) {
                far = k;
                pos = j;
            }
        }

        if (pos == -1) pos = 0;

        f[pos] = p[i];
        faults++;
    }

    return faults;
}

int main() {
    int n, size;
    int p[MAX];

    printf("Enter length of page string: ");
    scanf("%d", &n);

    printf("Enter number of frames (1-7): ");
    scanf("%d", &size);

    if (size < 1 || size > 7) {
        printf("Invalid frame size!\n");
        return 0;
    }

    srand(time(0));
    gen(p, n);

    printf("\nPages: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", p[i]);
    }

    printf("\n\nPage Faults:\n");
    printf("FIFO    = %d\n", fifo(p, n, size));
    printf("LRU     = %d\n", lru(p, n, size));
    printf("OPTIMAL = %d\n", optimal(p, n, size));

    return 0;
}