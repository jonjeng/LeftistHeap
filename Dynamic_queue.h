/*****************************************
 Project 3 - CIS 22C
 
 * Contributors:
 * Evan Finnigan
 * Forest Finnigan
 * Jonathan Jeng
 * Abhishek Rajbahndri
 *****************************************/

#ifndef DYNAMIC_QUEUE_H
#define DYNAMIC_QUEUE_H

#ifndef nullptr
#define nullptr 0
#endif

#include <algorithm>
#include "ece250.h"
#include "Exception.h"

template <typename Type>
class Dynamic_queue {
private:
    int initial_capacity;
    int array_capacity;
    Type *array;
    int ihead;
    int itail;
    int entry_count;
    // other integer member variables, as necessary
    
public:
    Dynamic_queue( int = 10 );
    Dynamic_queue( Dynamic_queue const & );
    ~Dynamic_queue();
    
    Type head() const;
    Type tail() const;
    int size() const;
    bool empty() const;
    int capacity() const;
    
    void swap( Dynamic_queue & );
    Dynamic_queue &operator=( Dynamic_queue );
    void enqueue( Type const & );
    Type dequeue();
    void clear();
    
    // Friends
    
    template <typename T>
    friend std::ostream &operator<<( std::ostream &, Dynamic_queue<T> const & );
};

template <typename Type>
Dynamic_queue<Type>::Dynamic_queue( int n ):
initial_capacity( std::max( n, 1 ) ),
array_capacity( initial_capacity ),
array( new Type[initial_capacity] ),
ihead( 0 ),
itail( 0 ),
entry_count( 0 ) {
    // Enter your implementation here.
    // Instructions: If the argument is either 0 or a negative integer, set the initial capacity of the array to 1. The default initial capacity of the array is 10. Other member variables are assigned as appropriate.
    // Jon: Do we need to add anything here?
}

template <typename Type>
Dynamic_queue<Type>::Dynamic_queue( Dynamic_queue const &queue ):
initial_capacity( queue.initial_capacity ),
array_capacity( queue.array_capacity ),
array( new Type[array_capacity] ),
ihead( queue.ihead ),
itail( queue.itail ),
entry_count( queue.entry_count ) {
    // The above initializations copy the values of the appropriate
    // member variables and allocate memory for the data structure;
    // however, you must still copy the stored objects.
    
    // The copy constructor creates a new instance of the queue. (O(n))
    
    // Enter your implementation here.
    
    // If the array is empty, there is nothing to copy
    if (empty()) return;
    
    // Otherwise, iterate through the elements of queue and copy them to this
    for (int i = 0; i < array_capacity; i++)
        array[i] = queue.array[i];
}

template <typename Type>
Dynamic_queue<Type>::~Dynamic_queue() {
    // Enter your implementation here.
    // The destructor deletes the dynamically allocated memory (for the array)
    delete [] array;
}

template <typename Type>
int Dynamic_queue<Type>::size() const {
    // Enter your implementation here.
    return (itail - ihead);
}

template <typename Type>
int Dynamic_queue<Type>::capacity() const {
    // Enter your implementation here.
    return array_capacity;
}

template <typename Type>
bool Dynamic_queue<Type>::empty() const {
    // Enter your implementation here.
    return !(itail - ihead);
}

template <typename Type>
Type Dynamic_queue<Type>::head() const {
    // Enter your implementation here.
    // Return the object at the head of the queue (the object that would be removed by Type dequeue()). It may throw a underflow exception).
    if (empty()) throw underflow();
    return array[ihead];
}

template <typename Type>
Type Dynamic_queue<Type>::tail() const {
    // Enter your implementation here.
    // Return the object at the head of the queue (the object that would be removed by Type dequeue()). It may throw a underflow exception).
    if (empty()) throw underflow();
    return array[itail];
}

template <typename Type>
void Dynamic_queue<Type>::swap( Dynamic_queue<Type> &queue ) {
    std::swap( initial_capacity, queue.initial_capacity );
    std::swap( array_capacity, queue.array_capacity );
    std::swap( array, queue.array );
    std::swap( ihead, queue.ihead );
    std::swap( itail, queue.itail );
    std::swap( entry_count, queue.entry_count );
}

template <typename Type>
Dynamic_queue<Type> &Dynamic_queue<Type>::operator=( Dynamic_queue<Type> rhs ) {
    swap( rhs );
    
    return *this;
}

template <typename Type>
void Dynamic_queue<Type>::enqueue( Type const &obj ) {
    // Enter your implementation here.
    
    // Check if array is full. An array of size 0 will have its tail at position 0, and this must be accounted for
    if (itail != 0 && itail == array_capacity) {
        // if so, double the capacity of the array
        array_capacity *= 2;
        
        // The array must be copied in a new array of twice the capacity, which must then be copied back into the array member of "this"
        Type *temp = new Type[array_capacity];
        for (int i = 0, iterator = ihead; iterator < itail; i++, iterator++)
            temp[i] = array[iterator];
        delete [] array;
        array = std::move(temp);
    }
    
    // Insert the argument at the tail of the queue and increment the tail and entry_count
    array[itail++] = obj;
    entry_count++;
    
}

template <typename Type>
Type Dynamic_queue<Type>::dequeue() {
    // Enter your implementation here.
    
    //If the queue is empty, the underflow exception is thrown
    if (empty()) throw underflow();
    
    // Remove the object at the head of the queue and increment ihead to reflect the change
    Type dequeuedObj = array[ihead];
    array[ihead++] = NULL;
    
    // If, after the object is removed, the array is 1/4 full and the array capacity is greater than the initial capacity, the capacity of the array is halved
    if ((itail-ihead+1)/array_capacity > 1/4 && array_capacity > initial_capacity) {
        array_capacity *= .5;
        Type *temp = new Type[array_capacity];
        for (int i = 0, iterator = ihead; iterator <= itail; i++, iterator++)
            temp[i] = array[iterator];
        array = std::move(temp);
    }
    
    return dequeuedObj;
}

template <typename Type>
void Dynamic_queue<Type>::clear() {
    // Enter your implementation here.
    // Empties the queue by resetting the member variables. The array is resized to the initial capacity. (O(1))
    initial_capacity = 10;
    array_capacity = initial_capacity;
    delete [] array;
    ihead = 0;
    itail = 0;
    entry_count = 0;
}

// You can modify this function however you want:  it will not be tested

template <typename Type>
std::ostream &operator<<( std::ostream &out, Dynamic_queue<Type> const &queue ) {
    // I don't know how you are implementing your queue so I cannot print it.
    // If you want, you can print whatever you want here and then call cout
    // in the driver.
    
    // Remember to redirect to out, e.g.,
    //      out << "Hello!";
    
    return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
