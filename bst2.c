#include <stdio.h>
#include "bst.h"
#include <stdlib.h>
#include <stdbool.h>


struct _Node{
    // int value;
    struct _Node *left;
    struct _Node *right;
    int value;
};

// gets a new node if the tree is empty or the root is null
Node *getNewNode(int value){
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// finds the parent node of the node to be added
Node *findParentNode(Node *root, int value){
    Node *temp;
    if (value < root->value){
        temp = root->right;
    }else{
        temp = root->left;
    }

    if (temp == NULL){
        return root;
    }
    else{
        return findParentNode(temp, value);
    }
}

// checks if the node being added is already in the tree to prevent addition of duplicate nodes
bool ifNodeExists(Node *root, int value){
    if (root == NULL){
        return false;
    }else if (root->value == value){
        return true;
    }else if (ifNodeExists(root->left, value)){
        return true;
    }else{
        return ifNodeExists(root->right, value);
    }
}


Node *addNode(Node *root, int value){
    if (root == NULL){
        return getNewNode(value);
    }

    if (ifNodeExists(root, value)){
        return NULL;
    }

    Node *newNode = findParentNode(root, value);
    Node *newNodeParent = findParentNode(root, value);

    if (value > newNodeParent->value){
        newNode = newNodeParent->left;
    }else if (value < newNodeParent->value){
        newNode = newNodeParent->right;
    }

    if (newNode == NULL){
        newNode = getNewNode(value);
        if (value > newNodeParent->value){
            newNodeParent->left = newNode;
        }else{
            newNodeParent->right = newNode;
        }
        return newNode;
    }
    return NULL;
}

Node *getLeftMax(Node *root){
    Node *temp = root;
    while (temp && temp->left != NULL){
        temp = temp->left;
    }
    return temp;
}

Node *removeNode(Node *root, int value)
{
    if (root == NULL)
        return root;
    if (value < root->value)
        root->right = removeNode(root->right, value);
    else if (value > root->value)
        root->left = removeNode(root->left, value);
    else{
        if ((root->left == NULL) && (root->right == NULL)){
            free(root);
            return NULL;
        }else if (root->left == NULL){
            Node *temp = root->right;
            free(root);
            return temp;
        }else if (root->right == NULL){
            Node *temp = root->left;
            free(root);
            return temp;
        }else{
            Node *leftMax = getLeftMax(root->right);
            root->value = leftMax->value;
            root->right = removeNode(root->right, leftMax->value);
        }
    }
    return root;
}

void displaySubtree(Node *N){
    if (N == NULL){
        return;
    }
    displaySubtree(N->right);
    printf("%d \n", N->value);
    displaySubtree(N->left);
}

int numberLeaves(Node *N){
    int count = 0;
    if (N->right == NULL && N->left == NULL){
        count++;
    }else{
        if (N->right != NULL){
            count += numberLeaves(N->right);
        }if (N->left != NULL){
            count += numberLeaves(N->left);
        }
    }
    return count;
}

// checks if the node is present in the tree
bool isPresent(Node *root, Node *N){
    if (root == NULL || N == NULL){
        return false;
    }else if (root->value == N->value){
        return true;
    }else if (N->value < root->value){
        return isPresent(root->right, N);
    }else{
        return isPresent(root->left, N);
    }
}

// returns -1 if the node is not present in the tree and returns the height of the node if it is present
int nodeDepth(Node *root, Node *N){
    bool is_Present = isPresent(root, N);
    if (!isPresent(root, N)){
        return -1;
    }
    int count = 0;
    if (root == NULL || N == NULL){
        count = -1;
    }else if (root->value == N->value){
        count = 0;
    }else if (N->value < root->value){
        count = 1 + nodeDepth(root->right, N);
    }else{
        count = 1 + nodeDepth(root->left, N);
    }
    return count;
}

void removeTree(Node *root){
    if (root == NULL){
        return;
    }
    removeTree(root->left);
    removeTree(root->right);
    free(root);
}

Node *removeSubtree(Node *root, int value){
    if (root == NULL){
        return root;
    }if (value > root->value){
        root->left = removeSubtree(root->left, value);
    }else if (value < root->value){
        root->right = removeSubtree(root->right, value);
    }else if (value == root->value){
        removeTree(root);
        root = NULL;
    }
    return root;
}
