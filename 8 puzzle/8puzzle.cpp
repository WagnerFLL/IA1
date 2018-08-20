#include <bits/stdc++.h>
using namespace std;

int row[] = { 1, 0, -1, 0 };
int col[] = { 0, -1, 0, 1 };

struct Node {
    Node* parent;
    int set[3][3];
    int x, y, cost, level;
};

struct comp {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return (lhs->cost + lhs->level) > (rhs->cost + rhs->level);
    }
};
 
int printMatrix(int set[3][3]) {
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++)
            printf("%d ", set[i][j]);
        printf("\n");
    }
}
 
Node* newNode(int set[3][3], int x, int y, int X, int Y, int level, Node* parent) {
    
    Node* node = new Node;
    node->parent = parent;
    
    memcpy(node->set, set, sizeof node->set);
    swap(node->set[x][y], node->set[X][Y]);
 
    
    node->cost = INT_MAX;
    node->level = level;
    node->x = X;
    node->y = Y;
 
    return node;
}
 
int calculateCost(int initial[3][3], int final[3][3]) {

    int count = 0;
    
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        if (initial[i][j] && initial[i][j] != final[i][j])
           count++;
    
    return count;
}
 

int isSafe(int x, int y) {
    return (x >= 0 && x < 3 && y >= 0 && y < 3);
}
 
void printPath(Node* root) {
    
    if (root == NULL) return;
    
    printPath(root->parent);
    printMatrix(root->set);
 
    printf("\n");
}

void solve(int initial[3][3], int x, int y, int final[3][3]) {
    
    priority_queue<Node*, std::vector<Node*>, comp> pq;
    Node* root = newNode(initial, x, y, x, y, 0, NULL);
    root->cost = calculateCost(initial, final);
 
    pq.push(root);
 
    while (!pq.empty()) {
        
        Node* min = pq.top();
        pq.pop();
 
        if (min->cost == 0) {
            printPath(min);
            return;
        }

        for (int i = 0; i < 4; i++) {
            if (isSafe(min->x + row[i], min->y + col[i])) {
                
                Node* child = newNode(min->set, min->x,
                              min->y, min->x + row[i],
                              min->y + col[i],
                              min->level + 1, min);
                child->cost = calculateCost(child->set, final);
                pq.push(child);
            }
        }
    }
}
 
int main() {
    
    int initial[3][3];

    printf("Digite os valores iniciais: ");
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            scanf("%d",&initial[i][j]);
 
    int final[3][3] = {
        {1, 2, 3},
        {5, 8, 6},
        {0, 7, 4}
    };
 
    int x = 1, y = 2;
 
    solve(initial, x, y, final);
 
    return 0;
}
