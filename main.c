#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Para o uso da função sleep
#include <stdbool.h>

#define SIZE 8

// Declara uma matriz 8x8 de ponteiros para strings
int *matrix[SIZE][SIZE];
// Declara variáveis para armazenar a posição inicial do robô
int stationLine, stationColumn;

int trashCounter;
typedef struct {
    int line;
    int column;
} Position;

Position trash[SIZE * SIZE];
Position robot;

// Função para inicializar a matriz com valores padrão "***"
void createMatrix() {
    // Percorre todas as linhas
    for (int i = 0; i < SIZE; i++) {
        // Percorre todas as colunas
        for (int j = 0; j < SIZE; j++) {
            // Define o valor padrão "***" em cada posição
            matrix[i][j] = 1;
        }
    }
}
// 1 = PAREDE
// 2 = LUGAR QUE PODE PASSAR = LIXO/ESTAÇÃO
// 0 = LUGAR LIMPO
// -1 = ROBO

// Função para imprimir a matriz no console
void printMatrix() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    
    // Percorre todas as linhas
    for (int i = 0; i < SIZE; i++) {
        // Percorre todas as colunas
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == -1) {
                printf("|-_-|");
                //printf("| %d |", matrix[i][j]);
            } else if (matrix[i][j] == 0) {
                printf("|   |");
                //printf("| %d |", matrix[i][j]);
            } else if (matrix[i][j] == 1) {
                printf("|---|");
                //printf("| %d |", matrix[i][j]);
            } else if (i == stationLine && j == stationColumn) {
                printf("| E |");
                //printf("| %d |", matrix[i][j]);
            } 
            else if (matrix[i][j] == 2) {
                printf("|@@@|");
                //printf("| %d |", matrix[i][j]);
            }
        }
        // Pula para a próxima linha após imprimir todas as colunas
        printf("\n");
    }
    printf("\nFeito por: Leonardo Almeida \n");
}

// Função para definir a posição inicial do robô
void addStation() {
    // Exibe a matriz na tela
    printMatrix();
    
    // Solicita ao usuário a linha inicial do robô
    printf("Digite a linha inicial do robo: ");
    scanf("%d", &stationLine);
    
    // Verifica se a linha está fora do intervalo permitido e solicita novamente se necessário
    while (stationLine < 0 || stationLine > SIZE - 1) {
        printf("Digite a linha inicial entre 0 e 7 do robo: ");
        scanf("%d", &stationLine);
    }
    
    // Solicita ao usuário a coluna inicial do robô
    printf("Digite a coluna inicial do robo: ");
    scanf("%d", &stationColumn);
    
    // Verifica se a coluna está fora do intervalo permitido e solicita novamente se necessário
    while (stationColumn < 0 || stationColumn > SIZE - 1) {
        printf("Digite a coluna inicial entre 0 e 7 do robo: ");
        scanf("%d", &stationColumn);
    }
    
    matrix[stationLine][stationColumn] = 3;
}

void verifyTrash() {
    trashCounter = 0; // Resetar contador Lixo antes de verificar novamente

    // Percorre todas as linhas
    for (int i = 0; i < 8; i++) {
        // Percorre todas as colunas
        for (int j = 0; j < 8; j++) {
            // Verifica se a posição atual contém lixo
            if (matrix[i][j] == 2 && !(i == stationLine && j == stationColumn)) {
                // Armazena a posição do lixo na estrutura lixo
                trash[trashCounter].line = i;
                trash[trashCounter].column = j;
                // Incrementa o contador de lixo
                trashCounter++;
            }
        }
    }
}

int isValidMove(int x, int y) {
    return y < SIZE && y >= 0 && x < SIZE && x >= 0;
}

