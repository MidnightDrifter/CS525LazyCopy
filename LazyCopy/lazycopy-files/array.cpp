#include "array.h"
#include <iostream>
#include <iomanip>


	Integer* Array::DeepCopy()
	{
		Integer* ret = new Integer[this->getSize()];
		for (int i = 0; i < this->getSize(); ++i)
		{
			ret[i] = this->data[i];
		}
		return ret;
	}

	void Array::DeleteData()
	{
		/*for (int i = 0; i < this->getSize(); ++i)
		{
			delete data[i];
		}*/
		delete[] data;
	
	}

	Array::Array() : size(0), data(NULL), counter(new int(1)) { }
	Array::Array(int s) : size(s), data(new Integer[s]), counter(new int(1)) {}
	//Array::Array(const Array& a) : size(a.getSize()), data(new Integer[size]), counter(new int(1)) { for (int i = 0; i < size; i++) { this->data[i] = a.data[i]; } }  //Deep copy
	Array::Array(const Array& a) : size(a.getSize()), data(a.getData()), counter(a.getCounter()) { (*(this->counter)) +=1; }
	Array::~Array() { if (--(*counter) <= 0) { delete counter;    delete[] data; } } //for (int i = 0; i < size; i++) { delete data[i]; }
	
	

	int Array::getSize() const { return size; }
	int* Array::getCounter() const { return counter; }
	int Array::getCounterValue() const { return *counter; }


	const ElementProxy Array::operator[](long pos) { return ElementProxy(*this, pos); }
	Integer Array::operator[](long pos) const { return data[pos]; }
	Integer* Array::getData() const { return data; }

	const Array& Array::operator=(const Array& a)
	{
		if (this != &a)
		{
			this->size = a.getSize();
			*(this->counter) = (a.getCounterValue());
			delete[] data;
			data = new Integer[size];
			for(int i=0; i<size;i++)
			{
				data[i] = a.data[i];
			}

		}
		return *this;
	}


    // Array class implementation
    
    std::ostream& operator<<( std::ostream &out, Array const& array ) {
        for ( int i=0; i<array.size; ++i ) {
            out << array.data[i] << " ";
        }
        return out;
    }

    void Array::Insert( int pos, Integer const& val ) {

		if (*counter == 1)
		{



			if (pos >= size) {
				int old_size = size;
				size = 2 * pos + 1; // +1 is required if the first write is at 0
				//std::cout << "in function " << __FUNCTION__ << ": new size = " << size << std::endl;
				Integer* new_data = new Integer[size];
				//std::cout << "in function " << __FUNCTION__ << ": copy " << old_size << " elements" << std::endl;
				for (int i = 0; i < old_size; ++i) {
					new_data[i] = data[i];
				}

				delete[] data;
				data = new_data;
			}
			 //std::cout << "in function " << __FUNCTION__ << ": insert element at position " << pos << std::endl;
			std::cout << "in function Insert: insert element at position " << pos << std::endl;

			data[pos] = val;
		}

		else
		{

			(*counter)--;
			this->data = this->DeepCopy();
			this->counter = new int(1);
			this->Insert(pos, val);

			

		}
    }


