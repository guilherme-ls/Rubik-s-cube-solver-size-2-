#include"solver.hpp"

// lookup table de soluções possíveis
char solucoes[24][24] = {
    {'W', 'W', 'W', 'W', 'B', 'B', 'O', 'O', 'G', 'G', 'R', 'R', 'B', 'B', 'O', 'O', 'G', 'G', 'R', 'R', 'Y', 'Y', 'Y', 'Y'},
    {'G', 'G', 'G', 'G', 'W', 'W', 'O', 'O', 'Y', 'Y', 'R', 'R', 'W', 'W', 'O', 'O', 'Y', 'Y', 'R', 'R', 'B', 'B', 'B', 'B'},
    {'Y', 'Y', 'Y', 'Y', 'G', 'G', 'O', 'O', 'B', 'B', 'R', 'R', 'G', 'G', 'O', 'O', 'B', 'B', 'R', 'R', 'W', 'W', 'W', 'W'},
    {'B', 'B', 'B', 'B', 'Y', 'Y', 'O', 'O', 'W', 'W', 'R', 'R', 'Y', 'Y', 'O', 'O', 'W', 'W', 'R', 'R', 'G', 'G', 'G', 'G'},
    {'W', 'W', 'W', 'W', 'R', 'R', 'B', 'B', 'O', 'O', 'G', 'G', 'R', 'R', 'B', 'B', 'O', 'O', 'G', 'G', 'Y', 'Y', 'Y', 'Y'},
    {'O', 'O', 'O', 'O', 'W', 'W', 'B', 'B', 'Y', 'Y', 'G', 'G', 'W', 'W', 'B', 'B', 'Y', 'Y', 'G', 'G', 'R', 'R', 'R', 'R'},
    {'Y', 'Y', 'Y', 'Y', 'O', 'O', 'B', 'B', 'R', 'R', 'G', 'G', 'O', 'O', 'B', 'B', 'R', 'R', 'G', 'G', 'W', 'W', 'W', 'W'},
    {'R', 'R', 'R', 'R', 'Y', 'Y', 'B', 'B', 'W', 'W', 'G', 'G', 'Y', 'Y', 'B', 'B', 'W', 'W', 'G', 'G', 'O', 'O', 'O', 'O'},
    {'W', 'W', 'W', 'W', 'G', 'G', 'R', 'R', 'B', 'B', 'O', 'O', 'G', 'G', 'R', 'R', 'B', 'B', 'O', 'O', 'Y', 'Y', 'Y', 'Y'},
    {'B', 'B', 'B', 'B', 'W', 'W', 'R', 'R', 'Y', 'Y', 'O', 'O', 'W', 'W', 'R', 'R', 'Y', 'Y', 'O', 'O', 'G', 'G', 'G', 'G'},
    {'Y', 'Y', 'Y', 'Y', 'B', 'B', 'R', 'R', 'G', 'G', 'O', 'O', 'B', 'B', 'R', 'R', 'G', 'G', 'O', 'O', 'W', 'W', 'W', 'W'},
    {'G', 'G', 'G', 'G', 'Y', 'Y', 'R', 'R', 'W', 'W', 'O', 'O', 'Y', 'Y', 'R', 'R', 'W', 'W', 'O', 'O', 'B', 'B', 'B', 'B'},
    {'W', 'W', 'W', 'W', 'O', 'O', 'G', 'G', 'R', 'R', 'B', 'B', 'O', 'O', 'G', 'G', 'R', 'R', 'B', 'B', 'Y', 'Y', 'Y', 'Y'},
    {'R', 'R', 'R', 'R', 'W', 'W', 'G', 'G', 'Y', 'Y', 'B', 'B', 'W', 'W', 'G', 'G', 'Y', 'Y', 'B', 'B', 'O', 'O', 'O', 'O'},
    {'Y', 'Y', 'Y', 'Y', 'R', 'R', 'G', 'G', 'O', 'O', 'B', 'B', 'R', 'R', 'G', 'G', 'O', 'O', 'B', 'B', 'W', 'W', 'W', 'W'},
    {'O', 'O', 'O', 'O', 'Y', 'Y', 'G', 'G', 'W', 'W', 'B', 'B', 'Y', 'Y', 'G', 'G', 'W', 'W', 'B', 'B', 'R', 'R', 'R', 'R'},
    {'O', 'O', 'O', 'O', 'G', 'G', 'W', 'W', 'B', 'B', 'Y', 'Y', 'G', 'G', 'W', 'W', 'B', 'B', 'Y', 'Y', 'R', 'R', 'R', 'R'},
    {'B', 'B', 'B', 'B', 'O', 'O', 'W', 'W', 'R', 'R', 'Y', 'Y', 'O', 'O', 'W', 'W', 'R', 'R', 'Y', 'Y', 'G', 'G', 'G', 'G'},
    {'R', 'R', 'R', 'R', 'B', 'B', 'W', 'W', 'G', 'G', 'Y', 'Y', 'B', 'B', 'W', 'W', 'G', 'G', 'Y', 'Y', 'O', 'O', 'O', 'O'},
    {'G', 'G', 'G', 'G', 'R', 'R', 'W', 'W', 'O', 'O', 'Y', 'Y', 'R', 'R', 'W', 'W', 'O', 'O', 'Y', 'Y', 'B', 'B', 'B', 'B'},
    {'R', 'R', 'R', 'R', 'G', 'G', 'Y', 'Y', 'B', 'B', 'W', 'W', 'G', 'G', 'Y', 'Y', 'B', 'B', 'W', 'W', 'O', 'O', 'O', 'O'},
    {'B', 'B', 'B', 'B', 'R', 'R', 'Y', 'Y', 'O', 'O', 'W', 'W', 'R', 'R', 'Y', 'Y', 'O', 'O', 'W', 'W', 'G', 'G', 'G', 'G'},
    {'O', 'O', 'O', 'O', 'B', 'B', 'Y', 'Y', 'G', 'G', 'W', 'W', 'B', 'B', 'Y', 'Y', 'G', 'G', 'W', 'W', 'R', 'R', 'R', 'R'},
    {'G', 'G', 'G', 'G', 'O', 'O', 'Y', 'Y', 'R', 'R', 'W', 'W', 'O', 'O', 'Y', 'Y', 'R', 'R', 'W', 'W', 'B', 'B', 'B', 'B'},
};
char* solucao;

