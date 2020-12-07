/******************************************************************************

Name: Bridget Naylor
Lab: 8 DFS
Date: 12/5/2020 

*******************************************************************************/
#include <iostream>
#include <bits/stdc++.h> 
using namespace std;

//used from last lab
class node
{
    private:
        string color;
        string name;
        node*parent;
        int dist;
        
        
        
    public:
    vector<node*> adj;
    //keeps track of direction of the arrows
        vector<bool> dir;
        static int timer;
        int numer = 0;
        int denom = 0;
        node( string name );
        node( string name, string color );
        node( string n, int d, node *p, vector<node*> a );
        
        string getName();
        vector<node*> getAdj();
        int getDist();
        node* getParent();
        string getColor();
        
        void setDist( int d );
        void setParent( node * n );
        void setColor( string c );
        
        void addNeighbor( node * n);
        void addNeighbor( node * n, bool d1, bool d2 );
        void deleteNeighbor( node n );
};

void printAdjMatrix( vector<node*> list )
{
    int size = list.size();
    
    for ( int i = 0; i < size; i ++ )
    {
        cout<<"  "<<list.at(i)->getName();
    }
    cout<<endl;
    
    for ( int i = 0; i < size; i ++ )
    {
        int itrList = 0;
        int itr = 0;
        string oneOrZero = "";
        int sizeAdj = list.at( i )->getAdj().size();
        cout<<list.at( i )->getName();
        for ( int j = 0; j < size; j++ )
        {
            if ( (sizeAdj > 0) && (list.at( itrList )->getName() == list.at( i )->getAdj().at( itr )->getName()))
            {
                oneOrZero = "1";
                itr++;
                sizeAdj--;
            }
            else
            {
                oneOrZero = "0";
            }
            itrList++;
            cout<<" "<<oneOrZero<<" ";
        }
        cout<<endl;
    }
}

int node::timer = 0;

void DFS_Visit( node* n )
{
    node::timer++;
    n->numer = node::timer;
    for ( int i = 0; i < n->getAdj().size(); i++ ) 
    { 
        
        if ( n->adj[i]->getParent() == NULL && n->dir[i] )
        {
            n->adj[i]->setParent( n );
            DFS_Visit( n->adj[i] );
        }
        else if ( n->adj[i]->denom == 0 && n->dir[i] )
        {
            cout<<"Cycle detected, topological sort is impossible "<<endl;
            exit(0);
        }
        
    }
    node::timer++;
    n->denom = node::timer;
    cout<<n->getName()<<" "<<n->numer<<"/"<<n->denom<<endl;

    
}

void DFS( vector<node*> v)
{
    node nullNode( "NULL" );
    for (auto& eachNode : v) { 
        if ( eachNode->getParent() == NULL )
        {
            eachNode->setParent( &nullNode );
            DFS_Visit( eachNode );
        }
    } 
}

void printTopological( vector<node*> graph )
{
    cout<<"print "<<graph.size()<<endl;
    for (auto& n : graph ) 
    { 
        cout<<"Node = "<<n->getName()<<" Time = "<<n->numer<<"/"<<n->denom<<endl;
    }
    
}


int main()
{
    vector<node*> graph;
    node a = node( "a" );
    node b = node( "b" );
    node c = node( "c" );
    node d = node( "d" );
    node e = node( "e" );
    node f = node( "f" );
    node g = node( "g" );
    
    
    graph.push_back( &a );
    graph.push_back( &b );
    graph.push_back( &c );
    graph.push_back( &d );
    graph.push_back( &e );
    graph.push_back( &f );
    graph.push_back( &g );
    
    
    //Graph 1
    // a.addNeighbor( &b, true, false );
    // a.addNeighbor( &c, true, false );
    // a.addNeighbor( &d, true, false );
    // b.addNeighbor( &d, true, false );
    // c.addNeighbor( &d, true, false );
    // d.addNeighbor( &e, true, false ); 
    // e.addNeighbor( &f, false, true );
    // e.addNeighbor( &g, true, false );
    
    //Graph 2
    a.addNeighbor( &b, true, false );
    a.addNeighbor( &c, true, false );
    b.addNeighbor( &c, true, false );
    b.addNeighbor( &d, true, false );
    b.addNeighbor( &e, true, true );
    c.addNeighbor( &e, true, false );
    d.addNeighbor( &e, false, true ); 
    d.addNeighbor( &f, true, false ); 
    e.addNeighbor( &f, false, true );
    
    printAdjMatrix( graph );
    DFS( graph );
   

    return 0;
}



node::node( string n )
{
    name = n;
    dist = 0;
    parent = NULL;
    
}

node::node( string n, string c )
{
    name = n;
    color = c;

}

node::node( string n , int d, node *p, vector<node*> a )
{
    name = n;
    dist = d;
    parent = p;

    for ( int i = 0; i < a.size(); i ++ )
    {
        adj.push_back( a.at(i) );
    }
}

string node::getName()
{
    return name;
}

vector<node*> node::getAdj()
{
    return adj;
}

int node::getDist()
{
    return dist;
}

node* node::getParent()
{
    return parent;
}

string node::getColor()
{
    return color;
}

void node::setDist( int d )
{
    dist = d;
}

void node::setParent( node * n )
{
    parent = n;
}

void node::setColor( string c )
{
    color = c;
}

void node::addNeighbor( node * n )
{
    adj.push_back( n );
    
    n->adj.push_back( this );
    //cout<<"inaddneighbor n->getAdj().at(0) "<<(n->getAdj().at(0))<<endl;
    
}

void node::addNeighbor( node * n, bool d1, bool d2 )
{
    adj.push_back( n );
    
    
    n->adj.push_back( this );
    
    dir.push_back( d1 );
    n->dir.push_back( d2 );
    //cout<<"inaddneighbor n->getAdj().at(0) "<<(n->getAdj().at(0))<<endl;
    
}

