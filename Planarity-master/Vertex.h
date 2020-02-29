#pragma once
#include <cstddef>
#include <vector>

#define WHITE 0
#define GRAY 1
#define BLACK 2
// #define G1 1
// #define G2 2
class Vertex{
public:
	Vertex() = default;
	Vertex(const size_t name);
	void setPi(int pi);
	void setTimeIn(const size_t time_in);
	void setTimeOut(const size_t time_out);
	void setName(const int name);
	void setWhite();
	void setGrey();
	void setBlack();
	// void changeStatus(int status);

	// int getStatus() const;
	int getName() const;
	int getPi() const;
	size_t getTimeIn() const;
	size_t getTimeOut() const;
	size_t getColor() const;

	bool operator< (const Vertex& other) const{
		return name_ < other.name_;
	}
	friend bool operator== (const Vertex &u, const Vertex &v);

private:
	int name_ = -1;
	size_t time_in_ = 0;
	size_t time_out_ = 0;
	int pi_ = -1;
	size_t color_ = WHITE;
	// size_t status_ = G1;
};

class VertexList{
public:
	VertexList():
	vertexes_(std::vector<Vertex>())
	{}
	Vertex& operator[] (const size_t name){
		for (auto & elem: vertexes_){
			if (elem.getName() == name) 
				return elem;
		}
		exit(0);
	}
	bool check(const int v){
		return std::find(vertexes_.begin(), vertexes_.end(), Vertex(v)) != vertexes_.end();
	}
	void push_back(const Vertex& v){
		vertexes_.push_back(v);
	}
	void push_front(const Vertex& v){
		vertexes_.insert(vertexes_.begin(), v);
	}
	void clear(){
		vertexes_.clear();
	}
	size_t size(){
		return vertexes_.size();
	}
private:
	std::vector<Vertex> vertexes_;
};
