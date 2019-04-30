//
// Created by Lawrence Beutlich on 2019-04-29.
//

#include "Node.h"

int Node::getElement() const {
    return element;
}

void Node::setElement(int element) {
    Node::element = element;
}

TreeColors Node::getColor() const {
    return color;
}

void Node::setColor(TreeColors color) {
    Node::color = color;
}

Node *Node::getParent() const {
    return parent;
}

void Node::setParent(Node *parent) {
    Node::parent = parent;
}

Node *Node::getLeft() const {
    return left;
}

void Node::setLeft(Node *left) {
    Node::left = left;
}

Node *Node::getRight() const {
    return right;
}

void Node::setRight(Node *right) {
    Node::right = right;
}

Node::Node(int element, TreeColors color, Node *parent, Node *left, Node *right) :
        element(element), color(color), parent(parent), left(left), right(right) {
    Node::empty = false;
    if (Node::parent) {
    }
}

Node::Node(int element, TreeColors color) : Node::Node(element, color, nullptr, nullptr, nullptr) {
    Node::empty = false;
}

Node::Node() : Node::Node(0, TreeColors::BLACK, nullptr, nullptr, nullptr) {
    Node::empty = true;
}

bool Node::isEmpty() const {
    return empty;
}

void Node::setEmpty(bool empty) {
    Node::empty = empty;
}

std::ostream &operator<<(std::ostream &out, const Node &node) {
    std::cout << "Element: " << node.element << std::endl;
//    std::cout << "IsEmpty: " << node.empty << std::endl;
    std::cout << "Color: " << (node.color == TreeColors::RED ? "Red" : "Black") << std::endl;
    if (node.parent) {
        std::cout << "Parent: " << node.parent->getElement() << std::endl;
    }
    if (!node.left->isEmpty()) {
        std::cout << "Left: " << node.left->getElement() << std::endl;
    }

    if (!node.right->isEmpty()) {
        std::cout << "Right: " << node.right->getElement() << std::endl;
    }
    return out;
}




