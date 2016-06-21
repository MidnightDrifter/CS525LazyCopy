#ifndef ARRAY_H
#define ARRAY_H
#include <fstream> // std::ostream
#include "int.h"
#include <stdio.h>
namespace CS225 {
	class ElementProxy;
    class Array {
        public:
			Array() : size(0), data( new Integer[]), counter(&1) {}
			Array(int s) : size(s), data(new Integer[s]), counter(&1) {}
			Array(Array const& a) : size(a.size), data(a.data), counter((*a.counter)+1) { (*a.counter)+=1}
			~Array();

			
			const ElementProxy operator[](long pos);
			Integer operator[](long pos) const;

			friend std::ostream& operator<<(std::ostream &out, Array const& array);
			void Array Insert(int pos, Integer const& val);
			Array const& DeepCopy(Array const& a);
        private:
            int size;
			Integer[]  data;
			int* counter;
    };





	class ElementProxy {
	private:
		SparseVector &v;
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
		Array& getVector() const;

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

		Array& getVector() const
		{
			return this->v;
		}

		void setPos(long pos)
		{
			this->pos = pos;
		}

		void setVector(SparseVector& v)
		{
			this->v = v;
		}






		// .......

	};

































}
#endif
