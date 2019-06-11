/* 
    Your main program goes here
*/
#include <map>
#include <iostream>
#include <queue>
#include "network_manager.h"
#include "gplot.h"
#include "path.h"

using namespace std;
vector< pair<int,int>> trails;
void FindEulerCircuit(int x, vector< vector<int> > &A_matrix);
void Find_path(int src, int dst, vector< vector<int> > &adj, string name_table[]);
void Dijkstra(int src, int parent[], int d[], bool visit[], vector< vector<int> > &adj);
void find_path(int src, int dst, vector< vector<int> > &adj, string name_table[]);
// create NetworkManager first
NetworkManager *nm = new NetworkManager();
int node_num;

int main(int argc, char** argv){

    /* start your program */

    // read from file
    nm->interpret("topo.txt");

    //count node number
    //int node_num = 0;//********************
    Vertex *nlist = nm->get_all_nodes();
    Vertex *tmp = nlist;
    while(tmp!=NULL){
	cout<<tmp->name<<" ";
	node_num++;
	//tmp->degree=0;
	tmp=tmp->next;
    }
    cout<<"\nnode_num : "<<node_num<<endl;

    //count edge number
    int edge_num = 0;
    Edge *elist = nm->elist;
    while(elist!=NULL){
	edge_num++;
	elist=elist->next;
    }
    cout<<"\nedge_num : "<<edge_num<<endl;

//-----------build name table------------//
    string name_table[node_num];//index to name
    tmp=nlist;
    int i=0;
    while(tmp!=NULL){
	name_table[i]=tmp->name;
	i++;
	tmp=tmp->next;
    }
    for(i=0;i<node_num;i++)
	cout<<"name_table["<<i<<"] : "<<name_table[i]<<endl;

    map<string, int> m;//a map: name to index
    tmp=nlist;
    int index=0;
    while(tmp!=NULL){
	m[tmp->name]= index;
	//cout<<"m["<<tmp->name<<"] = "<<m[tmp->name]<<endl;
	index++;
	tmp=tmp->next;
    }
//----------------------------------//

//------build adjacent matrix-------//
    //int A_matrix[node_num][node_num];
    vector<vector<int> > A_matrix(node_num, vector<int> (node_num,0));
    //initiate
    for(i=0;i<node_num;i++){
      for(int j=0;j<node_num;j++){
	A_matrix[i][j]=0;
      }
    }
    //start building
    elist = nm->elist;
    while(elist!=NULL){
      A_matrix[m[elist->head->name]][m[elist->tail->name]]++;
      A_matrix[m[elist->tail->name]][m[elist->head->name]]++;
      elist=elist->next;
    }
    cout<<"\ta\tb\tc\td\te\n";
    for(i=0;i<node_num;i++){
	cout<<name_table[i]<<"\t";
      for(int j=0;j<node_num;j++){
	cout<<A_matrix[i][j]<<"\t";
        if(j==node_num-1)
	  cout<<"\n";
      }
    }
//----------------------------------//

//-----------count degree-----------//
    vector<int> degree;
    int temp;
    for(int i=0;i<node_num;i++){
	temp=0;
      for(int j=0;j<node_num;j++){
	temp=temp+A_matrix[i][j];
	if(j==node_num-1)
	  degree.push_back(temp);
      }
    }
    for(i=0;i<degree.size();i++)
	cout<<"degree["<<name_table[i]<<"] = "<<degree[i]<<endl;
//----------------------------------//

//------add extra edge on add degree node------//
    vector<int> extra_edge;//1:need to add extra edge
			   //0:no need extra edge

    //determine which node need to add extra edge
    for(int i=0;i<node_num;i++){
      if(degree[i]%2==1){//odd degree node
	extra_edge.push_back(1);
      }
      else {//even degree node
	extra_edge.push_back(0);
      }
    }

    int node1, node2;
    queue<int> Q;//store 2 odd node into a pair
    for(int i=0;i<node_num;i++){
      if(extra_edge[i]==1){
	Q.push(i);
      }
      if(Q.size()==2){
	node1 = Q.front(); Q.pop();
	node2 = Q.front(); Q.pop();
	Find_path(node1,node2,A_matrix,name_table);//add edge along path from node1 to node2
	cout<<endl;
      }
    }

//---------------------------------------------//

    //count edge number again
    edge_num = 0;
    elist = nm->elist;
    while(elist!=NULL){
	edge_num++;
	elist=elist->next;
    }
    cout<<"\nedge_num after add extra edge: "<<edge_num<<endl;

//------update adjacent matrix-------//
    //initiate
    for(i=0;i<node_num;i++){
      for(int j=0;j<node_num;j++){
	A_matrix[i][j]=0;
      }
    }
    //update building
    elist = nm->elist;
    while(elist!=NULL){
      A_matrix[m[elist->head->name]][m[elist->tail->name]]++;
      A_matrix[m[elist->tail->name]][m[elist->head->name]]++;
      elist=elist->next;
    }
    cout<<"\ta\tb\tc\td\te\n";
    for(i=0;i<node_num;i++){
	cout<<name_table[i]<<"\t";
      for(int j=0;j<node_num;j++){
	cout<<A_matrix[i][j]<<"\t";
        if(j==node_num-1)
	  cout<<"\n";
      }
    }
//----------------------------------//

    int start =0;
    FindEulerCircuit(start, A_matrix);
    for(int i=0; i<trails.size();i++){
	cout<<name_table[trails[i].second]<<"-->"<<name_table[trails[i].first]<<endl;
    }


    //using gplot to export a dot file, and then using graphviz to generate the figure
    Gplot *gp = new Gplot();
    gp->gp_add(nm->elist);
    gp->gp_dump(true);
    gp->gp_export("plot");

    return 0;
}
//------------------end of main function-------------------//

