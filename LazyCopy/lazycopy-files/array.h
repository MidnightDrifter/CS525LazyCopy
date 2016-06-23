#ifndef ARRAY_H
#define ARRAY_H
#include <fstream> // std::ostream
#include "int.h"
#include <stdio.h>
namespace CS225 {
	class ElementProxy;

	class Array {
		friend class ElementProxy;
	public:
		Array() : size(NULL), data(NULL), counter(NULL) { *counter = 1;  *size = 0; }
		Array(int s) : size(NULL), data(new Integer[s]), counter(NULL) { *counter = 1;   *size = s; }
		Array(Array const& a) : size(a.size), data(a.data), counter(NULL) { (*a.counter) += 1;  (this->counter) = a.counter; }
		~Array();


		const ElementProxy operator[](long pos) { return ElementProxy(*this, pos); }
		Integer operator[](long pos) const { return data[pos]; }

		friend std::ostream& operator<<(std::ostream &out, Array const& array);
		void Insert(int pos, Integer const& val);
		Array const& DeepCopy(Array const& a);
	private:
		int* size;
		Integer* data;
		int* counter;
	};





	class ElementProxy {
		//friend class Array;
	private:
		Array &v;
		long pos;



	public:
		ElementProxy() : v(v), pos(-1) {}
		ElementProxy(Array& v, long pos) : v(v), pos(pos) {}
		~ElementProxy()
		{

		}
		void setPos(long pos);
		void setArray(Array& v);
		long getPos() const;
		Array& getArray() const;

		//friend ElementProxy operator*(int t, ElementProxy& p);

		operator int() const
		{
			return this->v.data[pos];
		}

		ElementProxy& operator=(int x)
		{
			//this->v.Insert(x, this->getPos());
			this->v.Insert(this->getPos(), x);
			return *this;
		}

		const ElementProxy& operator=(const int x) const
		{
			//this->v.Insert(x, this->getPos());
			this->v.Insert(this->getPos(), x);
			return *this;

		}


		long getPos() const
		{
			return this->pos;
		}

		Array& getArray() const
		{
			return this->v;
		}

		void setPos(long pos)
		{
			this->pos = pos;
		}

		void setArray(Array& v)
		{
			this->v = v;
		}






		// .......

	};





























}
#endif
