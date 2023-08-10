
None selected


#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* left;   
    struct node* right;  
    int height; 
}Node;

int ctr = 0;

Node* getNewNode(int key) {
    Node* new = (Node*)malloc(sizeof(Node));
    new->data = key;
    new->left = new->right = NULL;
    new->height = 0;
    return new;
}

int getHeight(Node* node) {
    if (node == NULL) {return -1;}
    else {
        return node->height;
    }
}

int getBalFac(Node* node) {
    return getHeight(node->left) - getHeight(node->right);
}

int maximum(int n1, int n2) {
    return n1 >= n2 ? n1 : n2;
}

void updateHeight(Node* node) {
    node->height = maximum(getHeight(node->left), getHeight(node->right)) + 1;
}

Node* leftRotate(Node* node) {
    // Node* ret = node->right;

    // Node* t1 = node->right->left;
    Node* t2 = node->right;
    // node->right = t1;
    node->right = t2->left;
    t2->left = node;

    updateHeight(node);
    updateHeight(t2);

    return t2;
}

Node* rightRotate(Node* node) {
    // Node* ret = node->left;

    // Node* t1 = node->left->right;
    Node* t2 = node->left;
    // node->left = t1;
    node->left = t2->right;
    t2->right = node;

    updateHeight(node);
    updateHeight(t2);

    return t2;
}


Node* insert(int data, Node* tree) {
    if (tree == NULL) {
        tree = getNewNode(data);
        return tree;
    }

    if (data > tree->data) {
        // tree->height++;
        tree->right = insert(data, tree->right);
    }
    else if (data < tree->data) {
        // tree->height++;
        tree->left = insert(data, tree->left);
    }


    updateHeight(tree);
    int bf = getBalFac(tree);
    if (bf == 2) {
        ctr++;
        int bfl = getBalFac(tree->left);
        if (bfl == 1 || bfl == 0) {
            tree = rightRotate(tree);   
        }
        else {
            tree->left = leftRotate(tree->left);
            tree = rightRotate(tree);
        }
    }
    else if (bf == -2) {
        ctr++;
        int bfr = getBalFac(tree->right);
        if (bfr == -1 || bfr == 0) {
            tree = leftRotate(tree);
        }
        else {
            tree->right = rightRotate(tree->right);
            tree = leftRotate(tree);
        }
    }
    return tree;

}

void inorder(Node* tree) {
    if (tree == NULL) {return;}

    inorder(tree->left);
    printf("%d address: %p height: %d left: %p right: %p\n", tree->data, tree, tree->height, tree->left, tree->right);
    inorder(tree->right);
}

Node* findMin(Node* node) {
    while (node->left != NULL) { node = node->left;} 
    return node;
}

Node* deleten(int data, Node* tree) {
    if (tree == NULL) {return tree;}

    if (data > tree->data) {
        tree->right = delete(data, tree->right);
    }
    else if (data < tree->data)  {
        tree->left = delete(data, tree->left);
    }
    else {
        if (tree->left == NULL && tree->right == NULL) {
            free(tree);
            tree = NULL;
        }
        else if (tree->left == NULL) {
            Node* temp = tree->right;
            free(tree);
            tree = temp;
        }
        else if (tree->right == NULL) {
            Node* temp = tree->left;
            free(tree);
            tree = temp;
        }
        else {
            Node* min = findMin(tree->right);
            tree->data = min->data;
            tree->right = delete(min->data, tree->right);
        }
    }
    if (tree == NULL) {return tree;}

    updateHeight(tree);
    int bf = getBalFac(tree);

    if (bf == 2) {
        ctr++;
        int bfl = getBalFac(tree->left);
        if (bfl == 1 || bfl == 0) {
            tree = rightRotate(tree);   
        }
        else {
            tree->left = leftRotate(tree->left);
            tree = rightRotate(tree);
        }
    }
    else if (bf == -2) {
        ctr++;
        int bfr = getBalFac(tree->right);
        if (bfr == -1 || bfr == 0) {
            tree = leftRotate(tree);
        }
        else {
            tree->right = rightRotate(tree->right);
            tree = leftRotate(tree);
        }
    }

    return tree;
    
}


int main() {
    Node* tree = NULL;
    tree = insert(3, tree);
    tree = insert(2, tree);
    tree = insert(1, tree);
    tree = insert(4, tree);
    tree = insert(5, tree);
    tree = insert(6, tree);
    tree = insert(7, tree);
    tree = insert(16, tree);
    tree = insert(15, tree);
    tree = insert(14, tree);

    inorder(tree);
    printf("ctr: %d\n\n\n", ctr);

    tree = delete(2, tree);
    tree = delete(3, tree);
    tree = delete(16, tree);
    tree = delete(15, tree);
    tree = delete(7, tree);
    inorder(tree);
    printf("ctr: %d\n\n\n", ctr);
}
message-1.txt
Displaying message-1.txt.