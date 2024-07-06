#include "node.h"

vector<RoutingNode *> distanceVectorNodes;

void routingAlgo(vector<RoutingNode *> distanceVectorNodes);

int main(){
  int n;
  cin >> n;
  string name;
  distanceVectorNodes.clear();
  for(int i = 0; i < n; i++){
    RoutingNode *newnode = new RoutingNode();
    cin >> name;
    newnode->setName(name);
    newnode->setid(distanceVectorNodes.size());
    distanceVectorNodes.push_back(newnode);
  }
  cin >> name;

  while(name != "EOE"){
    for(int i = 0; i < distanceVectorNodes.size(); i++){
      string myeth, oeth, oname;
      if(distanceVectorNodes[i]->getName() == name){
        cin >> myeth;
        cin >> oeth;
        cin >> oname;
        for(int j = 0; j < distanceVectorNodes.size(); j++)
        {
          if(distanceVectorNodes[j]->getName() == oname){
            distanceVectorNodes[i]->addInterface(myeth, oeth, distanceVectorNodes[j]);
            distanceVectorNodes[i]->addTblEntry(myeth, 0);
            break;
          }
        }
      }
    }
    cin >> name;
  }
  routingAlgo(distanceVectorNodes);
}
