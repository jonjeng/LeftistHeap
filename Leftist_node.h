/*****************************************
 Project 3 - CIS 22C
 
 * Contributors:
 * Evan Finnigan
 * Forest Finnigan
 * Jonathan Jeng
 * Abhishek Rajbahndri
 *****************************************/

#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include "Dynamic_queue.h"
#include <algorithm>
// You may use std::swap and std::min

#ifndef nullptr
#define nullptr 0
#endif

template <typename Type>
class Leftist_node {
	private:
		Type element;
		Leftist_node *left_tree;
		Leftist_node *right_tree;
		int heap_null_path_length;

	public:
		Leftist_node( Type const & );

		Type retrieve() const;
		bool empty() const;
		Leftist_node *left() const;
		Leftist_node *right() const;
		int count( Type const & ) const;
		int null_path_length() const;

		void push( Leftist_node *, Leftist_node *& );
		void clear();
    
};

template <typename Type>
Leftist_node<Type>::Leftist_node( Type const &obj ):
element( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
heap_null_path_length( 0 ) {
	// does nothing
}

template <typename Type>
Type Leftist_node<Type>::retrieve() const {
    return element;
}

template <typename Type>
bool Leftist_node<Type>::empty() const {
    return (this == nullptr);
}

template <typename Type>
Leftist_node<Type>* Leftist_node<Type>::left() const {
    return left_tree;
}

template <typename Type>
Leftist_node<Type>* Leftist_node<Type>::right() const {
    return right_tree;
}

template <typename Type>
int Leftist_node<Type>::count(const Type &subj) const {
    // Return the number of instances of the argument in this sub-tree. (O(n))
    
    int count = 0;
    // If the node's element is equal to the argument, increment count.
    if (element == subj)
        count++;
    // Recursively increment count for each subtree node that has an element equal to the argument.
    count += left_tree->count(subj);
    count += right_tree->count(subj);
    
    return count;
}

template <typename Type>
int Leftist_node<Type>::null_path_length() const {
    return heap_null_path_length;
}

template <typename Type>
void Leftist_node<Type>::push(Leftist_node<Type> *heap_to_insert, Leftist_node<Type> *&ptr_to_this) {
    // If the heap to insert is null, return.
    if (heap_to_insert == nullptr)
        return;
    
    // Otherwise, the heap to insert into is empty. Insert accordingly
    else if (ptr_to_this == nullptr) {
        ptr_to_this = heap_to_insert;
        return;
    }
    
    // Otherwise, the heap to insert into is not empty. Insert accordingly
    
    // If the heap to insert has a smaller value than the least element of the heap to be inserted into, the heap to insert should be made the heap to be inserted into and vice versa
    if (heap_to_insert->element < ptr_to_this->element)
        std::swap(ptr_to_this, heap_to_insert);
    
    // If the root of the heap to be inserted into has no children, the heap to insert should be inserted as its left child
    if (ptr_to_this->right_tree == nullptr)
        if (ptr_to_this->left_tree == nullptr)
            ptr_to_this->left_tree = heap_to_insert;
    // If the root of the heap to be insered into has a left child, the heap to insert should be inserted as its right child
        else ptr_to_this->right_tree = heap_to_insert;
    // Otherwise, recursively insert the heap into the right child position (everything subsequent also occurs recursively if applicable
    else (push(heap_to_insert, ptr_to_this->right_tree));
    
    // If the heap's left tree has a null path length lower than that of the right tree, swap them
    if (ptr_to_this->left_tree && ptr_to_this->right_tree)
        if (ptr_to_this->left_tree->heap_null_path_length < ptr_to_this->right_tree->heap_null_path_length)
            std::swap(ptr_to_this->left_tree, ptr_to_this->right_tree);
    
    // Update the node's null path length
    if (ptr_to_this->right_tree)
        ptr_to_this->heap_null_path_length = ptr_to_this->right_tree->heap_null_path_length + 1;
}

template <typename Type>
void Leftist_node<Type>::clear() {
    // Call clear on the left sub-tree and then on the right and then delete this.
    if (left_tree)
        left_tree->clear();
    if (right_tree)
        right_tree->clear();
    delete this;
}

#endif
