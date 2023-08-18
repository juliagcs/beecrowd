#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f

/*
Johnattan Silva Ferreira - 0059794
Julia Gabriella Correa Silva - 0048842

Problema 1977 - I can't be late
Neste programa e implementado o algoritmo de Dijkstra para encontrar o menor caminho entre dois vertices de um grafo.

A classe Graph armazena as informacoes sobre o grafo, possuindo os seguintes metodos:
    -add_edge para adicionar uma nova aresta ao grafo;
    -string2index converte uma string representando um vertice em um indice;
    -dijkstra executa o algoritmo para encontrar o menor caminho entre dois vertices;
    -calctime calcula o tempo de chegada previsto em funcao do tempo de viagem e retorna o tempo total.

Na main, os valores de X, N e V sao lidos do usuario, onde para cada caso e criado uma instancia da classe Graph e
as informacoes de viagem sao lidas, incluindo o ponto de origem, o destino e o tempo da viagem. O algoritmo de Dijkstra
e executado para encontrar o menor caminho entre "varzea" e "alto", e o metodo calctime e chamado para calcular o horario
de chegada previsto, e e retornado a reposta do horario de chegada e se estara atrasado ou nao. O vetor de strings utilizado
para armazenar os nomes dos vertices e limpado para a proxima iteracao do loop. Se as entradas forem X=0, N=0 e V=0,
o programa e encerrado.
*/
class Graph
{
    private:
        int V;
        list< pair<int, int> > *E;
    public:
        Graph(int _V){V = _V; E = new list<pair<int, int>>[V];}
        virtual ~Graph() {delete[] E;}
        void add_edge(int v1, int v2, int w) {E[v1].push_back(make_pair(v2, w));} //adiciona os vertices e o peso no grafo
        int string2index(vector<string> &sv, string v) //retorna o indice da string do vertice
        {
            for(int i=0; i<sv.size(); i++)
            {
                if(sv[i] == v)
                {
                    return i;
                }
            }
            sv.push_back(v);
            return sv.size() - 1;
        }
        int dijkstra(int _v1, int _v2) //algoritmo de dijkstra
        {
            set<pair<int, int>> list_w;
            vector<int> wv(V, INF);
            list_w.insert(make_pair(0, _v1));
            wv[_v1] = 0;

            while (!list_w.empty())
            {
                list<pair<int, int>>::iterator i;
                pair<int, int> _pair;
                int u, v, w;

                _pair = *(list_w.begin());
                list_w.erase(list_w.begin());
                u = _pair.second;

                for (i = E[u].begin(); i != E[u].end(); ++i)
                {
                    v = (*i).first;
                    w = (*i).second;

                    if (wv[v] > wv[u] + w)
                    {
                        if (wv[v] != INF)
                        {
                            list_w.erase(list_w.find(make_pair(wv[v], v)));
                        }
                        wv[v] = wv[u] + w;
                        list_w.insert(make_pair(wv[v], v));
                    }
                }
            }
            return wv[_v2];
        }
        int calctime(int x, int routtime) //calcula o tempo total do caminho do onibus + rota
        {
            int exittime, arrival, hour, minutes;
            if(x <= 30)
            {
                exittime = 1050; //onibus das 17h30
            }
            else
            {
                exittime = 1070; //onibus das 17h50
            }
            return exittime + routtime;
        }
};

int main()
{
    int X, N, V, T, v1, v2, varzea, alto, y, x, arrival, hour, minutes;
    string O, D;
    vector<string> sv;

    while(cin >> X >> N >> V)
    {
        if(X != 0 && N != 0 && V != 0)
        {
            x = X;
            Graph g(V);
            for(int i=0; i<N; i++)
            {
                cin >> O >> D >> T;
                v1 = g.string2index(sv, O);
                v2 = g.string2index(sv, D);

                g.add_edge(v1, v2, T);
            }
            varzea = g.string2index(sv, "varzea");
            alto = g.string2index(sv, "alto");
            y = g.dijkstra(varzea, alto);
            arrival = g.calctime(x, y);
            hour = arrival/60;
            minutes = arrival%60;

            cout<<hour<<":";
            if((minutes) == 0)
            {
                cout<<"00"<<endl;
            }
            else
            {
                if((minutes) < 10)
                {
                    cout<<"0"<<(minutes)<<endl;
                }
                else
                {
                    cout<<(minutes)<<endl;
                }
            }
            if(arrival <= 1080 )
            {
                cout<<"Nao ira se atrasar"<<endl;
            }
            else
            {
                cout<<"Ira se atrasar"<<endl;
            }
            sv.clear();
        }
        else
        {
            return 0;
        }
    }
}
