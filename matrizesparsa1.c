#include <stdio.h>
#include <stdlib.h>

//define o "objeto" ponto
typedef struct {
    int row;
    int col;
} Point;

//define o "objeto" linha
typedef struct {
    Point from;
    Point to;
} Line;

//função para desenhar linhas
void drawLine(Line line, int** matrix) {
    int i, j;
    int startRow = line.from.row;
    int startCol = line.from.col;
    int endRow = line.to.row;
    int endCol = line.to.col;

    // Verifica se é uma linha horizontal
    if (startRow == endRow) {
        for (j = startCol; j <= endCol; j++) {
            matrix[startRow][j] = 1;
        }
    }
    // Verifica se é uma linha vertical
    else if (startCol == endCol) {
        for (i = startRow; i <= endRow; i++) {
            matrix[i][startCol] = 1;
        }
    }
    // Verifica se é uma linha diagonal
    else {
        int rowDirection = (startRow < endRow) ? 1 : -1;
        int colDirection = (startCol < endCol) ? 1 : -1;

        i = startRow;
        j = startCol;
        while (i != endRow && j != endCol) {
            matrix[i][j] = 1;
            i += rowDirection;
            j += colDirection;
        }
        matrix[endRow][endCol] = 1;
    }
}


//função para desenhar pontos
void drawPoint(Point point, int** matrix) {
    matrix[point.row][point.col] = 1;
}

int main() {
    FILE* file = fopen("fileScript.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int** matrix = (int**)malloc(16 * sizeof(int*));
    if (matrix == NULL) {
        printf("Erro de alocação de memória.\n");
        return 1;
    }

    int i, j;
    for (i = 0; i < 16; i++) {
        matrix[i] = (int*)calloc(16, sizeof(int));
        if (matrix[i] == NULL) {
            printf("Erro de alocação de memória.\n");
            return 1;
        }
    }

    //o bloco abaixo é para definir o que cada script do arquivo faz
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '<') {
            if (line[1] == 'd') {
                Line newLine;
                sscanf(line, "<de(%d,%d) ate(%d,%d)>", &newLine.from.row, &newLine.from.col, &newLine.to.row, &newLine.to.col);
                drawLine(newLine, matrix);
            } else {
                Point newPoint;
                sscanf(line, "<(%d,%d)>", &newPoint.row, &newPoint.col);
                drawPoint(newPoint, matrix);
            }
        }
    }

    fclose(file);

    for (i = 0; i < 16; i++) {
        for (j = 0; j < 16; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < 16; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
