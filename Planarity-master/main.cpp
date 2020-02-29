#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>

class Graph{
    public:
        //создаем граф    
        Graph(int vertex_capasity):  vertexcapacity(vertex_capasity), matrix(vertex_capasity, std::vector<int>(vertex_capasity, false)),
        visited(vertex_capasity), vertices(vertex_capasity, 0) {}
    
        //добавляем ребра в оба направления (то есть одно неориентированное)
        void AddEdge(int source, int flow) {
            vertices[source] = vertices[flow] = 1;
            matrix[source][flow] = matrix[flow][source] = 1;
    
        }

        //кол-во вершин
        int GetVerticesNum() {
            return vertexcapacity;
        }

        //множество вершин, смежных вершине vertex
        void GetNextVertices(int vertex, std::vector<int> &vertices) const {
            vertices.clear();

            //идем по строке матрицы и добавляем все вершины, смежные нашей
            for(int i = 0; i < vertexcapacity; i++) {
                if (matrix[vertex][i] == 1) {
                    vertices.push_back(i);
                }
            }
        }


        //поиск цикла поиском в глубину
        bool FindCycle(int u, int& cycle_begin, int& cycle_end) {
            //начальная — посещенная вершина (серая)
            visited[u] = 1; 

            std::vector<int> related_vertices;
            GetNextVertices(u, related_vertices);

            for(int v : related_vertices) {
                //если вершина непосещенная (белая), то рекурсивно идем из нее
                if (visited[v] == 0) { 
                    prev[v] = u;
                    if (FindCycle(v, cycle_begin, cycle_end) == true) {
                        return true;
                    }
                }

                //если рассматриваемая вершина уже посещенная и это не родитель (нашли цикл)
                if ((visited[v] == 1) && (v != prev[u])) {
                    //нашли начало цикла
                    cycle_begin = v; 

                    //нашли конец цикла
                    cycle_end = u; 
                    return true;
                }
            }

            //закрываем вершину, как вышли из нее
            visited[u] = 2;//black
            return false;
        }

        //поиск в глубину
        int DFS(std::vector<int> &cycle) {

            //отмечаем, что все массив посещенных пока нулевой (все вершины белые = 0)
            visited.assign(vertexcapacity, 0);

            //значения предков — константа
            prev.assign(vertexcapacity, -1);

            int cycle_begin = -1;
            int cycle_end = 0;

            //ищем цикл
            for (int i = 0; i < vertexcapacity; i++){
                if (visited[i] == 0){
                    if (FindCycle(i, cycle_begin, cycle_end) == true) 
                        break;
                }
            }
            
            if (cycle_begin == -1) { //если цикл существует, то значение будет != -1
                return 0;
            } else {
                //добавили начало цикла
                cycle.push_back(cycle_begin);

                //добавляем весь цикл (от последней идем по предкам)
                for (int v = cycle_end; v != cycle_begin; v = prev[v]) {
                    cycle.push_back (v);
                }

                //запечатали
                cycle.push_back(cycle_begin);
                
                return 1;
            }
        }

        bool FindChain(std::vector<int>& chain, int u, int& chain_end, std::vector<int>& connectVertices) {
            //посещенная вершина
            visited[u] = 1;

            //смежные вершины
            std::vector<int> related_vertices;
            GetNextVertices(u, related_vertices);


            for(int v : related_vertices){
                if (visited[v] == 0){
                    prev[v] = u;
                    if (std::find(connectVertices.begin(), connectVertices.end(), v) != connectVertices.end()){
                        chain_end = v;
                        return true;
                    }
                    else{
                        if (FindChain(chain, v, chain_end, connectVertices))
                            return true;
                    };
                }
            }
            visited[u] = 2;//black
            return false;
        }

