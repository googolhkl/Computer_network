#include "dijkstra.h"

Node::Node(int name)
{ 
    m_name = name;
    m_connectedNum = 0;
    for(int i=0; i < NUM_OF_LINK; i++) 
    {
        m_connectedNode[i] = INFINITY;
        m_connectedCost[i] = INFINITY;
    }
}

int Node::GetName() { return m_name;} 
int Node::GetConnectedNode(int idx) { return m_connectedNode[idx]; }
int Node::GetConnectedCost(int idx) { return m_connectedCost[idx]; }
void Node::Connect(int to,int cost) //현재 노드에서 to로 cost가격으로 연결
{
    m_connectedNode[m_connectedNum] = to;
    m_connectedCost[m_connectedNum] = cost;
    m_connectedNum++;
}

Controller::Controller() : m_numOfArr(0) 
{
    for(int i=0; i < NUM_OF_NODE; i++)
    {
        d[i] = INFINITY;
        m_arr[i] = NULL;
    }
}
void Controller::AddNode(Node* node)
{
    m_arr[m_numOfArr++] = node;
    Q.push_back(node->GetName());
}
void Controller::Connect(int node1, int node2, int cost) //node1과 node2를 cost만큼 연결
{
    m_arr[node1]->Connect(node2,cost);
    m_arr[node2]->Connect(node1,cost);
}
void Controller::Init(int from)
{
    S.clear();
    Q.clear();
    for(int i=0; i < NUM_OF_NODE; i++)
    {
        Q.push_back(i);
        d[i] = INFINITY;
        preNode[i] = INFINITY;
    }
    d[from] = 0;
    preNode[from] = -1;
}


void Controller::Find()
{
    while( !Q.empty() )
    {
        if( S.empty() ) // S가 공집합일 때
        {
            // d[N]에서 0인 값을 찾아 그 값을 Q에서 제거 후 S에 삽입
            for(int i=0; i< NUM_OF_NODE; i++)   
            {
                if( d[i] == 0)
                {
                    Q.erase(Q.begin() + i);
                    S.push_back(i);
                }
            }
            //S의 마지막원소에서 연결된 노드를 d[N]에 삽입
            for(int i=0; i < NUM_OF_LINK; i++)
            {
                d[m_arr[S.back()]->GetConnectedNode(i)] = m_arr[S.back()]->GetConnectedCost(i);
                preNode[m_arr[S.back()]->GetConnectedNode(i)] = S.back();
                preNode[S.back()] = S.back();
            }
        }
        else // S가 공집합이 아닐 때
        {
            int temp= INFINITY;
            int tempIndex = INFINITY;
            int qN=INFINITY;
            int dN=INFINITY;
            // d[N]의 값 10개를 다 돌아서 Q에도 있고 가장작은 가격의 N을 구한다.
            for(int i=0; i < NUM_OF_NODE; i++)
            {
                if( (d[i] != INFINITY) && (i != S[0])   ) // 값이 있고 S의 첫번째 요소가 아니면
                {
                    //Q에서 있는지 확인
                    qN = FindQ(i);
                    if( qN != INFINITY) //Q에 있으면
                    {
                        if( d[i] < temp)
                        {
                            dN= i;
                            temp = d[dN];
                            tempIndex=qN;
                        }
                    }
                    else { continue; }
                }
                else { continue; }
            }
            // 이 N을 Q에서 제거 후 S에 삽입한다.
            Q.erase(Q.begin() + tempIndex);
            S.push_back(dN);
            // 마지막원소와 연결된노드 + 해당노드가격이 d[N]보다 작으면 이 연결된노드 + 해당노드가격으로 업데이트
            for(int i=0; i< NUM_OF_LINK; i++)
            {
                if( m_arr[S.back()]->GetConnectedCost(i) + d[S.back()] < d[m_arr[S.back()]->GetConnectedNode(i)] )
                {
                    d[m_arr[S.back()]->GetConnectedNode(i)] = m_arr[S.back()]->GetConnectedCost(i) + d[S.back()];
                    preNode[m_arr[S.back()]->GetConnectedNode(i)] = S.back();
                }
            }
        }
    }//while
}//Find

void Controller::ShowPath(int node)
{
    if( node == preNode[node])
    {
        std::cout<<(char)(node+'A')<<" -> ";
        return;
    }
    ShowPath(preNode[node]);
    std::cout<<(char)(node+'A')<<" -> ";
}
void Controller::ShowCost(int node)
{
    std::cout<<" "<<d[node]<<std::endl;
}

/*  private */
Node* Controller::GetNode(int idx) { return m_arr[idx]; }
int Controller::FindQ(int num)
{
    int idx = INFINITY;
    for(int i=0; i<Q.size(); i++)
    {
        if( num == Q[i])
        {
            idx = i;
        }
    }
    return idx;
}
