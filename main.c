#include <stdio.h>
#include <stdlib.h>
#include "chess_board.h"
#include "coord.h"
#include "stack.h"

chess board[SIZE][SIZE];
stack record={.top=-1};

void get_move(coord *st,coord *ed,char*in){
	st->x=8-(in[0] - '0' -1);
	st->y=in[1] - '0' -1;
	ed->x=8-(in[3] - '0' -1);
	ed->y=in[4] - '0' -1;
}

int main(int argc, char *argv[]) {
	initialize(board);
	show(board);
	coord start,end;
	int turn=0;
	COLOR player=BLUE;
	char input_str[6];
	while(true){
		printf("player %d : ",player);
		gets(input_str);
		if(input_str[0] == 's'){
			write_file(record,"new_game");
		}else if(input_str[0] =='0' && turn != 0){
			step back = pop(&record);
			regret(board,back,player);
			player = !player;
			show(board);
			print_stack(&record);
		}else{
			get_move(&start,&end,input_str);
			//printf("end %d %d\n",end.x,end.y);
			//printf("start %d %d\n",start.x,start.y);
			if(valid_move(board,start,end,player)){
				CHESS_TYPE capture=board[end.y][end.x].type;
				move_chess(board,start,end);
				
				bool check_promote = false;
				if(can_promote(board[end.y][end.x].type,start,end,player)){
					printf("Do you want to promote %s ? Yes:1 No:0 :",chess_name[board[end.y][end.x].type]);
					gets(input_str);
					if(input_str[0]=='1'){
						promote(board,end);
						check_promote=true;
					}
				}
				step now={.start=start,.end=end,.promote=check_promote,.capture=capture};
				push(&record,now);
				turn+=1;
				player = !player;
				show(board);
				print_stack(&record);
			}else{
				printf("invalid \n");
			}
		}
	}
	return 0;
}
