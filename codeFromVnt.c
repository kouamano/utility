#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char **argv){
	FILE *IFP;
	int IFP_open = 0;
	int c;
	int BF = 0;	//buff switch
	char *minibuff;
	minibuff = malloc(sizeof(char)*4);
	minibuff[0] = '\0';
	int buff_count = 0;
	int v = 0;
	int noCL = 0;
	if(argc == 1){
		IFP = stdin;
	}else if(argc == 2){
		IFP = fopen(argv[1],"r");
		IFP_open++;
	}

	while((c = fgetc(IFP)) != EOF){
		noCL = 0;
		if(BF != 1 && c != '='){
			printf(":%02X:",c);
		}
		if((char)c == '='){
			//printf("!");
			BF = 1;
			buff_count = 0;
		}
		if(BF == 1){
			minibuff[buff_count] = (char)c;
			buff_count++;
			if(c == '\n'){
				BF = 0;
				minibuff[0] = '\0';
				buff_count = 0;
				noCL = 1;
			}
		}
		if(buff_count == 3){
			v = 0;
			minibuff[buff_count] = '\0';
			//printf(">%s<",minibuff);
			sscanf(minibuff+1,"%x",&v);
			if(v != 0){
				printf("<%02X>",v);
			}
			BF = 0;
			buff_count = 0;
		}
		if((char)c == '\n' && noCL == 0){
			printf("%c",(char)c);
		}
		//printf("<%02X>",c);
	}

	if(IFP_open > 0){
		fclose(IFP);
	}
}
