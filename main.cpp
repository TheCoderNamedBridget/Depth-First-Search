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
        vector<node*> adj;
        //keeps track of direction of the arrows
        vector<bool> dir;
        
    public:
        static int timer;
        int numer;
        int denom;
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
        void addNeighbor( node * n, bool direction );
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
    n->numer = node::timer;
    for (auto& adj : n->getAdj() ) 
    { 
        if ( adj->getParent() == NULL )
        {
            adj->setParent( n );
            DFS_Visit( adj );
        }
        else if ( adj->denom == 0 )
        {
            cout<<"Cycle detected, topological sort is impossible "<<endl;
        }
    }
    node::timer++;
    n->denom = node::timer;

    
}

void DFS( vector<node*> v)
{
    node nullNode( "NULL" );
    for (auto& eachNode : v) { 
        
        if ( eachNode->getParent() == NULL )
        {
            eachNode->setParent( &nullNode );
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
    
    
    // Practice Graph from Lab 7 p 1
    // node h = node( "h" );
    // graph.push_back( &h );
    // a.addNeighbor( &c );
    // a.addNeighbor( &d );
    // b.addNeighbor( &c );
    // b.addNeighbor( &e );
    // c.addNeighbor( &d );
    // d.addNeighbor( &e ); 
    // d.addNeighbor( &f );
    // e.addNeighbor( &f );
    // f.addNeighbor( &h );
    
    //Graph 1
    a.addNeighbor( &b, true );
    a.addNeighbor( &c, true );
    a.addNeighbor( &d, true );
    b.addNeighbor( &d, true );
    c.addNeighbor( &d, true );
    d.addNeighbor( &e, true ); 
    e.addNeighbor( &f, false );
    e.addNeighbor( &g, true );
    
    //Graph 2
    // a.addNeighbor( &b );
    // a.addNeighbor( &c );
    // b.addNeighbor( &c );
    // b.addNeighbor( &d );
    // b.addNeighbor( &e );
    // c.addNeighbor( &e );
    // d.addNeighbor( &e ); 
    // d.addNeighbor( &f ); 
    // e.addNeighbor( &b );
    // e.addNeighbor( &f );
    
    //vector<node*> topo;
    DFS( graph );
   
    printAdjMatrix( graph );
    
    //printTopological( topo );

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
    numer = 0;
    denom = 0;
}

node::node( string n , int d, node *p, vector<node*> a )
{
    name = n;
    dist = d;
    parent = p;
    numer = 0;
    denom = 0;
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

void node::addNeighbor( node * n, bool direction )
{
    adj.push_back( n );
    //dir.push_back( direction );
    
    n->adj.push_back( this );
    //n->dir.push_back( !direction );
    //cout<<"inaddneighbor n->getAdj().at(0) "<<(n->getAdj().at(0))<<endl;
    
}
