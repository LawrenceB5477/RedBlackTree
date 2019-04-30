//
// Created by Lawrence Beutlich on 2019-04-29.
//

#include <iostream>
#include "RedBlackTree.h"

int RedBlackTree::size() {
    return RedBlackTree::sz;
}

bool RedBlackTree::isEmpty() {
    return RedBlackTree::sz == 0;
}

Node *RedBlackTree::getRoot() {
    return RedBlackTree::root;
}

Node *RedBlackTree::getParent(Node *node) {
    return node->getParent() ? node->getParent() : nullptr;
}

Node *RedBlackTree::getLeft(Node *node) {
    return node->getLeft() ? node->getLeft() : nullptr;
}

Node *RedBlackTree::getRight(Node *node) {
    return node->getRight() ? node->getRight() : nullptr;
}

bool RedBlackTree::isInternal(Node *node) {
    if (node->isEmpty()) {
        return false;
    }

    bool internal = false;
    if (!node->getRight()->isEmpty() || !node->getLeft()->isEmpty()) {
        internal = true;
    }
    return internal;
}

bool RedBlackTree::isExternal(Node *node) {
    return !isInternal(node);
}

bool RedBlackTree::isRoot(Node *node) {
    return node == RedBlackTree::root;
}

Node *RedBlackTree::search(int num) {
    return internalSearch(num, RedBlackTree::root);
}

Node *RedBlackTree::internalSearch(int num, Node *node) {
    if (node->isEmpty() || node->getElement() == num) {
        return node;
    } else if (num < node->getElement()) {
        return internalSearch(num, node->getLeft());
    } else {
        return internalSearch(num, node->getRight());
    }
}

RedBlackTree::RedBlackTree() : sz(0), root(new Node()) {
}

Node *RedBlackTree::expand(Node *node, int num) {
    node->setElement(num);
    node->setColor(TreeColors::RED);
    node->setEmpty(false);

    //empty nodes
    Node *left = new Node();
    Node *right = new Node();
    left->setParent(node);
    right->setParent(node);
    node->setLeft(left);
    node->setRight(right);

    //TODO balance here
    if (node == root) {
        node->setColor(TreeColors::BLACK);
    }

    return node;
}

void RedBlackTree::balanceInsert(Node *x) {
    if (isRoot(x)) {
        return;
    }

    Node* y = getParent(x);
    Node* z = getParent(y);
        //Add a red to a black, fine
    if (y->getColor() == TreeColors::BLACK) {
        return;

        //Double red
    } else {
        Node *uncle = getUncle(y);

        //Trinode restructuring
        if (uncle->getColor() == TreeColors::BLACK) {
            std::cout << "We are here"<< std::endl;
            //Single rotation
          if (addedNodeStraight(x)) {
              rotate(y);
              y->setColor(TreeColors::BLACK);
              z->setColor(TreeColors::RED);
              //Double rotation
          } else {
              rotate(x);
              rotate(x);

              x->setColor(TreeColors::BLACK);
              z->setColor(TreeColors::RED);
          }
            //Recolor
        } else {
            y->setColor(TreeColors::BLACK);
            uncle->setColor(TreeColors::BLACK);
            if (!isRoot(z)) {
                z->setColor(TreeColors::RED);
            }
            balanceInsert(z);
        }
    }
}


Node *RedBlackTree::insert(int num) {
    Node *position = search(num);
    if (position->isEmpty()) {
        Node* node = expand(position, num);

        //Balance node after adding it
        balanceInsert(node);

        return node;
    } else {
        return position;
    }
}

void RedBlackTree::inorder(std::vector<int> &vec, Node *node) {
    if (!node->isEmpty()) {
        if (node->getLeft()) {
            inorder(vec, node->getLeft());
        }
        vec.push_back(node->getElement());
        if (node->getRight()) {
            inorder(vec, node->getRight());
        }
    }

}

std::vector<int> *RedBlackTree::elements() {
    auto *vec = new std::vector<int>;
    inorder(*vec, root);
    return vec;
}

void RedBlackTree::inorderNodes(std::vector<Node *> &vec, Node *node) {
    if (!node->isEmpty()) {
        if (node->getLeft()) {
            inorderNodes(vec, node->getLeft());
        }
        vec.push_back(node);
        if (node->getRight()) {
            inorderNodes(vec, node->getRight());
        }
    }
}

std::vector<Node *> *RedBlackTree::nodes() {
    auto vec = new std::vector<Node *>;
    inorderNodes(*vec, root);
    return vec;
}

void RedBlackTree::freeNodes(Node *node) {
    if (node->getLeft()) {
        freeNodes(node->getLeft());
    }

    if (node->getRight()) {
        freeNodes(node->getRight());
    }

    delete node;
}

RedBlackTree::~RedBlackTree() {
    freeNodes(root);
}

int RedBlackTree::getHeight() {
    return calcHeight(root);
}

