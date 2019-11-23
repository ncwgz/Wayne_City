//
// Created by wangguozhi on 2019-11-21.
//

#include <iostream>
#include <iomanip>

#ifndef WAYNE_CITY_REDBLACKTREE_H
#define WAYNE_CITY_REDBLACKTREE_H

#endif //WAYNE_CITY_REDBLACKTREE_H

template <class K, class V>
class Node {
public:
    bool isRed = false;
    Node<K, V> *left = nullptr;
    Node<K, V> *right = nullptr;
    Node<K ,V> *parent = nullptr;
    K key;
    V value;

    Node(K key, V value) {
        this->key = key;
        this->value = value;
        this->isRed = true;
    }
};

template <class K, class V>
class RedBlackTree {
private:
    Node<K, V> *root = nullptr;

    Node<K, V>* getNodeByKey(K key, Node<K, V> *node) {
        while( node != nullptr && node->key != key) {
            if (key < node->key) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return node;
    }

    Node<K, V>* min(Node<K, V> *tree) {
        if (tree == nullptr) {
            return nullptr;
        }
        while (tree->left != nullptr) {
            tree = tree->left;
        }
        return tree;
    }

    Node<K, V>* max(Node<K, V> *tree) {
        if (tree == nullptr) {
            return nullptr;
        }
        while (tree->right != nullptr) {
            tree = tree->right;
        }
    }

    Node<K, V>* successor(Node<K, V> *node) {
        if (node->right != nullptr) {
            return min(node->right);
        }
        Node<K, V> *parent = node->parent;
        while (parent != nullptr && node == parent->right) {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }

    Node<K, V>* predecessor(Node<K, V> *node) {
        if (node->left != nullptr) {
            return max(node->left);
        }
        Node<K, V> *parent = node->parent;
        while (parent != nullptr && node == parent->left) {
            node = node->parent;
            parent = parent->parent;
        }
        return parent;
    }

    void leftRotate(Node<K, V> *node) {
        Node<K, V> *right = node->right;
        node->right = right->left;
        if (right->left != nullptr) {
            right->left->parent = node;
        }
        right->parent = node->parent;
        if (root = node->parent) {
            root = right;
        } else {
            if (node->parent->left = node) {
                node->parent->left = right;
            } else {
                node->parent->right = right;
            }
        }
        right->left = node;
        node->parent = right;
    }

    void rightRotate(Node<K, V> *node) {
        Node<K, V> *left = node->left;
        node->left = left->right;
        if (left->right != nullptr) {
            left->right->parent = node;
        }
        left->parent = node->parent;
        if (root = node) {
            root = left;
        } else {
            if (node == node->parent->right) {
                node->parent->right = left;
            } else {
                node->parent->left = left;
            }
        }
    }

    void insertFix(Node<K, V> *node) {
        Node<K, V> *parent, *grandparent;
        while ((parent == node->parent) && parent->isRed) {
            grandparent = parent->parent;
            if (parent == grandparent->left) {
                Node<K, V> *uncle = grandparent->right;
                if (uncle && uncle->isRed) {
                    uncle->isRed = false;
                    parent->isRed = false;
                    grandparent->isRed = true;
                    node = grandparent;
                    continue;
                }
                if (parent->right == node) {
                    Node<K, V> *temp;
                    leftRotate(parent);
                    temp = parent;
                    parent = node;
                    node = temp;
                }
                parent->isRed = false;
                grandparent->isRed = true;
                rightRotate(grandparent);
            } else {
                Node<K, V> *uncle = grandparent->left;
                if (uncle && uncle->isRed) {
                    uncle->isRed = false;
                    parent->isRed = false;
                    grandparent->isRed = true;
                    node = grandparent;
                    continue;
                }
                if (parent->left == node){
                    Node<K, V> *temp;
                    rightRotate(parent);
                    temp = parent;
                    parent = node;
                    node = temp;
                }
                parent->isRed = false;
                grandparent->isRed = true;
                leftRotate(grandparent);
            }
        }
        root->isRed = false;
    }

    void insert(Node<K, V> *node, Node<K, V> *parent) {
        Node<K, V> *y = nullptr;
        while (parent != nullptr) {
            y = parent;
            if (node->key < parent->key) {
                parent = parent->left;
            } else if (node->key > parent->key) {
                parent = parent->right;
            } else {
                exit(0);
            }
        }
        node->parent = y;
        if (y != nullptr) {
            if (node->key < y->key) {
                y->left = node;
            } else {
                y->right = node;
            }
        } else {
            root = node;
        }
        insertFix(node);
    }

    void removeFix(Node<K, V> *node, Node<K, V> *parent) {
        Node<K, V> *cousin;
        while ((!node || !node->isRed) && root != node) {
            if (parent->left == node) {
                cousin = parent->right;
                if (cousin->isRed) {
                    cousin->isRed = false;
                    parent->isRed = true;
                    leftRotate(parent);
                    cousin = parent->right;
                }
                if ((!cousin->left || !cousin->left->isRed)
                && (!cousin->right || !cousin->right->isRed)) {
                    cousin->isRed = true;
                    node = parent;
                    parent = node->parent;
                } else {
                    if (!cousin->right || !cousin->right->isRed) {
                        cousin->left->isRed = false;
                        cousin->isRed = true;
                        rightRotate(cousin);
                        cousin = parent->right;
                    }
                    cousin->isRed = parent->isRed;
                    parent->isRed = false;
                    cousin->right->isRed = false;
                    leftRotate(parent);
                    node = root;
                    break;
                }
            } else {
                cousin = parent->left;
                if (cousin->isRed) {
                    cousin->isRed = false;
                    parent->isRed = true;
                    rightRotate(parent);
                    cousin = parent->left;
                }
                if ((!cousin->left || !cousin->left->isRed)
                &&(!cousin->right || !cousin->right->isRed)) {
                    cousin->isRed = true;
                    node = parent;
                    parent = node->parent;
                } else {
                    if (!cousin->left || !cousin->left->isRed) {
                        cousin->right->isRed = false;
                        cousin->isRed = true;
                        leftRotate(cousin);
                        cousin = parent->left;
                    }
                    cousin->isRed = parent->isRed;
                    parent->isRed = false;
                    cousin->left->isRed = false;
                    rightRotate(parent);
                    node = root;
                    break;
                }
            }
        }
        if (node) {
            node->isRed = false;
        }
    }
    
    void remove(Node<K, V> *node) {
        Node<K, V> *child, *parent;
        bool originalColor;
        
        if (node->left != nullptr && node->right != nullptr) {
            Node<K, V> *toReplace = node;
            toReplace = toReplace->right;
            while (toReplace->left != nullptr) {
                toReplace = toReplace->left;
            }
            if (root != node) {
                if (node->parent->left == node) {
                    node->parent->left = toReplace;
                } else {
                    node->parent->right = toReplace;
                }
            } else {
                root = toReplace;
            }
            child = toReplace->right;
            parent = toReplace->parent;
            originalColor = toReplace->isRed;
            if (parent == node) {
                parent = toReplace;
            } else {
                if (child) {
                    child->parent = parent;
                }
                parent->left = child;
                toReplace->right = node->right;
                node->right->parent = toReplace;
            }
            toReplace->parent = node->parent;
            toReplace->isRed = node->isRed;
            toReplace->left = node->left;
            node->left->parent = toReplace;

            if(!originalColor) {
                removeFix(child, parent);
            }
            delete node;
            return;
        }
        if (node->left != nullptr) {
            child = node->left;
        } else {
            child = node->right;
        }
        parent = node->parent;
        originalColor = node->isRed;
        if (child) {
            child->parent = parent;
        }
        if (parent) {
            if (parent->left == node) {
                parent->left = child;
            } else {
                parent->right = child;
            }
        } else {
            root = child;
        }
        if (!originalColor) {
            removeFix(child, parent);
        }
        delete node;
    }

public:

    RedBlackTree() {

    }

    V getValueByKey(K key) {
        Node<K, V> *node = getNodeByKey(key, root);
        if (node != nullptr) {
            return node->value;
        } else {
            return nullptr;
        }
    }

    void insert(K key, V value) {
        Node<K, V> *node = new Node<K, V>(key, value);
        insert(node, root);
    }

    void remove(K key) {
        Node<K, V> *node = getNodeByKey(key, root);
        remove(node);
    }

    void update(K key, V value) {
        Node<K, V> *node = getNodeByKey(key, root);
        node->value = value;
    }
};