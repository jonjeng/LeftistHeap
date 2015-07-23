/*****************************************
 Project 1 - CIS 22C
 
 * Contributors:
 * Evan Finnigan
 * Forest Finnigan
 * Jonathan Jeng
 * Abhishek Rajbahndri
 *****************************************/

#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Leftist_node.h"
#include <cmath>
#include "Dynamic_queue.h"

template <typename Type>
class Leftist_heap {
	private:
		Leftist_node<Type> *root_node;
		int heap_size;

	public:
		Leftist_heap();
		Leftist_heap( Leftist_heap const & );
		~Leftist_heap();

		void swap( Leftist_heap &heap );
		Leftist_heap &operator=( Leftist_heap );

		bool empty() const;
		int size() const;
		int null_path_length() const;
		Type top() const;
		int count( Type const & ) const;

		void push( Type const & );
		Type pop();
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Leftist_heap<T> const & );
};

//Constructor
template <typename Type>
Leftist_heap<Type>::Leftist_heap():
root_node( nullptr ),
heap_size( 0 ) {
	// does nothing
}

//Copy constructor
template <typename Type>
Leftist_heap<Type>::Leftist_heap( Leftist_heap const &heap ):
root_node( nullptr ),
heap_size( heap.heap_size ) {
	// Traverses through the argument heap and pushes the entries
	// into this heap--you may use whatever traversal you want
    //  You may use any linked list, stack or queue data structure from either Project 1 or 2 to perform the traversal of the tree that is being copied. If you wish, you may use the Standard Template Library (STL) stack or queue classes. 
    //
    if (heap.heap_size == 0) {
        heap_size = 0;
        return;
    }
    else if (heap.heap_size == 1) {
        Leftist_node<Type> *newNode = new Leftist_node<Type>;
        newNode = heap.root_node;
        root_node = newNode;
    }
    // Copy heap parameter into an array (arrayCopy) by breadth-first traversal
    else {
        /*
         put root node onto a queue
         while the queue is not empty
         dequeue the next node and visit it
         enqueue left child
         enqueue right child
         */
        Dynamic_queue<Type> queueCopy(heap.heap_size/2)
        Leftist_node<Type> *curr = heap.root_node;
        queueCopy.enqueue(curr);
        while (!queueCopy.empty()) {
            curr = queueCopy.head();
            push(queueCopy.dequeue());
            if (curr->left_tree != nullptr) {
                queueCopy.enqueue(curr->left_tree);
            }
            if (curr->right_tree != nullptr) {
                queueCopy.enqueue(curr->right_tree);
            }
        }
        
    }
    
}

template <typename Type>
Leftist_heap<Type>::~Leftist_heap() {
    Leftist_heap<Type>::clear();  // might as well use it...
}

template <typename Type>
void Leftist_heap<Type>::swap( Leftist_heap<Type> &heap ) {
	std::swap( root_node, heap.root_node );
	std::swap( heap_size, heap.heap_size );
}

template <typename Type>
Leftist_heap<Type> &Leftist_heap<Type>::operator=( Leftist_heap<Type> rhs ) {
	swap( rhs );

	return *this;
}

template <typename Type>
bool Leftist_heap::empty() const {
    // Returns true if the heap is empty, false otherwise.
    if (heap_size == 0)
        return true;
    return false;
}

template <typename Type>
int Leftist_heap::size() const {
    // Returns the number of nodes in the heap.
    return heap_size;
}

template <typename Type>
int Leftist_heap::null_path_length() const {
    // Returns the null-path length of the root node. (O(1))
    return root_node->null_path_length();
}

template <typename Type>
Type Leftist_heap::top() const {
    // Return the element at the top of the heap. If the tree is empty, this function throws an underflow exception. (O(1))
    // try {
    if (heap_size == 0)
        throw underflow();
    // } catch { std::cout << "Error: the heap is empty and there is no top element!\n"; return; }
    return root_node;
}

template <typename Type>
int Leftist_heap::count(const Type &subj) const {
    // Return the number of instances of the argument in the heap. (O(n))
    int count = 0;
    if (root_node->element == subj)
        count++;
    // Make use of Leftist_node<Type>::count(const type &subj) to traverse the subtrees accordingly.
    count += root_node->left_tree->count(subj);
    count += root_node->right_tree->count(subj);
    return false;
}

template <typename Type>
void Leftist_heap::push(const Type &obj) {
    // Insert the new element into the heap by creating a new leftist node and calling push on the root node using root_node as a second argument.
    Leftist_node<Type> *new_node = new Leftist_node<Type>(obj);
    root_node.push(new_node, root_node);
    
    // Increment the heap size.
    heap_size++;
}

template <typename Type>
Type Leftist_heap::pop() {
    // Remove root, leaving two subtrees (root's left_tree and right_tree).
            // Merge the two trees - find the subtree with the min element (which subtree's root node is smaller).
                // Recursively merge the right subtree (tree x) of the heap (that has the smallest element) with the rightmost element of the left heap. (place the rightmost element (node n) of the other tree into tree x)
                // Check if tree x's left subtree has a null path length at least as large as the right subtree. Swap right_tree and left_tree if it doesn't. Connect tree x to be the right child of the tree that originally contained node x
                // Check if left subtree has a null pat length at least as large as the right subtree. Swap right_tree and left_tree if it doesn't.
                // Connect this heap to tree x as its new right child
                // Check if tree x's left subtree has a null path length at least as large as the right subtree. Swap right_tree and left_tree if it doesn't
    

    
    
    // Pop the least element in the heap and delete its node. If the tree is empty, this function throws an underflow exception. Otherwise, the left sub-tree of the root node is made the root node and the right-sub tree of the original root node is pushed into the new root node. Return the element in the popped node and decrement the heap size. (O(ln(n)))
    
    // If the heap is size 0, no elements can be popped so throw an underflow exception.
    // try {
    if (heap_size == 0)
        throw underflow();
    // } catch { std::cout << "Error: the heap is empty. No elements can be popped.\n"; return; }
    
    // If the heap has size 1, call clear()
    if (heap_size == 1) {
        Type result = root_node->retrieve();
        Leftist_heap<Type>::clear();
        return result;
    }
    
    // Otherwise, the heap has size greater than 1
    Leftist_node<Type> *leftChild = root_node->left_tree;
    Leftist_node<Type> *rightChild = root_node->right_tree;
    
    Type result = root_node->retrieve();
    delete root_node;
    
    // The left sub-tree of the root node is made the root node (note: not the subtree with the min element?)
    root_node = leftChild;
    
    // The right-subtree of the original root node is pushed into the new root node
    root_node.push(rightChild, root_node);
    
    // Decrement heap_size to reflect the poppinng
    heap_size--;
    
    // Return the element in the popped node
    return result;
}

template <typename Type>
void Leftist_heap::clear() {
    // Call clear on the root node
    root_node.Leftist_node<Type>::clear();
    
    // Reset the root node and heap size.
    root_node = nullptr;
    heap_size = 0;
}

template <typename T>
std::ostream &operator<<( std::ostream &out, Leftist_heap<T> const &heap ) {
	return out;
}

#endif
