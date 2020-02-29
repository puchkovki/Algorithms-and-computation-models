#include "Vertex.h"

Vertex::Vertex(const size_t name):
	name_(name),
	pi_(-1),
	time_in_(0),
	time_out_(0),
	color_(WHITE)//,
	// status_(G1)
{}

// void Vertex::changeStatus(int status){
// 	status_ = status;
// }

void Vertex::setName(const int name){
	name_ = name;
}

void Vertex::setPi(int pi){
	pi_ = pi;
}

void Vertex::setTimeIn(const size_t time_in){
	time_in_ = time_in;
}

void Vertex::setTimeOut(const size_t time_out) {
	time_out_ = time_out;
}

void Vertex::setWhite(){
	color_ = WHITE;
}

void Vertex::setGrey(){
	color_ = GRAY;
}

void Vertex::setBlack(){
	color_ = BLACK;
}

int Vertex::getPi() const{
	return pi_;
}

size_t Vertex::getTimeIn() const{
	return time_in_;
}

size_t Vertex::getTimeOut() const{
	return time_out_;
}

int Vertex::getName() const{
	return name_;
}

size_t Vertex::getColor() const{
	return color_;
}

bool operator== (const Vertex &u, const Vertex &v){
    return u.name_ == v.name_;
}
// int Vertex::getStatus() const{
// 	return status_;
// }