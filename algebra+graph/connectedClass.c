/*connectedClass                      */
/* input : dfile -> adjacency matrix  */
/* connected : >= 1                   */
/* not-connected : 0                  */
/* diagonal : class                   */
/* output : Node Id list with class   */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/alloc.c"
#include "../../include/data_read.c"
#define FILE_NAME_LEN 1024
#define SEPS "\t "

struct options {
	int help;
	int stat;
	int check;
	int create;
	char *dfile;
	int msize;
};

void help(void){
	printf("DESCRIPTION:\n");
	printf(" connectedClass prints node IDs with its connected-class from adjacency matrix.\n");
	printf("USAGE:\n");
	printf(" connectedClass [-h] [-s] [-c] [-C] df=<file of distance matrix> size=<matrix size> .\n");
	printf("  -h : help.\n");
	printf("  -s : status.\n");
	printf("  -c : check args.\n");
	printf("  -C : create symmetric adjacency matrix from input.\n");
	printf("  file of distance matrix : with no header.\n");
	printf("  matrix size (size=0 :: auto) : size of square matrix.\n");
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
	if(((*p).dfile = malloc(sizeof(char) * FILE_NAME_LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	return(p);
}

void init_options(struct options *opt){
	(*opt).help = 0;
	(*opt).stat = 0;
	(*opt).check = 0;
	(*opt).create = 0;
	(*opt).dfile[0] = '\0';
	(*opt).msize = 0;
}

void get_options(int optc, char **optv, struct options *opt){
	int i = 0;
	for(i=0;i<optc;i++){
		if(strcmp(optv[i],"-h") == 0){
			(*opt).help = 1;
		}else if(strcmp(optv[i],"-s") == 0){
			(*opt).stat = 1;
		}else if(strcmp(optv[i],"-c") == 0){
			(*opt).check = 1;
		}else if(strcmp(optv[i],"-C") == 0){
			(*opt).create = 1;
		}else if(strncmp(optv[i],"df=",3) == 0){
			sscanf(optv[i],"df=%s",(*opt).dfile);
		}else if(strncmp(optv[i],"size=",5) == 0){
			sscanf(optv[i],"size=%d",&(*opt).msize);
		}else{
			printf("%s : undefined.",optv[i]);
		}
	}
}

void check_options(struct options *opt){
	printf("OPTIONS:\n");
	printf(" opt.dfile:%s:\n",(*opt).dfile);
	printf(" opt.msize:%d:\n",(*opt).msize);
}



int main(int argc, char **argv){
	FILE *fp;
	int c;
	int u,v,i,j,p,q,z;
	int ng = 0;
	int ie = 0;
	struct options *opt;
	float **dmat;

	opt = alloc_options();
	init_options(opt);
	get_options(argc-1, argv+1, opt);

	if(argc == 1){
		(*opt).help = 1;
	}
	if((*opt).help == 1){
		help();
		ie = 1;
	}
	if((*opt).stat == 1){
		status();
		ie = 1;
	}
	if((*opt).check == 1){
		check_options(opt);
		ie = 1;
	}
	if(ie == 1){
		exit(0);
	}

        if((*opt).msize == 0){   //auto-get of size
                int col = 0;
                if((fp = fopen((*opt).dfile,"r")) == NULL){
			perror((*opt).dfile);
			exit(1);
                }
                while((c=fgetc(fp)) != EOF){
                        if(c == SEPS[0]||c == SEPS[1]){
                                col++;
                        } else if(c == '\n'){
                                break;
                        }else{
                                ;
                        }
                }
                fclose(fp);
                ((*opt).msize) = (col+1);
        }

	if((fp = fopen((*opt).dfile,"r")) == NULL){
		perror((*opt).dfile);
		exit(1);
	}
	dmat = f_alloc_mat((*opt).msize,(*opt).msize);
	read_ftable_from_stream((*opt).msize, (*opt).msize,fp,dmat);
	fclose(fp);

	/* algorithm */
	/* class initialize */
	for(i=0;i<(*opt).msize;i++){
		dmat[i][i]=i;
	}
	/* create symmetric */

	/* minimum class */

	/* print dmat */
	for(i=0;i<(*opt).msize;i++){
		for(j=0;j<(*opt).msize;j++){
			printf("%f ",dmat[i][j]);
		}
		printf("\n");
	}

 
	return(0);
}
