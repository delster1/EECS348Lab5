#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char* month;
    float sales;
} SalesData;

int compareSales(const void *a, const void *b) {
    const SalesData *dataA = (const SalesData *)a;
    const SalesData *dataB = (const SalesData *)b;

    // For decreasing order
    if (dataB->sales > dataA->sales) return 1;
    else if (dataB->sales < dataA->sales) return -1;
    else return 0;
}

void print_monthly_sales_report(const char *months[], const float sales[]) {
    FILE *out;
    out = fopen("out.tsv", "w");
    if (out == NULL) {
        perror("Failed to open file");
        return;
    }
    fprintf(out, "Monthly sales report for 2022:\n");
    int min;
    int max;
    float total;
    SalesData data[12];

    for (int i = 0; i < 12; i++) {
        if (i == 0) {
            min = i;
            max = i;
        }
        
        if (sales[i] < min) {
            min = i;
        }
        if (sales[i] > max) {
            max = i;
        }
        total += sales[i];
        data[i].month = months[i]; // Correctly populate the SalesData array
        data[i].sales = sales[i];
        fprintf(out, "%s\t%.2f\n", months[i], sales[i]);
    }
    fprintf(out, "Sales Summary:\n");

    fprintf(out, "Minimum Sales:\t%.2f\t(%s)\n", sales[min], months[min]);
    fprintf(out, "Maximum Sales:\t%.2f\t(%s)\n", sales[max], months[max]);
    fprintf(out, "Average Sales:\t%.2f\t\n", total/12);

    fprintf(out, "\nSix-Month Moving Average Report:\n");
    for (int i =0; i < 7; i++) {
        float avg;
        float total = 0;
        for (int j = 0; j<6;j++) {
            total += sales[i+j];
        }        
        avg = total / 6;
        fprintf(out, "%s - %s\t%.2f\n", months[i], months[i+5], avg);

    }
    fprintf(out, "\nSales Report (Highest to Lowest):\n");
     
    qsort(data, 12, sizeof(SalesData), compareSales);
    // Writing sorted data to the file
    for (int i = 0; i < 12; i++) {
        fprintf(out, "%s\t%.2f\n", data[i].month, data[i].sales);
    }

    fclose(out);
}

int main() {
    char *months[12] = {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    };
    FILE *fptr;
    fptr = fopen("input.txt", "r");

    char myString[100];
    float sales[12];
    int i = 0;


    while (fgets(myString, 100, fptr) && i < 12) {
        // Try to convert string to float and check for success
        if (sscanf(myString, "%f", &sales[i]) == 1) {
            i++;
        }
    }

    fclose(fptr);
    print_monthly_sales_report(months, sales);
    return 0;
}
