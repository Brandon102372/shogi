#include "file_processing.h"
void write_file(const stack *st,const char *name){
	FILE *fptr;
	char file_name[30];
	int i;
	for(i=0;i<strlen(name);i++){
		file_name[i]=name[i];
	}
	file_name[strlen(name)]='\0';
	strcat(file_name,".bin");
	
	if ((fptr = fopen(file_name,"w")) == NULL){
		printf("Error! opening file\n");
   	}else{
   		printf("Saving file.......\r");
   		printf("top = %d",st->top);
		int i;
		step data;
		for(i=0;i<=st->top;i++){
			data=st->content[i];
			//printf("start: %d,%d end: %d,%d promote: %d capture %d\n",data.start.x,data.start.y,data.end.x,data.end.y,data.promote,data.capture);
			fwrite(&data, sizeof(step), 1, fptr); 
		}
		printf("Sucessfully save the file!\n");
	}
	fclose(fptr);
}

void read_file(stack *st,const char *name){
	FILE *fptr;
	char file_name[30];
	int i;
	for(i=0;i<strlen(name);i++){
		file_name[i]=name[i];
	}
	file_name[strlen(name)]='\0';
	strcat(file_name,".bin");
	
	if ((fptr = fopen(file_name,"r")) == NULL){
		printf("Error! opening file\n");
	}else{
		printf("Loading...\r");
		step read;
		while(!feof(fptr)){
			fread(&read, sizeof(step), 1, fptr);
			push(st,read);
		}
		pop(st);
		int i;
		for(i=0;i<=st->top;i++){
			read=st->content[i];
			printf("start %d,%d end %d,%d promote %d capture %d\n",read.start.x,read.start.y,read.end.x,read.end.y,read.promote,read.capture);
		}
		printf("Sucessfully load the file!\n");
	}
	fclose(fptr);
}
