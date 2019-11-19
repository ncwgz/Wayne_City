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
     *    NL  R`     =>      N` RR`
     *      RL RR`         NL RL
     */
    void leftRotate(Node<T> *node) {
        Node<T> *right = node->right;
        node->right = right->left;
        right->left = node;
    }

    /*
     * Right Rotate:
     *       N                  L
     *    `L  NR      =>     `LL `N
     *  `LL LR                  LR NR
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
                insertFix(to_append);
            } else {
                append(to_append, parent->left);
            }
        } else {
            if (parent->right == nullptr) {
                parent->right = to_append;
                insertFix(to_append);
            } else {
                append(to_append, parent->right);
            }
        }
    }

    void rootRedCheck() {
        if (this->root->isRed) {
            this->root->isRed = false;
        }
    }

    void insertFix(Node<T> *node) {
        if (node == root) {
            return;
        }
        // Two continuous red nodes
        while (node->parent->isRed) {
            if (node->parent == node->parent->parent->left) {
                // The color-change case
                if (node->parent->parent->right->isRed) {
                    node->parent->isRed = false;
                    node->parent->parent->right->isRed = false;
                    node->parent->parent->isRed = true;
                    node = node->parent->parent;
                    rootRedCheck();
                } else {
                    // The LR-rotate case
                    if (node->parent->right == node) {
                        node = node->parent;
                        leftRotate(node);
                    }
                    // The LL-rotate case
                    node->parent->isRed = false;
                    node->parent->parent->isRed = true;
                    rightRotate(node->parent->parent);
                }
            } else {
                // The color-change case
                if (node->parent->parent->left->isRed) {
                    node->parent->isRed = false;
                    node->parent->parent->left->isRed = false;
                    node->parent->parent->isRed = true;
                    node = node->parent->parent;
                    rootRedCheck(node);
                } else {
                    // The RL-rotate case
                    if (node->parent->left == node) {
                        node = node->parent;
                        rightRotate(node);
                    }
                    // The RR-rotate case
                    node->parent->isRed = false;
                    node->parent->parent->isRed = true;
                    leftRotate(node->parent->parent);
                }
            }
        }
    }

    Node<T>* getRightMin(Node<T> *node) {
        Node<T>* min = node->right;
        while (min->left != nullptr) {
            min = min->left;
        }
        return min;
    }

    Node<T>* getLeftMin(Node<T> *node) {
        Node<T>* min = node->left;
        while (min->right != nullptr) {
            min = min->right;
        }
        return min;
    }

    Node<T>* replace(Node<T> *to_replace) {
        if (to_replace->left == nullptr && to_replace->right == nullptr) {
            return;
        }
        Node<T> *min = nullptr;
        if (to_replace->left == nullptr) {
            min = getRightMin(to_replace);
            min->parent->left = to_replace;
        } else {
            min = getLeftMin(to_replace);
            min->parent->right = to_replace;
        }
        min->left = to_replace->left;
        min->right = to_replace->right;
        to_replace->left = nullptr;
        to_replace->right = nullptr;
        if (this->root == to_replace) {
            root = min;
        } else if (to_replace->parent->left == to_replace) {
            to_replace->parent->left = min;
        } else {
            to_replace->parent->right = min;
        }
        return min;
    }

public:
    void insert(T &t) {
        Node<T> node = Node<T>(t);
        node.isRed = true;
        append(node, root);
    }
};
