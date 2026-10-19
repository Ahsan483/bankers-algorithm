/*
 * bankers.c - Banker's algorithm: safety check and resource requests
 *
 * Uses the classic 5-process, 3-resource example. Then tries two requests:
 * one that keeps the system safe (granted) and one that would not (denied).
 */
#include <stdio.h>
#include <string.h>

#define P 5
#define R 3

static int avail[R] = { 3, 3, 2 };
static int max[P][R]   = { {7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3} };
static int alloc[P][R] = { {0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2} };

static void need(int n[P][R])
{
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++) n[i][j] = max[i][j] - alloc[i][j];
}

static int safe(int print)
{
    int n[P][R], work[R], finish[P] = { 0 }, seq[P], k = 0;
    need(n);
    memcpy(work, avail, sizeof work);

    for (int round = 0; round < P; round++) {
        for (int i = 0; i < P; i++) {
            if (finish[i]) continue;
            int ok = 1;
            for (int j = 0; j < R; j++) if (n[i][j] > work[j]) { ok = 0; break; }
            if (!ok) continue;
            for (int j = 0; j < R; j++) work[j] += alloc[i][j];
            finish[i] = 1;
            seq[k++] = i;
            if (print) printf("  P%d can finish -> work = (%d %d %d)\n", i, work[0], work[1], work[2]);
        }
    }
    if (print) {
        if (k == P) {
            printf("  SAFE. Sequence: ");
            for (int i = 0; i < P; i++) printf("P%d%s", seq[i], i < P - 1 ? " -> " : "\n");
        } else {
            printf("  UNSAFE. Only %d of %d processes can finish.\n", k, P);
        }
    }
    return k == P;
}

static void table(void)
{
    int n[P][R];
    need(n);
    printf("       Alloc     Max      Need\n       A B C    A B C    A B C\n");
    for (int i = 0; i < P; i++)
        printf("  P%d   %d %d %d    %d %d %d    %d %d %d\n", i,
               alloc[i][0], alloc[i][1], alloc[i][2], max[i][0], max[i][1], max[i][2], n[i][0], n[i][1], n[i][2]);
    printf("  Available: %d %d %d\n\n", avail[0], avail[1], avail[2]);
}

static void request(int pid, int a, int b, int c)
{
    int req[R] = { a, b, c }, n[P][R];
    need(n);
    printf("\nRequest P%d (%d %d %d): ", pid, a, b, c);
    for (int j = 0; j < R; j++) {
        if (req[j] > n[pid][j]) { printf("DENIED, exceeds its maximum claim\n"); return; }
        if (req[j] > avail[j])  { printf("WAIT, not enough available\n"); return; }
    }
    for (int j = 0; j < R; j++) { avail[j] -= req[j]; alloc[pid][j] += req[j]; }   /* pretend */
    if (safe(0)) {
        printf("GRANTED, system stays safe\n");
        safe(1);
    } else {
        for (int j = 0; j < R; j++) { avail[j] += req[j]; alloc[pid][j] -= req[j]; } /* roll back */
        printf("DENIED, would lead to an unsafe state (rolled back)\n");
    }
}

int main(void)
{
    printf("Banker's algorithm: 5 processes, resources A B C\n\n");
    table();
    printf("Safety check:\n");
    safe(1);
    request(1, 1, 0, 2);
    request(4, 3, 3, 0);
    request(0, 0, 2, 0);
    return 0;
}
