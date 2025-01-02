#include "avltree.h"

#include <QtCore/qdebug.h>
#include <algorithm>
#include <sstream>
#include <stack>

// template <typename K, typename V>
// typename AVLTree<K, V>::Node* AVLTree<K, V>::nil = nullptr;

// template <typename K, typename V>
// int AVLTree<K, V>::nilInstances_ = 0;

template <typename K, typename V>
AVLTree<K, V>::AVLTree() {
    root = nullptr;
    size_ = 0;
}

template <typename K, typename V>
AVLTree<K, V>::AVLTree(const AVLTree<K, V>& other) {
    root = nullptr;
    size_ = 0;

    // deep copy tree
    if (other.root != nullptr) {
        copyTree(other.root);
    }
}

template <typename K, typename V>
AVLTree<K, V>::~AVLTree() {
    clear();
}

// helper functions ---------------------------

// min()
// If the subtree rooted at R is not empty, returns a pointer to the
// leftmost Node in that subtree, otherwise returns nil.
template <typename K, typename V>
typename AVLTree<K, V>::Node* AVLTree<K, V>::min(Node* x) const {
    if (x == nullptr) return nullptr;
    while (x->left != nullptr) x = x->left;
    return x;
}

// max()
// if the subtree rooted at R is not empty, returns a pointer to the
// rightmost Node in that subtree, otherwise returns nil.
template <typename K, typename V>
typename AVLTree<K, V>::Node* AVLTree<K, V>::max(Node* x) const {
    if (x == nullptr) return nullptr;
    while (x->right != nullptr) x = x->right;
    return x;
}

// leftRotate()
// do a single left rotation on the node x.
template <typename K, typename V>
void AVLTree<K, V>::leftRotate(Node* x) {
    if(x == nullptr || x->right == nullptr) return; // can't rotate

    // normal rotation
    Node* y = x->right;
    x->right = y->left;
    if(x->right != nullptr) x->right->parent = x;
    y->left = x;

    // relink parent
    y->parent = x->parent;
    x->parent = y;

    if(y->parent == nullptr) root = y;
    else if (y->parent->left == x) y->parent->left = y; // left child
    else y->parent->right = y; // right child

    // update height
    x->height = 1 + std::max( (x->left ? x->left->height : -1), (x->right ? x->right->height : -1) );
    y->height = 1 + std::max( (y->left ? y->left->height : -1), (y->right ? y->right->height : -1) );
}

// rightRotate()
// do a single right rotation on the node x.
template <typename K, typename V>
void AVLTree<K, V>::rightRotate(Node* x) {
    if(x == nullptr || x->left == nullptr) return; // can't rotate

    // normal rotation
    Node* y = x->left;
    x->left = y->right;
    if(x->left != nullptr) x->left->parent = x;
    y->right = x;

    // relink parent
    y->parent = x->parent;
    x->parent = y;

    if(y->parent == nullptr) root = y;
    else if (y->parent->left == x) y->parent->left = y; // left child
    else y->parent->right = y; // right child

    // update height
    x->height = 1 + std::max( (x->left ? x->left->height : -1), (x->right ? x->right->height : -1) );
    y->height = 1 + std::max( (y->left ? y->left->height : -1), (y->right ? y->right->height : -1) );
}

// balance()
// balances the tree after an insertion or deletion.
template <typename K, typename V>
void AVLTree<K, V>::balance(Node* x) {
    while (x != nullptr && x->parent != nullptr) {
        Node* y = x->parent; // get parent

        // update height
        int leftHeight = (y->left ? y->left->height : -1);
        int rightHeight = (y->right ? y->right->height : -1);
        y->height = 1 + std::max(leftHeight, rightHeight);

        // calculate bf
        int bf = leftHeight - rightHeight;

        if (bf > 1) { // left heavy
            int leftBf = (y->left->left ? y->left->left->height : -1) -
                         (y->left->right ? y->left->right->height : -1);
            if (leftBf < 0) leftRotate(y->left); // right heavy on left subtree
            rightRotate(y);
        } else if (bf < -1) { // right heavy
            int rightBf = (y->right->left ? y->right->left->height : -1) -
                          (y->right->right ? y->right->right->height : -1);
            if (rightBf > 0) rightRotate(y->right); // left heavy on right subtree
            leftRotate(y);
        }

        x = y;
    }
}

template <typename K, typename V>
void AVLTree<K, V>::copyTree(Node* x) {
    if (x == nullptr) return;

    // prewalk
    std::stack<Node*> stack;
    stack.push(x);

    while (!stack.empty()) {
        Node* current = stack.top();
        stack.pop();

        upsert(current->key, current->val);

        // push right child first so left is processed first
        if (current->right != nullptr) {
            stack.push(current->right);
        }
        if (current->left != nullptr) {
            stack.push(current->left);
        }
    }
}

// accessors ---------------------------

// size()
// returns the number of pixels in the tree.
template <typename K, typename V>
int AVLTree<K, V>::size() const {
    return size_;
}

// contains()
// returns true if the tree contains a pixel at location k.
template <typename K, typename V>
bool AVLTree<K, V>::contains(const K k) const {
    Node* cur = root;
    while (cur != nullptr) {
        if (k == cur->key) return true;
        if (k < cur->key) cur = cur->left;
        else cur = cur->right;
    }
    return false;
}

// get(const Location k)
// returns the pixel at location k. If there is no pixel at location k, returns std::nullopt.
template <typename K, typename V>
std::optional<std::reference_wrapper<V>> AVLTree<K, V>::get(const K k) const {
    Node* cur = root;
    while (cur != nullptr) {
        if (k == cur->key) return std::ref(cur->val);
        if (k < cur->key) cur = cur->left;
        else cur = cur->right;
    }
    return std::nullopt;
}

