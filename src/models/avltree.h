#ifndef AVLTREE_H
#define AVLTREE_H

#include <QColor>
#include <QRect>
#include <optional>

template <typename K, typename V>

class AVLTree {

private:
    struct Node {
        K key;
        V val;
        Node* parent;
        Node* left;
        Node* right;
        int height;

        Node(K k, V v)
            : key(k), val(std::move(v)), parent(nullptr), left(nullptr), right(nullptr), height(0) {};
    };

    static Node* nil;
    static int nilInstances_;
    Node* root;
    int size_;

    // helper functions ---------------------------

    // find the min
    Node* min(Node* x) const;

    // find the max
    Node* max(Node* x) const;

    // rotate left on node x
    void leftRotate(Node* x);

    // rotate right on node x
    void rightRotate(Node* x);

    // fix the balance after an insertion or deletion
    void balance(Node* x);

    // copy a tree from node x
    void copyTree(Node* x);

public:
    // constructor destructor ---------------------------
    AVLTree();
    AVLTree(const AVLTree& other);
    ~AVLTree();

    // accessors ---------------------------

    // return the number of nodes in the tree
    int size() const;

    // return if there is a node at location k
    bool contains(const K k) const;

    // return the value at key k. If there is no node at key k, return nil
    std::optional<std::reference_wrapper<V>> get(const K k) const;
    // return all values within a given range (inclusive). If there are no values in the range, return an empty vector
    QVector<QPair<K, std::reference_wrapper<V>>> getRange(const K lower, const K upper) const;

    // mutators ---------------------------

    // clear the tree
    void clear();

    // update the pixel at location k with value v. If the pixel does not exist, do nothing
    void update(const K k, const V v);

    // insert a pixel at location k with value v. If the pixel already exists, update the pixel
    void upsert(const K k, const V v);

    // remove the pixel at location k. If the pixel does not exist, do nothing
    void remove(const K k);

    // other functions ---------------------------

    // write the tree in string format
    std::string toString(std::function<std::string(const K&)> keyToStr) const;
};

#endif // AVLTREE_H
