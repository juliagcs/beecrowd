#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
const int ms = 99;

/*
Johnattan Silva Ferreira - 0059794
Julia Gabriella Correa Silva - 0048842

Problema 1427 - The Problem of Scrooge Co.
Neste programa e implementado o algoritmo de Floyd-Warshall para calcular a distancia minima entre todos os pares de localidades
de um grafo.

A classe Graph armazena as informacoes sobre o grafo, possuindo os seguintes metodos:
    -add_edge: funcao que adiciona uma aresta entre os vertices v1 e v2 com peso w;
    -get_w funcao que retorna o peso da aresta entre os vertices v1 e v2;
    -set_w: funcao que modifica o peso da aresta entre os vertices v1 e v2 para o valor w;
    -get_path: funcao que retorna o caminho entre os vertices v1 e v2;
    -set_path: funcao que modifica o caminho entre os vertices v1 e v2 para o valor w;
    -relax: funcao que atualiza o peso e o caminho da aresta entre os vertices i e j baseado no vertice intermediario k;
    -floyd_warshall: funcao que implementa o algoritmo de caminho minimo para encontrar o caminho mais curto entre todos
                    os pares de vertices em um grafo.

Na main, e lido um valor c que representa o numero de casos de teste. E iniciado um loop com c iteracoes, no qual e lido
informacoes sobre a cidade, nome das localidades e as distancias entre elas, o algoritmo de Floyd-Warshall e executado para
determinar as distancias minimas entre todos os pares de localidades na cidade. Por fim, sao lidos o numero de empregados e
suas rotas de viagem desejadas. Para cada empregado, e verificado se existe uma rota de viagem disponivel entre as localidades
de origem e destino. Se houver, e impresso o valor da viagem e o caminho a ser seguido. Caso contrario, e exibida uma
mensagem de erro.
*/

class Graph{
    private:
        int V;
        int E[ms][ms]; //armazena o peso da aresta
        int path[ms][ms]; //armazena o caminho entre dois vertices
    public:
        Graph(int _V){V = _V;}
        virtual ~Graph(){}
        void add_edge(int v1, int v2, int w) //adiciona uma aresta entre dois vertices no grafo
        {
            if(w != -1)
            {
                E[v1][v2] = w; //peso da aresta e definido como o valor de w
                path[v1][v2] = v2; //caminho entre v1 e v2 e definido como v2
            }
            else
            {
                E[v1][v2] = INF; //peso da aresta e definido como infinito
                path[v1][v2] = -1; //caminho sera definido como -1
            }
        }

        //acessores
        int get_w(int v1, int v2){return E[v1][v2];}
        void set_w(int v1, int v2, int w){E[v1][v2] = w;}
        int get_path(int v1, int v2){return  path[v1][v2];}
        void set_path(int v1, int v2, int w){path[v1][v2] = w;}
        void relax(int i, int j, int k) //relaxamento seguindo o pseudocodigo do material disponivel
        {
            if(get_w(i, k)!=INF && get_w(k, j)!=INF)
            {
                if(get_w(i, j)>get_w(i, k)+get_w(k, j))
                {
                    set_w(i, j, get_w(i, k)+get_w(k, j));
                    set_path(i, j, get_path(i, k));
                }
            }
        }
        void floyd_warshall(int v)//algoritmo floyd_warshall
        {
            for(int k=0; k<v; k++)
            {
                for(int i=0; i<v; i++)
                {
                    for(int j=0; j<v; j++)
                    {
                       relax(i, j, k);
                    }
                }
            }
        }
};

int main()
{
    int c, p, w, r, v,  from_index, to_index;
    string loc_name, emplo_name, from, to;
    map<string, int> int_name;
    map<int, string> name_int;
    cin >> c;
    for(int i=0; i < c; i++)
    {
        cin >> p;
        Graph g(p);
        for(int i=0; i<p; i++)
        {
            cin >> loc_name;
            int_name[loc_name] = i;
            name_int[i] = loc_name;
        }
        for(int i=0; i<p; i++)
        {
            for(int j=0; j<p; j++)
            {
                cin >> w;
                g.add_edge(i, j, w);
            }
        }
        g.floyd_warshall(p);
        cin >> r;

        for(int i=0; i<r; i++)
        {
            cin >> emplo_name >> from >> to;

            from_index = int_name[from];
            to_index = int_name[to];

            if(g.get_w(from_index, to_index) == INF)
            {
                cout << "Sorry Mr " << emplo_name << " you can not go from " << from << " to " << to << endl;
            }
            else
            {
                cout << "Mr " << emplo_name << " to go from " << from << " to " << to << ", you will receive " << g.get_w(from_index, to_index) << " euros" << endl;
                cout << "Path:" << from;
                v = from_index;
                while(v != to_index)
                {
                    v = g.get_path(v, to_index);
                    cout << " " << name_int[v];
                }
                if(from == to)
                {
                    cout << " " << to;
                }
                cout << endl;
            }
        }
        int_name.clear();
        name_int.clear();
    }
    return 0;
}
