#include "chess_board.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))
void show(chess board[][SIZE]){
	int i,j;
	printf("   9   8   7   6   5   4   3   2   1\n");
	printf("¢z¢w¢w¢w¢s¢w¢w¢w¢s¢w¢w¢w¢s¢w¢w¢w¢s¢w¢w¢w¢s¢w¢w¢w¢s¢w¢w¢w¢s¢w¢w¢w¢s¢w¢w¢w¢{\n");
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			printf("¢x");
			printf(" %s",chess_name[board[i][j].type]);
			/*if (board[i][j].color==RED){
				printf("\033[31m %s \033[m",chess_name[board[i][j].type]);
			}else if (board[i][j].color==BLUE){
				printf("%s",chess_name[board[i][j].type]);
			}*/
		}
		printf("¢x %d\n",i+1); 
		if(i!=SIZE-1){
			printf("¢u¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢q¢w¢w¢w¢t\n");	
		}
	}
	printf("¢|¢w¢w¢w¢r¢w¢w¢w¢r¢w¢w¢w¢r¢w¢w¢w¢r¢w¢w¢w¢r¢w¢w¢w¢r¢w¢w¢w¢r¢w¢w¢w¢r¢w¢w¢w¢}\n");
}

void set_chess(chess *target,CHESS_TYPE type,COLOR color){
	target->type=type;
	target->color=color;
}
void initialize(chess board[][SIZE]){
	int i,j;
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			set_chess(&board[i][j],EMPTY,BLACK);
		}
	}
	for(i=0;i<2;i++){
		COLOR color= i%2==0? RED:BLUE;
		short col=8*i;
		set_chess(&board[col][0],LANCE,color);
		set_chess(&board[col][1],KNIGHT,color);
		set_chess(&board[col][2],SILVER,color);
		set_chess(&board[col][3],GOLD,color);
		set_chess(&board[col][4],KING,color);
		set_chess(&board[col][5],GOLD,color);
		set_chess(&board[col][6],SILVER,color);
		set_chess(&board[col][7],KNIGHT,color);
		set_chess(&board[col][8],LANCE,color);
		
		for (j=0;j<9;j++){
			set_chess(&board[abs(col-2)][j],PAWN,color);
		}
	}
	set_chess(&board[1][7],BISHOP,RED);
	set_chess(&board[1][1],ROOK,RED);
	set_chess(&board[7][1],BISHOP,BLUE);
	set_chess(&board[7][7],ROOK,BLUE);
}

bool clear_path(chess board[][SIZE],coord st,coord ed){
	bool ans=true;
	coord tmp=minus(ed,st);
	short len=MAX(abs(tmp.x),abs(tmp.y));
	tmp=devide(tmp,len);
	//printf("tmp: %d,%d\n",tmp.x,tmp.y);
	int i;
	for(i=1;i<=len;i++){
		if(board[tmp.y*i+st.y][tmp.x*i+st.x].color==board[st.y][st.x].color){
			//printf("type= %d\n",board[tmp.y*i+st.y][tmp.x*i+st.x].type);
			ans=false;
			break;
		}else if(board[tmp.y*i+st.y][tmp.x*i+st.x].color==!board[st.y][st.x].color && i!=len){
			ans=false;
			break;
		}
	}
	return ans;
}