        void ChainBFS(std::vector<int>& chain, int chain_begin, std::vector<int>& connectVertices){
            visited.assign(vertexcapacity, 0);//white
            prev.assign(vertexcapacity, -1);
            int chain_end = 0;
            FindChain(chain, chain_begin, chain_end, connectVertices);
            for (int v = chain_end; v!=chain_begin; v = prev[v])
                chain.push_back (v);
            chain.push_back(chain_begin);
        }

        //находим все вершины, лежащие в сегменте
        void FindVerticesInSegment(int u, std::vector<int> &cycle, std::vector<int> &vertices){
            std::vector<int> related_vertices;

            vertices.push_back(u);
            if (cycle[u] == 1){ //если вершина в цикле, то это конец сегмента
                return;
            }

            //она не присутствует в цикле, помечаем, что находится где-то в середине сегмента
            visited[u] = 1;

            //получаем смежные вершины
            GetNextVertices(u, related_vertices);

            for(int v : related_vertices) {
                if (visited[v] == 0) { 
                    FindVerticesInSegment(v, cycle, vertices);
                }
            }
    
        }

        //ищем сегменты
        Graph* FindSegment(int u, std::vector<int>& cycle) {
            std::vector<int> vertices_in_segment;
            FindVerticesInSegment(u, cycle, vertices_in_segment);

            int size = vertices_in_segment.size();
            if (size > 1) {
                Graph* graph = new Graph(this->matrix.size());
                for (int i = 0; i < size; i++) {
                    for (int j = i + 1; j < size; j++) {
                        if (this->matrix[vertices_in_segment[i]][vertices_in_segment[j]] == 1) {
                            graph->AddEdge(vertices_in_segment[i],vertices_in_segment[j]);
                        }
                    }
                }
                return graph;
            }
            return nullptr;
        }

        //добавляем сегменты
        void AddSegments (std::vector<Graph*>& segments, std::vector<int>& cycle) {
            visited.assign(vertexcapacity, false);

            //добавляем сегменты первого типа из ребра, вершины которого лежат в цикле
            int size = matrix.size();
            for (int i = 0; i < size; i++) {
                int column_size = matrix[i].size();
                for (int j = i + 1; j < column_size; j++) {
                    if (cycle[i] && cycle[j] && matrix[i][j]) { //вершины находятся в одном цикле и между ними есть ребро в исходной матрице
                        Graph* graph = new Graph(matrix.size()); //создаем сегмент из одного ребра
                        graph->AddEdge(i,j);
                        segments.push_back(graph); //добавляем в мн-во сегментов
                    }
                }
            }

            for (int i = 0; i < vertexcapacity; i++) {
                if (visited[i] == 0){
                    //находим сегменты не из одного ребра, которые начинаются из вершиныне из цикла
                    Graph* graph = FindSegment(i, cycle);
                    if (graph!= nullptr) {
                        segments.push_back(graph);
                    }
                }
            }
        }

        // вырезаем ребра подграфа graph из исходного графа; если больше не осталось ребер, то граф планарен
        bool Cut_rreviewed_edges (Graph& graph){
            bool b = true;
            int size = graph.matrix.size();
            for (int i = 0; i < size; i++) {
                int column_size = graph.matrix[i].size();
                for (int j= i + 1; j < column_size; j++) {
                    if (graph.matrix[i][j] == 1) { //удаляем совпавшие ребра
                        matrix[i][j] = matrix[j][i] = 0;
                    }
                    if (matrix[i][j] == 1) { //если ребро не было рассмотрено, но граф может быть не планарен
                        b = false;
                    }
                }
            }
            return b;
        }

        int GetVertex(int i) {
            return vertices[i];
        }
    private:
        std::vector<std::vector<int>> matrix;
        std::vector<int> vertices;
        std::vector<int> visited;
        std::vector<int> prev;
        int vertexcapacity;
};

bool Solution(Graph& graph);
 
