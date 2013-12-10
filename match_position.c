#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define F_NAME_LEN 1024

struct options {
	int help;
	int stat;
	int qsize;
	char *sfile;
	char *qfile;
};

void help(void){
	printf("USAGE:\n");
	printf(" match_potistion [-h] [-s] qf=<query file> sf=<source file> [qb=<query buf>] -seek(not available)\n");
	printf("  -h : help.\n");
	printf("  -s : status.\n");
	printf("  qf : query file.\n");
	printf("  sf : source file.\n");
	printf("  qb : query buffer size,\n");
	printf("     | -qb=0 : auto.\n");
	printf("  -seek : seek source file without buffer.\n");
}

void status(void){
	printf("STATUS:\n");
	printf(" Under construction.\n");
}

struct options *alloc_options(void){
	struct options *p;
	if((p = malloc(sizeof(struct options) * 1)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).sfile = malloc(sizeof(char) * F_NAME_LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).qfile = malloc(sizeof(char) * F_NAME_LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	return(p);
}

void init_options(struct options *opt){
	(*opt).help = 0;
	(*opt).stat = 0;
	(*opt).qsize = 0;
	(*opt).sfile[0] = '\0';
	(*opt).qfile[0] = '\0';
}

void get_options(int optc, char **optv, struct options *opt){
	int i = 0;
	for(i=0;i<optc;i++){
		if(strcmp(optv[i],"-h") == 0){
			(*opt).help = 1;
		}else if(strcmp(optv[i],"-s") == 0){
			(*opt).stat = 1;
		}else if(strncmp(optv[i],"qf=",3) == 0){
			sscanf(optv[i],"qf=%s",(*opt).qfile);
		}else if(strncmp(optv[i],"sf=",3) == 0){
			sscanf(optv[i],"sf=%s",(*opt).sfile);
		}else{
			fprintf(stderr,"%s : undefined.\n",optv[i]);
		}
	}
}

int main(int argc, char **argv){
	//vars
	struct options *opt;
	FILE *IN;
	FILE *SIN;
	struct stat st_qfile;
	struct stat st_sfile;
	char *qbuf;
	char c;
	int i;
	int j;
	int num_qptrs;
	int *qptrs;
	int curr_pos_qptr;
	int source_size;
	char *source;
	//int tmp_len;

	//option analysis
	opt = alloc_options();
	init_options(opt);
	get_options(argc-1, argv+1, opt);

	//put help
	if((*opt).help ==1){
		help();
	}
	//put status
	if((*opt).stat ==1){
		status();
	}
	//exit
	if(((*opt).help ==1) || ((*opt).stat ==1)){
		exit(0);
	}

	//get stat qfile
	stat((*opt).qfile, &st_qfile);
	//set (*opt).qsize
	(*opt).qsize = (st_qfile.st_size + 1);
	  //printf("st_size:%d:\n",(*opt).qsize);
	//alloc qbuf
	if((qbuf = malloc(sizeof(char) * (*opt).qsize)) == NULL){
		printf("failed : malloc() for qbuf.\n");
		exit(1);
	}

	//open qfile
	if((IN = fopen((*opt).qfile,"r")) == NULL){
		perror((*opt).qfile);
		exit(1);
	}
	//read qfile
	i = 0;
	num_qptrs = 0;
	while(((c = fgetc(IN)) != EOF)){
		if(c == '\n'){
			num_qptrs++;
			c = '\0';
		}
		qbuf[i] = c;
		i++;
	}
	qbuf[i] = '\0';
	//close qfile
	fclose(IN);

	//alloc qptrs
	if((qptrs = malloc(sizeof(int) * num_qptrs)) == NULL){
		printf("failed : malloc() for qptrs.\n");
		exit(1);
	}
	//record qptr
	i = 0;
	curr_pos_qptr = 0;
	qptrs[curr_pos_qptr] = i;
	for(i=0;i<(*opt).qsize;i++){
		if(qbuf[i] == '\0'){
			curr_pos_qptr++;
			qptrs[curr_pos_qptr] = (i+1);
		}
	}
	  //test
	//fprintf(stdout,":::%d:::\n",num_qptrs);
	//for(i=0;i<num_qptrs;i++){
	//	fprintf(stdout,"%s",qbuf+(qptrs[i]));
	//	fprintf(stdout,":%d:",strlen(qbuf+(qptrs[i])));
	//}
	//fprintf(stdout,"\n");

	//get stat sfile
	stat((*opt).sfile, &st_sfile);
	//printf("OK2\n");
	//set source_size
	source_size = (st_sfile.st_size + 1);
	//alloc source
	if((source = malloc(sizeof(char)*(source_size + 1))) == NULL){
		printf("failed : malloc() for source.\n");
		exit(1);
	}

	//open sfile
	if((SIN = fopen((*opt).sfile,"r")) == NULL){
		perror((*opt).sfile);
		exit(1);
	}
	//read sfile
	i = 0;
	while(((c = fgetc(SIN)) != EOF)){
		source[i] = c;
		i++;
	}
	fclose(SIN);
	source[i] = '\0';

	//scan
	for(i=0;i<num_qptrs;i++){  //query
		//printf("%s: ",qbuf+(qptrs[i]));
		for(j=0;j<source_size;j++){
			//printf("sptr:%d:\n",j);
			if(strncmp(qbuf+(qptrs[i]),source+j,strlen(qbuf+(qptrs[i]))) == 0){
				printf("%s	%d	%d\n",qbuf+(qptrs[i]),j,j-1+(int)strlen(qbuf+(qptrs[i])));
			}
		}
		//printf("\n");
	}
	return(0);
}
