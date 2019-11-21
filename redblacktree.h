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
        if (root != node) {
            Node<K, V> *parent = node->parent;
            parent->left = left;
            left->parent = parent;
        }

        node->left = left->right;
        if (left->right != nullptr) {
            node->left->parent = node;
        }

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
        // Node to fix is root.
        if (root == toFix) {
            if (toFix->left != nullptr) {
                root = toFix->left;
            } else if (toFix->right != nullptr) {
                root = toFix->right;
            } else {
                root = nullptr;
            }
            delete toFix;
            rootRedCheck();
        }
        // No rebalancing needed.
        else if (toFix->isRed) {
            // No subtrees, just delete.
            if (toFix->left == nullptr && toFix->right == nullptr) {
                if (toFix == toFix->parent->left) {
                    toFix->parent->left = nullptr;
                } else {
                    toFix->parent->right = nullptr;
                }
            }
            // A left subtree exists.
            else if (toFix->left != nullptr) {
                if (toFix == toFix->parent->left) {
                    toFix->parent->left = toFix->left;
                } else {
                    toFix->parent->right = toFix->left;
                }
                toFix->left->parent = toFix->parent;
            }
            // A right subtree exists.
            else if (toFix->right != nullptr) {
                if (toFix == toFix->parent->left) {
                    toFix->parent->left = toFix->right;
                } else {
                    toFix->parent->right = toFix->right;
                }
                toFix->right->parent = toFix->parent;
            }
            delete (toFix);
        }
        // Node to fix is black, need rebalancing.
        else {
            // Node to fix is the left of its parent.
            if (toFix == toFix->parent->left) {
                Node<K, V> *cousin = toFix->parent->right;
                // Left subtree is deficient.
                if (toFix->left != nullptr) {
                    toFix->parent->left = toFix->left;
                    toFix->left->parent = toFix->parent;
                    delete(toFix);
                    // Left subtree is red, turn it into black.
                    if (toFix->left->isRed) {
                        toFix->left->isRed = false;
                    }
                    // The deficient subtree is black.
                    else {

                    }
                }
                // Right subtree is deficient.
                else {
                    Node<K, V> node = toFix->right;
                    toFix->parent->left = node;
                    node->parent = toFix->parent;
                    delete(toFix);
                    // Right subtree is red, turn it into black.
                    if (node->isRed) {
                        node->isRed = false;
                    }
                    // The deficient subtree is black.
                    else {

                    }
                }
            }
            // Node to fix is right of its parent.
            else {

                Node<K, V> *cousin = toFix->parent->left;
                // Left subtree is deficient.
                if (toFix->left != nullptr) {
                    Node<K, V> node = toFix->left;
                    toFix->parent->right = node;
                    node->parent = toFix->parent;
                    delete(toFix);
                    // Left subtree is red, turn it into black.
                    if (node->isRed) {
                        node->isRed = false;
                    }
                    // The deficient subtree is black.
                    else {
                        if (!cousin->isRed) {
                            if ((cousin->left == nullptr || !cousin->left->isRed)
                                && (cousin->right == nullptr || !cousin->right->isRed)) {
                                cousin->isRed = true;
                                if (node.parent->isRed) {
                                    node.parent->isRed = false;
                                    cousin->isRed = true;
                                }
                            } else if (cousin->right != nullptr && cousin->right->isRed) {
                                leftRotate(cousin);
                                rightRotate(node.parent);
                                cousin->isRed = node.parent->isRed;
                                node.parent->isRed = false;
                            } else if (cousin->left != nullptr && cousin->left->isRed) {
                                rightRotate(node.parent);
                                cousin->left->isRed = false;
                                cousin->isRed = node.parent->isRed;
                                node.parent->isRed = false;
                            }
                        }
                        else {
                            Node<K, V> *cRight = cousin->right;
                                if (cRight == nullptr) {
                                    rightRotate(node.parent);
                                    cousin->isRed = false;
                                }
                                else if ((cRight->left == nullptr || !cRight->left->isRed)
                                || (cRight->right == nullptr || !cRight->right->isRed)) {
                                    rightRotate(node.parent);
                                    cousin->isRed = false;
                                    cRight->isRed = true;
                                } else if ()
                        }
                    }
                }
                // Right subtree is deficient.
                else {
                    Node<K, V> node = toFix->right;
                    toFix->parent->right = node;
                    node->parent = toFix->parent;
                    delete(toFix);
                    // Right subtree is red, turn it into black.
                    if (node->isRed) {
                        node->isRed = false;
                    }
                    // The deficient subtree is black.
                    else {

                    }
                }
            }
        }
    }

    void printTree() {
        printNode(root);
    }
};
