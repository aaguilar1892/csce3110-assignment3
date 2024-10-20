struct AvlNode {
    int element;
    AvlNode *left;
    AvlNode *right;
    int height;

    AvlNode (const int & ele, AvlNode *lt, AvlNode *rt, int h = 0) {
        element = ele;
        left = lt;
        right = rt; 
    }
};
