# Rubik's cube solver - size 2

O código em questão soluciona Rubik's cube de tamanho 2x2x2, empregando tanto busca em largura, quanto A*. A heurística adotada consiste no número de cores em posições distintas das esperadas na solução.

Para executar o programa, os seguintes comandos devem ser executados na terminal:
```
make
./main
```

A partir daí, basta inserir em sequência o código equivalente às cores das 24 posições do seu cubo (`BRWYYRBGOGYROGOOBWRBWWYG`, por exemplo), sendo:
- 'Y' = amarelo;
- 'B' = azul;
- 'R' = vermelho;
- 'W' = branco;
- 'O' = laranja;
- 'G' = verde;

Por fim, o programa exibirá o número de passos que levou, o caminho encontrado e sua distância. A notação do caminho é padrão para cubos mágicos. A exemplo, uma execução do programa toma a seguinte forma:
```
Insira o estado inicial do cubo:
BRORWYGYBBWOOOWGWRYBGRYG
Calculando solucao...
Quantidade de nos visitados: 31282
Caminho: F R' U U F' U F'
Distancia calculada pela busca em largura: 7

Quantidade de nos visitados: 4396
Caminho: F R' U U F' U F'
Distancia calculada pelo A*: 7 
```
