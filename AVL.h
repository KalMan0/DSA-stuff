fndef AVL_H
#define AVL_H 

#include <iostream>

enum Traversal {INORDER,PREORDER,POSTORDER};

template<typename T>
struct Node {

    T data;

    Node* right;
    Node* left;

    int height;
};

template <typename T>
    class AVL {

    private:

        Node<T>* Head;

        void         in_order       (Node<T>*);   // traversal tech
        void         post_order     (Node<T>*);
        void         pre_order      (Node<T>*);
        void         Destroy        (Node<T>*);
        Node<T>*     Remove         (Node<T>*,const T&);
        Node<T>*     RightRotate    (Node<T>*); // avl rotations 
        Node<T>*     LeftRotate     (Node<T>*);
        Node<T>*     NewNode        (const T&);  // returns a newly created node 
        Node<T>*     modtree        (Node<T>*, const T&);
        int          get_balance    (Node<T>*);
        int          height         (Node<T>*);
        int          max            (int, int);

        Node<T>*    minvalueBF      (Node<T>*); 
        Node<T>*    maxvalueBF      (Node<T>*);
        
 
    public:

        AVL();
        ~AVL();

        void         Insert         (const T&);
        void         output         (enum Traversal);
        void         Delete         (const T&);
        Node<T>* BalanceNode(Node<T>* root, const T& Data);
        
        
};

template <typename T> AVL<T>::AVL() {}

template <typename T> AVL<T>::~AVL()
{
    Destroy(Head);
}


template <typename T> void AVL<T>::Delete(const T& data)
{
    Head = Remove(Head, data); 
}

template <typename T> Node<T>* AVL<T>::BalanceNode(Node<T>* root, const T& Data)
{
    root->height = 1 + max(height(root->left), height(root->right)); // create balance function ? 

    int balance = get_balance(root);

    if (balance > 1 && Data < root->left->data) // left left rot 
    {
        return RightRotate(root);
    }

    if (balance < -1 && Data > root->right->data) // right right rot 
    {
        return LeftRotate(root);
    }

    if (balance > 1 && Data > root->left->data) // left right rot 
    {
        root->left = LeftRotate(root->left);
        return RightRotate(root);
    }

    if (balance < -1 && Data < root->right->data) // right left rot
    {
        root->right = RightRotate(root->right);  // Fix: Change to root->right instead of root->left
        return LeftRotate(root);
    }

    return root; 
}

template <typename T>
Node<T>* AVL<T>::Remove(Node<T>* root, const T& Data)
{
    if (root == nullptr) return root;

    if (Data < root->data)
    {
        root->left = Remove(root->left, Data);
    }
    else if (Data > root->data)
    {
        root->right = Remove(root->right, Data);
    }
    else
    {
        if (root->left == nullptr || root->right == nullptr)
        {
            Node<T>* tmp = root->left ? root->left : root->right;

            if (tmp == nullptr)
            {
                tmp = root;
                root = nullptr;
            }
            else
            {
                *root = *tmp;
                delete tmp;
            }
        }
        else
        {
            Node<T>* tmp = minvalueBF(root->right);
            root->data = tmp->data;
            root->right = Remove(root->right, tmp->data);
        }
    }

    // Balance the node after removal
    if (root != nullptr)
        root = BalanceNode(root, Data);

    return root;
}



template <typename T> Node<T>* AVL<T>::minvalueBF(Node<T>* root)
{
    Node<T>* current = root; 

    while (current->left != nullptr)
    {
        current = current->left; 
    } // traverse left side of tree till min val 
    return current; 
}

template <typename T> Node<T>* AVL<T>::maxvalueBF(Node<T>* root)
{
    Node<T>* current = root; 

    while (current->right != nullptr)
    {
        current = current->right; 
    }

    return current; 
}

template <typename T> Node<T>* AVL<T>::RightRotate(Node<T>* root)
{
    Node<T>* newHead = root->left;
    Node<T>* nhtemp = newHead->right;

    newHead->right = root;
    root->left = nhtemp;

    root->height = 1 + max(height(root->left), height(root->right));
    newHead->height = 1 + max(height(newHead->left), height(newHead->right));

    return newHead;
}

template <typename T> Node<T>* AVL<T>::LeftRotate(Node<T>* root)
{
    Node<T>* newHead = root->right;
    Node<T>* nhtemp = newHead->left;

    newHead->left = root;
    root->right = nhtemp;

    root->height = 1 + max(height(root->left), height(root->right));
    newHead->height = 1 + max(height(newHead->left), height(newHead->right));

    return newHead;
}

template <typename T> Node<T>* AVL<T>::modtree(Node<T>* root, const T& Data)
{
    if (root == nullptr) return NewNode(Data);

    if (Data < root->data)
    {
        root->left = modtree(root->left, Data);
    }
    else if (Data > root->data)
    {
        root->right = modtree(root->right, Data);
    }
    else
    {
        return root;
    }

    root = BalanceNode(root, Data); 
    return root;
}

template <typename T> void AVL<T>::Destroy(Node<T>* root) //destroys the tree 
{
    if (root == nullptr) return;
    Destroy(root->left);
    Destroy(root->right);

    delete root;
}



template <typename T> void AVL<T>::in_order(Node<T>* root)
{
    if (root != nullptr)
    {
        in_order(root->left);
        std::cout << root->data << std::endl;
        in_order(root->right);
    }
}

template <typename T> void AVL<T>::post_order(Node<T>* root)
{
    if (root != nullptr)
    {
        post_order(root->left);
        post_order(root->right);
        std::cout << root->data << std::endl;
    }
}

template <typename T> void AVL<T>::pre_order(Node<T>* root)
{
    if (root != nullptr)
    {
        std::cout << root->data << std::endl;
        pre_order(root->left);
        pre_order(root->right);
    }
}

template <typename T>  Node<T>* AVL<T>::NewNode(const T& data)
{
    Node<T>* nn = new Node<T>;

    nn->right = nullptr;
    nn->left = nullptr;
    nn->data = data;
    nn->height = 1;

    return nn;
}


template <typename T> void AVL<T>::output(enum Traversal x)
{
    switch (x)
    {
        case PREORDER  : pre_order (Head); break;
        case POSTORDER : post_order(Head); break;
        case INORDER   : in_order  (Head); break;
        default: break;
    }
}

template <typename T> void AVL<T>::Insert(const T& data)
{
    Head = modtree(Head, data);
}

template <typename T> int AVL<T>::max(int x, int y)
{
    return (x > y) ? x : y;
}

template <typename T> int AVL<T>::height(Node<T>* node)
{
    if (node == nullptr) return 0;
    return node->height;
}

template <typename T> int AVL<T>::get_balance(Node<T>* node)
{
    if (node == nullptr) return 0;
    return height(node->left) - height(node->right);
}
#endif 