bool SegmentProcessing(int& min,int n, std::vector<std::vector<int>>& ConnectVertices,
                       std::vector<std::vector<int>>& verges, std::vector<Graph*>& segments, std::vector<int>& vec,
                       std::vector<std::vector<int>>& CyclesofVerges, std::vector<int>& vergeForSegment){
    std::vector<int> chain;
    segments[min]->ChainBFS(chain, ConnectVertices[min][0], ConnectVertices[min]);
    //нашли цепь
    //Обновляем грани грани
    int x = chain[0];
    int y = chain[chain.size()-1];
    int k =vergeForSegment[min];
    std::vector<int> newCycle;
    std::vector<int> newVerge(n,0);
    for (int i=0;i<chain.size();++i){
        verges[k][chain[i]] = 1;
        newVerge[chain[i]] = 1;
        newCycle.push_back(chain[i]);
    }
    bool c=false;
    for (int i=0;i<CyclesofVerges[k].size();++i){
        if (CyclesofVerges[k][i] == y) {
            break;
        }
        if (CyclesofVerges[k][i] == x) {
            c = true;
        }
    }
    if (c){
        std::reverse(CyclesofVerges[k].begin(),CyclesofVerges[k].end());
    }
    c = false;
    int ind=0;
    for (int i=0;i<CyclesofVerges[k].size();++i){
        if (CyclesofVerges[k][i] == y) {
            c = true;
        }
        if (CyclesofVerges[k][i] == x) {
            c = false;
        }
        else if(c){
            newVerge[CyclesofVerges[k][i]] = 1;
            if (CyclesofVerges[k][i] != y) {
                newCycle.push_back(CyclesofVerges[k][i]);
                verges[k][CyclesofVerges[k][i]] = 0;
                CyclesofVerges[k].erase(CyclesofVerges[k].begin() + i);
                i--;
            }
            else{
                ind = i;
            }
        }
    }
 
    for (int t=1;t<chain.size()-1;++t) {
        ind++;
        CyclesofVerges[k].insert(CyclesofVerges[k].begin() + ind, chain[chain.size() - t-1]);
    }
 
    verges.push_back(newVerge);
    CyclesofVerges.push_back(newCycle);
    Graph chainGr(n);
    for (int i=0;i<chain.size()-1;++i){
        chainGr.AddEdge(chain[i],chain[i+1]);
        vec[chain[i]] = 1;
    }
    vec[chain[chain.size()-1]] = 1;
    segments[min]->Cut_rreviewed_edges(chainGr);
    segments[min]->AddSegments(segments, vec);
    segments.erase(segments.begin()+min);
    ConnectVertices = std::vector<std::vector<int>>(segments.size());
    for (int i=0;i<n;++i){
        for (int k=0;k<verges.size();++k){
            if (verges[k][i] == 1)
                for (int j=0;j<segments.size();++j){
                    if (segments[j]->GetVertex(i)){
                        if (std::find(ConnectVertices[j].begin(),ConnectVertices[j].end(), i) == ConnectVertices[j].end())
                            ConnectVertices[j].push_back(i);
                    }
                }
        }
    }
    for (int i=0;i<segments.size();++i){
        if (ConnectVertices[i].size() <= 1){
            if (!Solution(*(segments[i])))
                return false;
            else {
                segments.erase(segments.begin()+i);
                ConnectVertices.erase(ConnectVertices.begin()+i);
                i--;
            }
        }
    }
    int mincnt = 3000;//по условию больше не м б
    //для каждого сегмента вычисляем допустимые грани, вычисляем min
    for (int i =0;i<segments.size();++i){
        int cnt=0;
        for (int k=0;k<verges.size();++k){
 
            bool flag = true;
            for (int j=0;j<ConnectVertices[i].size();++j){
                if(!verges[k][ConnectVertices[i][j]]){
                    flag = false;
                }
            }
            if (flag){
                vergeForSegment[i] = k;
                ++cnt;
            }
        }
        if (cnt == 0){
            return false;
        }
        if (cnt<mincnt){
            mincnt = cnt;
            min = i;
        }
    }
}

