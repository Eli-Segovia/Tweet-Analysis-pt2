//
// Created by Eli Segovia on 4/6/20.
//

#ifndef INC_20S_PA03_ELISEGO45_BSTNODE_H
#define INC_20S_PA03_ELISEGO45_BSTNODE_H
template <typename T>
class bstNode{
public:
    enum NODE_COLOR : bool{RED=0, BLACK=1};    // Typical node stuff... Nothing special to see here
private:
    T data;
    NODE_COLOR color;
    bstNode<T>* right;
    bstNode<T>* left;

public:
    bstNode(T newData){
        this->data = newData;
        right = nullptr;
        left = nullptr;
        color = RED;
    }
    bstNode(const bstNode<T>& rhs){
        this-> left  =  new bstNode<T>(rhs.left->data);
        this-> right = new bstNode<T>(rhs.right->data);
        this-> color = rhs.color;
        this-> data = rhs.data;
    }
    bstNode<T>& operator=(const bstNode<T>& rhs){
        this-> left  =  new bstNode<T>(rhs.left->data);
        this-> right = new bstNode<T>(rhs.right->data);
        this-> color = rhs.color;
        this-> data = rhs.data;
        return *this;
    }
    ~bstNode(){
        this->left = nullptr;
        this->right = nullptr;
    }

    bool operator>(const bstNode<T>& rhs){
        return this->data > rhs.data;
    }

    bool operator<(const bstNode<T>& rhs){
        return this->data < rhs.data;
    }

    bool operator==(const bstNode<T>& rhs){
        return this->data == rhs.data;
    }

    bool operator!=(const bstNode<T>& rhs){
        return !(operator==(rhs));
    }

    template <typename U>
    friend class RBTree;


};
#endif //INC_20S_PA03_ELISEGO45_BSTNODE_H
