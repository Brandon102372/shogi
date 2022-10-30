#include "file_processing.h"
void write_file(const stack st,const char *name){
	FILE *fptr;
	char file_name[30];
	int i;
	printf("len %d\n",strlen(name));
	for(i=0;i<strlen(name);i++){
		file_name[i]=name[i];
	}
	file_name[strlen(name)]='\0';
	strcat(file_name,".bin");
	
	if ((fptr = fopen(file_name,"w")) == NULL){
		printf("Error! opening file\n");
   	}else{
   		printf("Saving file.......\r");
		while(!isEmpty(&st)){
			step data=pop(&st);
			fwrite(&data, sizeof(step), 1, fptr); 
		}
		printf("Sucessfully save the file!\n");
	}
	fclose(fptr);
}
