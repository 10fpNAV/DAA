#include <stdio.h>
#include <stdlib.h>

double tw, tp = 0.0;

struct Item {
    int profit;
    int w;
    double ratio;
};

double calcrat(int profit, int w) {
    return (double) profit / w;
}

void greedy_knapsack(double w, int n, struct Item a[]) {
    double currentWeight = 0;

    printf("Object num\tXi\t   Remaining weight\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t\t", i + 1);

        if (currentWeight + a[i].w <= w) {
            currentWeight += a[i].w;
            tp += a[i].profit;
            printf("%d\t\t", 1);  
        } else {
            double fraction = (w - currentWeight) / a[i].w;
            tp += a[i].profit * fraction;
            currentWeight += a[i].w * fraction;
            printf("%lf\t\t", fraction);  
            break;
        }

        printf("%lf\n", w - currentWeight);
    }
}

int main() {
    int num, temp;
    printf("Enter number of unique items: ");
    scanf("%d", &num);

    printf("Enter total weight: ");
    scanf("%lf", &tw);

    struct Item a[num];

    for (int i = 0; i < num; i++) {
        printf("Enter profit of object %d: ", i);
        scanf("%d", &temp);
        a[i].profit = temp;

        printf("Enter weight of object %d: ", i);
        scanf("%d", &temp);
        a[i].w = temp;
        a[i].ratio = calcrat(a[i].profit, a[i].w);
    }

    struct Item swap;
    for (int c = 0; c < num - 1; c++) {
        int swapped = 0;
        for (int b = 0; b < num - c - 1; b++) {
            if (a[b].ratio < a[b + 1].ratio) {
                swap = a[b];
                a[b] = a[b + 1];
                a[b + 1] = swap;
                swapped = 1;
            }
        }
        if (swapped == 0)
            break;
    }
    printf("\n");
    greedy_knapsack(tw, num, a);
    printf("\n");
    printf("\nThe maximum profit is %lf\n", tp);

    return 0;
}

