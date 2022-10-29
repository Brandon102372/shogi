#include <stdio.h>
#include <stdlib.h>
#include "chess_board.h"
#include "coord.h"
#include "stack.h"

chess board[SIZE][SIZE];
stack record={.top=-1};

void input(coord *st,coord *ed){
	char line[3];
	scanf(" %s",line);
	st->x=8-(line[0] - '0' -1);
	st->y=line[1] - 48 -1;
	scanf(" %s",line);
	ed->x=8-(line[0] - 48 -1);
	ed->y=line[1] - 48 -1;
}

int main(int argc, char *argv[]) {
	initialize(board);
	show(board);
	coord start,end;
	int turn=0;
	COLOR player;
	while(true){
		player = turn%2==0?BLUE:RED;
		bool check_promote=false;
		input(&start,&end);
		if(valid_move(board,start,end,player)){
			move_chess(board,start,end);
			if(can_promote(board[end.y][end.x].type,start,end,player)){
				int in=0;
				printf("Do you want to promote %s ? Yes:1 No:0 :",chess_name[board[end.y][end.x].type]);
				scanf("%d",&in);
				if(in==1){
					promote(board,end);
					check_promote=true;
				}
			}
			step now={.start=start,.end=end,.promote=check_promote};
			push(&record,now);
			turn+=1;
			show(board);
			print_stack(&record);
		}
	}
	return 0;
}
