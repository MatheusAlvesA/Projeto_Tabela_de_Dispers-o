#Tabela de Disperção

Autor:
 - [Matheus Alves de Andrade] (https://github.com/MatheusAlvesA)

#Introdução
Esse projeto implementa uma estrutura de dados conhecida como tabela de disperção,
basicamente composta por um vetor de listas onde cada novo elemento a ser guardado
vai ocupar uma posição especifica nessa tabela, essa posição é dada atravez de
um algoritimo de hash, onde, uma vez extraido o hash, será decidida a posição na
tabela da forma hash%SizeOfTabela, assim a tabela guardará todos os elementos
organizados em seus indices dados a partir de seus hash's.
No caso de uma colisão, ou seja, duas entradas resultarem no mesmo hash, a entrada
nova será apenas colocada no "fundo" da lista atravez do método push_back();,
assim garantindo que todos os elementos poderam ser colocados na tabela.
Caso o fator de carga fique maior que um: a tabela deve dobrar de tanho, o fator
de carga é dado pera razão entra o número de elementos e o tamanho da tabela.

#Implementação
O algoritmo de base foi implementado pelo professor Selan da turma de LP1 do 
semestre 2016.1, a lista usada é a lista duplamente encadeada nativa do STL(std::list).

#Até agora
Todos os métodos foram implementados, porém, nem todos foram testados, a função
rehash não foi testada pois o algoritmo ainda não foi preparado para detectar
quando o fator de carga está alto, diversos outros testes precisam ser feitos
para comporvar o funcionamento do algoritmo, essa verificação de carga e os 
demais testes seram feitos e submetidos na próxima versão do programa.

#Como compilar
Um arquivo makefile está disponível então para compilar basta executar o comando make
no terminal, o arquivo binário será salvo na pasta bin/ certifique-se que a pasta
está presente ou a compilação não poderá ser feita.

Opcionalmente você tambem pode compilar usando o Comando abaixo:
g++ -Wall -std=c++11 src/main.cpp -I include -o programa
