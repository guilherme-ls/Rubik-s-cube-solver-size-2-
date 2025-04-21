#include"solver.hpp"

int main() {
    Estado estado_inicial;
    printf("Insira o estado inicial do cubo:\n");
    for(int i = 0; i < 24; i++) {
        scanf("%c", &(estado_inicial.cubo[i]));
    }

    printf("Calculando solucao...\n");
    // determina qual das soluções melhor se adequa ao caso em análise
    determina_solucao(estado_inicial.cubo);

    int distancia = bfs(estado_inicial);
    printf("Distancia calculada pela busca em largura: %d\n\n", distancia);

    distancia = A_estrela(estado_inicial);
    printf("Distancia calculada pelo A*: %d\n", distancia);

    return 0;
}