// determina qual será a solução buscada
void determina_solucao(char* cubo) {
    for(int i = 0; i < 24; i++) {
        if(cubo[12] == solucoes[i][12] && cubo[19] == solucoes[i][19] && cubo[22] == solucoes[i][22]) {
            solucao = solucoes[i];
            return;
        }
    }

    // algo de errado na entrada impediu que a solução seja encontrada
    printf("Erro, entrada invalida\n");
    exit(1);
}

// função para comparação de custos da heurísitica na heap
struct compara_heuristica {
    constexpr bool operator()(Estado const& x, Estado const& y) const noexcept {
        return x.f > y.f;
    }
};

// checa se foi encontrada a solução
bool checa_final(char* cubo) {
    if(memcmp(cubo, solucao, sizeof(char)*24) == 0)
        return true;
    return false;
}

// checa se o estado em análise já foi visitado antes
bool checa_igualdade(std::vector<Estado>* nos_visitados, Estado* estado_checado) {
    for(auto iterador = nos_visitados->cbegin(); iterador < nos_visitados->cend(); iterador++) {
        if(memcmp(estado_checado->cubo, (*iterador).cubo, sizeof(estado_checado->cubo)) == 0)
            return true;
    }
    return false;
}

// calcula valor da função heurística escolhida
void calcula_heuristica(Estado* estado, int g_previo) {
    estado->g = g_previo + 1.0f;
    
    // determina o menor número de caracteres distintos em relação à solução
    float contagem_distintos = 0.0f;
    for(int i = 0; i < 24; i++) {
        if(estado->cubo[i] != solucao[i])
            ++contagem_distintos;
    }

    // determina o menor número possível de movimentos para alcançar a solução
    estado->h = contagem_distintos / 12.0f;

    // calcula o valor da função heurística no nó
    estado->f = estado->g + estado->h;
}

