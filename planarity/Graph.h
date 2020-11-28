#pragma once
#include "Vertex.h"
#include <vector>
#include <map>
#include <set>

typedef std::pair<size_t, size_t> edge_t;

class Graph{
    public:
        Graph(std::vector< std::vector<size_t> >& matrix);
        Graph(std::vector< edge_t >& list); 
        Graph() = default;
        size_t size() const;
        std::vector < std::vector <size_t> > getMatrix() const;
        std::map <size_t, std::vector<size_t> > getList() const;
        std::vector <edge_t> getEdges() const;
        VertexList getVertexes() const;
        void MakeUndirect();
        std::vector <edge_t> getCycle();
        std::vector <Graph> getCompanents();
        std::vector < std::set<int> > Gamma();
        std::vector <std::set <edge_t> > SegmentsFind_();
        void addEdge(edge_t edge);
        // std::vector <uint64_t> getBiteCodes() const;
        friend std::ostream& operator << (std::ostream &ostr, const Graph &graph);
        friend bool operator== (const Graph &gr1, const Graph &gr2);

    private:
        size_t graph_size_;
        size_t dfs_timer_;
        std::vector < std::vector <size_t> > graph_matrix_;
        std::map <size_t, std::vector<size_t> > graph_list_;
        std::vector <uint64_t> graph_bit_code_;
        VertexList vertexes_;
        std::vector <edge_t> edges_;
        std::vector <edge_t> cycle_;
        std::vector <Graph> segments_;
        std::vector<edge_t> Cycle_visit_(size_t v, std::vector<edge_t> comp);
        std::vector<edge_t> Companents_visit_(size_t v, std::vector<edge_t> comp);
        std::vector<edge_t> Get_Cycle_(std::vector<edge_t> cycle, size_t from, size_t to);
        bool pred(const edge_t &a, edge_t &b);
};

