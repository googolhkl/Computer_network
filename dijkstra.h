#ifndef __DIJKSTRA_H__
#define __DIJKSTRA_H__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define NUM_OF_NODE 10
#define NUM_OF_LINK 3
#define INFINITY 1000000000

enum NODE_NAME{ A,B,C,D,E,F,G,H,I,J};

class Node
{
    public:
        Node(int name);
        int GetName();          
        int GetConnectedNode(int idx);
        int GetConnectedCost(int idx);
        void Connect(int to,int cost); 
    private:
        int m_name;
        int m_connectedNum;
        int m_connectedNode[NUM_OF_LINK];
        int m_connectedCost[NUM_OF_LINK];
};

class Controller
{
    public:
        Controller();
        void AddNode(Node* node); 
        void Connect(int node1, int node2, int cost); //node1과 node2를 cost만큼 연결
        void Init(int from);    
        void Find();    // dijkstra 알고리즘
        void ShowPath(int node); // 재귀적으로 출력
        void ShowCost(int node);

    private:
        Node* m_arr[NUM_OF_NODE];
        int m_numOfArr;

        int d[NUM_OF_NODE];
        std::vector<int> S;
        std::vector<int> Q;
        int preNode[NUM_OF_NODE];

        //method
        Node* GetNode(int idx);   //idx번째 노드얻기
        int FindQ(int num); //Q에서 num찾기
};

#endif
