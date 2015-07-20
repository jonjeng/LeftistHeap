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
    // If the heap to insert is null, return.
    if (heap_to_insert == nullptr)
        return;
    
    // Otherwise, insert the heap
    if (this == nullptr) {
        this = heap_to_insert;
    }
    else if (element <= heap_to_insert->element) {
        // If the current node is storing a value <= the value stored in the root of the new heap, push the new node onto the right sub-tree with right_tree.
        push(heap_to_insert, right_tree);
        
        // Update the null-path length
        heap_null_path_length = 1 + std::min(null_path_length(left_tree), null_path_length(right_tree));
        
        // If the left-sub-tree has a smaller null-path length than the right sub-tree, swap the two sub-trees
        if (left_tree->null_path_length() < right_tree->null_path_length()) {
            std::swap(left_tree, right_tree)
        }
    }
    else /* if (element > heap_to_insert->element) */ {
        //  Otherwise, set ptr_to_this to be the heap_to_insert and push this node into the new heap (with an appropriate second argument).
        std::swap(ptr_to_this, heap_to_insert);
        ptr_to_this->push(heap_to_insert, left_tree);
        
        // Update the null-path length
        ptr_to_this->heap_null_path_length = 1 + std::min(null_path_length(ptr_to_this->left_tree), null_path_length(ptr_to_this->right_tree));
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