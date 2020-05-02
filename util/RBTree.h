//
// Created by Eli Segovia on 4/6/20.
//

#ifndef INC_20S_PA03_ELISEGO45_RBTREE_H
#define INC_20S_PA03_ELISEGO45_RBTREE_H
#define COUNT 10
#include <iostream>
#include "bstNode.h"
#include <vector>

template<typename T>
using node = bstNode<T>;

template <typename U>
class RBTree{
private:
    int size = 0;
    node<U>* root = nullptr;

    // add new node given a pointer to the current node
    void add(U& newData, node<U>*& curr){ // find way to make sure duplicates are not being added
        if(newData > curr->data && curr->right == nullptr){ // if newData gt, we go to the right
            curr->right = new node<U>(newData);
        }
        else if(newData < curr->data && curr->left == nullptr){// if newData lt, we go to the left
            curr->left = new node<U>(newData);
        }
        else if(newData > curr->data){ // if left or right spots pass down information recursively
            add(newData, curr->right);
            checkRightInsert(curr);
        }
        else{
            add(newData, curr->left);
            checkLeftInsert(curr);
        }
        root->color = node<U>::BLACK; // at the end we assign root's color black
    }


    // helper method to the parent method below
    node<U>* parent(node<U>* child){
        return parent(child, root);
    }


    node<U>* parent(node<U>* child, node<U>* curr){ // method that finds the parent of a node
        if(root == nullptr)
            throw std::invalid_argument("Look at parent method...something is wrong");
        if(child == root)  // root has no parent
            return NULL;
        if(curr->left == child or curr->right == child){ // found the element
            return curr;
        } else if (child->data > curr->data){ // you can't find it, throw exception else recurse down
            if(curr->right == nullptr)
                throw std::exception();
            else{
                return parent(child, curr->right);
            }
        }
        else{
            if(curr->left == nullptr)
                throw std::exception();
            else{
                return parent(child, curr->left);
            }
        }
    }


    //checks four r-b cases once a node was inserted to the right of the grandparent node of the newly inserted one
    void checkRightInsert(node<U>*& curr){ //
        auto zNode = curr;
        auto yNode = curr->right;
        auto& yColor = yNode->color;

        if(yColor == node<U>::RED && ((yNode->left != nullptr && yNode->left->color == yColor)
                                      || (yNode->right != nullptr && yNode->right->color == yColor))){
            // if parent is red. that means we have red red conflict
            if(zNode->left != nullptr && zNode->left->color == yColor){// case 1 considers when there is a red uncle
                yNode->color = node<U>::BLACK;
                zNode->left->color = node<U>::BLACK; //simply flip parent,uncle,and grandparent colors
                zNode->color = node<U>::RED;
            }
            else if(yNode->right != nullptr && yNode->right->color == yColor){//case 2 considers a straight line
                zNode->right = yNode->left;                                   // of red red nodes
                yNode->left= zNode;       // rotate left and change grandparent to red and parent to black
                zNode->color = node<U>::RED;
                yNode->color = node<U>::BLACK;
                auto xParent = parent(zNode);
                if(xParent == NULL){  // the great grandparent's pointer if possible: if NULL that means it is now root
                    root = yNode;
                }
                else if(yNode->data > xParent->data)
                    xParent->right = yNode;
                else
                    xParent->left = yNode;
            }
            else if(yNode->left != nullptr && yNode->left->color == yColor &&
                   !(yNode->left->left != nullptr && yNode->left->right != nullptr)){ // case 3 considers a triangle
                zNode->right = yNode->left; // gp points to former grandchild
                yNode->left = nullptr;      // former child now has no left
                zNode->right->right = yNode;
                checkRightInsert(zNode);
            }
            else if(yNode->left != nullptr && yNode->left->color == yColor){ //considers a triangle with in inner node
                auto xNode = yNode->left;                                  // you can't use case 3 on an inner node
                yNode->left = xNode->right;                                // you have to do a rotation for these!
                xNode->right= yNode;
                zNode->right = xNode;
                checkRightInsert(zNode);
            }
        }


    }


