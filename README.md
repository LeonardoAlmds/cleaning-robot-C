# Projeto Robô de Limpeza

## Descrição

Este projeto implementa um robô de limpeza que opera em uma grade 8x8. O robô começa de uma posição inicial definida pelo usuário e se move pela grade para limpar posições marcadas como lixo (`"@@@"`). O robô limpa a grade substituindo o lixo por espaços vazios (`"   "`), e finalmente retorna à sua posição inicial (a estação) após a limpeza.

## Funcionalidades

- Inicializar uma grade 8x8 com valores padrão.
- Definir a posição inicial do robô.
- Adicionar posições de lixo na grade.
- Mover automaticamente o robô para limpar o lixo.
- Retornar o robô à sua posição inicial após a limpeza.

## Primeiros Passos

### Pré-requisitos

- Um compilador C (por exemplo, `gcc`).
- Um terminal ou interface de linha de comando.

### Compilação

Para compilar o programa, use o seguinte comando:
```sh
gcc cleaning_robot.c -o cleaning_robot
```

### Executando o Programa

Após compilar, execute o programa com:
```sh
./cleaning_robot
```

### Instruções

1. **Inicialize a grade**:
    - A grade será inicializada com valores padrão (`"***"`).

2. **Defina a posição inicial do robô**:
    - O programa solicitará que você insira a linha e a coluna iniciais para o robô.
    - Insira valores entre `0` e `7` tanto para a linha quanto para a coluna.

3. **Adicione lixo na grade**:
    - O programa solicitará que você insira a linha e a coluna para cada posição de lixo.
    - Insira valores entre `0` e `7` tanto para a linha quanto para a coluna.
    - Para parar de adicionar lixo e iniciar o processo de limpeza, insira `-1` para a linha.

4. **Processo de limpeza do robô**:
    - O robô se moverá automaticamente para limpar todas as posições de lixo.
    - Após a limpeza, o robô retornará à sua posição inicial.

## Visão Geral do Código

### Estruturas de Dados

- `Position`:
    - Armazena as coordenadas de uma posição de lixo.

- `Robot`:
    - Armazena as coordenadas atuais do robô.

### Funções

- `createMatrix()`:
    - Inicializa a grade com valores padrão (`"***"`).

- `printMatrix()`:
    - Imprime o estado atual da grade no console.

- `addStation()`:
    - Solicita ao usuário definir a posição inicial do robô.

- `checkDirectionBase()`:
    - Determina a direção que o robô deve se mover para retornar à estação.

- `returnBase()`:
    - Move o robô de volta à sua posição inicial.

- `checkDirectionTrash()`:
    - Determina a direção que o robô deve se mover para encontrar e limpar o lixo.

- `moveRobot()`:
    - Controla os movimentos do robô para limpar o lixo e retornar à estação.

- `addTrash()`:
    - Solicita ao usuário adicionar posições de lixo na grade.

### Função Principal

A função `main()` inicializa a grade, define a posição inicial do robô, adiciona posições de lixo e inicia o processo de limpeza.

## Exemplo de Uso

1. **Definir a posição inicial do robô**:
    ```plaintext
    Digite a linha inicial do robo: 2
    Digite a coluna inicial do robo: 3
    ```

2. **Adicionar posições de lixo**:
    ```plaintext
    Digite a linha do lixo ou -1 para realizar a limpeza: 1
    Digite a coluna do lixo: 2
    Digite a linha do lixo ou -1 para realizar a limpeza: 4
    Digite a coluna do lixo: 5
    Digite a linha do lixo ou -1 para realizar a limpeza: -1
    ```

3. **Processo de limpeza do robô**:
    - O robô se moverá e limpará a grade, atualizando sua posição no console.

## Notas

- Certifique-se de que a posição inicial do robô e as posições do lixo estejam dentro do intervalo válido (`0` a `7`).
- O robô não limpará posições que estejam fora dos limites ou onde a estação do robô está localizada.

## Autor

Leonardo Almeida

## Licença

Este projeto está licenciado sob a Licença MIT.
