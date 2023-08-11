include<stdio.h>
#include<stdlib.h>
struct node
{
        int data;
        struct node *left;
        struct node *right;
        int height;
};
int max(int a,int b)
{
        if(a>b)
        {
                return a;
        }
        else
        {
                return b;
        }
}
struct node *createnew(int value)
{
        struct node *newnode;
        newnode=(struct node *)malloc(sizeof(struct node));
        newnode->data=value;
        newnode->left=NULL;
        newnode->right=NULL;
        newnode->height=1;
        return newnode;
}
int height(struct node *root)
{
        if(root==NULL)
        {
                return 0;
        }
        else
        {
                return root->height;
        }
}
int getbalance(struct node *root)
{
        if(root==NULL)
        {
                return 0;
        }
        else
        {
                return (height(root->left)-height(root->right));
        }
}
struct node *llrotation(struct node *node1)
{
        struct node *node2,*node3;
        node2=node1->left;
        node3=node2->right;
        node2->right=node1;
        node1->left=node3;
        node1->height=max(height(node1->left),height(node1->right))+1;
        node2->height=max(height(node2->left),height(node2->right))+1;
        return node2;
}
struct node *rrrotation(struct node *node1)
{
        struct node *node2,*node3;
        node2=node1->right;
        node3=node2->left;
        node2->left=node1;
        node1->right=node3;
        node1->height=max(height(node1->left),height(node1->right))+1;
        node2->height=max(height(node2->left),height(node2->right))+1;
        return node2;
}
struct node *creation(struct node *root,int value)
{
        if(root==NULL)
        {
                return createnew(value);
        }
        if(root->data>value)
        {
                root->left=creation(root->left,value);
        }
        else if(root->data<value)
        {
                root->right=creation(root->right,value);
        }
        else
        {
                printf("No duplicate entries are allowed in the AVL Tree.");
                return root;
        }
        root->height=max(height(root->left),height(root->right))+1;
        int balance;
        balance=getbalance(root);
        if(balance>1 && root->left->data>value)
        {
                return llrotation(root);
        }
        if(balance<-1 && root->right->data<value)
        {
                return rrrotation(root);
        }
        if(balance>1 && root->left->data<value)
        {
                root->left=rrrotation(root->left);
                return llrotation(root);
        }
        if(balance<-1 && root->right->data>value)
        {
                root->right=llrotation(root->right);
                return rrrotation(root);
        }
        else
        {
                return root;
        }
}
void inorder(struct node *root)
{
        if(root==NULL)
        {
                return;
        }
        else
        {
                inorder(root->left);
                printf("The data is:%d\n",root->data);
                inorder(root->right);
        }
}
struct node *minvalue(struct node *root)
{
    struct node *curr;
    curr=root;
    while(curr->left!=NULL)
    {
        curr=curr->left;
    }
    return curr;
}
struct node *deletion(struct node *root,int value)
{
    if(root==NULL)
    {
        return root;
    }
    if(root->data>value)
    {
        root->left=deletion(root->left,value);
    }
    else if(root->data<value)
    {
        root->right=deletion(root->right,value);
    }
    else
    {
        if((root->left==NULL)||(root->right==NULL))
        {
            struct node *temp=root->left?root->left:root->right;
            if(temp==NULL)
            {
                temp=root;
                root=NULL;
            }
            else
            {
                *root=*temp;
            }
            free(temp);
        }
        else
        {
            struct node *temp;
            temp=minvalue(root->right);
            root->data=temp->data;
            root->right=deletion(root->right,temp->data);
        }
    }
    if(root==NULL)
    {
        return root;
    }
    root->height=max(height(root->left),height(root->right))+1;
    int balance=getbalance(root);
    if(balance>1 && getbalance(root->left)>=0)
    {
        return llrotation(root);
    }
    if(balance>1 && getbalance(root->left)<0)
    {
        root->left=rrrotation(root->left);
        return llrotation(root);
    }
    if(balance<-1 && getbalance<=0)
    {
        return rrrotation(root);
    }
    if(balance<-1 && getbalance>0)
    {
        root->right=llrotation(root->right);
        return rrrotation(root);
    }
    else
    {
        return root;
    }
}
int main()
{
        int n,value;
        printf("Enter the number of nodes to be inserted in the AVL tree:");
        scanf("%d",&n);
        struct node *root;
        root=NULL;
        for(int i=0;i<n;i++)
        {
                printf("Enter the %dth data:",i+1);
                scanf("%d",&value);
                root=creation(root,value);
        }
        printf("The inorder traversal of the given tree is:\n");
        inorder(root);
        printf("The root data is:%d\n",root->data);
        root=deletion(root,30);
        printf("The inorder traversal of the tree is:\n");
        inorder(root);
        return 0;
}