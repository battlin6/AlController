#include "AIController.h"
#include <utility>
#include <cstdio>
#include <queue>
#include <cstring>
#define MAX 0x3f3f3f3f
using namespace std;

bool vis[12][12][12][12],v[12][12];
int walkx[4]={1,0,-1,0},walky[4]={0,-1,0,1};
struct Node{
	int x,y;
	int sum; 
}my,th;

extern int ai_side;
string ai_name = "the second";

void init() {
	if(ai_side == 0) my.x=8,my.y=4,th.x=0,th.y=4;
	if(ai_side == 1) my.x=0,my.y=4,th.x=8,th.y=4;
}

bool He(int x1,int y1,int x2,int y2){
	if(vis[x1][y1][x2][y2]==true) return 0;
	if(x2<0||y2<0|x2>8||y2>8) return 0;
	return 1;
}

bool Des(int x){
	if(ai_side==0&&x==0) return 1;
	if(ai_side==1&&x==8) return 1;
	return 0;
}

int bfs(Node init,int upp){
	memset(v,0,sizeof(v));
	queue<Node> q;
	init.sum = 0;
	q.push(init);
	v[init.x][init.y]=true;
	while(!q.empty()){
		Node now=q.front();
		if(now.sum>upp) return MAX;
		q.pop();
		for(int i=0;i<4;++i){
			Node news;
			news.x=now.x+walkx[i];
			news.y=now.y+walky[i];
			news.sum = now.sum+1;
			if(!He(now.x,now.y,news.x,news.y)) continue;
			if(v[news.x][news.y]==true) continue;
			if(Des(news.x))return news.sum;
			q.push(news);
			v[news.x][news.y]==true;
		}
	}
	return MAX;
}	

Node Go(){
	int mys=MAX;
	Node Best;
	for(int i=0;i<4;++i){
		Node news;
		news.x=my.x+walkx[i];
		news.y=my.y+walky[i];
		if(!He(my.x,my.y,news.x,news.y)) continue;
		if(news.x==th.x&&news.y==th.y){
			Node news1;
			news1.x=news.x+walkx[i];
		    news1.y=news.y+walky[i];
		    if(He(news.x,news.y,news1.x,news1.y)){
		    	int T=bfs(news1,mys);
		    	if(T<mys){
			   	    mys=T;
				    Best=news1;    
				}
			}
			else{
				Node news2,news3;
				news2.x=news.x+walkx[(i+1)%4];
		        news2.y=news.y+walky[(i+1)%4];
		        news3.x=news.x+walkx[(i+3)%4];
		    	news3.y=news.y+walky[(i+3)%4];
		    	if(He(news.x,news.y,news2.x,news2.y)){
		    		int T=bfs(news2,mys);
		    		if(T<mys){
			   	    	mys=T;
				    	Best=news2;    
					}
				}
				if(He(news.x,news.y,news3.x,news3.y)){
		    		int T=bfs(news3,mys);
		    		if(T<mys){
			   	    	mys=T;
				    	Best=news3;    
					}
				}
			}
		}
		else{
			int T=bfs(news,mys);
		    	if(T<mys){
			   	    mys=T;
				    Best=news;
				}
		}
	}
	cerr<<Best.x<<"   "<<Best.y<<"   "<<mys<<endl; 
	return Best;
}

pair<int, pair<int, int> > action(pair<int, pair<int, int> > loc) {
	int a=loc.first,b=loc.second.first,c=loc.second.second;
	if(a == -1){
	    my.x=7,my.y=4;
		return make_pair(0, make_pair(7, 4));
	}
	if(a == 0)
	    th.x=b,th.y=c;
	if(a == 1)
	    vis[b][c][b][c+1]=true,vis[b][c+1][b][c]=true,vis[b+1][c][b+1][c+1]=true,vis[b+1][c+1][b+1][c]=true;
	if(a == 2)
	    vis[b][c][b+1][c]=true,vis[b+1][c][b][c]=true,vis[b][c+1][b+1][c+1]=true,vis[b+1][c+1][b][c+1]=true;
	    
	Node s=Go();
	my.x=s.x,my.y=s.y;
	return make_pair(0, make_pair(s.x, s.y));
}
