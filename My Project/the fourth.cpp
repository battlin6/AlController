#include "AIController.h"
#include <utility>
#include <cstdio>
#include <queue>
#include <cstring>
#define MAX 0x3f3f3f3f
#pragma GCC optimize(2)
using namespace std;

bool vis[12][12][12][12],v[12][12];
int walkx[4]={-1,0,1,0},walky[4]={0,-1,0,1};
int panel=10;
struct Node{
	int x,y;
	int sum;
}my,th;

extern int ai_side;
string ai_name = "the fourth";

void init() {
	if(ai_side == 0) my.x=8,my.y=4,th.x=0,th.y=4;
	if(ai_side == 1) my.x=0,my.y=4,th.x=8,th.y=4;
	memset(vis,0,sizeof(vis));
}

bool He(int x1,int y1,int x2,int y2){
	if(x2<0||y2<0||x2>8||y2>8) 
		return 0;
	else if(vis[x1][y1][x2][y2]==true) 
		return 0;
	return 1;
}

bool Des(int x){
	if(ai_side == 0 && x == 0) 
		return 1;
	if(ai_side == 1 && x == 8) 
		return 1;
	return 0;
}

bool Desth(int x){
	if(ai_side == 1 && x == 0) 
		return 1;
	if(ai_side == 0 && x == 8) 
		return 1;
	return 0;
}


int bfs(Node init){
	Node e=init;
	memset(v,0,sizeof(v));
	queue<Node> q;
	e.sum = 0;
	q.push(e);
	v[e.x][e.y] = true;
	while(!q.empty()){
		Node now=q.front();
		if(Des(now.x))
			return now.sum;
		q.pop();
		for(int i=0;i<4;++i){
			Node news;
			news.x=now.x+walkx[i];
			news.y=now.y+walky[i];
			news.sum = now.sum+1;
			if(!He(now.x,now.y,news.x,news.y)) continue;
			if(v[news.x][news.y] == true) continue;
			q.push(news);
			v[news.x][news.y] = true;
		}
	}
	return MAX; 
}

int bfsth(Node init){
	Node e = init;
	memset(v,0,sizeof(v));
	queue<Node> q;
	e.sum = 0;
	q.push(e);
	v[e.x][e.y] = true;
	while(!q.empty()){
		Node now=q.front();
		if(Desth(now.x))
			return now.sum;
		q.pop();
		for(int i=0;i<4;++i){
			Node news;
			news.x=now.x+walkx[i];
			news.y=now.y+walky[i];
			news.sum = now.sum+1;
			if(!He(now.x,now.y,news.x,news.y)) continue;
			if(v[news.x][news.y] == true) continue;
			q.push(news);
			v[news.x][news.y] = true;
		}
	}
	return MAX;
}	

Node Putpanel2(){
	int mys=MAX,mi=0,mj=0;
	for(int i=0;i<=7;++i){
		for(int j=0;j<=7;++j){
			if(vis[i][j][i+1][j]==false&&vis[i+1][j][i][j]==false&&vis[i][j+1][i+1][j+1]==false&&vis[i+1][j+1][i][j+1]==false&&!(vis[i][j][i][j+1]==true&&vis[i+1][j][i+1][j+1]==true)){
				vis[i][j][i+1][j]=true,vis[i+1][j][i][j]=true,vis[i][j+1][i+1][j+1]=true,vis[i+1][j+1][i][j+1]=true;
				int T1=bfs(my);
				int T2=bfsth(th);
				if(T1==MAX||T2==MAX){
					vis[i][j][i+1][j]=false,vis[i+1][j][i][j]=false,vis[i][j+1][i+1][j+1]=false,vis[i+1][j+1][i][j+1]=false;
					continue;
				}
				if(T1-T2<mys){
					mys=T1-T2;
					mi=i,mj=j;
				}
				vis[i][j][i+1][j]=false,vis[i+1][j][i][j]=false,vis[i][j+1][i+1][j+1]=false,vis[i+1][j+1][i][j+1]=false;
			}	
		}
	}
	Node s;
	s.x=mi,s.y=mj,s.sum=mys;
	return s;
}

