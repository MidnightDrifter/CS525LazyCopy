#include "vector.h"
#include <stdio.h>
#include <stdlib.h>



namespace CS225
{

   SparseVector operator*(int t, SparseVector& v)
    {
        return v*t;
    }


   SparseVector operator*(int t, const SparseVector& v)
   {
	   return v*t;
   }











   ElementProxy operator*(int t,  ElementProxy& p)
   {
	   return p*t;
   }

SparseVector::~SparseVector()
{
//printf("Calling destructor\n");
    if(pHead != NULL)
  {

    ElementNode * current = pHead;
    ElementNode * next = (*pHead).next;

    while(current != NULL)
    {
        delete(current);
        current = next;
        if(next != NULL)
        {next = next->next;}
    }
}

}




    /* this is the only place where dimension is used */
std::ostream& operator<<(std::ostream &out, const SparseVector &v) {
	int i,last_pos=-1;
	ElementNode* p_e=v.getHead();
	while (p_e) {
		for (i=last_pos+1;i<p_e->pos;++i) out << " " << "0";
		out << " " << p_e->data;
		last_pos=p_e->pos;
		p_e = p_e->next;
	}
	for (i=last_pos+1;i<v.getDimension();++i) out << " " << "0";

	return out;
}






void SparseVector::Insert(int val, long pos)
{


if (pos>=this->getDimension())
{this->setDimension(pos+1); }// automatically set dimension (it effects operator<< only)



    ElementNode * nodeToInsert = new ElementNode();


        if(nodeToInsert == NULL)
    {
       
        delete(nodeToInsert);
        return;
    }



    nodeToInsert->data = val;
    nodeToInsert->pos = pos;
    nodeToInsert->next = NULL;



    ElementNode * current = this->getHead();




 
if(current == NULL)
{
  
    if(val!=0)
   {
     
       this->setHead(nodeToInsert);
       return;
   }

    else
{
 
 delete(nodeToInsert);
 return;

}

}

ElementNode * next = getHead()->next;

if(next == NULL)
{
    /* If input pos < head pos, this node becomes the new head   DOUBLE CHECK DIS  */
	
		if(pos < (this->getHead())->pos)
    {
		if (val != 0)
		{
			nodeToInsert->next = (this->getHead());
			this->getHead()->next = NULL;
			this->setHead(nodeToInsert);
		}
        return;
    }
    /*  If input pos > head pos, this node comes AFTER the head node, and the head stays the same  */
    else if(pos > this->getHead()->pos)
    {

		if (val != 0)
		{
			this->getHead()->next = nodeToInsert;
		}



        return;
    }

    else if(val==0)
    {delete(this->getHead());

            delete(nodeToInsert);
        return;
    }

    else
    {
      
      
        (this->getHead())->data = val;

        delete(nodeToInsert);
        return;
    }
}



do
{

    /* Input pos < starting node pos, make nodeToInsert the new head and point it to the old one  */
    if(pos < (this->getHead())->pos)
    {
		if (val != 0)
		{
			nodeToInsert->next = (this->getHead());
			this->setHead(nodeToInsert);
		}


        return;

    }
    /* Input pos == starting node pos, delete & update head if val = 0, update data otherwise */
    else if(pos == (this->getHead())->pos)
    {
        if(val==0)
        {
          
            nodeToInsert = (this->getHead())->next;
            delete(this->getHead());
            this->setHead(nodeToInsert);


            return;
        }
        else
        { 
            (this->getHead())->data = val;
            delete(nodeToInsert);
            return;
        }
    }

    /* Input pos fits between some two nodes, put it in between those two nodes  */
	else if (next != NULL && current->pos < pos && next->pos > pos)
	{
		if (val != 0)
		{	current->next = nodeToInsert;
		nodeToInsert->next = next;
		}

        return;
    }

    else if(next!= NULL && next->pos == pos)
    {

        if(val==0)
        {
           
         current->next = next->next;
         delete(next);

            delete(nodeToInsert);
         return;
        }

        else
        {  
            next->data = val;

            delete(nodeToInsert);
            return;
        }
    }

/* Reached the end of the list and input position STILL greater than last node's position, just append nodeToInsert to the end of the list */
    else if(current->pos < pos && next == NULL)
    {
		if (val != 0)
		{
			current->next = nodeToInsert;
		}

        return;
    }


    else
    {

    
        current = next;
        next = next->next;
    }
}while(current != NULL);

}



int SparseVector::Get(long pos) const
{
 const ElementNode * n = this->getHead();
 if (n == NULL)
 {
	 return 0;
 }

    do{
    if(n->pos == pos)
    {
        return n->data;
    }

    else
    {

        if(n->pos > pos)
        {
            n=NULL;
        }
        else
      {
          n=n->next;
      }
}
    }while(n!=NULL);
	n = NULL;
	return 0;
}

int SparseVector::operator[](long pos) const
{
    return this->Get(pos);
}



void SparseVector::Delete(long pos)
{



    ElementNode * prev = this->getHead();
	if(prev == NULL)
	{
		return;
	}
    ElementNode * current = (prev)->next;

	

    if(prev->pos == pos)
    {
        delete(prev);
		if (current != NULL)
		{
			this->setHead(current);
		}

		else
		{
			this->setHead(NULL);
		}
		return;
    }


    do
    {
		if(current == NULL)
		{
			return;
		}
        if(current->pos == pos)
        {
            /* If we're deleting the head node, delete *p_e and point the head to the next node */

            prev->next = current->next;
            delete(current);

        }

        else if(current->pos > pos)
        {
            current = NULL;
            /* No position corresponding to input, nothing to delete. */
        }

        else
        {

            prev = current;
            if(current != NULL)
            {current=current->next;}
        }

    }
    while(current!=NULL);

	current = NULL;
	prev = NULL;


}

ElementNode* SparseVector::getHead() const
{
    return pHead;
}



long SparseVector::getDimension() const
{

return dimension;


}

void SparseVector::setHead(ElementNode* p)
{
    pHead = p;
}

void SparseVector::setDimension(long x)
{
    dimension=x;
}

long ElementProxy::getPos() const
{
    return this->pos;
}

SparseVector& ElementProxy::getVector() const
{
    return this->v;
}

void ElementProxy::setPos(long pos)
{
    this->pos = pos;
}

void ElementProxy::setVector(SparseVector& v)
{
    this->v = v;
}




const ElementProxy SparseVector::operator[](long pos)
{
ElementProxy t = ElementProxy(*this, pos);

return t;

}


