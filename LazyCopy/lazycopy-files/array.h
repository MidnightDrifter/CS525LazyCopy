#ifndef ARRAY_H
#define ARRAY_H
#include <fstream> // std::ostream
#include "int.h"
namespace CS225 {
	class ElementProxy;

	class Array {
		friend class ElementProxy;
	public:
		Array();
		Array(int s);
		Array(const Array& a);
		~Array();

		const Array& operator=(const Array& a);
		int getSize() const;
		int* getCounter() const;
		int getCounterValue() const;
		Integer* getData() const;

		friend	std::ostream& operator<<(std::ostream& out, Array const& a);

		void Insert(int pos, Integer const& val);

		const ElementProxy operator[](long pos);
		//Integer operator[](long pos) const;
		const Integer& operator[](long pos)const;

	

	private:
		int size;
		Integer* data;
		int* counter;

		Integer* DeepCopy();
		void DeleteData();


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


		//friend ElementProxy operator*(int t, ElementProxy& p);

		operator int() const
		{
			return this->v.data[pos];
		}

		ElementProxy& operator=(int x)
		{
			//this->v.Insert(x, this->getPos());
			this->v.Insert(this->getPos(), (x));
			return *this;
		}

		const ElementProxy& operator=(const int x) const
		{
			//this->v.Insert(x, this->getPos());
			this->v.Insert(this->getPos(), (x));
			return *this;

		}

		const ElementProxy& operator=(Integer& x)
		{
			this->v.Insert(this->getPos(), x);
			return *this;
		}

		const ElementProxy& operator=(const Integer& x) const
		{
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
