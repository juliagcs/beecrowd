#include<bits/stdc++.h>
using namespace std;

/*

Johnattan Silva Ferreira - 0059794
Julia Gabriella Correa Silva - 0048842

Problema 2545 - Manyfile
Resposta - Runtime error

Neste programa e implementado o algoritmo DFS (Busca em Profundidade) para resolver um problema
de ordenacao topologica.

A estrutura Vertex e utilizada para armazenar informacoes sobre cada vertice do grafo, sendo a cor
(0 = branco, 1 = cinza, 2 = preto), o predecessor (inicializa com -1), o tempo de descoberta e o
tempo de finalizacao.

A classe Graph representa um grafo direcionado, contendo informacoes sobre a quantidade de vertices,
lista de ordenacao topologica, lista de adjacencia, a lista de vertices e o tempo de profundidade,
possuindo os seguintes metodos:
    -add_edge verifica se existem ciclos antes de adicionar uma aresta ao grafo;
    -dfs: inicializa as informacoes de todos os vertices do grafo de cor como branco e sem predecessores.
          Em seguida, a funcao percorre todos os vertices do grafo que ainda nao foram visitados e chama a
          funcao dfs_visit para cada. Por fim, retorna a ordem topologica;
    -dfs_visit: funcao auxiliar que marca o vertice atual como cinza e com tempo de descoberta, e entao
                verifica todos os vertices adjacentes a ele. Se um dos vertices adjacentes ainda nao foi
                visitado, a funcao dfs_visit e chamada recursivamente. Quando todos os vertices adjacentes
                foram visitados, o atual e atulizado as informacoes e adicionado a lista de ordenacao topologica.

Na main, a quantidade de vertices e lido pelo usuario e criado uma instancia da classe Graph. Em seguida,
foram lidas e adicionadas as arestas ao grafo, e se houver um ciclo, o programa retorna -1. Caso contrario,
o metodo dfs e chamado e sera retornado o tempo de finalizacao do primeiro vertice da lista topologica
*/

struct Vertex
{
    int c = 0;
    int p = -1;
    int d = 0;
    int f = 0;
};

class Graph
{
    private:
        int V;
        list<Vertex> top_sort;
        list<int> *E;
        vector<Vertex> Vx;
        int time;
    public:
        Graph(int _V){V = _V; E = new list<int>[V]; Vx.resize(V); time = 0;}
        virtual ~Graph() {}
        bool add_edge(int v1, int v2) //adiciona os vertices no grafo
        {
            if(Vx[v1].p != v2)
            {
                E[v2].push_back(v1);
                Vx[v2].p = v1;
                return true;
            }
            return false;
        }
        void dfs_visit(int u) //dfs auxiliar que visita um vertice
        {
            time ++;
            Vx[u].d = time;
            Vx[u].c = 1;
            for(auto v2: E[u])
            {
                if(Vx[v2].c == 0)
                {
                    Vx[v2].p = u;
                    dfs_visit(v2);
                }
            }
            Vx[u].c = 2;
            time ++;
            Vx[u].f = time;
            top_sort.push_back(Vx[u]);
        }
        list<Vertex> dfs() //algoritmo DFS
        {
            for(int i=0; i<V; i++)
            {
                Vx[i].c = 0;
                Vx[i].p = -1;
            }
            for(int i=0; i<V; i++)
            {
                if(Vx[i].c == 0 && Vx[i].p == -1)
                {
                    dfs_visit(i);
                }
            }
            return top_sort;
        }
};

int main()
{
    int N, M, D;
    list<Vertex> _top_sort;
    bool error;
    while(cin >> N)
    {
        _top_sort.clear();
        Vertex vertex;
        Graph g(N);
        error = false;
        for(int i=0; i<N; i++)
        {
            cin >> M;
            for(int j=0; j<M; j++)
            {
                if(M != 0)
                {
                    cin >> D;
                    if(!g.add_edge(i, D-1))
                    {
                        i = N;
                        j = M;
                        error = true;
                    }
                }
            }
        }
        if(!error)
        {
            _top_sort = g.dfs();
            vertex = _top_sort.front();
            cout << vertex.f << endl;
        }
        else
        {
            cout << "-1" << endl;
        }
    }
}
