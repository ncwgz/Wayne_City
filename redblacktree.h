//
// Created by wangguozhi on 2019-11-14.
//

#include <iostream>

#ifndef WAYNE_CITY_REDBLACKTREE_H
#define WAYNE_CITY_REDBLACKTREE_H

#endif //WAYNE_CITY_REDBLACKTREE_H

template <class K, class V>
class Node {
private:

public:
    Node *parent = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;
    bool isRed = false;
    K key;
    V value;
    Node(K key, V value) {
        this->key = key;
        this->value = value;
    }
    Node() {
        this->key = NULL;
        this->value = NULL;
    }
};

template <class K, class V>
class RedBlackTree {
private:

    /*
     * Left Rotate:
     *      N                  R
     *    NL  R`     =>      N` RR`
     *      RL RR`         NL RL
     */
    void leftRotate(Node<K, V> *node) {
        Node<K, V> *right = node->right;
        if (root != node) {
            Node<K, V> *parent = node->parent;
            parent->right = right;
            right->parent = parent;
        }

        node->right = right->left;
        if (right->left != nullptr) {
            node->right->parent = node;
        }

        right->left = node;
        node->parent = right;

        if (root == node) {
            root = right;
        }
    }

    /*
     * Right Rotate:
     *       N                  L
     *    `L  NR      =>     `LL `N
     *  `LL LR                  LR NR
     */
    void rightRotate(Node<K, V> *node) {
        Node<K, V> *left = node->left;
        Node<K, V> *parent = node->parent;

        node->left = left->right;
        if (left->right != nullptr) {
            node->left->parent = node;
        }

        parent->left = left;
        left->parent = parent;

        left->right = node;
        node->parent = left;

        if (root == node) {
            root = left;
        }
    }

    void append(Node<K, V> *to_append, Node<K, V> *parent) {
        if (root == nullptr) {
            root = to_append;
            insertFix(to_append);
        } else {
            if (parent->key > to_append->key) {
                if (parent->left == nullptr) {
                    parent->left = to_append;
                    to_append->parent = parent;
                    insertFix(to_append);
                } else {
                    append(to_append, parent->left);
                }
            } else {
                if (parent->right == nullptr) {
                    parent->right = to_append;
                    to_append->parent = parent;
                    insertFix(to_append);
                } else {
                    append(to_append, parent->right);
                }
            }
        }
    }

    void rootRedCheck() {
        if (this->root->isRed) {
            this->root->isRed = false;
        }
    }

    void insertFix(Node<K, V> *node) {
        if (node == root) {
            node->isRed = false;
            return;
        }
        // Two continuous red nodes
        while (node->parent->isRed) {
            if (node->parent == node->parent->parent->left) {
                // The color-change case
                if (node->parent->parent->right != nullptr && node->parent->parent->right->isRed) {
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
                if (node->parent->parent->left != nullptr && node->parent->parent->left->isRed) {
                    node->parent->isRed = false;
                    node->parent->parent->left->isRed = false;
                    node->parent->parent->isRed = true;
                    node = node->parent->parent;
                    rootRedCheck();
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

    Node<K, V>* getRightMin(Node<K, V> *node) {
        Node<K, V>* min = node->right;
        while (min->left != nullptr) {
            min = min->left;
        }
        return min;
    }

    Node<K, V>* getLeftMin(Node<K, V> *node) {
        Node<K, V>* min = node->left;
        while (min->right != nullptr) {
            min = min->right;
        }
        return min;
    }

    Node<K, V>* getNodeByKey(K key) {
        Node<K, V> *node = root;
        while (true) {
            if (node == nullptr) {
                return nullptr;
            }
            if (node->key == key) {
                return node;
            } else if (node->key < key) {
                node = node->right;
            } else {
                node = node->left;
            }
        }
    }

    Node<K, V>* replace(K key) {
        Node<K, V> * to_replace = this->getNodeByKey(key);
        if (to_replace->left == nullptr && to_replace->right == nullptr) {
            return to_replace;
        }
        Node<K, V> *min = nullptr;
        bool isToFixLeft = true;
        if (to_replace->left == nullptr) {
            min = getRightMin(to_replace);
            min->parent->left = to_replace;
            isToFixLeft = false;
        } else {
            min = getLeftMin(to_replace);
            min->parent->right = to_replace;
            isToFixLeft = true;
        }
        bool originalNodeColor = to_replace->isRed;
        bool originalMinColor = min->isRed;

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

        to_replace->isRed = originalMinColor;
        min->isRed = originalNodeColor;

        if (isToFixLeft) {
            return min->left;
        } else {
            return min;
        }
    }

    void printNode(Node<K, V> *node) {
        if (node->left != nullptr) {
            printNode(node->left);
        }
        std::cout<<'('<<node->key<<','<<node->value<<')';
        if (node->isRed) {
            std::cout<<'R'<<std::endl;
        } else {
            std::cout<<'B'<<std::endl;
        }
        if (node->right != nullptr) {
            printNode(node->right);
        }
    }

public:
    Node<K, V> *root = nullptr;

    void insert(K key, V value) {
        Node<K, V> *node = new Node<K, V>(key, value);
        node->isRed = true;
        append(node, root);
    }

    V getValueByKey(K &key) {
        Node<K, V> node = getNodeByKey(key);
        return node.value;
    }

    void search(K &kLeft, K &kRight) {

    }

    void remove(K key) {
        Node<K, V> *toFix = replace(key);
        if (toFix->left == nullptr && toFix->right == nullptr) {
            if (toFix->parent->left == toFix) {
                toFix->parent->left = nullptr;
            } else {
                toFix->parent->right = nullptr;
            }
            delete toFix;
        }
        if (toFix->parent->isRed == false) {
            while (toFix->isRed == false && toFix != root) {
                if (toFix == toFix->parent->left) {
                    Node<K, V> *cousin = toFix->parent->right;
                    if (cousin->isRed) {
                        cousin->isRed = false;
                        toFix->parent->isRed = true;
                        leftRotate(toFix->parent);
                        cousin = toFix->parent->right;
                    }
                    if (cousin->left->isRed == false && cousin->right->isRed == false) {
                        cousin->isRed = true;
                        toFix = toFix->parent;
                    } else if (cousin->right->isRed == false) {
                        cousin->left->isRed = false;
                        cousin->isRed = true;
                        rightRotate(cousin);
                        cousin = toFix->parent->right;
                    }
                    cousin->isRed = toFix->parent->isRed;
                    toFix->parent->isRed = false;
                    cousin->right->isRed = false;
                    leftRotate(toFix->parent);
                    toFix = root;
                } else {
                    Node<K, V> *cousin = toFix->parent->left;
                    if (cousin->isRed) {
                        cousin->isRed = false;
                        toFix->parent->isRed = true;
                        rightRotate(toFix->parent);
                        cousin = toFix->parent->left;
                    }
                    if (cousin->right->isRed == false && cousin->left->isRed == false) {
                        cousin->isRed = true;
                        toFix = toFix->parent;
                    } else if (cousin->left->isRed == false) {
                        cousin->right->isRed = false;
                        cousin->isRed = true;
                        leftRotate(cousin);
                        cousin = toFix->parent->left;
                    }
                    cousin->isRed = toFix->parent->isRed;
                    toFix->parent->isRed = false;
                    cousin->left->isRed = false;
                    rightRotate(toFix->parent);
                    toFix = root;
                }
            }
            toFix->isRed = false;
        }
    }

    void printTree() {
        printNode(root);
    }
};
