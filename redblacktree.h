//
// Created by wangguozhi on 2019-11-14.
//

#ifndef WAYNE_CITY_REDBLACKTREE_H
#define WAYNE_CITY_REDBLACKTREE_H

#endif //WAYNE_CITY_REDBLACKTREE_H

template<class T>
class Node {
private:
    Node *parent = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;
    bool isRed = false;
    T data;
public:
    Node(T t) {
        this->data = t;
    }
};

template<class T>
class RedBlackTree {
private:
    Node<T> *root = nullptr;

    /*
     * Left Rotate:
     *      N                  R
     *    NL  R      =>      N  RR
     *      RL RR          NL RL
     */
    void leftRotate(Node<T> *node) {
        Node<T> *right = right;
        node->right = right->left;
        right->left = node;
    }

    /*
     * Right Rotate:
     *       N                  L
     *     L  NR      =>      LL  N
     *   LL LR                  LR NR
     */
    void rightRotate(Node<T> *node) {
        Node<T> *left = node->left;
        node->left = left->right;
        left->right = node;
    }

    void append(Node<T> *to_append, Node<T> *parent) {
        if (parent->data > to_append->data) {
            if (parent->left == nullptr) {
                parent->left = to_append;
            } else {
                append(to_append, parent->left);
            }
        } else {
            if (parent->right == nullptr) {
                parent->right = to_append;
            } else {
                append(to_append, parent->right);
            }
        }
    }

    void insertFix(Node<T> *node) {
        while (node->parent->isRed) {
            if (node->parent = node->parent->parent->left) {
                if (node->parent->parent->right->isRed) {
                    node->parent->isRed = false;
                    node->parent->parent->right->isRed = false;
                    node->parent->parent->isRed = true;
                    node = node->parent->parent;
                } else {
                    
                }
            }
        }
    }

public:
    int insert(T &t) {
        Node<T> node = Node<T>(t);
        node.isRed = true;
        append(node, root);
    }
};