//искомое рещение
bool Solution(Graph& graph) {
    std::vector<int> cycle;


    if (graph.DFS(cycle) == 0) //цикл отсутствует
        //если нарушено это свойство, то граф — дерево и нарисовать его плоскую укладку тривиально.
        return true;
    else { //присутствует цикл в графе
        //кол-во вершин в графе
        int vertexcapacity = graph.GetVerticesNum();

        //мн-во граней (см. Гамма-алгоритм)
        std::vector<std::vector<int>> verges;

        //нашли первый цикл
        std::vector<int> vector(vertexcapacity, false);
        for (int i = 0; i < cycle.size() - 1; i++) {
            vector[cycle[i]] = true;
        }

        verges.push_back(vector);
        verges.push_back(vector); //надо бы еще подумать

        //мн-во сегментов
        std::vector<Graph*> segments;

        //создаем граф из начального цикл — он точно планарен
        Graph planar(vertexcapacity);
        int size = cycle.size() - 1;
        for (int i = 0; i < size; i++) {
            planar.AddEdge(cycle[i], cycle[i + 1]);
        }

        //вырезаем ребра первого цикла из исходного графа; если больше не осталось ребер, то граф планарен
        if (graph.Cut_rreviewed_edges(planar) == true){
            return true;
        }

        //добавляем множество сегментов
        graph.AddSegments(segments, vector);

        std::vector<std::vector<int>> ConnectVertices(segments.size());
        for (int i=0;i<vertexcapacity;++i){
            for (int k=0;k<verges.size();++k){
                if (verges[k][i] == 1)
 
                    for (int j=0;j<segments.size();++j){
                        if (segments[j]->GetVertex(i)){
                            if (std::find(ConnectVertices[j].begin(),ConnectVertices[j].end(), i) == ConnectVertices[j].end())
                                ConnectVertices[j].push_back(i);
                        }
                    }
            }
        }
        for (int i=0;i<segments.size();++i){
            if (ConnectVertices[i].size() <= 1){
                if (!Solution(*(segments[i])))
                    return false;
                else {
                    segments.erase(segments.begin()+i);
                    ConnectVertices.erase(ConnectVertices.begin()+i);
                    i--;
                }
            }
        }
        std::vector<std::vector<int>> CyclesofVerges;
        cycle.erase(cycle.end()-1);
        CyclesofVerges.push_back(cycle);
        CyclesofVerges.push_back(cycle);
        int mincnt = 3000;
        int min =0;
        std::vector<int> vergeForSegment(vertexcapacity,0);
        //для каждого сегмента вычисляем допустимые грани, вычисляем min
        for (int i =0;i<segments.size();++i){
            int cnt=0;
            for (int k=0;k<verges.size();++k){
 
                bool flag = true;
                for (int j=0;j<ConnectVertices[i].size();++j){
                    if(!verges[k][ConnectVertices[i][j]]){
                        flag = false;
                    }
                }
                if (flag){
                    vergeForSegment[i] = k;
                    ++cnt;
                }
            }
            if (cnt == 0){
                return false;
            }
            if (cnt<mincnt){
                mincnt = cnt;
                min = i;
            }
        }
        while (segments.size()!=0){
            if(!SegmentProcessing(min, vertexcapacity, ConnectVertices, verges,segments, vector, CyclesofVerges, vergeForSegment))
                return false;
        }
        return true;
    }
}

int main() {
    //Считываем кол-во вершин и ребер соответственно
    int vertex_capacity, edges_capacity = 0;
    std::cin >> vertex_capacity >> edges_capacity;

    //создаем граф
    Graph graph(vertex_capacity);

    //заполнили матрицу
    int source, flow = 0;
    for (int i = 0; i < edges_capacity; i++){
        std::cin >> source >> flow;
        graph.AddEdge(source, flow);
    }
    
    if (Solution(graph) == true)
        std::cout << "YES" << std::endl;
    else {
        std::cout << "NO" << std::endl;
    }
    return 0;
}