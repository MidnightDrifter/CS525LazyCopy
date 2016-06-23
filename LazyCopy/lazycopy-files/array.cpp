#include "array.h"

namespace CS225 {


	

	Array::Array() : size(0), data(NULL), counter(NULL) { }
	Array::Array(int s) : size(s), data(new Integer[s]), counter(new int(1)) {}
	Array::Array(const Array& a) : size(a.getSize()), data(new Integer[size]), counter(new int(1)) { for (int i = 0; i < size; i++) { this->data[i] = a.data[i]; } }  //Deep copy


	int Array::getSize() const { return size; }
	int* Array::getCounter() { return counter; }
	int Array::getCounterValue() const { return *counter; }

	const ElementProxy& Array::operator[](long pos) { return ElementProxy(*this, pos); }
	Integer Array::operator[](long pos) const { return data[pos]; }


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


        if ( pos >= size ) {
            int old_size = size;
            size = 2*pos +1; // +1 is required if the first write is at 0
            //std::cout << "in function " << __FUNCTION__ << ": new size = " << size << std::endl;
            Integer* new_data = new Integer[ size ];
            //std::cout << "in function " << __FUNCTION__ << ": copy " << old_size << " elements" << std::endl;
            for ( int i=0; i<old_size; ++i ) {
                new_data[i] = data[i];
            }

            delete [] data;
            data = new_data;
        }
        //std::cout << "in function " << __FUNCTION__ << ": insert element at position " << pos << std::endl;
        data[ pos ] = val;
    }

}