template<typename K, typename V>
QVector<QPair<K, std::reference_wrapper<V>>> AVLTree<K, V>::getRange(const K lower, const K upper) const {
    QVector<QPair<K, std::reference_wrapper<V>>> values;
    if (lower > upper) return values;

    // in-order traversal
    std::stack<Node*> stack;
    Node* cur = root;

    while (cur != nullptr || !stack.empty()) {
        while (cur != nullptr) {
            if (cur->key >= lower) { // normal push
                stack.push(cur);
                cur = cur->left;
            } else {
                cur = cur->right; // skip left subtree
            }
        }

        if (stack.empty()) break;

        cur = stack.top();
        stack.pop();

        if (cur->key >= lower && cur->key <= upper)
            values.push_back({cur->key, std::ref(cur->val)});

        if (cur->key > upper) break;
        cur = cur->right;
    }

    return values;
}

// mutators ---------------------------

// clear()
// clears the tree.
template <typename K, typename V>
void AVLTree<K, V>::clear() {
    // post-walk the tree
    Node* cur = root;

    while (cur != nullptr) {
        if (cur->left != nullptr) {
            // traverse left as far as possible
            cur = cur->left;
        } else if (cur->right != nullptr) {
            // if left is unavailable, go right if possible
            cur = cur->right;
        } else {
            // no leaf nodes left. delete current and step back
            Node *N = cur;
            cur = cur->parent;

            if (cur != nullptr) { // set nils
                if (cur->left == N) cur->left = nullptr;
                else if (cur->right == N) cur->right = nullptr;
            }

            delete N;
        }
    }

    cur = nullptr;
    root = nullptr;
    size_ = 0;
}

// update()
// updates the pixel at location k with value v. If the pixel does not exist, does nothing.
template <typename K, typename V>
void AVLTree<K, V>::update(const K k, const V v) {
    // insert or update
    Node* cur = root;
    while (cur != nullptr && cur->key != k) {
        if (k < cur->key) cur = cur->left;
        else cur = cur->right;
    }

    if (cur != nullptr) { // update
        cur->val = v;
    }
}

// upsert()
// inserts or updates the pixel at location k with value v.
template <typename K, typename V>
void AVLTree<K, V>::upsert(const K k, const V v) {
    // insert or update
    Node* cur = root;
    Node* parent = nullptr;
    while (cur != nullptr && cur->key != k) {
        parent = cur;
        if (k < cur->key) cur = cur->left;
        else cur = cur->right;
    }

    if (cur != nullptr) { // update
        cur->val = v;
        return;
    }

    // create new node
    cur = new Node(k, v);
    cur->parent = parent;
    cur->left = nullptr;
    cur->right = nullptr;

    // update parent
    if(parent == nullptr) root = cur;
    else if (k < parent->key) parent->left = cur;
    else parent->right = cur;

    // balance the tree
    balance(cur);
    size_++;
}

// remove()
// removes the pixel at location k. If the pixel does not exist, does nothing.
template <typename K, typename V>
void AVLTree<K, V>::remove(const K k) {
    Node* cur = root;
    while (cur != nullptr) {
        if (k == cur->key) break;
        if (k < cur->key) cur = cur->left;
        else cur = cur->right;
    }
    if(cur == nullptr) return; // element doesnt exist

    Node* parent = cur->parent;

    if (cur->left == nullptr) {
        // move right subtree to where cur is
        if (cur == root) root = cur->right;
        else if (cur == parent->left) parent->left = cur->right;
        else parent->right = cur->right;

        // update parent if right is not nil
        if(cur->right != nullptr) cur->right->parent = parent;

        // delete cur
        delete cur;
    } else if (cur->right == nullptr) {
        // move left subtree to where cur is
        if (cur == root) root = cur->left;
        else if (cur == parent->left) parent->left = cur->left;
        else parent->right = cur->left;

        // update parent if left is not nil (should always be true)
        if(cur->left != nullptr) cur->left->parent = parent;

        // delete cur
        delete cur;
    } else { // find the min in the right subtree
        Node* minRight = min(cur->right);
        cur->key = minRight->key;
        cur->val = minRight->val;
        parent = minRight->parent;

        // remove the old min value
        if (minRight == minRight->parent->left) minRight->parent->left = minRight->right;
        else minRight->parent->right = minRight->right;

        // update parent if minRight's right is not nil
        if(minRight->right != nullptr) minRight->right->parent = minRight->parent;

        // delete minRight
        delete minRight;
    }

    // balance the tree
    balance(parent);
    size_--;
}

// toString()
// returns a string representation of the tree.
template <typename K, typename V>
std::string AVLTree<K, V>::toString(std::function<std::string(const K&)> keyToStr) const{
    // dfs the tree
    std::ostringstream oss;
    std::stack<Node*> stack;
    stack.push(root);

    while (!stack.empty()) {
        Node* cur = stack.top();
        stack.pop();

        // print current node
        oss << "(" << keyToStr(cur->key) << ") -> ";
        // print child if there is any
        if (cur->left != nullptr) oss << "(" << keyToStr(cur->left->key) << ")";
        else oss << "nil";
        oss << ", ";
        if (cur->right != nullptr) oss << "(" << keyToStr(cur->right->key) << ")";
        else oss << "nil";
        oss << std::endl;

        // push right child
        if (cur->right != nullptr) stack.push(cur->right);
        // push left child
        if (cur->left != nullptr) stack.push(cur->left);
    }

    return oss.str();
}

template class AVLTree<int, QColor>;
template class AVLTree<int, AVLTree<int, QColor>>;
template class AVLTree<int, int>;
template class AVLTree<int, std::string>;
