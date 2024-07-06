#include "node.h"
#include <iostream>
#include <unordered_map>
#include <queue>
#include <bits/stdc++.h>

using namespace std;

void printRT(vector<RoutingNode *> nd){
  for (int i = 0; i < nd.size(); i++){
    nd[i]->printTable();
  }
}

void routingAlgo(vector<RoutingNode *> nd)
{

  bool saturation = false;

  int array1[nd.size()][nd.size()];

  for(int i = 1; i < nd.size(); ++i){
    for(RoutingNode *node : nd){
      for(int j = 1; j < nd.size(); ++j){
        array1[i-1][j-1] = 0;
      }
    }
  }

  int pointer = 0;

  for (RoutingNode *node : nd)
  {
    node->initialFlooding();
    node->sendMsg();
    pointer = pointer + node->getInterfaceCount();
  }


  for (RoutingNode *node : nd){
    node->djikstra(nd, node);
  }

  printf("Printing the routing tables after the convergence \n");
  printRT(nd);
}

void RoutingNode::recvMsg(RouteMsg *msg)
{
  // your code here

  // Traverse the routing table in the message.
  // Check if entries present in the message table is closer than already present
  // entries.
  // Update entries.
  

  return;


}
string getip(RoutingNode* p, RoutingNode* d){
  vector<pair<NetInterface, Node*> > interfaces = p->getinterfaces();
  for (int i = 0; i < interfaces.size(); ++i)
  {
    if (interfaces[i].second->getName() == d->getName())
    {
      pair<string, string> ip;
      return interfaces[i].first.getip();
    }
  }
  return "";
}

string getconnectedip(RoutingNode *p, RoutingNode *d){
  vector<pair<NetInterface, Node*> > interfaces = p->getinterfaces();
  for (int i = 0; i < interfaces.size(); ++i)
  {
    if (interfaces[i].second->getName() == d->getName())
    {
      pair<string, string> ip;
      return interfaces[i].first.getConnectedIp();
    }
  }
  return "";
}
int getnh(vector<RoutingNode *> nd, int i, int parent[])
{
  while (parent[parent[i]] != -1)
  {
    i = parent[i];
  }
  return i;
}
void RoutingNode::djikstra(vector<RoutingNode *> nd, RoutingNode* source)
{
  int n = 0 + nd.size();
  int distance_array[nd.size()];
  int visited_array[nd.size()];
  int parent[nd.size()];
  // int graph[n][n]={0};
  int **graph = new int*[n];
  for (int i = 0; i < n; ++i)
  {
    graph[i] = new int[n];
    distance_array[i] = INT_MAX;
    visited_array[i] = 0;
    parent[i] = -1;
  }
  for (int i = 0; i < nd.size(); ++i)
  {
    for(auto n:nd[i]->neighbours){
      graph[i][n.first.getid()] = n.second;
    }
  }
  distance_array[source->getid()] = 0;
  for (int count = 0; count < nd.size() - 1; count++){
    int min_value = INT_MAX, min_index;

    for (int pointer2 = 0; pointer2 < nd.size(); pointer2++){
      if (visited_array[pointer2] == 0){
        if(distance_array[pointer2] <= min_value){
          min_value = distance_array[pointer2], min_index = pointer2;
        }
      }
    }
    int u = min_index;
    visited_array[u] = 1;

    for (int i = 0; i<nd[u]->neighbours.size(); i++){
      int v = nd[u]->neighbours[i].first.getid();
      if (!visited_array[v] && graph[u][v] && distance_array[u] != INT_MAX && distance_array[u] + graph[u][v] < distance_array[v]){
        distance_array[v] = distance_array[u] + graph[u][v];
        parent[v] = u;
      }
    }
  }
  for (int i = 0; i < n;i++){
    cout<<parent[i]<<" ";
  }
  cout<<endl;
  for (int i = 0; i < n;i++){
    if(parent[i]==-1){
      continue;
    }
    int nh = getnh(nd, i, parent);
    string nhs = getconnectedip(source,nd[nh]);
    string src = getip(source, nd[nh]);
    for(auto itf2:nd[i]->ips){
      source->addTblEntry(itf2,nhs,src,distance_array[i]);
    }
  }
}