Node Putpanel3(){
	int mys=MAX,mi=0,mj=0;
	for(int i=0;i<=7;++i){
		for(int j=0;j<=7;++j){
			if(vis[i][j][i][j+1]==false&&vis[i][j+1][i][j]==false&&vis[i+1][j][i+1][j+1]==false&&vis[i+1][j+1][i+1][j]==false&&!(vis[i+1][j][i][j]==true&&vis[i][j+1][i+1][j+1]==true)){
				vis[i][j][i][j+1]=true,vis[i][j+1][i][j]=true,vis[i+1][j][i+1][j+1]=true,vis[i+1][j+1][i+1][j]=true;
				int T1=bfs(my);
				int T2=bfsth(th);
				if(T1==MAX||T2==MAX){
					vis[i][j][i][j+1]=false,vis[i][j+1][i][j]=false,vis[i+1][j][i+1][j+1]=false,vis[i+1][j+1][i+1][j]=false;
					continue;
				}
				if(T1-T2<mys){ 
					mys=T1-T2;
					mi=i,mj=j;
				}
				vis[i][j][i][j+1]=false,vis[i][j+1][i][j]=false,vis[i+1][j][i+1][j+1]=false,vis[i+1][j+1][i+1][j]=false;
			}
				
		}
	}
	Node s;
	s.x=mi,s.y=mj,s.sum=mys;
	return s;
}

Node Go(){
	int mys=MAX;
	Node Best;
	for(int i=(2*ai_side);i<4+(2*ai_side);++i){
		Node news;
		news.x=my.x+walkx[i%4];
		news.y=my.y+walky[i%4];
		if(!He(my.x,my.y,news.x,news.y)) continue;
		if(news.x==th.x&&news.y==th.y){
			Node news1;
			news1.x=news.x+walkx[i%4];
		    news1.y=news.y+walky[i%4];
		    if(He(news.x,news.y,news1.x,news1.y)){
		    	int T=bfs(news1);
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
		    		int T=bfs(news2);
		    		if(T<mys){
			   	    	mys=T;
				    	Best=news2;    
					}
				}
				if(He(news.x,news.y,news3.x,news3.y)){
		    		int T=bfs(news3);
		    		if(T<mys){
			   	    	mys=T;
				    	Best=news3; 
					}
				}
			}
		}
		else{
			int T=bfs(news);
		    	if(T<mys){
			   	    mys=T;
				    Best=news;
				}
		}
	}
	cerr<<"Best:"<<Best.x<<"   "<<Best.y<<"   "<<mys<<endl;
	Best.sum=mys;
	return Best;
}
 

pair<int, pair<int, int> > action(pair<int, pair<int, int> > loc) {
	int a=loc.first,b=loc.second.first,c=loc.second.second;
	if(a == -1){
	    my.x=7,my.y=4;
		return make_pair(0, make_pair(7, 4));
	}
	else if(a == 0)
	    th.x=b,th.y=c;
	else if(a == 1)
	    vis[b][c][b][c+1]=true,vis[b][c+1][b][c]=true,vis[b+1][c][b+1][c+1]=true,vis[b+1][c+1][b+1][c]=true;
	else if(a == 2)
	    vis[b][c][b+1][c]=true,vis[b+1][c][b][c]=true,vis[b][c+1][b+1][c+1]=true,vis[b+1][c+1][b][c+1]=true;
	

	Node s1 = Go();
	s1.sum++;
	cerr<<"s1"<<" "<<s1.x<<" "<<s1.y<<" "<<s1.sum<<endl; 
	Node s2 = Putpanel2();
	cerr<<"s2"<<" "<<s2.x<<" "<<s2.y<<" "<<s2.sum<<endl;
	Node s3 = Putpanel3();
	cerr<<"s3"<<" "<<s3.x<<" "<<s3.y<<" "<<s3.sum<<endl; 
	int T2=bfsth(th); 
	cerr<<"对手还差步数："<< T2 << endl;
	if(s2.sum!=MAX&&s3.sum!=MAX&&panel>0&&s2.sum<=s1.sum-T2&&s2.sum<s3.sum){ 
		panel--;
		vis[s2.x][s2.y][s2.x+1][s2.y]=true,vis[s2.x+1][s2.y][s2.x][s2.y]=true,vis[s2.x+1][s2.y+1][s2.x][s2.y+1]=true,vis[s2.x][s2.y+1][s2.x+1][s2.y+1]=true;
		return make_pair(2, make_pair(s2.x, s2.y));
	}
	else if(s2.sum!=MAX&&s3.sum!=MAX&&panel>0&&s3.sum<=s1.sum-T2&&s3.sum<s2.sum){
		panel--;
		vis[s3.x][s3.y][s3.x][s3.y+1]=true,vis[s3.x][s3.y+1][s3.x][s3.y]=true,vis[s3.x+1][s3.y+1][s3.x+1][s3.y]=true,vis[s3.x+1][s3.y][s3.x+1][s3.y+1]=true;
		return make_pair(1, make_pair(s3.x, s3.y));
	}
	else{
	    my.x=s1.x,my.y=s1.y;
		return make_pair(0, make_pair(s1.x, s1.y));
	}
}
