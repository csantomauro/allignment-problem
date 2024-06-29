#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void align_sequences(char X[], char Y[]) {
    int m = strlen(X);
    int n = strlen(Y);
    int dp[m + 1][n + 1];

    // Initialize the DP table
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i == 0) dp[i][j] = j * 2;
            else if (j == 0) dp[i][j] = i * 2;
            else if (X[i - 1] == Y[j - 1]) dp[i][j] = dp[i - 1][j - 1];
            else dp[i][j] = (dp[i - 1][j] + 2 > dp[i][j - 1] + 2) ? dp[i][j - 1] + 2 : dp[i - 1][j] + 2;
        }
    }

    // Reconstruct the aligned strings
    char aligned_X[m + n + 1];
    char aligned_Y[m + n + 1];
    int i = m;
    int j = n;
    int aligned_index = 0;

    while (i > 0 && j > 0) {
        if (dp[i][j] == dp[i - 1][j] + 2) {

            aligned_X[aligned_index] = X[i - 1];
            aligned_Y[aligned_index] = '_';
            --i;
        } else if (dp[i][j] == dp[i][j - 1] + 2) {

            aligned_X[aligned_index] = '_';
            aligned_Y[aligned_index] = Y[j - 1];
            --j;
        } else {
            aligned_X[aligned_index] = X[i - 1];
            aligned_Y[aligned_index] = Y[j - 1];
            --i;
            --j;
        }
        ++aligned_index;
    }

    while (i > 0){
        aligned_X[aligned_index] = X[i - 1];
        aligned_Y[aligned_index] = '_';
        --i;
        ++aligned_index;
        }
    while (j > 0){
        aligned_X[aligned_index] = '_';
        aligned_Y[aligned_index] = Y[j - 1];
        --j;
        ++aligned_index;
        }

    aligned_X[aligned_index] = '\0';
    aligned_Y[aligned_index] = '\0';

    // Reverse the aligned strings to get the correct order
    int len = strlen(aligned_X);
    for (int start = 0, end = len - 1; start < end; ++start, --end) {
        char temp = aligned_X[start];
        aligned_X[start] = aligned_X[end];
        aligned_X[end] = temp;

        temp = aligned_Y[start];
        aligned_Y[start] = aligned_Y[end];
        aligned_Y[end] = temp;
    }

    // Calculate the minimum cost
    int min_cost = dp[m][n];

    printf("Aligned X: %s\n", aligned_X);
    printf("Aligned Y: %s\n", aligned_Y);

}

void generate_max_cost_sequences(int n, int m, int gap_cost, int replacement_cost) {
    int total_cost = 0;
    char X[] = "AGTCC";
    char Y[] = "CTGAA";
    char X1[n];
    char Y1[m];

     strcpy(X1, X);
    if(n <= 4){
      X1[n] = '\0';
    }else{
      for(int i = 4; i < n;i++){
        X1[i] = 'C';
      }
    }
    strcpy(Y1, Y);
    if(m <= 4){
      Y1[m] = '\0';
    }else{
      for(int j = 4; j < n;j++){
        Y1[j] = 'A';
      }
    }

    total_cost = (n+m-2) * gap_cost;
    int star_total_cost;
    if(n > m){
      star_total_cost = replacement_cost * 2 * m + (n - m) * gap_cost;
    }else{
      star_total_cost = replacement_cost * 2 * n + (m - n) * gap_cost;
    }

    if(total_cost > star_total_cost){
      if(n > m){

        for(int i = 0; i < m; i++){
            X1[i] = '*';
            Y1[i] = '*';
        }

        for(int j = m; j < n; j++){
            Y1[j] = '_';
        }

        printf("Aligned X: %s\n", X1);
        printf("Aligned Y: %s\n", Y1);

    }else{

        for(int i = 0; i < n; i++){
            X1[i] = '*';
            Y1[i] = '*';
        }

        for(int j = n; j < m; j++){
            X1[j] = '_';

        }

        printf("Aligned X: %s\n", X1);
        printf("Aligned Y: %s\n", Y1);
    }

    total_cost = star_total_cost;
    }else{
    align_sequences(X1, Y1);
    }

    printf("Total cost: %d\n", total_cost);



}

int main() {
    int n = 6;
    int m = 4;
    int gap_cost = 2;
    int replacement_cost = 5;

    generate_max_cost_sequences(n, m, gap_cost, replacement_cost);



    return 0;
}
