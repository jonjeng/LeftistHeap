/*****************************************
 Project 1 - CIS 22C
 
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
    
    // If the smallest element in the original heap (ptr_to_this), recursively merge right subtree of original heap with new heap (heap_to_insert)
    if (ptr_to_this->element <= heap_to_insert->element) {
        ptr_to_this->right_tree->push(heap_to_insert, ptr_to_this->right_tree);
        ptr_to_this->right_tree->heap_null_path_length = heap_to_insert->heap_null_path_length + 1;
    
        // Recursively check if the right subtree of the node has larger null path length than the left subtree. If so, then swap the two and update the null path length
        if (ptr_to_this->left_tree) {
            if (ptr_to_this->right_tree->heap_null_path_length > ptr_to_this->left_tree->heap_null_path_length) {
                std::swap(ptr_to_this->right_tree, ptr_to_this->left_tree);
                ptr_to_this->heap_null_path_length = 1 + ptr_to_this->left_tree->heap_null_path_length;
            }
            else
                ptr_to_this->heap_null_path_length = 1 + ptr_to_this->right_tree->heap_null_path_length;
        }
        else {
            ptr_to_this->heap_null_path_length = 0;
            std::swap(ptr_to_this->left_tree, ptr_to_this->right_tree);
        }
    }

    // if smallest element is in the new heap (heap_to_insert), recursively merge it with the original heap (ptr_to_this)
    else if (heap_to_insert->element < ptr_to_this->element) {
        ptr_to_this = heap_to_insert;
        heap_to_insert->push(this, heap_to_insert);
    }
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