void FindEulerCircuit(int x, vector< vector<int> > &A_matrix){
  for(int y=0; y<node_num; ++y){
    if(A_matrix[x][y] > 0){
	A_matrix[x][y]--;
	if(x != y) A_matrix[y][x]--;
	FindEulerCircuit(y, A_matrix);
	trails.push_back( make_pair(x,y) );
    }
  }
}

void Dijkstra(int src, int parent[], int d[], bool visit[], vector< vector<int> > &adj){
	
		
	for (int i=0; i<node_num; i++) visit[i] = false;
    for (int i=0; i<node_num; i++) d[i] = 1e9;
 
    d[src] = 0;
    parent[src] = src;
 
    for (int k=0; k<node_num; k++)
    {	//cout<<"k: "<<k<<endl;
        int a = -1, b = -1, min = 1e9;
        for (int i=0; i<node_num; i++){
        	if (!visit[i] && d[i] < min)
            {
                a = i;  // Record the chosen edge
                min = d[i];
                //cout<<"a: "<<a<<"\t";
                //cout<<"min: "<<min<<endl;
            }
		}

 
        if (a == -1) break;     // all the connected node was visit
        visit[a] = true;
 
        // edge<a,b> doing relaxation
        for (b=0; b<node_num; b++){
            if (!visit[b] && d[a] + adj[a][b] < d[b] && adj[a][b]!=0)
            {
                d[b] = d[a] + adj[a][b];
                parent[b] = a;
                //cout<<"d["<<b<<"] : "<<d[b]<<"\t";
                //cout<<"parent["<<b<<"] : "<<parent[b]<<endl;
            }
		}
		
		//cout<<"---------------------------\n\n";
    }
}

void find_path(int dst, int parent[], string name_table[])   
// Print the shortest path to dst
{
    if (dst != parent[dst]) // Print the privious path
    {
        find_path(parent[dst], parent,name_table);
	nm->connect(name_table[dst],name_table[parent[dst]]);
        cout << name_table[dst] <<"<--"<<name_table[parent[dst]]<<endl;  // Print the destination
    }
}
void Find_path(int src, int dst, vector< vector<int> > &adj, string name_table[]){
	int* parent = new int[node_num];
	int* d = new int[node_num];
	bool* visit = new bool[node_num];
	
	Dijkstra(src, parent, d, visit, adj);
	find_path(dst, parent,name_table);
}