 SparseVector SparseVector::operator+(const SparseVector& v)
{
	SparseVector temp;

	const ElementNode * current1 = this->getHead();
	const ElementNode * current2 = v.getHead();

	int holder = 0;
	int i = 0;




	while (current1 != NULL || current2 != NULL)
	{
		

		    holder = this->Get(i) + v.Get(i);

	

	if (holder != 0)
	{

		temp.Insert(holder, i);
	}



	if (current1 != NULL  &&  i == current1->pos)
	{

		current1 = current1->next;


	}

	if (current2 != NULL && i == current2->pos)
	{

		current2 = current2->next;

	}


	i++;


	}
	current1 = NULL;
	current2 = NULL;

		return temp;


}


 SparseVector SparseVector::operator*(const int t)
 {
	 if (t != 0)
	 {
		 SparseVector v(*this);

		 ElementNode * x = v.getHead();

		 while (x)
		 {
			 //v.Insert(x->data * t, x->pos);
			 x->data = x->data*t;
			 x = x->next;
		 }
		 x = NULL;

		 return v;
	 }
	 else
	 {
		 SparseVector v;
		 return v;
	 }
 }

SparseVector SparseVector::operator*(const int t) const
{
	if (t != 0)
	{
		SparseVector v(*this);

		ElementNode * x = v.getHead();

		while (x)
		{
			//v.Insert(x->data * t, x->pos);
			x->data = x->data*t;
			x = x->next;
		}
		x = NULL;

		return v;
	}

	else
	{
		SparseVector v;
		return v;
	}

}



const SparseVector& SparseVector::operator=( const SparseVector& v1)
{
	//printf("Calling assignment operator\n");
	if (this->getHead() == NULL)
	{
		SparseVector v = SparseVector();
		*this = v;
	}
	ElementNode * inputStart = v1.getHead();

	/*while (this->getHead())
	{
		Delete(this->getHead()->pos);
	}
	*/


	while (inputStart)
	{
		this->Insert(inputStart->data, inputStart->pos);
		inputStart = inputStart->next;
	}
	


	/*

	while (thisStart || inputStart)
	{
		if()

		if(inputStart->pos > thisStart->pos)
		{
			this->Delete( thisStart->pos);
			thisStart = thisStart->next;
		}

		else
		{
			if (inputStart->data != 0)
			{
				this->Insert(inputStart->data, inputStart->pos);
			}
			inputStart = inputStart->next;
		}

	}
*/
	//if it broke because thisStart == NULL, continue inserting until inputStart == NULL
	//if it broke because inputStart==NULL, zero out everything else in this
	inputStart = NULL;



	return *this;

}





int SparseVector::operator*(const SparseVector& v1) const
{
	int temp = 0;

	const ElementNode * current1 =this->getHead();
	const ElementNode * current2 = v1.getHead();


	while (current1 != NULL && current2 != NULL)
	{
		if (current1->pos > current2->pos)
		{
			current2 = current2->next;
		}

		else if (current1->pos < current2->pos)
		{
			current1 = current1->next;
		}

		else
		{
			temp = temp + (current1->data * current2->data);
			current1 = current1->next;

		}
	}

	current1 = NULL;
		current2 = NULL;
		delete(current1);
		delete(current2);
	return temp;



}



SparseVector SparseVector::operator+=(const SparseVector& v)
{

	//SparseVector temp;

	const ElementNode * current1 = this->getHead();
	const ElementNode * current2 = v.getHead();

	int holder = 0;
	int i = 0;


	/*
	while(current1 !=NULL && current2!=NULL)
	{

	if(current1->pos > current2->pos)
	{

	current2=current2->next;
	}

	else if(current1->pos < current2->pos)
	{
	current1=current1->next;
	}

	else
	{
	insert_element(&temp, current1->pos, (current1->data + current2->data));
	current1=current1->next;

	}
	}*/

	while (current1 != NULL || current2 != NULL)
	{
		/* printf("Inserting element %i into new vector.\n", i);*/
		/*
		printf("Current loop:  %i\n", i);
		printf("Current positions in curr1, cur2:  (%i, %i)\n", current1->pos, current2->pos);

		*/     holder = this->Get(i) + v.Get(i);

		/*  printf("a+b = holder:  %i + %i = %i", a, b, holder);
		printf("Holder value assigned:  %i\n", holder);*/

	if (holder != 0)
	{

		this->Insert(holder, i);
	}



	if (current1 != NULL  &&  i == current1->pos)
	{

		current1 = current1->next;


	}

	if (current2 != NULL && i == current2->pos)
	{

		current2 = current2->next;

	}


	i++;


	}
	current1 = NULL;
	current2 = NULL;

	return *this;

}


SparseVector SparseVector::operator-=(const SparseVector& v)
{
	//SparseVector temp;

	const ElementNode * current1 = this->getHead();
	const ElementNode * current2 = v.getHead();

	int holder = 0;
	int i = 0;


	/*
	while(current1 !=NULL && current2!=NULL)
	{

	if(current1->pos > current2->pos)
	{

	current2=current2->next;
	}

	else if(current1->pos < current2->pos)
	{
	current1=current1->next;
	}

	else
	{
	insert_element(&temp, current1->pos, (current1->data + current2->data));
	current1=current1->next;

	}
	}*/

	while (current1 != NULL || current2 != NULL)
	{
		/* printf("Inserting element %i into new vector.\n", i);*/
		/*
		printf("Current loop:  %i\n", i);
		printf("Current positions in curr1, cur2:  (%i, %i)\n", current1->pos, current2->pos);

		*/     holder = this->Get(i) - v.Get(i);

		/*  printf("a+b = holder:  %i + %i = %i", a, b, holder);
		printf("Holder value assigned:  %i\n", holder);*/

	if (holder != 0)
	{

		this->Insert(holder, i);
	}



	if (current1 != NULL  &&  i == current1->pos)
	{

		current1 = current1->next;


	}

	if (current2 != NULL && i == current2->pos)
	{

		current2 = current2->next;

	}


	i++;


	}
	current1 = NULL;
	current2 = NULL;

	return *this;
}


SparseVector SparseVector::operator-(const SparseVector& v)
{
	SparseVector temp;

	const ElementNode * current1 = this->getHead();
	const ElementNode * current2 = v.getHead();

	int holder = 0;
	int i = 0;


	/*
	while(current1 !=NULL && current2!=NULL)
	{

	if(current1->pos > current2->pos)
	{

	current2=current2->next;
	}

	else if(current1->pos < current2->pos)
	{
	current1=current1->next;
	}

	else
	{
	insert_element(&temp, current1->pos, (current1->data + current2->data));
	current1=current1->next;

	}
	}*/

	while (current1 != NULL || current2 != NULL)
	{
		/* printf("Inserting element %i into new vector.\n", i);*/
		/*
		printf("Current loop:  %i\n", i);
		printf("Current positions in curr1, cur2:  (%i, %i)\n", current1->pos, current2->pos);

		*/     holder = this->Get(i) + v.Get(i);

		/*  printf("a+b = holder:  %i + %i = %i", a, b, holder);
		printf("Holder value assigned:  %i\n", holder);*/

	if (holder != 0)
	{

		temp.Insert(holder, i);
	}



	if (current1 != NULL  &&  i == current1->pos)
	{

		current1 = current1->next;


	}

	if (current2 != NULL && i == current2->pos)
	{

		current2 = current2->next;

	}


	i++;


	}
	current1 = NULL;
	current2 = NULL;

	return temp;
}


}

