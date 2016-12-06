#include "cmap.h"
#include <iostream>

using namespace std;

CMap::CMap(int c)
{
    mCapacity = c;
    mNodeCount = 0;
    pNodeArray = new Node[mCapacity];
    pMatrix = new int[mCapacity * mCapacity];
    memset(pMatrix, 0, mCapacity * mCapacity * sizeof(int));
}

CMap::~CMap()
{
    delete []pMatrix;
    delete []pNodeArray;
}

bool CMap::setValueToMatrixForUndirectedGraph(int row, int col, int val)
{
    if (row < 0 || row >= mCapacity)
    {
        return false;
    }
    if (col < 0 || col >= mCapacity)
    {
        return false;
    }
    pMatrix[row * mCapacity + col] = val;
    pMatrix[col * mCapacity + row] = val;
    return true;
}

void CMap::printMatrix()
{
    for (int i = 0; i < mCapacity; i++)
    {
        for (int j = 0; j < mCapacity; j++)
        {
            cout << pMatrix[i * mCapacity + j] << "  ";
        }
        cout << endl;
    }
}
