#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//#include <ev.h>
#include "chess_board.h"
#include "coord.h"
#include "stack.h"
#include "file_processing.h" 
#define INPUT_SIZE 7

chess board[SIZE][SIZE];
stack record={.top=-1};
typedef enum {NEW,LOAD}MODE;
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
	int turn=-1;
	COLOR player=BLUE;
	MODE current;
	char input_str[INPUT_SIZE];
	char file_name[30];
	char arguments;
	while((arguments=getopt(argc,argv,"ns:l:"))!=-1){
		switch(arguments){
			case 'n':
				current=NEW;
				break;
			case 'l':
				current=LOAD;
				strncpy(file_name,optarg,30);
				break;
			case 's':
				strncpy(file_name,optarg,30);
				break;
			default:
				break;
		}
	}
	
	switch(current){
		case LOAD:
			read_file(&record,file_name);
			while(true){
				printf("foward=f , back=b : ");
				scanf(" %s",input_str);
				step now;
				if(input_str[0]=='f' && turn<record.top){
					turn+=1;
					now=record.content[turn];
					//printf("start %d,%d end %d,%d promote %d capture %d\n",now.start.x,now.start.y,now.end.x,now.end.y,now.promote,now.capture);
					move_chess(board,now.start,now.end,now.promote);
					player=!player;
					show(board);
				}else if(input_str[0]=='b' && turn>=0){
					now=record.content[turn];
					//printf("start %d,%d end %d,%d promote %d capture %d\n",now.start.x,now.start.y,now.end.x,now.end.y,now.promote,now.capture);
					turn-=1;
					regret(board,now,player);
					player=!player;
					show(board);
				}else{
					printf("invalid\n");
				}
			}
			break;
		case NEW:
			while(true){
				printf("player %d : ",player);
				fgets(input_str,INPUT_SIZE,stdin);
				if(input_str[0] == 's'){
					write_file(&record,file_name);
				}else if(input_str[0] =='0' && turn >0){
					step back = pop(&record);
					regret(board,back,player);
					player = !player;
					turn-=1;
					show(board);
					//print_stack(&record);
				}else{
					get_move(&start,&end,input_str);
					//printf("end %d %d\n",end.x,end.y);
					//printf("start %d %d\n",start.x,start.y);
					if(valid_move(board,start,end,player)){
						CHESS_TYPE capture=board[end.y][end.x].type;
						bool check_promote = false;
				
						if(can_promote(board[start.y][start.x].type,start,end,player)){
							printf("Do you want to promote %s ? Yes:1 No:0 :",chess_name[board[start.y][start.x].type]);
							fgets(input_str,INPUT_SIZE,stdin);
							if(input_str[0]=='1')check_promote=true;
						}
						move_chess(board,start,end,check_promote);
						step now={.start=start,.end=end,.promote=check_promote,.capture=capture};
						push(&record,now);
						turn+=1;
						player = !player;
						show(board);
						//print_stack(&record);
					}else{
						printf("invalid input !\n");
					}
				}
			}
			break;
		default:
			break;
	}
	return 0;
}
