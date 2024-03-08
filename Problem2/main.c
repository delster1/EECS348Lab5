#include <stdio.h>
#include <stdlib.h>

void calc_scores(int n) {

    for (int touchdown_2point = 0; touchdown_2point * 8 <= n; touchdown_2point++)
        for (int touchdown_1point = 0; touchdown_1point * 7 + touchdown_2point * 8 <= n; touchdown_1point++)
            for (int touchdown = 0; touchdown * 6 + touchdown_1point * 7 + touchdown_2point * 8 <= n; touchdown++)
                for (int field_goal = 0; field_goal * 3 + touchdown * 6 + touchdown_1point * 7 + touchdown_2point * 8 <= n; field_goal++)
                    for (int safety = 0; safety * 2 + field_goal * 3 + touchdown * 6 + touchdown_1point * 7 + touchdown_2point * 8 <= n; safety++)
                        if (+ safety * 2 + field_goal * 3 + touchdown * 6 + touchdown_1point * 7 + touchdown_2point * 8 == n)
                            printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n", touchdown_2point, touchdown_1point, touchdown, field_goal, safety);
}


int main() {
    
    printf("Please enter 0 to stop\n");
    int user_in;

    printf("Please enter the NFL score: ");
    scanf("%d", &user_in);

    while (user_in != 0) {
        printf("possible combinations of scoring plays: \n");

        calc_scores(user_in);
        printf("\nPlease enter 0 to STOP\n");
        printf("Please enter the NFL score: ");
        scanf("%d", &user_in);
    }
    return 0;
}