// algoritmo de busca em largura
int bfs(Estado estado_inicial) {
    std::queue<Estado> nos_abertos;
    std::vector<Estado> nos_visitados;
    nos_abertos.emplace(estado_inicial);
    int contador = 0;

    // enquanto a lista de nós não for vazia, os explora
    while(!nos_abertos.empty()) {
        // seleciona o primeiro nó inserido para buscar
        Estado estado_atual = nos_abertos.front();
        nos_abertos.pop();
        nos_visitados.emplace_back(estado_atual);

        // se é nó final, conclui busca
        if(checa_final(estado_atual.cubo)) {
            printf("Quantidade de nos visitados: %d\n", contador);
            std::cout << "Caminho: " << estado_atual.caminho << std::endl;
            return (int)estado_atual.g;
        }

        // se não for nó final, adiciona novos nós atingíveis à lista
        transicoes_bfs(&estado_atual, &nos_abertos, &nos_visitados);
        contador++;
    }

    return -1;
}

// algoritmo de busca A*
int A_estrela(Estado estado_inicial) {
    std::vector<Estado> nos_abertos;
    std::vector<Estado> nos_visitados;
    nos_abertos.emplace_back(estado_inicial);
    int contador = 0;

    // enquanto a lista de nós não for vazio, os explora
    while(!nos_abertos.empty()) {
        // seleciona nó com menor valor de f
        std::pop_heap(nos_abertos.begin(), nos_abertos.end(), compara_heuristica());
        Estado estado_atual = *(nos_abertos.end() - 1);
        nos_abertos.pop_back();
        nos_visitados.emplace_back(estado_atual);

        // se é nó final, conclui busca
        if(checa_final(estado_atual.cubo)) {
            printf("Quantidade de nos visitados: %d\n", contador);
            std::cout << "Caminho: " << estado_atual.caminho << std::endl;
            return (int)estado_atual.g;
        }

        // se não for nó final, adiciona novos nós atingíveis à lista
        transicoes_A_estrela(&estado_atual, &nos_abertos, &nos_visitados);
        contador++;
    }

    return -1;
}

// adiciona novos movimentos à lista de movimentos possíveis e ordena para o caso bfs
void transicoes_bfs(Estado* estado_atual, std::queue<Estado>* estados, std::vector<Estado>* visitados){
    Estado estado_novo;

    // adiciona movimentos
    rotacionar_frontal_horario(estado_atual->cubo, estado_novo.cubo);
    if(!checa_igualdade(visitados, &estado_novo)) {
        estado_novo.caminho = estado_atual->caminho + "F ";
        estado_novo.g = estado_atual->g + 1.0f;
        estados->emplace(estado_novo);
    }
    
    rotacionar_frontal_antihorario(estado_atual->cubo, estado_novo.cubo);
    if(!checa_igualdade(visitados, &estado_novo)) {
        estado_novo.caminho = estado_atual->caminho + "F' ";
        estado_novo.g = estado_atual->g + 1.0f;
        estados->emplace(estado_novo);
    }
    
    rotacionar_topo_horario(estado_atual->cubo, estado_novo.cubo);
    if(!checa_igualdade(visitados, &estado_novo)) {
        estado_novo.caminho = estado_atual->caminho + "U ";
        estado_novo.g = estado_atual->g + 1.0f;
        estados->emplace(estado_novo);
    }
    
    rotacionar_topo_antihorario(estado_atual->cubo, estado_novo.cubo);
    if(!checa_igualdade(visitados, &estado_novo)) {
        estado_novo.caminho = estado_atual->caminho + "U' ";
        estado_novo.g = estado_atual->g + 1.0f;
        estados->emplace(estado_novo);
    }
    
    rotacionar_direita_horario(estado_atual->cubo, estado_novo.cubo);
    if(!checa_igualdade(visitados, &estado_novo)) {
        estado_novo.caminho = estado_atual->caminho + "R ";
        estado_novo.g = estado_atual->g + 1.0f;
        estados->emplace(estado_novo);
    }
    
    rotacionar_direita_antihorario(estado_atual->cubo, estado_novo.cubo);
    if(!checa_igualdade(visitados, &estado_novo)) {
        estado_novo.caminho = estado_atual->caminho + "R' ";
        estado_novo.g = estado_atual->g + 1.0f;
        estados->emplace(estado_novo);
    }
}

