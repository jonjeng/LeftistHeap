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
    
    friend class Leftist_heap<Type>
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
Leftist_node* Leftist_node<Type>::left() const {
    return left_tree;
}

template <typename Type>
Leftist_node* Leftist_node<Type>::right() const {
    return right_tree;
}

template <typename Type>
int Leftist_node<Type>::count(const type &subj) const {
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
    // If this is a nullptr, return -1
    if (this == nullptr)
        return -1;
    
    return heap_null_path_length;
}

template <typename Type>
void Leftist_node<Type>::push(Leftist_node *heap_to_insert, Leftist_node *&ptr_to_this) const {
    /*// Only one node can be inserted at a time
    if (heap_to_insert->heap_null_path_length > 0) {
        std::cout << "Error: only one node can be inserted at a time\n";
        return;
    }*/
    
    // If the heap to insert is null, return.
    if (heap_to_insert == nullptr)
        return;
    
    // Otherwise, insert the heap
    if (this == nullptr) {
        this = heap_to_insert;
    }
    
    // If the smallest element in the original heap (ptr_to_this), recursively merge right subtree of original heap with new heap (heap_to_insert)
    else if (ptr_to_this->element <= heap_to_insert->element) {
        Leftist_node<Type> curr = ptr_to_this;
        while (curr->right_tree != nullptr)
            curr = curr->right_tree;
        curr->right_tree = heap_to_insert;
        curr->right_tree->heap_null_path_length + heap_to_insert->null_path_length + 1;
        
        // Check if right subtree of curr has larger null path length than left subtree. If so, then swap right tree and left tree.
        if (curr->left_tree) {
            if (curr->right_tree->heap_null_path_length > curr->left_tree->heap_null_path_length)
                std::swap(curr->right_tree, curr->left_tree);
        }
        
        // Check if right subtree of root node has larger null path length than left subtree. If so, then swap right tree and left tree.
        if (ptr_to_this->left_tree) {
            if (ptr_to_this->right_tree->heap_null_path_length > ptr_to_this->left_tree->heap_null_path_length)
                std::swap(ptr_to_this->right_tree, ptr_to_this->left_tree);
        }
    }
    
    // if smallest element is in the new heap (heap_to_insert), recursively merge right subtree of new heap with original heap (ptr_to_this)
    else if (heap_to_insert->element < ptr_to_this->element) {
        Leftist_node<Type> curr = heap_to_insert;
        while (curr->right_tree != nullptr)
            curr = curr->right_tree;
        curr->right_tree = ptr_to_this;
        curr->right_tree->heap_null_path_length + heap_to_insert->null_path_length + 1;
        
        // If the curr's right subtree has larger null path length than its left subtree, swap the right subtree with its left subtree
        if (curr->left_tree) {
            if (curr->right_tree->heap_null_path_length > curr->left_tree->heap_null_path_length)
                std::swap(curr->right_tree, curr->left_tree);
        }
        
        // Check if right subtree of root node has larger null path length than left subtree. If so, then swap right tree and left tree.
        if (heap_to_insert->left_tree) {
            if (heap_to_insert->right_tree->heap_null_path_length > heap_to_insert->left_tree->heap_null_path_length)
                std::swap(heap_to_insert->right_tree, heap_to_insert->left_tree);
        }
    }
    
}

template <typename Type>
void Leftist_node<Type>::clear() const {
    // If this is nullptr, return
    if (this == nullptr) return;
    // Call clear on the left sub-tree and then on the right and then delete this.
    left_tree.clear();
    right_tree.clear();
    delete this;
}

#endif
