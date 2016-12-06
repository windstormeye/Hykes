#ifndef CMAP_H
#define CMAP_H


#include <stdio.h>
#include "Node.h"
#include <vector>

class CMap
{
public:
    CMap(int cacacity);
    ~CMap();
    bool addNode(Node *node);       // 向图中加入结点
    void resetNode();       // 重置结点
    bool setValueToMatrixForUndirectedGraph(int row, int col, int val = 1);     // 为无向图设置邻接矩阵
    void printMatrix();     // 打印邻接矩阵
    void depthFirstTraverse(int nodeindex);     // 深度优先遍历
    void breadthFirstTraverse(int nodeindex);       //广度优先遍历

    void primTree(int nodeIndex);     // 普利姆算法
    void kruskalTree();     // 克鲁斯卡尔算法

private:
    bool getValueFromMatrix(int row, int col, int &val);        //从矩阵中获取权值
    void breathFirstTraverseImpl(std::vector<int> preVec);
    bool isInSet(std::vector<int> nodeSet, int target);      // 判断顶点是否在某个点集合中
    void mergeNodeSet(std::vector<int> &nodeSetA, std::vector<int> nodeSetB);     // 合并两个顶点集合

private:
    int mCapacity;       // 图中最多可容纳的定点数
    int mNodeCount;      // 已添加的借结点个数
    Node *pNodeArray;        // 存放结点数组
    int *pMatrix;        // 存放邻接矩阵
};

#endif // CMAP_H
