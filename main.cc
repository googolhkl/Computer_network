#include "dijkstra.h"
using namespace std;

int main()
{
    Controller ctl[NUM_OF_NODE];
    for(int i=0; i < NUM_OF_NODE; i++)  // adding node
    {
        for(int j=0; j< NUM_OF_NODE; j++)
        {
            ctl[i].AddNode(new Node(j));
        }
    }

    for(int i=0; i< NUM_OF_NODE; i++)  // connect each node  
    {
        ctl[i].Connect(A,B,2);
        ctl[i].Connect(A,E,1);
        ctl[i].Connect(A,F,5);
        ctl[i].Connect(B,C,2);
        ctl[i].Connect(B,D,1);
        ctl[i].Connect(C,I,4);
        ctl[i].Connect(C,J,5);
        ctl[i].Connect(D,E,1);
        ctl[i].Connect(D,G,2);
        ctl[i].Connect(E,F,3);
        ctl[i].Connect(F,G,1);
        ctl[i].Connect(G,H,1);
        ctl[i].Connect(H,I,1);
        ctl[i].Connect(H,J,2);
        ctl[i].Connect(I,J,2);
    }

    for(int i=0; i < NUM_OF_NODE; i++)  // initialize
    {
        ctl[i].Init(i);
        ctl[i].Find();
    }
    for(int i=0; i< NUM_OF_NODE; i++)   // show all path table
    {
        cout<<"============from "<<(char)(i+'A')<<"================="<<endl;
        for(int j=0; j< NUM_OF_NODE; j++)
        {
            ctl[i].ShowPath(j);
            ctl[i].ShowCost(j);
        }
        cout<<"==================================="<<endl;
    }
    
    // input
    do
    {
        char from=0,to=0;
        cout<<"===========Usage example==========="<<endl;
        cout<<"<from> <to>: A J"<<endl;
        cout<<"A -> E -> D -> G -> H -> J ->  7"<<endl;
        cout<<"==================================="<<endl;
        cout<<"<from> <to>: ";
        cin>>from;
        cin>>to;
        from -= 'A'; to -= 'A';
        if( ((from < (NUM_OF_NODE-NUM_OF_NODE))||(from > (NUM_OF_NODE-1)))
                || ((to < (NUM_OF_NODE-NUM_OF_NODE))||(to > (NUM_OF_NODE-1))) ) // incorrect input
        {
            cout<<"Please input correct node number"<<endl;
            continue;
        }
        ctl[(int)from].ShowPath((int)to);
        ctl[(int)from].ShowCost((int)to);
        cout<<"continue 'ENTER' quit 'q'"<<endl;
        cin.get();
    } while( (cin.get() != 'q')  );
}
