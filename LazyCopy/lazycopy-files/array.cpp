#include "array.h"
#include <fstream>
#include <stdio.h>
namespace CS225 {






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

	Array const& DeepCopy(Array const& a)
	{
		for (int i = 0; i < a.size; ++i)
		{
			Insert(i, a[i]);
		}

	}
	Array::~Array()
	{
		--(*counter);
		if ((*counter)== 0)
		{
			for (int i = 0; i < size; ++i)
			{
				delete data[i];
			}
			delete data;
			delete counter;
		}
		delete this;
	}

}
