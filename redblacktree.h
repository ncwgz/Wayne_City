//
// Created by wangguozhi on 2019-11-23.
//

#include <cstdlib>

#ifndef WAYNE_CITY_MYREDBLACKTREE_H
#define WAYNE_CITY_MYREDBLACKTREE_H

#endif //WAYNE_CITY_MYREDBLACKTREE_H

template <class K, class V>
class Node {
public:
    bool isRed;
    Node<K, V> *parent;
    Node<K, V> *left;
    Node<K, V> *right;
    K key;
    V value;

    Node (K key, V value) {
        this->key = key;
        this->value = value;
        this->isRed = true;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }
};

template <class K, class V>
class RedBlackTree {
private:
    Node<K, V> *root;

    void leftRotate(Node<K, V> *node) {
        Node<K, V> *right = node->right;
        node->right = right->left;
        if (right->left != nullptr) {
            right->left->parent = node;
        }
        if (root != node) {
            if (node == node->parent->right) {
                node->parent->right = right;
            } else {
                node->parent->left = right;
            }
            right->parent = node->parent;
        } else {
            root = right;
            root->isRed = false;
            node->isRed = true;
            right->parent = nullptr;
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
        if (root != node) {
            if (node == node->parent->left) {
                node->parent->left = left;
            } else {
                node->parent->right = left;
            }
            left->parent = node->parent;
        } else {
            root = left;
            root->isRed = false;
            node->isRed = true;
            left->parent = nullptr;
        }
        left->right = node;
        node->parent = left;
    }

    void appendFix(Node<K, V> *node) {
        while (root != node && node->parent->isRed) {
            if (node->parent == node->parent->parent->left) {
                // Color-change
                if (node->parent->parent->right != nullptr && node->parent->parent->right->isRed) {
                    node->parent->isRed = false;
                    node->parent->parent->right->isRed = false;
                    node->parent->parent->isRed = true;
                    root->isRed = false;
                    node = node->parent->parent;
                }
                // LL-Rotate
                else if (node == node->parent->left) {
                    node->parent->isRed = false;
                    node->parent->parent->isRed = true;
                    root->isRed = false;
                    rightRotate(node->parent->parent);
                }
                // LR-Rotate
                else {
                    node->isRed = false;
                    node->parent->parent->isRed = true;
                    root->isRed = false;
                    leftRotate(node->parent);
                    rightRotate(node->parent);
                }
            }
            else {
                // Color-change
                if (node->parent->parent->left != nullptr && node->parent->parent->left->isRed) {
                    node->parent->isRed = false;
                    node->parent->parent->left->isRed = false;
                    node->parent->parent->isRed = true;
                    root->isRed = false;
                    node = node->parent->parent;
                }
                // RR-Rotate
                else if (node == node->parent->right) {
                    node->parent->isRed = false;
                    node->parent->parent->isRed = true;
                    root->isRed = false;
                    leftRotate(node->parent->parent);
                }
                // RL-Rotate
                else {
                    node->isRed = false;
                    node->parent->parent->isRed = true;
                    root->isRed = false;
                    rightRotate(node->parent);
                    leftRotate(node->parent);
                }
            }
        }
    }

    void append(Node<K, V> *node, Node<K, V> *parent) {
        if (root == nullptr) {
            node->isRed = false;
            root = node;
            return;
        }
        if (node->key < parent->key) {
            if (parent->left == nullptr) {
                parent->left = node;
                node->parent = parent;
                appendFix(node);
            } else {
                append(node, parent->left);
            }
        }
        else if (node->key > parent->key) {
            if (parent->right == nullptr) {
                parent->right = node;
                node->parent = parent;
                appendFix(node);
            } else {
                append(node, parent->right);
            }
        } else {
            exit(0);
        }
    }

    Node<K, V>* minimum(Node<K, V> *node) {
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    Node<K, V>* maximum(Node<K, V> *node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    void replace(Node<K, V> *A, Node<K, V> *B) {
        bool OriginalColorOfA = A->isRed;
        A->isRed = B->isRed;
        B->isRed = OriginalColorOfA;
        Node<K, V> *tmp;
        if (A->left == B) {
            tmp = A->right;
            A->right = B->right;
            if (A->right != nullptr) A->right->parent = A;
            B->right = tmp;
            if (B->right != nullptr) B->right->parent = A;

            A->left = B->left;
            if (A->left != nullptr) A->left->parent = A;
            B->left = A;

            B->parent = A->parent;
            if (root != A) {
                if (A == A->parent->left) A->parent->left = B;
                else A->parent->right = B;
                A->parent = B;
            } else {
                A->parent = B;
                B->parent = nullptr;
                root = B;
            }
        }
        else if (A->right == B) {
            tmp = A->left;
            A->left = B->left;
            if (A->left != nullptr) A->left->parent = A;
            B->left = tmp;
            if (B->left != nullptr) B->left->parent = B;

            A->right = B->right;
            if (A->right != nullptr) A->right->parent = A;
            B->right = A;

            B->parent = A->parent;
            if (root != A) {
                if (A == A->parent->left) A->parent->left = B;
                else A->parent->right = B;
                A->parent = B;
            } else {
                A->parent = B;
                B->parent = nullptr;
                root = B;
            }
        } else {
            tmp = A->left;
            A->left = B->left;
            if (A->left != nullptr) A->left->parent = A;
            B->left = tmp;
            if (B->left != nullptr) B->left->parent = B;

            tmp = A->right;
            A->right = B->right;
            if (A->right != nullptr) A->right->parent = A;
            B->right = tmp;
            if (B->right != nullptr) B->right->parent = B;

            if (root != A && root != B) {
                tmp = A->parent;
                A->parent = B->parent;
                if (B == B->parent->left) B->parent->left = A;
                else B->parent->right = A;
                B->parent = tmp;
                if (A == tmp->left) tmp->left = B;
                else tmp->right = B;
            } else {
                if (root == A) {
                    A->parent = B->parent;
                    if (B == B->parent->left) B->parent->left = A;
                    else B->parent->right = A;
                    B->parent = nullptr;
                    root = B;
                } else {
                    B->parent = A->parent;
                    if (A == A->parent->left) A->parent->left = B;
                    else A->parent->right = B;
                    A->parent = nullptr;
                    root = A;
                }
            }
        }
    }

    void removeFix(Node<K, V> *parent, Node<K, V> *deficient) {
        // Change color
        if (deficient != nullptr && deficient->isRed) {
            deficient->isRed = false;
        } else {
            Node<K, V> *cousin;
            // L**
            if (parent->left == deficient) {
                cousin = parent->right;
                // Lb*
                if (cousin != nullptr && !cousin->isRed) {
                    // Lb0 (both cases)
                    if ((cousin->left == nullptr || !cousin->left->isRed)
                    && (cousin->right == nullptr || !cousin->right->isRed)) {
                        parent->isRed = false;
                        cousin->isRed = true;
                    }
                    // Lb1-right
                    else if ((cousin->left == nullptr || !cousin->left->isRed)
                         && (cousin->right != nullptr && cousin->right->isRed)) {
                        cousin->right->isRed = false;
                        cousin->isRed = parent->isRed;
                        parent->isRed = false;
                        leftRotate(parent);
                    }
                    // Lb1-left, Lb2
                    else if (cousin->left != nullptr && cousin->left->isRed) {
                        cousin->left->isRed = parent->isRed;
                        parent->isRed = false;
                        rightRotate(cousin);
                        leftRotate(cousin->parent);
                    }
                }
                // Lr(*)
                else if (cousin != nullptr) {
                    // Lr(0)
                    if (cousin->left == nullptr
                    || ((cousin->left->left == nullptr || !cousin->left->left->isRed)
                    && (cousin->left->right == nullptr || !cousin->left->right->isRed))) {
                        cousin->isRed = false;
                        if (cousin->left != nullptr) {
                            cousin->left->isRed = true;
                        }
                        leftRotate(parent);
                    }
                    Node<K, V> *child = cousin->left;
                    if (child != nullptr) {
                        // Lr(1)-right
                        if ((child->right != nullptr && child->right->isRed)
                        && (child->left == nullptr || !child->left->isRed)) {
                            child->right->isRed = false;
                            rightRotate(cousin);
                            leftRotate(child);
                        }
                        // Lr(1)-left, Lr(2)
                        else if (child->left != nullptr && child->left->isRed) {
                            child->left->isRed = false;
                            rightRotate(child);
                            rightRotate(cousin);
                            leftRotate(cousin->parent);
                        }
                    }
                }
            }
            // R**
            else {
                cousin = parent->left;
                // Rb*
                if (cousin!= nullptr && !cousin->isRed) {
                    // Rb0 (both cases)
                    if ((cousin->left == nullptr || !cousin->left->isRed)
                        && (cousin->right == nullptr || !cousin->right->isRed)) {
                        parent->isRed = false;
                        cousin->isRed = true;
                    }
                    // Rb1-left
                    else if ((cousin->left != nullptr && cousin->left->isRed)
                         && (cousin->right == nullptr || !cousin->right->isRed)) {
                        cousin->left->isRed = false;
                        cousin->isRed = parent->isRed;
                        parent->isRed = false;
                        rightRotate(parent);
                    }
                    // Rb1-right, Rb2
                    else if (cousin->right != nullptr && cousin->right->isRed) {
                        cousin->right->isRed = parent->isRed;
                        parent->isRed = false;
                        leftRotate(cousin);
                        rightRotate(cousin->parent);
                    }
                }
                // Rr(*)
                else {
                    // Rr(0)
                    if (cousin->right == nullptr
                    || ((cousin->right->left == nullptr || !cousin->right->left->isRed)
                    && (cousin->right->right == nullptr || !cousin->right->right->isRed))) {
                        cousin->isRed = false;
                        if (cousin->right != nullptr) {
                            cousin->right->isRed = true;
                        }
                        rightRotate(parent);
                    }
                    Node<K, V> *child = cousin->right;
                    if (child != nullptr) {
                        // Rr(1)-left
                        if ((child->left != nullptr && child->left->isRed)
                        && (child->right == nullptr || !child->right->isRed)) {
                            child->left->isRed = false;
                            leftRotate(cousin);
                            rightRotate(child);
                        }
                        // Rr(1)-right, Rr(2)
                        else if (child->right != nullptr && child->right->isRed) {
                            child->right->isRed = false;
                            leftRotate(child);
                            leftRotate(cousin);
                            rightRotate(cousin->parent);
                        }
                    }
                }
            }
        }
    }

    void remove(Node<K, V> *node) {
        Node<K, V> *toReplace;
        if (node->left != nullptr && node->right != nullptr) {
            if (node->left != nullptr) {
                toReplace = maximum(node->left);
            }
            else if (node->right != nullptr) {
                toReplace = minimum(node->right);
            }
            replace(node, toReplace);
        }

        Node<K, V> *deficient;
        Node<K, V> *parent;
        if (root == node) {
            if (root->left != nullptr) {
                root = root->left;
                root->parent = nullptr;
            } else if (root->right != nullptr) {
                root = root->right;
                root->parent = nullptr;
            } else {
                root = nullptr;
            }
            delete(node);
        } else {
            parent = node->parent;
            if (node == node->parent->left) {
                if (node->left != nullptr) {
                    deficient = node->left;
                    node->left->parent = node->parent;
                    node->parent->left = node->left;
                } else if (node->right != nullptr) {
                    deficient = node->right;
                    node->right->parent = node->parent;
                    node->parent->left = node->right;
                } else {
                    node->parent->left = nullptr;
                    deficient = nullptr;
                }
            } else {
                if (node->left != nullptr) {
                    deficient = node->left;
                    node->left->parent = node->parent;
                    node->parent->right = node->left;
                } else if (node->right != nullptr) {
                    deficient = node->right;
                    node->right->parent = node->parent;
                    node->parent->right = node->right;
                } else {
                    node->parent->right = nullptr;
                    deficient = nullptr;
                }
            }
            delete(node);
            removeFix(parent, deficient);
        }
    }

    Node<K, V>* getNodeByKey(K key) {
        Node<K, V> *node = root;
        while (node != nullptr) {
            if (key < node->key) {
                node = node->left;
            }
            else if (key > node->key) {
                node = node->right;
            } else {
                return node;
            }
        }
        return nullptr;
    }

    void getRange(K min, K max, Node<K, V> *node, std::vector<V> &v) {
        if (node == nullptr) {
            return;
        }
        else if (node->key >= min && node->key <= max) {
            getRange(min, max, node->left, v);
            v.push_back(node->value);
            getRange(min, max, node->right, v);
        }
        else if (node->key > max) {
            getRange(min, max, node->left, v);
        }
        else if (node->key < min) {
            getRange(min, max, node->right, v);
        }
    }

public:
    RedBlackTree() {
        this->root = nullptr;
    }

    void insert(K key, V value) {
        Node<K, V> *node = new Node<K, V>(key, value);
        append(node, root);
    }

    void remove(K key) {
        remove(getNodeByKey(key));
    }

    V getValueByKey(K key) {
        Node<K, V>* node = getNodeByKey(key);
        if (node != nullptr) {
            return node->value;
        }
        return V();
    }

    std::vector<V> getValuesByRange(K min, K max) {
        std::vector<V> v;
        if (min > max) {
            v.push_back(V());
            return v;
        }
        getRange(min, max, root, v);
        if (v.size() == 0) {
            v.push_back(V());
        }
        return v;
    }

    void update(K key, V value) {
        Node<K, V> *node = getNodeByKey(key);
        node->value = value;
    }
};