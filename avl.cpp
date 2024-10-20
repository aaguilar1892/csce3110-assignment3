#include <stdio.h>
#include <iostream>
#include "avl.hpp"
using namespace std;

#define IS_ROOT 0
#define IS_LEFT 1
#define IS_RIGHT 2

// Utility function to get the height of the node
int height(AvlNode *node) {
    return node == nullptr ? 0 : node->height;
}

// Utility function to update the height of the node
void updateHeight(AvlNode *node) {
    if (node != nullptr) {
        node->height = 1 + std::max(height(node->left), height(node->right));
    }
}

// Utility function to get the balance factor of the node
int getBalance(AvlNode *node) {
    return node == nullptr ? 0 : height(node->left) - height(node->right);
}

// Right rotate subtree rooted with y
AvlNode* rightRotate(AvlNode *y) {
    AvlNode *x = y->left;
    AvlNode *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    updateHeight(y);
    updateHeight(x);

    return x;
}

// Left rotate subtree rooted with x
AvlNode* leftRotate(AvlNode *x) {
    AvlNode *y = x->right;
    AvlNode *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    updateHeight(x);
    updateHeight(y);

    return y;
}

// Find the minimum node in the subtree
AvlNode* findMin(AvlNode* node) {
    while (node->left != nullptr)
        node = node->left;
    return node;
}

/**
 * Internal method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the subtree.
 * Set the new root of the subtree.
 */
void insert(const int &info, AvlNode *&root) {
    if (root == nullptr) {
        root = new AvlNode(info, nullptr, nullptr);
        return;
    }

    if (info < root->element)
        insert(info, root->left);
    else if (info > root->element)
        insert(info, root->right);
    else
        return; // Duplicate keys are not allowed

    // Update height of this ancestor node
    updateHeight(root);

    // Get the balance factor of this ancestor node to check if it became unbalanced
    int balance = getBalance(root);

    // If the node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && info < root->left->element)
        root = rightRotate(root);

    // Right Right Case
    if (balance < -1 && info > root->right->element)
        root = leftRotate(root);

    // Left Right Case
    if (balance > 1 && info > root->left->element) {
        root->left = leftRotate(root->left);
        root = rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && info < root->right->element) {
        root->right = rightRotate(root->right);
        root = leftRotate(root);
    }
}

/**
 * Internal method to remove from a subtree.
 * info is the item to remove.
 * root is the node that roots the subtree.
 * Set the new root of the subtree.
 */
void remove(const int &info, AvlNode *&root) {
    if (root == nullptr)
        return;

    if (info < root->element)
        remove(info, root->left);
    else if (info > root->element)
        remove(info, root->right);
    else {
        // Node with only one child or no child
        if ((root->left == nullptr) || (root->right == nullptr)) {
            AvlNode *temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp; // Copy the contents of the non-empty child

            delete temp;
        } else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            AvlNode* temp = findMin(root->right);

            // Copy the inorder successor's data to this node
            root->element = temp->element;

            // Delete the inorder successor
            remove(temp->element, root->right);
        }
    }

    if (root == nullptr)
        return;

    // Update height of the current node
    updateHeight(root);

    // Get the balance factor to check if this node became unbalanced
    int balance = getBalance(root);

    // Balance the node if needed
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        root = rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        root = rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        root = leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        root = leftRotate(root);
    }
}

/*
 * You will probably neesd auxiliary mathods to 
 *  - find the minimum of tree
 *  - rotate (single and double, in both directions
 *  - balance am AVL  tree
 */

/*
 * Print methods, do not change
 */
void print(AvlNode *root, int level, int type) {
  if (root == NULL) {
    return;
  }
  if (type == IS_ROOT) {
    std::cout << root -> element << "\n";
  } else {
    for (int i = 1; i < level; i++) {
      std::cout << "| ";
    }
    if (type == IS_LEFT) {
      std::cout << "|l_" << root -> element << "\n";
    } else {
      std::cout << "|r_" << root -> element << "\n";
    }
  }
  if (root -> left != NULL) {
    print(root -> left, level + 1, IS_LEFT);
  }
  if (root -> right != NULL) {
    print(root -> right, level + 1, IS_RIGHT);
  }
}
void print(AvlNode *root) {
  print(root, 0, IS_ROOT);
}
/*
 * END Print methods, do not change
 */


/* 
 * Main method, do not change
 */
int main(int argc, const char * argv[]) {
  AvlNode *root = NULL;
  std::string filename = argv[1];
  freopen(filename.c_str(), "r", stdin);
  std::string input;
  int data;
  while(std::cin >> input){
    if (input == "insert"){
      std::cin>>data;
      insert(data, root);
    } else if(input == "delete"){
      std::cin>>data;
      remove(data, root);
    } else if(input == "print"){
      print(root);
      std::cout << "\n";
    } else{
      std::cout<<"Data not consistent in file";
      break;
    }
  }
  return 0;
}
/*
 * END main method
 */
