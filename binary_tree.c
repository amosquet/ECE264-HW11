/*****+--*-**-**--*-*-**-*-*-**-----*--*---**-*--***************************
* Created on Thu Apr 10 2025
*
* Copyright (c) 2025 Artus Mosquet
******+--*-**-**--*-*-**-*-*-**-----*--*---**-*--**************************/

#include "binary_tree.h"

// ***
// *** Modify this file
// ***

// The function `createNode` dynamically allocates memory for a new binary tree node and initializes its value.
// It returns a pointer to the newly created node.
TreeNode* createNode(int data) {
    // Allocate memory for a new TreeNode

    // Check if the allocation was successful

    // Initialize the node's data and set its left and right children to NULL

    // Return the pointer to the new node

    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
    
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    newNode->left = NULL;
    newNode->right = NULL;
    newNode->data = data;
    
    return newNode;
}

// This is a warmup exercise.
// In-order traversal visits the left subtree, then the current node, and finally the right subtree.
// The function `inorderTraversal` prints the data of each node in the tree in in-order.
void inorderTraversal(TreeNode* root) {
    
    if (root == NULL) {
        return;
    }

    inorderTraversal(root->left);  //visit left subtree
    printf("%d\n", root->data);   //visit current node
    inorderTraversal(root->right); //visit right subtree
}

// This is a warmup exercise.
void preorderTraversal(TreeNode* root) {
    
    if (root == NULL) {
        return;
    }

    printf("%d\n", root->data);   //visit current node
    preorderTraversal(root->left);  //visit left subtree
    preorderTraversal(root->right); //visit right subtree
}

// The function `freeTree` frees the memory allocated for the binary tree.
// It recursively frees the left and right subtrees and then frees the current node.
// Step 1: if the root is NULL, return.
// Step 2: recursively free the left and right subtrees.
// Step 3: free the current node.
void freeTree(TreeNode* root) {

    if (root == NULL) {
        return;
    }

    freeTree(root->left); //free left subtree
    freeTree(root->right); //free right subtree
    free(root); //free current node
}

// The function `createTree` creates a binary tree from an array representation.
// Hint: You can create a helper function to recursively build the tree.
// Step 1: base case, return NULL. What is the base case?
// Step 2: create a new node.
// Step 3: recursively create the left and right subtrees.
// Step 4: return the created node.
TreeNode* createTreeHelper(int* arr, int size, int index) {

    //base case: if index is out of bounds, return NULL
    if (index >= size || arr[index] == -1) {
        return NULL;
    }

    //create a new node with the current value
    TreeNode* node = createNode(arr[index]);

    //recursively create the left and right subtrees
    node->left = createTreeHelper(arr, size, 2 * index + 1);
    node->right = createTreeHelper(arr, size, 2 * index + 2);

    return node;
}

TreeNode* createTree(int* arr, int size) {
    return createTreeHelper(arr, size, 0);
}

// trimTree function:
// Given a binary tree where each node contains a non-negative integer and two integers, `low` and `high`, 
// your task is to trim the tree such that every root-to-leaf path in the resulting tree has a sum within the inclusive range [low, high]. 
// Specifically, any *leaf* node whose path sum from the root to that leaf falls outside this range should be removed from the tree. 
// If removing a leaf node causes its parent to become a leaf and its new path sum also falls outside the valid range, that parent should be removed as well. 
// This process should continue recursively until all remaining root-to-leaf paths satisfy the constraint.
// The structure of the remaining nodes must be preserved, and the final tree must still be a valid binary tree. 
// Your function should return the root of the trimmed tree.

TreeNode* trimTreeHelper(TreeNode* root, int low, int high, int currentSum) {
    
    if (root == NULL) {
        return NULL;
    }

    currentSum += root->data;

    //recursively trim the left and right subtrees
    root->left = trimTreeHelper(root->left, low, high, currentSum);
    root->right = trimTreeHelper(root->right, low, high, currentSum);

    //if the current node is a leaf and its path sum is out of range, remove it
    if (root->left == NULL && root->right == NULL) {
        
        if (currentSum < low || currentSum > high) {
            
            free(root);
            return NULL;
        }
    }

    return root;
}

TreeNode* trimTree(TreeNode* root, int low, int high) {
    // Hint 1: You need to keep track of the sum of the path from the root to the current node. You can do this by creating a helper function.
    // Hint 2: In your helper function, check if the current node is a leaf node. If it is, check if the sum of the path from the root to this leaf node is within the range [low, high].
    // Hint 3: When you remove a node, do not forget to free the memory allocated for that node.

    return trimTreeHelper(root, low, high, 0);
}

// The function `toBST` converts a binary tree into a binary search tree (BST) by pruning subtrees that violate BST properties. 
// The transformation must ensure that for every node:
// - All nodes in the left subtree have values less than the current node.
// - All nodes in the right subtree have values greater than the current node.
// **Restrictions**: The root node must remain unchanged. If a node's value violates BST properties relative to all its ancestors, its entire subtree is removed.

TreeNode* toBSTHelper(TreeNode* root, int minValue, int maxValue) {
    
    if (root == NULL) {
        return NULL;
    }

    //check if the current node's value is within the valid range
    if (root->data < minValue || root->data > maxValue) {
        
        freeTree(root);
        return NULL;
    }

    //prune the left and right subtrees
    root->left = toBSTHelper(root->left, minValue, root->data);
    root->right = toBSTHelper(root->right, root->data, maxValue);

    return root;
}

TreeNode* toBST(TreeNode* root) {
    // Hint1: You need to keep track of the minimum and maximum values allowed for each node in the tree. You can do this by creating a helper function.
    // Hint2: In your helper function, check if the current node's value is within the valid range. If it is not, remove the subtree rooted at this node.
    // Hint3: When you remove a node, do not forget to free the memory allocated for that subtree.

    return toBSTHelper(root, INT_MIN, INT_MAX);
}