#include "AIController.h"
#include <utility>
#include <cstdio>
#include <queue>
using namespace std;

bool vis[12][12][12][12],v[12][12];
int A,B,C;
int walkx[4]={1,0,0,-1},walky[4]={0,-1,1,0};
struct Node{
	int x,y;
}my,th;

extern int ai_side;
string ai_name = "the first";

//init function is called once at the beginning
void init() {
	if(ai_side == 0) my.x=8,my.y=4,th.x=0,th.y=4;
	if(ai_side == 1) my.x=0,my.y=4,th.x=8,th.y=4;
}

/* The following notation is based on player 0's perspective
 * Rows are labeled 0 through 8 from player 1's side to player 0's side
 * Columns are labeled 0 through 8 from player 0's left to right
 * A coordinate is recorded as the row followed by the column, for example, player 0's pawn starts on (8, 4)
 * A pawn move is recorded as the new coordinate occupied by the pawn
 * A fence placement is recorded as the coordinate of the square whose bottom-right corner fits the center of the wall
 * A typecode is defined as follows: 0: pawn move
 *                                   1: vertical fence placement
 *                                   2: parallel fence placement
 * An action is defined as (typecode, (row-coordinate, column-coordinate))
 * You need to analyze your opponent's action and return your own action
 * If the typecode of your opponent's action is '-1', it means that you are on the offensive.
 */

void bfs(){
	queue<Node> q;
	q.push(my);
	v[my.x][my.y]=true;
	while(!q.empty()){
		Node now=q.front();
		q.pop();
		for(int i=0;i<4;++i){
			Node news;
			news.x=now.x+walkx[i];
			news.y=now.y+walky[i];
			if(news.x==th.x&&news.y==th.y) continue;
		}
	}  	
}

int Go(){
	for(int i=0;i<4;++i){
		int x=my.x+walkx[i],y=my.y+walky[i];
		if(x==th.x&&y==th.y) continue;
		if(vis[my.x][my.y][x][y]==true) continue;
		if(x<0||y<0||x>8||y>8) continue;
		return i;
	}
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
	int s=Go();
	    my.x=my.x+walkx[s],my.y=my.y+walky[s];
	    return make_pair(0, make_pair(my.x, my.y));
}
