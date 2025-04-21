#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<queue>
#include<string>

// classe para representar os estados do cubo
class Estado {
    public:
        std::string caminho;

        float g; // custo para chegar ao nó
        float h; // estimativa da função de avaliação
        float f; // função heurística
    
        char cubo[24]; // distribuição das cores atuais no cubo
    
    Estado() {
        g = h = f = 0;
        caminho = "";
    }
};

void determina_solucao(char* cubo);
int bfs(Estado estado_inicial);
int A_estrela(Estado estado_inicial);
void transicoes_A_estrela(Estado* estado_atual, std::vector<Estado>* estados, std::vector<Estado>* visitados);
void transicoes_bfs(Estado* estado_atual, std::queue<Estado>* estados, std::vector<Estado>* visitados);
void calcula_heuristica(Estado* estado, int g_previo);
void rotacionar_frontal_horario(char* cubo_atual, char* cubo_novo);
void rotacionar_frontal_antihorario(char* cubo_atual, char* cubo_novo);
void rotacionar_topo_horario(char* cubo_atual, char* cubo_novo);
void rotacionar_topo_antihorario(char* cubo_atual, char* cubo_novo);
void rotacionar_direita_horario(char* cubo_atual, char* cubo_novo);
void rotacionar_direita_antihorario(char* cubo_atual, char* cubo_novo);