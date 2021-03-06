#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

int getRandom(int lower, int upper) {
    return (rand() % (upper - lower + 1)) + lower;
}

int borderFixer(int val, int max) {
    if (val < 0) {
        return max - 1;
    } else if (val > max - 1) {
        return 0;
    } else {
        return val;
    }

}

void matrixYaz(int h, int w, int matrix[h][w]) {
    char word2[1000] = "";
    printf("        |");
    strcat(word2,"---------");
    for (int k = 0; k < w; ++k) {
        printf("(%6d)|", k + 1);
        strcat(word2,"---------");
    }
    printf("\n%s\n",word2);
    for (int i = 0; i < h; ++i) {
        char word[1000] = "";
        for (int j = -1; j < w; ++j) {
            if (j == -1){
                printf("(%-6d)|", i + 1);
            } else {
                printf("%-+8d|", matrix[i][j]);
            }
            strcat(word,"---------");
        }
        printf("\n%s\n",word);
    }
}

int main() {
    srand(time(0));
    int maxH, maxW;
    int status;
    printf("Enter Image Matrix sizes (Min: 3x3 Format: AxB):");
    status = scanf(" %dx%d", &maxH, &maxW);
    if (status != 2 || maxH < 3 || maxW < 3){
        printf("-Incorrect format.");
        exit(0);
    }
    printf("-Image Matrix define as %dx%d\n",maxH,maxW);
    int imageMatrix[maxH][maxW];
    for (int i = 0; i < maxH; ++i) {
        for (int j = 0; j < maxW; ++j) {
            imageMatrix[i][j] = getRandom(0, 255);
        }
    }
    int kernelMatrix[3][3] = {
            {0,  -1, 0},
            {-1, 5, -1},
            {0,  -1, 0}
    };
    printf("////////////////////////////////////////////\n");
    for (int k = 0; k < 3; ++k) {
        for (int i = 0; i < 3; ++i) {
            printf("Enter Kernel Matrix Values (Format: Number) (%dx%d Of 3x3):", k + 1, i + 1);
            status = scanf(" %d", &kernelMatrix[k][i]);
            if (status != 1){
                printf("-Incorrect format.");
                exit(0);
            }
        }
    }
    int resultMatrix[maxH][maxW];
    int h = 0;
    int w = 0;
    while (h < maxH) {
        while (w < maxW) {
            resultMatrix[h][w] =
                    imageMatrix[borderFixer(h - 1, maxH)][borderFixer(w - 1, maxW)] * kernelMatrix[0][0] +
                    imageMatrix[borderFixer(h - 1, maxH)][w] * kernelMatrix[0][1] +
                    imageMatrix[borderFixer(h - 1, maxH)][borderFixer(w + 1, maxW)] * kernelMatrix[0][2] +

                    imageMatrix[h][borderFixer(w - 1, maxW)] * kernelMatrix[1][0] +
                    imageMatrix[h][w] * kernelMatrix[1][1] +
                    imageMatrix[h][borderFixer(w + 1, maxW)] * kernelMatrix[1][2] +

                    imageMatrix[borderFixer(h + 1, maxH)][borderFixer(w - 1, maxW)] * kernelMatrix[2][0] +
                    imageMatrix[borderFixer(h + 1, maxH)][w] * kernelMatrix[2][1] +
                    imageMatrix[borderFixer(h + 1, maxH)][borderFixer(w + 1, maxW)] * kernelMatrix[2][2];
            w++;
        }
        w = 0;
        h++;
    }
    printf("////////////////////////////////////////////\n");
    int okunanA, okunanB;
    printf("Enter the matrix address (Format: AxB):");
    status = scanf(" %dx%d", &okunanA, &okunanB);
    if (status != 2 || okunanA > maxH || okunanB > maxW || okunanA < 1 || okunanB < 1){
        printf("-Incorrect format.");
        exit(0);
    }
    h = okunanA;
    w = okunanB;
    printf("*********************************************\n");
    printf("Result: %d\n", resultMatrix[okunanA - 1][okunanB - 1]);
    printf("*********************************************\n");
    printf("Matrix which the result is generated:\n"
           "-------------------------------------\n");
    printf("%-5d", imageMatrix[borderFixer(okunanA - 1 - 1, maxH)][borderFixer(okunanB - 1 - 1, maxW)]);
    printf("%-5d", imageMatrix[borderFixer(okunanA - 1 - 1, maxH)][okunanB - 1]);
    printf("%-5d", imageMatrix[borderFixer(okunanA - 1 - 1, maxH)][borderFixer(okunanB - 1 + 1, maxW)]);
    printf("\n");
    printf("%-5d", imageMatrix[okunanA - 1][borderFixer(okunanB - 1 - 1, maxW)]);
    printf("%-5d", imageMatrix[okunanA - 1][okunanB - 1]);
    printf("%-5d", imageMatrix[okunanA - 1][borderFixer(okunanB - 1 + 1, maxW)]);
    printf("\n");
    printf("%-5d", imageMatrix[borderFixer(okunanA - 1 + 1, maxH)][borderFixer(okunanB - 1 - 1, maxW)]);
    printf("%-5d", imageMatrix[borderFixer(okunanA - 1 + 1, maxH)][okunanB - 1]);
    printf("%-5d", imageMatrix[borderFixer(okunanA - 1 + 1, maxH)][borderFixer(okunanB - 1 + 1, maxW)]);
    printf("\nImage Matrix: \n"
           "-------------\n");
    matrixYaz(maxH, maxW, imageMatrix);

    printf("\nKernel Matrix: \n"
           "--------------\n");
    matrixYaz(3, 3, kernelMatrix);
    printf("\nResult Matrix: \n"
           "--------------\n");
    matrixYaz(maxH, maxW, resultMatrix);
    return 0;
}
