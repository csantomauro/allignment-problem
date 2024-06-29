
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
    printf("Minimum Cost: %d\n", min_cost);

    printf("dp matrix:");
    for(int u=0;u<m+1;u++){
        printf("\n");
        for(int v=0;v<n+1;v++){
            printf("%02d ", dp[u][v]);
        }
    }
}

int main() {
    char X[] = "ATCTCAG";
    char Y[] = "TGCATA";
    align_sequences(X, Y);

    return 0;
}
