class avl
{
    public:
        int val;
        avl*left;
        avl*right;
        int height;

        avl(int data)
        {
            val = data;
            left = NULL;
            right = NULL;
            height = 1;
        }
};

int height(avl*root)
{
    if(root == NULL) return 0;
    return root->height;

}

int max(int a , int b)
{
    if(a>b) return a;return b;
}

void RR(avl*&n )
{
    avl*x = n->right->left;
    avl*y = n;
    n = n->right;
    n->left  = y;
    y->right = x;
    y->height = 1+max(height(y->left), height(y->right));
    n->height = 1+max(height(n->left), height(n->right));
}

void LL(avl*&n)
{

    avl*x = n->left->right;
    avl*y = n;
    n = n->left;
    n->right  = y;
    y->left = x;
    y->height  = 1+max(height(y->left),height(y->right));
    n->height = 1+max(height(n->left),height(n->right));
}

avl* get(int data)
{
    avl* t = new avl(data);
    return t;
}


void ins(avl*&root,int data)
{
    if(root == NULL)
    {
        root = get(data);
        return;
    }
    else if(data < root->val)
    {
        ins(root->left, data);
    }
    else if(data > root->val)
    {
        ins(root->right, data);
    }
    else
        return;
    root->height = 1+max(height(root->left),height(root->right));
    int bal = height(root->left) - height(root->right);

    if(bal < -1 && (root->right->val < data))
    {
        cout<<"RR: ";
        cout<<root->val<<" "<<bal<<endl;
        RR(root);
        bal = height(root->left)-height(root->right);
        cout<<root->val<<" "<<bal<<endl;
    }
    else if(bal > 1 && (root->left->val > data))
    {
        cout<<"LL: ";
        cout<<root->val<<" "<<bal<<endl;
        LL(root);
        bal = height(root->left)-height(root->right);
        cout<<root->val<<" "<<bal<<endl;
    }
    else if(bal < -1)
    {
        cout<<"RL: ";
        bal = height(root->left)-height(root->right);
        cout<<root->val<<" "<<bal<<endl;
        LL(root->right);
        RR(root);
        bal = height(root->left)-height(root->right);
        cout<<root->val<<" "<<bal<<endl;
    }
    else if(bal > 1)
    {
        cout<<"LR: ";
        bal = height(root->left)-height(root->right);
        cout<<root->val<<" "<<bal<<endl;
        RR(root->left);
        LL(root);
        bal = height(root->left)-height(root->right);
        cout<<root->val<<" "<<bal<<endl;
    }

}

bool del(avl*&root,int data)
{
    if(root == NULL)
        return 0;
     else if(data < root->val)
        del(root->left, data);
    else if(data > root->val)
        del(root->right, data);
    else
    {
        if(root->left == NULL && root->right == NULL)
        {
            avl *t = root;
            root = NULL;
            delete t;
        }
        else if( root->left == NULL)
        {
            avl*t = root;
            root = root->right;
            delete t;
        }
        else if(root->right == NULL)
        {
            avl*t = root;
            root = root->left;
            delete t;
        }
        else
        {
            avl*iter = root->right;
            while(iter->left!=NULL)
            {
                iter = iter->left;
            }
            root->val = iter->val;
            iter->val = data;
            del(root->right,data);
        }
        if (root == NULL) {return 1;}

        root->height  = 1+max(height(root->left),height(root->right));
        int bal = height(root->left)-height(root->right);

        if(bal < -1 && (root->right->val < data))
        {
        cout<<"RR: ";
        cout<<root->val<<" "<<bal<<endl;
        RR(root);
        bal = height(root->left)-height(root->right);
        cout<<root->val<<" "<<bal<<endl;
        }
    else if(bal > 1 && (root->left->val > data))
    {
        cout<<"LL: ";
        cout<<root->val<<" "<<bal<<endl;
        LL(root);
        bal = height(root->left)-height(root->right);
        cout<<root->val<<" "<<bal<<endl;
    }
    else if(bal < -1)
    {
        cout<<"RL: ";
        bal = height(root->left)-height(root->right);
        cout<<root->val<<" "<<bal<<endl;
        LL(root->right);
        RR(root);
        bal = height(root->left)-height(root->right);
        cout<<root->val<<" "<<bal<<endl;
    }
    else if(bal > 1)
    {
        cout<<"LR: ";
        bal = height(root->left)-height(root->right);
        cout<<root->val<<" "<<bal<<endl;
        RR(root->left);
        LL(root);
        bal = height(root->left)-height(root->right);
        cout<<root->val<<" "<<bal<<endl;
    }
    return 1;
    }

}



void inorder(avl*root)
{
    if(root == NULL)
        return;
    inorder(root->left);
    cout<<root->val<<"\t";
    inorder(root->right);
}

int main()
{
    avl* root = NULL;
    while(1)
    {
        int op;
        cout<<"option: ";
        cin>>op;
        switch(op)
        {
            case(1):
                cout<<"Enter the element: ";
                cin>>op;
                ins(root, op);
                break;
            case(0):
                inorder(root);
                break;
            case(2):
                cout<<"Enter the element to del: ";
                cin>>op;
                cout<<del(root,op)<<endl;
                break;
        }
    }

}