// adiciona novos movimentos à lista de movimentos possíveis e calcula o valor da função heurística
void transicoes_A_estrela(Estado* estado_atual, std::vector<Estado>* estados, std::vector<Estado>* visitados) {
    Estado estado_novo;

    // adiciona movimentos
    rotacionar_frontal_horario(estado_atual->cubo, estado_novo.cubo);
    if(!checa_igualdade(visitados, &estado_novo)) {
        calcula_heuristica(&estado_novo, estado_atual->g);
        estado_novo.caminho = estado_atual->caminho + "F ";
        estados->emplace_back(estado_novo);
        std::push_heap(estados->begin(), estados->end(), compara_heuristica());
    }
    
    rotacionar_frontal_antihorario(estado_atual->cubo, estado_novo.cubo);
    if(!checa_igualdade(visitados, &estado_novo)) {
        calcula_heuristica(&estado_novo, estado_atual->g);
        estado_novo.caminho = estado_atual->caminho + "F' ";
        estados->emplace_back(estado_novo);
        std::push_heap(estados->begin(), estados->end(), compara_heuristica());
    }
    
    rotacionar_topo_horario(estado_atual->cubo, estado_novo.cubo);
    if(!checa_igualdade(visitados, &estado_novo)) {
        calcula_heuristica(&estado_novo, estado_atual->g);
        estado_novo.caminho = estado_atual->caminho + "U ";
        estados->emplace_back(estado_novo);
        std::push_heap(estados->begin(), estados->end(), compara_heuristica());
    }
    
    rotacionar_topo_antihorario(estado_atual->cubo, estado_novo.cubo);
    if(!checa_igualdade(visitados, &estado_novo)) {
        calcula_heuristica(&estado_novo, estado_atual->g);
        estado_novo.caminho = estado_atual->caminho + "U' ";
        estados->emplace_back(estado_novo);
        std::push_heap(estados->begin(), estados->end(), compara_heuristica());
    }
    
    rotacionar_direita_horario(estado_atual->cubo, estado_novo.cubo);
    if(!checa_igualdade(visitados, &estado_novo)) {
        calcula_heuristica(&estado_novo, estado_atual->g);
        estado_novo.caminho = estado_atual->caminho + "R ";
        estados->emplace_back(estado_novo);
        std::push_heap(estados->begin(), estados->end(), compara_heuristica());
    }
    
    rotacionar_direita_antihorario(estado_atual->cubo, estado_novo.cubo);
    if(!checa_igualdade(visitados, &estado_novo)) {
        calcula_heuristica(&estado_novo, estado_atual->g);
        estado_novo.caminho = estado_atual->caminho + "R' ";
        estados->emplace_back(estado_novo);
        std::push_heap(estados->begin(), estados->end(), compara_heuristica());
    }
}

/*
 * conjunto de rotações possíveis no cubo
 */

