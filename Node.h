//
// Created by Lawrence Beutlich on 2019-04-29.
//

#ifndef REDBLACK_NODE_H
#define REDBLACK_NODE_H

#include <iostream>

enum class TreeColors {
    RED,
    BLACK
};

class Node {
private:
public:
    Node(int element, TreeColors color, Node *parent, Node *left, Node *right);

    Node(int element, TreeColors color);

    Node();

    int getElement() const;

    void setElement(int element);

    TreeColors getColor() const;

    void setColor(TreeColors color);

    Node *getParent() const;

    void setParent(Node *parent);

    Node *getLeft() const;

    void setLeft(Node *left);

    Node *getRight() const;

    void setRight(Node *right);

    bool isEmpty() const;

    void setEmpty(bool empty);

    friend std::ostream &operator<<(std::ostream &out, const Node &node);

private:
    int element;
    TreeColors color;
    Node *parent;
    Node *left;
    Node *right;
    bool empty;
};


#endif //REDBLACK_NODE_H
