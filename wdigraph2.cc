//wdigraph2.cc
//Tim Dickens
//z1804759
//CSCI 340
//Assign10
//12/6/2017
//Section 3
//Ibrahim Onyuksel

#include "/home/cs340/progs/17f/p10/wdigraph.h"

//depth first search function prints depth first paths using a stack

void wdigraph::depth_first(int u) const
{
    //an array of bools dynamically allocated to represent visiting nodes
    bool *visited = new bool[adj_matrix.size()];
    for( unsigned i = 0; i < adj_matrix.size(); i++)
    {
        visited[i] = false;
    }
    //implementation of the stack to represent a depth first transversal
    stack<int> Node;
    Node.push(u);
    while(!Node.empty())
    {
        u = Node.top();
        if(!visited[u])
        {
            cout << label[u] << "->";
            visited[u] = true;
        }
        //for loop searches through graph links and pushes them onto the stack
        for(unsigned search = 0; search < adj_matrix.size(); search++)
        {
            if(!visited[search] && adj_matrix[u][search] != 0)
            {
                Node.push(search);
                u = Node.top();
                if(!visited[u])
                {
                    cout << label[u] << "->";
                    visited[u] = true;
                }
                search = -1;
            }
        }
        Node.pop();
    }
    cout << endl << endl;
    for(unsigned i = 0; i < adj_matrix.size(); i++)
    {
        visited[i] = false;
    }
    delete visited;
}

//print graph function prints the adjacency matrix and number of nodes

void wdigraph::print_graph() const
{
    unsigned count = 1;
    cout << endl << "Number of Nodes: " << this->get_size() << endl << endl;
    cout << "Adjacency Matrix:" << endl;
    cout << "-----------------" << endl << endl << " ";
    //for loop prints horizontal labels of adjacency matrix
    for(unsigned i = 0; i < adj_matrix.size(); i++)
        {
        cout << setw(3) << label[i] << setw(0);
        }
    cout << endl;
    // double for loop prints vertical labels and values of adjacency matrix
    for(unsigned i = 0; i < adj_matrix.size(); i++)
    {
        for(unsigned j = 0; j < adj_matrix[i].size(); j++)
        {
            if(count == 1)
            {
                cout << left << label[i];
            }
            if(adj_matrix[i][j] == 0){ cout << setw(3) << right << "-"; }
            else{ cout << setw(3) << right << adj_matrix[i][j]; }
            if(count % adj_matrix.size() == 0)
            {
                cout << right << endl << label[i+1];
            }
            count++;
        }
    }
cout << endl;
}
