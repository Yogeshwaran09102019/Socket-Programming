#include<iostream>
using namespace std;
#include<limits.h>
int minDistance(int dist[],bool *visited,int n)
{
  int min_index,min=INT_MAX;
  for(int i=0;i<n;i++)
  {
      if(visited[i]==false && dist[i]<=min)
      {
        min=dist[i];
        min_index=i;
      }
  }
  return min_index;
}
void display_sortest_distances(int array[],int src,int n)
{
    for(int i=0;i<n;i++)
    {
      cout<<"\nFrom "<<src+1<<" to "<<(i+1)<<" = "<<array[i];
    }
    cout<<"\n\n";
}
void dijkstra(int **wm,int src,int n)
{
   int max[n];
   bool *visited=new bool[n];
   int i;
   for(i=0;i<n;i++)
   {
    visited[i]=false;
    max[i]=INT_MAX;
   }
   max[src]=0;
   for(int count=0;count<n-1;count++)
   {
       int u=minDistance(max,visited,n);
       visited[u]=true;
       for(int v=0;v<n;v++)
       {
           if (!visited[v] && wm[u][v] && max[u] != INT_MAX
                && (max[u] + wm[u][v]) < max[v])
                max[v] = max[u] + wm[u][v];
       }
   }
   display_sortest_distances(max,src,n);
}
int main()
{
  cout<<"\nEnter total no of vertices: ";
  int n;
  cin>>n;
  int **weight_matrix=new int*[n];
  int i,j;
  for(i=0;i<n;i++)
  {
   weight_matrix[i]=new int[n];
   for(j=0;j<n;j++)
   {
        weight_matrix[i][j]=0;
   }
  }
  int m,u,v,weight;
  cout<<"\nEnter total no of edges: ";
  cin>>m;
  for(i=0;i<m;i++)
  {
      cout<<"\nEdge "<<(i+1)<<":";
      cout<<"\nEnter U: ";
      cin>>u;
      cout<<"\nEnter V: ";
      cin>>v;
      cout<<"\nEnter weight: ";
      cin>>weight;
      weight_matrix[u-1][v-1]=weight;
      weight_matrix[v-1][u-1]=weight;
  }
  int src;
  cout<<"\nEnter source vertex to begin: ";
  cin>>src;
  dijkstra(weight_matrix,src-1,n);
}
