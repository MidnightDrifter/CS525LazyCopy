#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <stdio.h>

namespace CS225
{
struct ElementNode {
int data;
int pos;
struct ElementNode *next;
};
//forward declaration
class ElementProxy;
class SparseVector {

private:
ElementNode* pHead;
long dimension;


public:

 SparseVector() : pHead(NULL), dimension(0) {}
 ~SparseVector();
 SparseVector(const SparseVector& v) : pHead(NULL), dimension(v.getDimension())
 {
	 //printf("Calling copy ctor\n");

	 ElementNode * start =v.getHead();


			 while (start)
			 {

					 Insert(start->data, start->pos);


				 start = start->next;

			 }


	 }



const ElementProxy operator[](long pos);
int operator[](long pos) const;
const SparseVector& operator=(const SparseVector& v1);
ElementNode* getHead(void) const;
long getDimension() const;
void setHead(ElementNode* p);
void setDimension(long x);
int Get(long pos) const;
void Insert(int val, long pos);
void Delete(long pos);
SparseVector operator+(const SparseVector&  v1);
SparseVector operator*(const int s);
SparseVector operator*(const int s) const;

int operator*(const SparseVector& v1) const;



SparseVector operator+=(const SparseVector& v);
SparseVector operator-=(const SparseVector& v);
SparseVector operator-(const SparseVector &v);


friend SparseVector operator*(int t, SparseVector& v);
friend SparseVector operator*(int t, const SparseVector& v);




void PrintRaw ()const{ //used for grading
ElementNode* curr=pHead;
std::cout << "Raw vector: ";
while (curr) {
std::cout << "(" << curr->data << ", " << curr->pos << ")";
curr=curr->next;
}
std::cout << std::endl;
}
friend std::ostream& operator<<(std::ostream &out, const SparseVector &v);//implemented
//......

};










// uncomment when done with basic class functionality and ready to implement Proxy
class ElementProxy {
    private:
SparseVector &v;
long pos;



public:
	ElementProxy() : v(v), pos(-1) {}
ElementProxy(SparseVector& v, long pos): v(v), pos(pos){}
~ElementProxy()
{

}
long getPos() const;
SparseVector& getVector() const;
void setPos(long pos);
void setVector(SparseVector& v);
friend ElementProxy operator*(int t, ElementProxy& p);

operator int() const
{
    return this->v.Get(pos);
}

ElementProxy& operator=(int x)
{
    this->v.Insert(x, this->getPos());

    return *this;
}

const ElementProxy& operator=(const int x) const
{
	this->v.Insert(x, this->getPos());
	return *this;

}
 ElementProxy operator*(int t)
 {
	 this->getVector().Insert(this->getVector().Get(this->getPos())*t, this->getPos());
	 return *this;
 }


 ElementProxy operator*(const ElementProxy& p)
 {


	 return (ElementProxy(this->getVector(), (this->getVector().Get(this->getPos()))*(p.getVector().Get(p.getPos()))));
 }

 ElementProxy operator+=(const ElementProxy& p) const
 {

	 this->getVector().Insert(this->getVector().Get(this->getPos()) + p.getVector().Get(p.getPos()), (this->getPos()));
	 return *this;
 }

 ElementProxy operator-=(const ElementProxy& p) const
 {
	 this->getVector().Insert(this->getVector().Get(this->getPos()) - p.getVector().Get(p.getPos()), (this->getPos()));
	 return *this;
 }


 ElementProxy operator+=(const int x) const
 {
	 this->v.Insert(this->getVector().Get(this->getPos())+x, this->getPos());
	 return *this;
 }



 ElementProxy operator-=(const int x) const
 {
	 this->v.Insert(this->getVector().Get(this->getPos())-x , this->getPos());
	 return *this;
 }





// .......

};


}
#endif // VECTOR_H