    // like right insert, except it does left check from granparent node
    void checkLeftInsert(node<U>*& curr){ // same as above, but mirrored
        auto zNode = curr;
        auto grandpa = parent(zNode);
        auto yNode = curr->left;
        auto& yColor = yNode->color;

        if(yColor == node<U>::RED && ((yNode->left != nullptr && yNode->left->color == yColor)
                                        || (yNode->right != nullptr && yNode->right->color == yColor))){
            if(zNode->right != nullptr && zNode->right->color == yColor){//case 1 red uncle..
                yNode->color = node<U>::BLACK;
                zNode->right->color = node<U>::BLACK;
                zNode->color = node<U>::RED;
            }
            else if(yNode->left != nullptr && yNode->left->color == yColor){ //case2 straight red

                zNode->left = yNode->right;
                yNode->right = zNode;
                zNode->color = node<U>::RED;
                yNode->color = node<U>::BLACK;
                auto xParent = parent(zNode);
                if(xParent == NULL){
                    root = yNode;
                }
                else if(yNode->data > xParent->data)
                    xParent->right = yNode;
                else
                    xParent->left = yNode;
            }

            else if(yNode->right != nullptr && yNode->right->color == yColor &&
                   !(yNode->right->right != nullptr && yNode->right->left != nullptr)){//case 3 triangle
                zNode->left = yNode->right;
                yNode->right = nullptr;
                zNode->left->left = yNode;
                checkLeftInsert(zNode);
            }
            else if(yNode->right != nullptr && yNode->right->color == yColor){ // case 4 triangle rotation
                auto xNode = yNode->right;
                yNode->right = xNode->left;
                xNode->left= yNode;
                zNode->left = xNode;
                checkLeftInsert(zNode);
            }
        }

    }
    U& get(U data, node<U>*& curr){
        if(data == curr->data)
            return curr->data;
        else if(data > curr->data && curr->right != nullptr){
            return get(data, curr->right);
        }
        else if(data < curr->data && curr->left != nullptr){
            return get(data, curr->left);
        }
        else{
            return root->data;
        }
    }

    bool contains(U& data, node<U>* curr){
        if(curr == nullptr)
            return false;
        else if(data == curr->data)
            return true;
        else if(data > curr->data && curr->right != nullptr){
            return contains(data, curr->right);
        }
        else if(data < curr->data && curr->left != nullptr){
            return contains(data, curr->left);
        }
        else{
            return false;
        }
    }


    void destroyTree(node<U>* curr){
        if(curr != nullptr){
            if(curr->left != nullptr){
                destroyTree(curr->left);
            }
            if(curr->right != nullptr){
                destroyTree(curr->right);
            }
            delete curr;
            curr = nullptr;
        } else
            return;
    }


    void copy(node<U>* rhsCurr){
         add(rhsCurr->data);
        if(rhsCurr->left != nullptr)
            copy(rhsCurr->left);
        if(rhsCurr->right != nullptr){
            copy(rhsCurr->right);
        }
    }


    void copyFrom(const RBTree<U>& rhs){
        if(rhs.root != nullptr)
            copy(rhs.root);
    }


    void gather(std::vector<U>& theData, node<U>* curr){
        if(curr->left != nullptr)
            gather(theData, curr->left);
        theData.push_back(curr->data);
        if(curr->right != nullptr)
            gather(theData, curr->right);
    }

public:
    // constructor
    RBTree(){
        size = 0;
        root = nullptr;
    }


    RBTree(U a){
        size = 1;
        root = new node<U>(a);
    }


    RBTree(const RBTree & rhs){
        this->size = rhs.size;
        copyFrom(rhs);
    }


    RBTree & operator=(const RBTree & rhs){
        if(this->root != nullptr){
            destroyTree();
        }
        this->size = rhs.size;
        copyFrom(rhs);
        return *this;
    }


    ~RBTree(){
        destroyTree();
    }


    void destroyTree(){
        destroyTree(root);
        root = NULL;
        size = 0;
    }


    // checks if the tree has a node
    bool contains(U data){
        return contains(data,root);
    }

    U& get(U data){
        return get(data,root);
    }


    //adds node to the tree
    void add(U newData){ // accessible for user
        if(root == nullptr){
            root = new node<U>(newData);
            root->color = node<U>::BLACK;
        }
        else if(contains(newData))
            return;
        else{
            add(newData, root);
        }
        size++;
    }


    //returns size...obviously
    unsigned int getSize(){
        return this->size;
    }


    std::vector<U> getData(){
        std::vector<U> theData;
        if(root != nullptr)
            gather(theData, root);
        return theData;
    }


    void printSet(){
        print2D();
    }

    // next major operation would be deletion, but I do not need that for this project...

//------------------ end of eli code -----------------------------------------------------


    // methods borrowed from geeks for geeks for testing

    void printTree(node<U> *r, int space)
    {
        // Base case
        if (r == nullptr)
            return;

        // Increase distance between levels
        space += COUNT;

        // Process right child first
        printTree(r->right, space);

        // Print current node after space
        // count
        std::cout<<std::endl;
        for (int i = COUNT; i < space; i++)
            std::cout<<" ";
        std::cout<<r->data << "(" << r->color <<")"<<"\n";

        // Process left child
        printTree(r->left, space);
    }

// Wrapper over print2DUtil()
    void print2D()
    {

        // Pass initial space count as 0
        printTree(root, 0);
    }
};
#endif //INC_20S_PA03_ELISEGO45_RBTREE_H