int RedBlackTree::calcHeight(Node *node) {
    int height  = 0;

    if (!isExternal(node)) {
        if (node->getLeft()) {
            height = std::max(height, calcHeight(node->getLeft()) + 1);
        }
        if (node->getRight()) {
            height = std::max(height, calcHeight(node->getRight()) + 1);
        }
    }

    return height;
}

Node *RedBlackTree::inorderPredecessor(Node *node) {
    if (!node->getLeft()->isEmpty()) {
        Node *pred = node->getLeft();
        while (!pred->getRight()->isEmpty()) {
            pred = pred->getRight();
        }
        return pred;
    }
    return nullptr;
}

void RedBlackTree::remove(int num) {
    Node *pos = search(num);

    if (!pos->isEmpty()) {
        //if the node is external
        if (isExternal(pos)) {
            makeNodeEmpty(pos);
            std::cout << "Node is leaf" << std::endl;

            //if the node is internal with one child
        } else if ((!pos->getLeft()->isEmpty() && pos->getRight()->isEmpty()) ||
                   (pos->getLeft()->isEmpty() && !pos->getRight()->isEmpty())) {
            //Get the child
            Node *child = nullptr;
            if (!pos->getLeft()->isEmpty()) {
                child = pos->getLeft();
            } else {
                child = pos->getRight();
            }

            //If we are removing the root
            if (isRoot(pos)) {
                root = child;
            } else {
                Node* parent = getParent(pos);

                bool left = true;

                if (getLeft(parent) != pos) {
                    left = false;
                }

                if (left) {
                    parent->setLeft(child);
                } else {
                    parent->setRight(child);
                }

                child->setParent(parent);
            }

            if (pos->getLeft()->isEmpty()) {
                delete pos->getLeft();
            } else {
                delete pos->getRight();
            }
            delete pos;
            std::cout << "Node is single internal" << std::endl;

            //if the node is internal with two children
        } else {
            Node *pred = inorderPredecessor(pos);
            int element = pred->getElement();
            remove(pred->getElement());
            pos->setElement(element);
        }

    }
}

//remove an external node
void RedBlackTree::makeNodeEmpty(Node *pos) {
    pos->setElement(0);
    pos->setEmpty(true);

    //Free external nodes
    delete pos->getLeft();
    delete pos->getRight();

    pos->setRight(nullptr);
    pos->setLeft(nullptr);
}

int RedBlackTree::depth(Node *node) {
    int depth = 0;
    while (!isRoot(node)) {
        depth++;
        node = getParent(node);
    }
    return depth;
}

Node* RedBlackTree::getUncle(Node *node) {
    Node *parent = getParent(node);

    if (getLeft(parent) == node) {
        return getRight(parent);
    } else {
        return getLeft(parent);
    }
}

bool RedBlackTree::addedNodeStraight(Node *x) {
    Node *y = getParent(x);
    Node *z = getParent(y);

    if ((z->getRight() == y && y->getRight() == x) || (z->getLeft() == y && y->getLeft() == x)) {
        return true;
    } else {
        return false;
    }
}

Node* RedBlackTree::rotate(Node *x) {
    Node* y = getParent(x);
    Node *z = getParent(y);
        //x is bottom node, y is top node
        //a b and c are inorder subtrees of x and y
        //Left to right
    if (x == getLeft(y)) {
        Node *b = x->getRight();

        x->setRight(y);
        y->setParent(x);

        y->setLeft(b);
        b->setParent(y);

        //Right to left
    } else {
        Node *b = x->getLeft();

        x->setLeft(y);
        y->setParent(x);

        y->setRight(b);
        b->setParent(y);
    }

    if (isRoot(y)) {
        root = x;
    } else {

        if (z->getLeft() == y) {
            z->setLeft(x);
            x->setParent(z);
        } else {
            z->setRight(x);
            x->setParent(z);
        }
    }
    return x;
}


std::ostream &operator<<(std::ostream &out, RedBlackTree &rb) {
    auto vec = rb.nodes();
    bool grid[rb.getHeight() + 1][vec->size()];

    for (int i = 0; i < rb.getHeight() + 1; i++) {
        for (int j = 0; j < vec->size(); j++) {
            grid[i][j] = false;
        }
    }

    for (int i = 0; i < vec->size(); i++) {
        grid[rb.depth(vec->at(i))][i] = true;
    }


    for (int i = 0; i < rb.getHeight() + 1; i++) {
        for (int j = 0; j < vec->size(); j++) {
            if (grid[i][j]) {
                if (vec->at(j)->getColor() == TreeColors::RED) {
                    printf("%c[%dm %d ", 0x1B, 31, vec->at(j)->getElement());
                } else {
                    printf("%c[%dm %d ", 0x1B, 97, vec->at(j)->getElement());
                }
            } else {
                std::cout << "    ";
            }
        }
        printf("%c[%dm", 0x1B, 97);
        std::cout << std::endl << std::endl;
    }

    std::cout << "Height: " << rb.getHeight() << std::endl;

    delete vec;
    return out;
}


