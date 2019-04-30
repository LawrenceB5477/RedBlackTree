//
// Created by Lawrence Beutlich on 2019-04-29.
//

#ifndef REDBLACK_REDBLACKTREE_H
#define REDBLACK_REDBLACKTREE_H

#include "Node.h"
#include <vector>

class RedBlackTree {
private:
    int sz;
    int height;
    Node *root;

    Node *internalSearch(int, Node *);

    Node *expand(Node *, int);

    void inorder(std::vector<int> &, Node *);

    void inorderNodes(std::vector<Node *> &, Node *);

    void freeNodes(Node *);

    Node *inorderPredecessor(Node *);

    void makeNodeEmpty(Node *);

    int calcHeight(Node* node);

    Node* rotate(Node *);

    Node* getUncle(Node *);

    bool addedNodeStraight(Node *);

    void balanceInsert(Node *) ;

public:
    RedBlackTree();

    int size();

    bool isEmpty();

    int getHeight();

    //Accessor methods
    Node *getRoot();

    Node *getParent(Node *);

    Node *getLeft(Node *);

    Node *getRight(Node *);

    //Query methods
    bool isInternal(Node *);

    bool isExternal(Node *);

    bool isRoot(Node *);

    int depth(Node *);

    //Red black tree methods
    Node *search(int);

    Node *insert(int);

    void remove(int);

    //Iterators
    std::vector<int> *elements();

    std::vector<Node *> *nodes();

    friend std::ostream &operator<<(std::ostream &, RedBlackTree &);

    ~RedBlackTree();
};


#endif //REDBLACK_REDBLACKTREE_H