int checkDirectionBase() {
    int directions[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
    
    for (int i = 0; i < 4; i++) {
        int step = 1;
        while (1) {
            matrix[stationLine][stationColumn] = 2;
            int newLine = robot.line + step * directions[i][0];
            int newColumn = robot.column + step * directions[i][1];
            
            if (!isValidMove(newLine, newColumn)) break;

            if ((newLine == stationLine && newColumn == stationColumn) || matrix[newLine][newColumn] == 0) {
                int sideLine = robot.line + directions[i][0];
                int sideColumn = robot.column + directions[i][1];
                
                if (isValidMove(sideLine, sideColumn) && 
                    (matrix[sideLine][sideColumn] == 0 || matrix[sideLine][sideColumn] == 3)) {
                    return i + 1;
                }
            }
            step++;
        }
    }
    return 0;
}

// Função para mover o robô de volta à base
void returnBase() {
    while (robot.line != stationLine || robot.column != stationColumn) {
        int direction = checkDirectionBase();
        
        if (robot.line != stationLine || robot.column != stationColumn) {
            matrix[robot.line][robot.column] = 0;
        }
        
        switch (direction) {
            case 1:
                robot.line -= 1;
                break;
            case 2:
                robot.column -= 1;
                break;
            case 3:
                robot.column += 1;
                break;
            case 4:
                robot.line += 1;
                break;
        }
        matrix[robot.line][robot.column] = -1;
        printMatrix();
        sleep(1);
    }
}

int checkDirectionTrash() {
    // Direções: Cima, Esquerda, Direita, Baixo 
    int directions[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
    int lastDirection = 0;

    for (int i = 0; i < 4; i++) {
        int step = 1;
        while (1) {
            int newLine = robot.line + step * directions[i][0];
            int newColumn = robot.column + step * directions[i][1];

            if (!isValidMove(newLine, newColumn)) break;

            // Verifica se a nova posição é válida e se contém lixo
            if (matrix[newLine][newColumn] == 2) {
                int sideLine = robot.line + directions[i][0];
                int sideColumn = robot.column + directions[i][1];
                
                if (isValidMove(sideLine, sideColumn) && 
                    (matrix[sideLine][sideColumn] == 0 || matrix[sideLine][sideColumn] == 2)) {
                    return i + 1; // Retorna a direção correspondente
                }
            }

            // Verifica se a nova posição é a base
            if (newLine == stationLine && newColumn == stationColumn) {
                lastDirection = i + 1; // Armazena a direção da base
            }
            step++;
        }
    }

    // Se nenhuma direção com lixo foi encontrada, retorna a direção da base, se disponível
    if (lastDirection != 0) {
        return lastDirection;
    }

    return 0; // Nenhum lixo ou base encontrado
}

int moveRobot() {
    // Inicializa a posição do robô na estação
    robot.line = stationLine;
    robot.column = stationColumn;
    verifyTrash();

    while (trashCounter > 0) {
        verifyTrash();
        int directionTrash = checkDirectionTrash();
        // Se o robô não está na estação, limpa a posição atual
        if (!(robot.line == stationLine && robot.column == stationColumn)) {
            matrix[robot.line][robot.column] = 0;
        }

        // Move o robô baseado na direção do lixo
        switch (directionTrash) {
            case 1: // Cima
                robot.line -= 1;
                trashCounter -= 1;
                break;
            case 2: // Esquerda        
                robot.column -= 1;
                trashCounter -= 1;
                break;
            case 3: // Direita
                robot.column += 1;
                trashCounter -= 1;
                break;
            case 4: // Baixo
                robot.line += 1;
                trashCounter -= 1;
                break;
            default:
                verifyTrash();
                break;
        }
        matrix[robot.line][robot.column] = -1;
        matrix[stationLine][stationColumn] = 3;
        printMatrix();
        sleep(1);
    }
    returnBase();
    return 0;
}

// Função para adicionar lixo na matriz
int addTrash() {
    int trashLine = 0, trashColumn = 0;  // Inicializa as variáveis para as coordenadas do lixo
    
    // Continua a solicitar entradas do usuário até que a linha do lixo seja -1
    while (trashLine != -1) {
        printMatrix();
        
        // Solicita ao usuário a linha do lixo
        printf("Digite a linha do lixo ou -1 para realizar a limpeza: ");
        scanf("%d", &trashLine);
        
        // Verifica se a linha do lixo está fora do intervalo permitido e solicita novamente se necessário
        while (trashLine < -1 || trashLine > SIZE - 1) {
            printf("Digite um numero entre 0 e 7 para a linha do lixo ou -1 para realizar limpeza: ");
            scanf("%d", &trashLine);
        }
        
        // Se a linha do lixo for -1, chama a função de limpeza
        if (trashLine == -1) {
            moveRobot();
            return 0;
        }
        
        // Solicita ao usuário a coluna do lixo
        printf("Digite a coluna do lixo: ");
        scanf("%d", &trashColumn);
        
        // Verifica se a coluna do lixo está fora do intervalo permitido e solicita novamente se necessário
        while (trashColumn < 0 || trashColumn > SIZE - 1) {
            printf("Digite um numero entre 0 e 7 para a coluna do lixo: ");
            scanf("%d", &trashColumn);
        }
        
        // Verifica se a posição do lixo coincide com a posição inicial do robô
        if (matrix[trashLine][trashColumn] == matrix[stationLine][stationColumn]) {
            // Informa que não é possível adicionar lixo na posição do robô
            printf("Impossivel adicionar lixo na estacao!!\n");
        } else {
            // Define a posição do lixo na matriz com "@@@"
            matrix[trashLine][trashColumn] = 2;
        }
    }
}

// Função principal
int main() {
    createMatrix();
    addStation();
    addTrash();
    printMatrix();
    return 0;
}