void rotacionar_frontal_horario(char* cubo_atual, char* cubo_novo) {
    cubo_novo[0] = cubo_atual[0];
    cubo_novo[1] = cubo_atual[1];
    cubo_novo[2] = cubo_atual[13];
    cubo_novo[3] = cubo_atual[5];
    cubo_novo[4] = cubo_atual[4];
    cubo_novo[5] = cubo_atual[20];
    cubo_novo[6] = cubo_atual[14];
    cubo_novo[7] = cubo_atual[6];
    cubo_novo[8] = cubo_atual[2];
    cubo_novo[9] = cubo_atual[9];
    cubo_novo[10] = cubo_atual[10];
    cubo_novo[11] = cubo_atual[11];
    cubo_novo[12] = cubo_atual[12];
    cubo_novo[13] = cubo_atual[21];
    cubo_novo[14] = cubo_atual[15];
    cubo_novo[15] = cubo_atual[7];
    cubo_novo[16] = cubo_atual[3];
    cubo_novo[17] = cubo_atual[17];
    cubo_novo[18] = cubo_atual[18];
    cubo_novo[19] = cubo_atual[19];
    cubo_novo[20] = cubo_atual[16];
    cubo_novo[21] = cubo_atual[8];
    cubo_novo[22] = cubo_atual[22];
    cubo_novo[23] = cubo_atual[23];
}

void rotacionar_frontal_antihorario(char* cubo_atual, char* cubo_novo) {
    cubo_novo[0] = cubo_atual[0];
    cubo_novo[1] = cubo_atual[1];
    cubo_novo[2] = cubo_atual[8];
    cubo_novo[3] = cubo_atual[16];
    cubo_novo[4] = cubo_atual[4];
    cubo_novo[5] = cubo_atual[3];
    cubo_novo[6] = cubo_atual[7];
    cubo_novo[7] = cubo_atual[15];
    cubo_novo[8] = cubo_atual[21];
    cubo_novo[9] = cubo_atual[9];
    cubo_novo[10] = cubo_atual[10];
    cubo_novo[11] = cubo_atual[11];
    cubo_novo[12] = cubo_atual[12];
    cubo_novo[13] = cubo_atual[2];
    cubo_novo[14] = cubo_atual[6];
    cubo_novo[15] = cubo_atual[14];
    cubo_novo[16] = cubo_atual[20];
    cubo_novo[17] = cubo_atual[17];
    cubo_novo[18] = cubo_atual[18];
    cubo_novo[19] = cubo_atual[19];
    cubo_novo[20] = cubo_atual[5];
    cubo_novo[21] = cubo_atual[13];
    cubo_novo[22] = cubo_atual[22];
    cubo_novo[23] = cubo_atual[23];
}

void rotacionar_topo_horario(char* cubo_atual, char* cubo_novo) {
    cubo_novo[0] = cubo_atual[2];
    cubo_novo[1] = cubo_atual[0];
    cubo_novo[2] = cubo_atual[3];
    cubo_novo[3] = cubo_atual[1];
    cubo_novo[4] = cubo_atual[6];
    cubo_novo[5] = cubo_atual[7];
    cubo_novo[6] = cubo_atual[8];
    cubo_novo[7] = cubo_atual[9];
    cubo_novo[8] = cubo_atual[10];
    cubo_novo[9] = cubo_atual[11];
    cubo_novo[10] = cubo_atual[4];
    cubo_novo[11] = cubo_atual[5];
    cubo_novo[12] = cubo_atual[12];
    cubo_novo[13] = cubo_atual[13];
    cubo_novo[14] = cubo_atual[14];
    cubo_novo[15] = cubo_atual[15];
    cubo_novo[16] = cubo_atual[16];
    cubo_novo[17] = cubo_atual[17];
    cubo_novo[18] = cubo_atual[18];
    cubo_novo[19] = cubo_atual[19];
    cubo_novo[20] = cubo_atual[20];
    cubo_novo[21] = cubo_atual[21];
    cubo_novo[22] = cubo_atual[22];
    cubo_novo[23] = cubo_atual[23];
}

