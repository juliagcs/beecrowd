#include<bits/stdc++.h>
using namespace std;

/*
Johnattan Silva Ferreira - 0059794
Julia Gabriella Correa Silva - 0048842

Problema 1152 - Dark Roads
Neste codigo e implementado o algoritmo de Kruskal para encontrar a Arvore Geradora Minima (MST, Minimum Spanning Tree)
de um grafo.

A classe DSU e uma implementacao de estrutura de dados dos conjuntos disjuntos, possuindo metodos para criar conjuntos,
unir conjuntos, encontrar o conjunto de um vertice e fazer o link entre dois conjuntos.

A classe Graph representa um grafo ponderado, possuindo metodos para adicionar arestas ao grafo, ordenar as arestas de
acordo com os pesos e o algoritmo de Kruskal.

Na main e lido varios casos de teste do usuario, onde para cada caso e criado uma instancia da classe Graph, adiciona as
arestas e calcula a MST usando o algoritmo de Kruskal. Em seguida, e calculado a diferenca entre a soma total dos pesos
das arestas do grafo e a soma total dos pesos das arestas da MST e retorna o resultado. Se as entradas forem v=0 e e=0,
o programa e encerrado.
*/

class DSU
{
    private:
        pair<int, int> *tree;
    public:
        DSU() {}
        DSU(int V) {tree = new pair<int, int>[V];}
        virtual ~DSU() {delete[] tree;}
        void make_set(int x) {tree[x].first = x; tree[x].second = 0;} // cria um novo conjunto disjunto
        void link(int x, int y) //faz a uniao dos conjuntos x e y por ordem
        {
            if(tree[x].second > tree[y].second)
            {
                tree[y].first = x;
            }
            else
            {
                tree[x].first = y;
                if(tree[x].second == tree[y].second)
                {
                    tree[y].second += 1;
                }
            }
        }
        int find_set(int x) //retorna um conjunto ao qual o x pertence.
        {
            if(x != tree[x].first)
            {
                tree[x].first = find_set(tree[x].first);
            }
            return tree[x].first;
        }
        void unite(int x, int y) {link(find_set(x), find_set(y));} //une os conjuntos dinâmicos que contem em x e y
};

class Graph
{
    private:
        int V;
        vector<pair<int, pair<int, int>>> E;
    public:
        Graph(int _V){V = _V;}
        virtual ~Graph() {}
        void add_edge(int v1, int v2, int w) {E.push_back(make_pair(w,make_pair(v1, v2)));} //adiciona os vertices e o peso no grafo
        int kruskal() //encontra a MST do grafo
        {
            int length = 0;
            DSU MST(V);
            vector<pair<int, pair<int, int>>> tree;
            for(int i=0; i<V; i++)
            {
                MST.make_set(i);
            }
            sort(E.begin(), E.end());
            for(int i=0; i<E.size(); i++)
            {
                if(MST.find_set(E[i].second.first) != MST.find_set(E[i].second.second))
                {
                       length += E[i].first;
                       MST.unite(E[i].second.first, E[i].second.second);
                }
            }
            return length;
        }
};

int main()
{
    int v, e, v1, v2, w, tree_w, graph_w, resp;
    while(cin >> v >> e)
    {
        tree_w = 0, graph_w= 0, resp = 0;
        Graph g(v);
        if(v != 0 && e != 0)
        {
            for(int i=0; i<e; i++)
            {
                cin >> v1 >> v2 >> w;
                graph_w += w;
                g.add_edge(v1, v2, w);
            }
            tree_w = g.kruskal();
            resp = graph_w - tree_w;
            cout << resp << endl;
        }
        else
        {
           return 0;
        }
    }
}