bool valid_move(chess board[][SIZE],coord start,coord end,COLOR player){
	short inv = board[start.y][start.x].color==BLUE? 1:-1;
	coord r_pos=minus(end,start);
	r_pos.y*=inv;
	bool ans=false;
	if ( end.x>=0 && end.x<SIZE && end.y>=0 && end.y<SIZE && board[end.y][end.x].color!=board[start.y][start.x].color && board[start.y][start.x].color==player){
		
		switch(board[start.y][start.x].type){
			case EMPTY:
				break;
			case KING:
				if(MAX(abs(r_pos.x),abs(r_pos.y))==1){
					ans=true;
				}
				break;
			case ROOK:
				if(r_pos.x*r_pos.y==0){
					ans=clear_path(board,start,end);
				}
				break;
			case DRAGON:
				if(r_pos.x*r_pos.y==0){
					ans=clear_path(board,start,end);
				}else if(abs(r_pos.x*r_pos.y)==1){
					ans=true;
				}
				break;
				
			case BISHOP:
				if(abs(r_pos.x)==abs(r_pos.y)){
					ans=clear_path(board,start,end);
				}
				break;
				
			case HORSE:
				if(abs(r_pos.x)==abs(r_pos.y)){
					ans=clear_path(board,start,end);
				}else if(abs(r_pos.x+r_pos.y)==1 && r_pos.x*r_pos.y==0){
					ans=true;
				}
				break;
			case GOLD:
				if((abs(r_pos.x+r_pos.y)==1 && r_pos.x*r_pos.y==0) || (r_pos.y==-1 && abs(r_pos.x)==1)){
					ans=true;
				}
				break;
				
			case SILVER:
				if(abs(r_pos.x*r_pos.y)==1 || (r_pos.y==-1 && r_pos.x==0)){
					ans=true;
				}
				break;
				
			case PRO_SILVER:
				if((abs(r_pos.x+r_pos.y)==1 && r_pos.x*r_pos.y==0) || (r_pos.y==-1 && abs(r_pos.x)==1)){
					ans=true;
				}
				break;
				
			case KNIGHT:
				if (r_pos.y==-2 && abs(r_pos.x)==1){
					ans=true;
				}
				break;
				
			case PRO_KNIGHT:
				if((abs(r_pos.x+r_pos.y)==1 && r_pos.x*r_pos.y==0) || (r_pos.y==-1 && abs(r_pos.x)==1)){
					ans=true;
				}
				break;
				
			case LANCE:
				if(r_pos.y<0 && r_pos.x==0){
					ans=clear_path(board,start,end);
				}
				break;
				
			case PRO_LANCE:
				if((abs(r_pos.x+r_pos.y)==1 && r_pos.x*r_pos.y==0) || (r_pos.y==-1 && abs(r_pos.x)==1)){
					ans=true;
				}
				break;
				
			case PAWN:
				if(r_pos.y==-1 && r_pos.x==0){
					ans=true;
				}
				break;
				
			case PRO_PAWN:
				if((abs(r_pos.x+r_pos.y)==1 && r_pos.x*r_pos.y==0) || (r_pos.y==-1 && abs(r_pos.x)==1)){
					ans=true;
				}
				break;
			default:
				break;
		}
	}
	/*else{
		printf("invalid move\n");
		//printf("end %d %d\n",end.x,end.y);
		//printf("start %d %d",start.x,start.y);
		//printf("Out of boarder %d\n",board[end.y][end.x].color!=board[start.y][start.x].color);
		//printf("color st: %d, color ed: %d\n",board[start.y][start.x].color,board[end.y][end.x].color);
		//printf("type st: %d, type ed: %d\n",board[start.y][start.x].type,board[end.y][end.x].type);
	}*/
	return ans;
}

void move_chess(chess board[][SIZE],coord start,coord end,short promote){
	//printf("end %d %d\n",end.x,end.y);
	//printf("start %d %d\n",start.x,start.y);
	set_chess(&board[end.y][end.x],board[start.y][start.x].type+promote,board[start.y][start.x].color);
	set_chess(&board[start.y][start.x],EMPTY,BLACK);
}

bool can_promote(CHESS_TYPE type,coord start,coord end,COLOR player){
	if(type==ROOK || type==BISHOP || type==SILVER || type==KNIGHT || type==LANCE || type==PAWN){
		if ((player==BLUE && (start.y<=2 || end.y<=2)) || (player==RED && (start.y>=6 || end.y>=6) ) ){
			return true;
		}
	}
	return false;	
}


void regret(chess board[][SIZE],step back,COLOR player){
	move_chess(board,back.end,back.start,-1*back.promote);
	if(back.capture!=EMPTY){
		set_chess(&board[back.end.y][back.end.x],back.capture,!player);	
	}	
}