void rotacionar_topo_antihorario(char* cubo_atual, char* cubo_novo) {
    cubo_novo[0] = cubo_atual[1];
    cubo_novo[1] = cubo_atual[3];
    cubo_novo[2] = cubo_atual[0];
    cubo_novo[3] = cubo_atual[2];
    cubo_novo[4] = cubo_atual[10];
    cubo_novo[5] = cubo_atual[11];
    cubo_novo[6] = cubo_atual[4];
    cubo_novo[7] = cubo_atual[5];
    cubo_novo[8] = cubo_atual[6];
    cubo_novo[9] = cubo_atual[7];
    cubo_novo[10] = cubo_atual[8];
    cubo_novo[11] = cubo_atual[9];
    cubo_novo[12] = cubo_atual[12];
    cubo_novo[13] = cubo_atual[13];
    cubo_novo[14] = cubo_atual[14];
    cubo_novo[15] = cubo_atual[15];
    cubo_novo[16] = cubo_atual[16];
    cubo_novo[17] = cubo_atual[17];
    cubo_novo[18] = cubo_atual[18];
    cubo_novo[19] = cubo_atual[19];
    cubo_novo[20] = cubo_atual[20];
    cubo_novo[21] = cubo_atual[21];
    cubo_novo[22] = cubo_atual[22];
    cubo_novo[23] = cubo_atual[23];
}

void rotacionar_direita_horario(char* cubo_atual, char* cubo_novo) {
    cubo_novo[0] = cubo_atual[0];
    cubo_novo[1] = cubo_atual[7];
    cubo_novo[2] = cubo_atual[2];
    cubo_novo[3] = cubo_atual[15];
    cubo_novo[4] = cubo_atual[4];
    cubo_novo[5] = cubo_atual[5];
    cubo_novo[6] = cubo_atual[6];
    cubo_novo[7] = cubo_atual[21];
    cubo_novo[8] = cubo_atual[16];
    cubo_novo[9] = cubo_atual[8];
    cubo_novo[10] = cubo_atual[3];
    cubo_novo[11] = cubo_atual[11];
    cubo_novo[12] = cubo_atual[12];
    cubo_novo[13] = cubo_atual[13];
    cubo_novo[14] = cubo_atual[14];
    cubo_novo[15] = cubo_atual[23];
    cubo_novo[16] = cubo_atual[17];
    cubo_novo[17] = cubo_atual[9];
    cubo_novo[18] = cubo_atual[1];
    cubo_novo[19] = cubo_atual[19];
    cubo_novo[20] = cubo_atual[20];
    cubo_novo[21] = cubo_atual[18];
    cubo_novo[22] = cubo_atual[22];
    cubo_novo[23] = cubo_atual[10];
}

void rotacionar_direita_antihorario(char* cubo_atual, char* cubo_novo) {
    cubo_novo[0] = cubo_atual[0];
    cubo_novo[1] = cubo_atual[18];
    cubo_novo[2] = cubo_atual[2];
    cubo_novo[3] = cubo_atual[10];
    cubo_novo[4] = cubo_atual[4];
    cubo_novo[5] = cubo_atual[5];
    cubo_novo[6] = cubo_atual[6];
    cubo_novo[7] = cubo_atual[1];
    cubo_novo[8] = cubo_atual[9];
    cubo_novo[9] = cubo_atual[17];
    cubo_novo[10] = cubo_atual[23];
    cubo_novo[11] = cubo_atual[11];
    cubo_novo[12] = cubo_atual[12];
    cubo_novo[13] = cubo_atual[13];
    cubo_novo[14] = cubo_atual[14];
    cubo_novo[15] = cubo_atual[3];
    cubo_novo[16] = cubo_atual[8];
    cubo_novo[17] = cubo_atual[16];
    cubo_novo[18] = cubo_atual[21];
    cubo_novo[19] = cubo_atual[19];
    cubo_novo[20] = cubo_atual[20];
    cubo_novo[21] = cubo_atual[7];
    cubo_novo[22] = cubo_atual[22];
    cubo_novo[23] = cubo_atual[15];
}
