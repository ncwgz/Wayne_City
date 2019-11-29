//
// Created by wangguozhi on 2019-11-23.
//

#include <cstdlib>

using namespace std;

#ifndef WAYNE_CITY_MYREDBLACKTREE_H
#define WAYNE_CITY_MYREDBLACKTREE_H

#endif //WAYNE_CITY_MYREDBLACKTREE_H

template<class K, class V>
class Node {
public:
    bool isRed; // 1 - Red, 0 - Black
    Node<K, V> *parent; // The pointer to its parent
    Node<K, V> *left; // The pointer to its left child
    Node<K, V> *right; // The pointer to its right child
    K key; // The key of the node. The tree uses this key to maintain order
    V value; // The value of the node

    // Construct a node with given key value pair
    Node(K key, V value) {
        this->key = key;
        this->value = value;
        this->isRed = true;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }

    // Construct a void node
    Node() {

    }
};

template<class K, class V>
class RedBlackTree {
private:
    Node<K, V> *root; // The pointer to the root node

    /*
     *    N             R
     *  Nl  R   ==>   N  Rr
     *    Rl Rr     Nl Nr
     */
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

    /*
     *       N              L
     *     L  Nr   ==>   Ll  N
     *   Ll Lr             Lr Nr
     */
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
    // Fix the tree after a node inserted
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
                    leftRotate(node->parent);
                    rightRotate(node->parent);
                    root->isRed = false;
                }
            } else {
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
                    rightRotate(node->parent);
                    leftRotate(node->parent);
                    root->isRed = false;
                }
            }
        }
    }
    // Append a node to the parent as a child
    void append(Node<K, V> *node, Node<K, V> *parent) {
        // If the tree is empty, make the node as root
        if (root == nullptr) {
            node->isRed = false;
            root = node;
            return;
        }
        // If the node has a key smaller than the parent's,
        if (node->key < parent->key) {
            // Parent has no left child, append the node here
            if (parent->left == nullptr) {
                parent->left = node;
                node->parent = parent;
                appendFix(node);
            }
            // Recursively append the node to the parent's left
            else {
                append(node, parent->left);
            }
        }
        // Symmetric as above
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
    // Get the right most node of node
    Node<K, V> *rightMost(Node<K, V> *node) {
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }
    // Get the left most node of node
    Node<K, V> *leftMost(Node<K, V> *node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    // Replace the node A with node B
    void replace(Node<K, V> *A, Node<K, V> *B) {
        // Replace color
        bool OriginalColorOfA = A->isRed;
        A->isRed = B->isRed;
        B->isRed = OriginalColorOfA;

        Node<K, V> *tmp;
        // B is the left child of A
        if (A->left == B) {
            // Replace right
            tmp = &*A->right;
            A->right = B->right;
            if (A->right != nullptr) A->right->parent = A;
            B->right = tmp;
            if (B->right != nullptr) B->right->parent = B;
            // Replace left
            A->left = B->left;
            if (A->left != nullptr) A->left->parent = A;
            B->left = A;
            // Replace parent
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
        // Symmetric as above
        else if (A->right == B) {
            tmp = &*A->left;
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
        }
        // A and B are not adjacent
        else {
            // Replace left
            tmp = &*A->left;
            A->left = B->left;
            if (A->left != nullptr) A->left->parent = A;
            B->left = tmp;
            if (B->left != nullptr) B->left->parent = B;
            // Replace right
            tmp = &*A->right;
            A->right = B->right;
            if (A->right != nullptr) A->right->parent = A;
            B->right = tmp;
            if (B->right != nullptr) B->right->parent = B;
            // Replace parent
            // If A and B are both not root
            if (root != A && root != B) {
                tmp = &*A->parent;
                A->parent = B->parent;
                if (B == B->parent->left) B->parent->left = A;
                else B->parent->right = A;
                B->parent = tmp;
                if (A == tmp->left) tmp->left = B;
                else tmp->right = B;
            }
            else {
                // A is root
                if (root == A) {
                    A->parent = B->parent;
                    if (B == B->parent->left) B->parent->left = A;
                    else B->parent->right = A;
                    B->parent = nullptr;
                    root = B;
                }
                // B is root
                else {
                    B->parent = A->parent;
                    if (A == A->parent->left) A->parent->left = B;
                    else A->parent->right = B;
                    A->parent = nullptr;
                    root = A;
                }
            }
        }
    }
    // Fix the tree after a node removed
    void removeFix(Node<K, V> *parent, Node<K, V> *deficient) {
        // Change color
        if (deficient == root) {
            return;
        }
        if (deficient != nullptr && deficient->isRed) {
            deficient->isRed = false;
            return;
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
                        cousin->isRed = true;
                        if (parent->isRed == false) {
                            removeFix(parent->parent, parent);
                        } else {
                            parent->isRed = false;
                        }
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
                        leftRotate(parent);
                    }
                }
                // Lr(*)
                else if (cousin != nullptr) {
                    // Lr(0)
                    if ((cousin->right == nullptr || !cousin->right->isRed)
                        && ((cousin->left == nullptr)
                            || ((cousin->left->left == nullptr || !cousin->left->left->isRed)
                                && (cousin->left->right == nullptr || !cousin->left->right->isRed)))) {
                        if (cousin->left != nullptr) {
                            cousin->left->isRed = true;
                        }
                        leftRotate(parent);
                    } else {
                        Node<K, V> *child = cousin->left;
                        if (child != nullptr) {
                            // Lr(1)-right
                            if ((child->right != nullptr && child->right->isRed)
                                && (child->left == nullptr || !child->left->isRed)) {
                                child->right->isRed = false;
                                rightRotate(cousin);
                                leftRotate(parent);
                            }
                            // Lr(1)-left, Lr(2)
                            else if (child->left != nullptr && child->left->isRed) {
                                child->left->isRed = false;
                                rightRotate(child);
                                rightRotate(cousin);
                                leftRotate(parent);
                            }
                        }
                    }
                }
            }
            // R**
            else {
                cousin = parent->left;
                // Rb*
                if (cousin != nullptr && !cousin->isRed) {
                    // Rb0 (both cases)
                    if ((cousin->left == nullptr || !cousin->left->isRed)
                        && (cousin->right == nullptr || !cousin->right->isRed)) {
                        cousin->isRed = true;
                        if (parent->isRed == false) {
                            removeFix(parent->parent, parent);
                        } else {
                            parent->isRed = false;
                        }
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
                        rightRotate(parent);
                    }
                }
                // Rr(*)
                else {
                    // Rr(0)
                    if ((cousin->left == nullptr || !cousin->left->isRed)
                        && ((cousin->right == nullptr)
                            || ((cousin->right->left == nullptr || !cousin->right->left->isRed)
                                && (cousin->right->right == nullptr || !cousin->right->right->isRed)))) {
                        cousin->isRed = false;
                        if (cousin->right != nullptr) {
                            cousin->right->isRed = true;
                        }
                        rightRotate(parent);
                    } else {
                        Node<K, V> *child = cousin->right;
                        if (child != nullptr) {
                            // Rr(1)-left
                            if ((child->left != nullptr && child->left->isRed)
                                && (child->right == nullptr || !child->right->isRed)) {
                                child->left->isRed = false;
                                leftRotate(cousin);
                                rightRotate(parent);
                            }
                            // Rr(1)-right, Rr(2)
                            else if (child->right != nullptr && child->right->isRed) {
                                child->right->isRed = false;
                                leftRotate(child);
                                leftRotate(cousin);
                                rightRotate(parent);
                            }
                        }
                    }
                }
            }
        }
    }
    // Remove the node
    void remove(Node<K, V> *node) {
        // Replace the node with a precursor or successor node
        Node<K, V> *toReplace;
        if (node->left != nullptr || node->right != nullptr) {
            if (node->left != nullptr) {
                toReplace = rightMost(node->left);
            } else if (node->right != nullptr) {
                toReplace = leftMost(node->right);
            }
            replace(node, toReplace);
        }

        // Remove the node and raise its child if it has one
        Node<K, V> *deficient;
        Node<K, V> *parent;
        if (root == node) {
            if (root->left != nullptr) {
                root = root->left;
                root->left->parent = nullptr;
            } else if (root->right != nullptr) {
                root = root->right;
                root->right->parent = nullptr;
            } else {
                root = nullptr;
            }
            delete (node);
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
            delete (node);
            // Fix the tree after removing
            removeFix(parent, deficient);
        }
    }
    // Get the node which its key is key
    Node<K, V> *getNodeByKey(K key) {
        Node<K, V> *node = root;
        while (node != nullptr) {
            if (key < node->key) {
                node = node->left;
            } else if (key > node->key) {
                node = node->right;
            } else {
                return node;
            }
        }
        return nullptr;
    }
    /*
     * Get the nodes which their key are in the range of min to max
     * Then store them into a vector v
     */
    void getRange(K min, K max, Node<K, V> *node, std::vector<V> &v) {
        if (node == nullptr) {
            return;
        } else if (node->key >= min && node->key <= max) {
            getRange(min, max, node->left, v);
            v.push_back(node->value);
            getRange(min, max, node->right, v);
        } else if (node->key > max) {
            getRange(min, max, node->left, v);
        } else if (node->key < min) {
            getRange(min, max, node->right, v);
        }
    }

public:
    // Construct a new red black tree by setting its root to null pointer
    RedBlackTree() {
        this->root = nullptr;
    }
    // Create a node with given arguments then insert it into the tree
    void insert(K key, V value) {
        Node<K, V> *node = new Node<K, V>(key, value);
        append(node, root);
    }
    // Remove the node which its key is key
    void remove(K key) {
        remove(getNodeByKey(key));
    }
    // Get value of the node which its key is key
    V getValueByKey(K key) {
        Node<K, V> *node = getNodeByKey(key);
        if (node != nullptr) {
            return node->value;
        }
        return V();
    }
    // Get values of the nodes which their key are in the range of min to max
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
};