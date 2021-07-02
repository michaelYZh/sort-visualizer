#ifndef _APVECTOR_H
#define _APVECTOR_H

// *******************************************************************
// Last Revised: 8/14/98, abort changed to exit
//
// January 13,1998, added explicit to int constructor
// APCS vector class template
//
// implements "safe" (range-checked) arrays
// examples are given at the end of this file
// *******************************************************************

// If your compiler supports the keyword explicit, comment out the
// #define explicit line below, leaving the #define means explicit
// is ignored, but doesn't generate an error
//
//   This will disallow a typically erroneous implicit type-conversion:
//   vector<int> v( 10 );
//   v = 0; // Oops!! Allowed because of implicit type-con2lversion.

#define explicit

#include <cstdlib>
#include <cassert>
#include <iostream>

template <class itemType>
class apvector
{
  public:

  // constructors/destructor
    apvector( );                        // default constructor (size==0)
    explicit apvector( int size );      // initial size of vector is size
    apvector( int size, const itemType & fillValue ); // all entries == fillValue
    apvector( const apvector & vec );   // copy constructor
    ~apvector( );                       // destructor

  // assignment
    const apvector & operator = ( const apvector & vec );

  // accessors
    int  length( ) const;                   // capacity of vector

  // indexing
    itemType &       operator [ ] ( int index );       // indexing with range checking
    const itemType & operator [ ] ( int index ) const; // indexing with range checking

  // modifiers
    void resize( int newSize );             // change size dynamically;
                                            // can result in losing values
  private:

    int  mySize;                            // # elements in array
    itemType * myList;                      // array used for storage
};

// *******************************************************************
//  Specifications for vector functions
//
//  The template parameter itemType must satisfy the following two conditions:
//   (1) itemType has a 0-argument constructor
//   (2) operator = is defined for itemType
//  Any violation of these conditions may result in compilation failure.
//
//  Any violation of a function's precondition will result in an error message
//  followed by a call to exit.
//
//  constructors/destructor
//
//   apvector( )
//     postcondition: vector has a capacity of 0 items, and therefore it will
//                    need to be resized
//
//   apvector( int size )
//     precondition: size >= 0
//     postcondition: vector has a capacity of size items
//
//   apvector( int size, const itemType & fillValue )
//     precondition: size >= 0
//     postcondition: vector has a capacity of size items, all of which are set
//                    by assignment to fillValue after default construction
//
//   apvector( const apvector & vec )
//     postcondition: vector is a copy of vec
//
//   ~apvector( )
//     postcondition: vector is destroyed
//
//  assignment
//
//   const apvector & operator = ( const apvector & rhs )
//     postcondition: normal assignment via copying has been performed;
//                    if vector and rhs were different sizes, vector
//                    has been resized to  match the size of rhs
//
//  accessor
//
//   int  length( ) const
//     postcondition: returns vector's size (number of memory cells
//                    allocated for vector)
//
//  indexing
//
//   itemType &       operator [ ] ( int k )       -- index into nonconst vector
//   const itemType & operator [ ] ( int k ) const -- index into const vector
//     description: range-checked indexing, returning kth item
//     precondition: 0 <= k < length()
//     postcondition: returns the kth item
//
//  modifier
//
//   void resize( int newSize )
//     description:  resizes the vector to newSize elements
//     precondition: the current capacity of vector is length; newSize >= 0
//
//     postcondition: the current capacity of vector is newSize; for each k
//                    such that 0 <= k <= min(length, newSize), vector[k]
//                    is a copy of the original; other elements of vector are
//                    initialized using the 0-argument itemType constructor
//                    Note: if newSize < length, elements may be lost
//
//  examples of use
//      apvector<int> v1;         // 0-element vector
//      apvector<int> v2(4);      // 4-element vector
//      apvector<int> v3(4, 22);  // 4-element vector, all elements == 22.


template <class itemType>
apvector<itemType>::apvector()
//postcondition: vector has a capacity of 0 items, and therefore it will
//               need to be resized
    : mySize(0),
      myList(0)
{

}

template <class itemType>
apvector<itemType>::apvector(int size)
// precondition: size >= 0
// postcondition: vector has a capacity of size items
   : mySize(size),
     myList(new itemType[size])
{

}

template <class itemType>
apvector<itemType>::apvector(int size, const itemType & fillValue)
// precondition: size >= 0
// postcondition: vector has a capacity of size items, all of which are set
//                by assignment to fillValue after default construction
    : mySize(size),
      myList(new itemType[size])
{
    int k;
    for(k = 0; k < size; k++)
    {
        myList[k] = fillValue;
    }
}

template <class itemType>
apvector<itemType>::apvector(const apvector<itemType> & vec)
// postcondition: vector is a copy of vec
    : mySize(vec.length()),
      myList(new itemType[mySize])
{
    int k;
        // copy elements
    for(k = 0; k < mySize; k++){
        myList[k] = vec.myList[k];
    }
}

template <class itemType>
apvector<itemType>::~apvector ()
// postcondition: vector is destroyed
{
    delete [] myList;
}

template <class itemType>
const apvector<itemType> &
apvector<itemType>::operator = (const apvector<itemType> & rhs)
// postcondition: normal assignment via copying has been performed;
//                if vector and rhs were different sizes, vector
//                has been resized to  match the size of rhs
{
    if (this != &rhs)                           // don't assign to self!
    {
        delete [] myList;                       // get rid of old storage
        mySize = rhs.length();
        myList = new itemType [mySize];         // allocate new storage

            // copy rhs
        int k;
        for(k=0; k < mySize; k++)
        {
            myList[k] = rhs.myList[k];
        }
    }
    return *this;                               // permit a = b = c = d
}

template <class itemType>
int apvector<itemType>::length() const
// postcondition: returns vector's size (number of memory cells
//                allocated for vector)
{
    return mySize;
}

template <class itemType>
itemType & apvector<itemType>::operator [] (int k)
// description: range-checked indexing, returning kth item
// precondition: 0 <= k < length()
// postcondition: returns the kth item
{

    if (k < 0 || mySize <= k)
    {
        std::cerr << "Illegal vector index: " << k << " max index = ";
        std::cerr << (mySize-1) << std::endl;
        exit(1);
    }
    return myList[k];
}

template <class itemType>
const itemType & apvector<itemType>::operator [] (int k) const
// safe indexing, returning const reference to avoid modification
// precondition: 0 <= index < length
// postcondition: return index-th item
// exception: exits if index is out-of-bounds
{
    if (k < 0 || mySize <= k)
    {
        std::cerr << "Illegal vector index: " << k << " max index = ";
        std::cerr << (mySize-1) << std::endl;
        exit(1);
    }
    return myList[k];
}

template <class itemType>
void apvector<itemType>::resize(int newSize)
// description:  resizes the vector to newSize elements
// precondition: the current capacity of vector is length(); newSize >= 0
// postcondition: the current capacity of vector is newSize; for each k
//                such that 0 <= k <= min(length, newSize), vector[k]
//                is a copy of the original; other elements of vector are
//                initialized using the 0-argument itemType constructor
//                Note: if newSize < length, elements may be lost
{
    int k;
    int numToCopy = newSize < mySize ? newSize : mySize;

         // allocate new storage and copy element into new storage

    itemType * newList = new itemType[newSize];
    for(k=0; k < numToCopy; k++)
    {
        newList[k] = myList[k];
    }
    delete [] myList;                      // de-allocate old storage
    mySize = newSize;                      // assign new storage/size
    myList = newList;
}


//#include "apvector.cpp"
#endif

