#ifndef MAZE_GEN
#define MAZE_GEN


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
/* definitions for maze size */

static char * hedges;
static char * vedges;
static int * squares;			        /* the maze data */
static int * hedgelist;			/* h edges left to check */
static int * vedgelist;			/* v edges left to check */
static int  SPACE;
static int XCOUNT;
static int YCOUNT;
static int INIT_FLAG=0;
char ** edgelist;

/* return 1 if the locations were the same.  Make them the same. */
/*
 * Each location in the maze points to some other location connected to it.
 * Because how this is constructed, these interrelations form a tree, and
 * you can check to see if two nodes are connected by going up to the roots,
 * and seeing if the roots are the same.
 *
 * This function adds one tree to the other if they're not connected.
 * As a side effect, it flattens the tree a bit for efficiency.
 */
int do_set(int * locations, int loc1, int loc2)
{
	int temp;

	/* chase loc1 down to the root */
	while (locations[loc1] != loc1)
	{
		temp = loc1;
		loc1 = locations[loc1];
		locations[temp] = locations[loc1];	/* flatten */
	}
	/* chase loc2 down to the root */
	while (locations[loc2] != loc2)
	{
		temp = loc2;
		loc2 = locations[loc2];
		locations[temp] = locations[loc2];	/* flatten */
	}
	/* are they connected somehow? */
	if (loc1 == loc2)
	{
		/* Yup, they were connected */
		return(1);
	} else {
		/* connect them */
		locations[loc2] = loc1;
		/* and say that they weren't connected before */
		return(0);
	}
}

void randomize(int v)
{
	int x, y;
	int hedgecount;				/* h edges count */
	int vedgecount;				/* v edges count */
	int index, curedge;
        if (v < 1){
          srand48((long)time((time_t *)NULL));
        }
        else{
          srand48((long)v);
        }
        
	/* set up the variables */
	hedgecount = 0;	/* haven't checked any horizontal edges yet */
	vedgecount = 0;	/* haven't checked any vertical edges yet */
	/* Initialize arrays of all horizontal edges left to check */
	for (x=0; x<XCOUNT; x++)
		for (y=1; y<YCOUNT; y++)
			hedgelist[hedgecount++] = x*YCOUNT+y;
	/* Initialize arrays of all vertical edges left to check */
	for (x=1; x<XCOUNT; x++)
		for (y=0; y<YCOUNT; y++)
			vedgelist[vedgecount++] = x*YCOUNT+y;

	/* label squares by what they're connected to: just self */
	for (x=0; x<XCOUNT; x++)
		for (y=0; y<YCOUNT; y++)
		{
			squares[x*YCOUNT+y] = x*YCOUNT+y;

		}
	
	/* and the interesting loop -- punch holes as necessary */
	while ((hedgecount > 0) || (vedgecount > 0))	/* all edges checked? */
	{
		/* do a horizontal edge if ... */
		if ((vedgecount == 0) ||	/* that's all that's left */
		    ((lrand48() % 2) &&	/* or 50/50 chance and */
		     (hedgecount > 0)))		/* there are some left */
		{
			/* horizontal edge */
			/* pick one at random from the unchecked */
			index = lrand48() % hedgecount;
			curedge = hedgelist[index];
			/* and remove it from the "to check" list */
			hedgelist[index] = hedgelist[--hedgecount];
			/* if the stuff on either side of it is already
			 * connected, leave it alone.  If they're not,
			 * then do_set connectes them, and we punch a hole
			 * in that wall */
			if (!do_set(squares,curedge,curedge-1)){
			  hedges[curedge] = 0;
                          x=curedge/YCOUNT;
                          y=curedge%YCOUNT;
			  edgelist[y*XCOUNT+x][0]=0;
			  edgelist[(y-1)*XCOUNT+x][2]=0;
			  //edgelist[curedge][0]=0;
                          //edgelist[curedge-1][2]=0;
                        }
                        else hedges[curedge]=1;
		} else {
			/* vertical edge */
			/* pick one at random from the unchecked */
			index = lrand48() % vedgecount;
			curedge = vedgelist[index];
			/* and remove it from the "to check" list */
			vedgelist[index] = vedgelist[--vedgecount];
			/* if the stuff on either side of it is already
			 * connected, leave it alone.  If they're not,
			 * then do_set connectes them, and we punch a hole
			 * in that wall */
			if (!do_set(squares,curedge,curedge-YCOUNT)){
			  vedges[curedge] = 0;
                          x=curedge/YCOUNT;
                          y=curedge%YCOUNT;
			  edgelist[y*XCOUNT+x][1]=0;
			  edgelist[y*XCOUNT+x-1][3]=0;
                          //edgelist[curedge][1]=0;
                          //edgelist[curedge-YCOUNT][3]=0;
                        }
                        else vedges[curedge]=1;

		}
	}
	/* Finish up the horizontal edges of the maze */
	for (x=0; x<XCOUNT; x++)
	{
		hedges[x*YCOUNT] = 1;
	}
	/* and the vertical edges too */
	for (y=0; y<YCOUNT; y++)
	{
		vedges[y] = 1;
	}
}

void print_edgelist(void)
{ int x,y;
  printf("---Start Edgelist----\n");
  for (y=0; y<YCOUNT; y++){
       for (x=0; x<XCOUNT; x++)
       {
	 printf("|%c:%c:%c:%c:",
           48+edgelist[y*XCOUNT+x][0],48+edgelist[y*XCOUNT+x][1],
           48+edgelist[y*XCOUNT+x][2],48+edgelist[y*XCOUNT+x][3]);
       }
       printf("|\n");
  }
  printf("---End Edgelist----\n");
}





/* and a function to display it using ascii graphics */
void print_maze(void)
{
	int x, y;

	/* first the arrow pointing in */
	for (x=0; x<XCOUNT; x++)
		if (hedges[x*YCOUNT])
		{
			putchar(' ');
			putchar(' ');
		}
		else
		{
			putchar(' ');
			putchar('|');
		}
	putchar('\n');
	for (x=0; x<XCOUNT; x++)
		if (hedges[x*YCOUNT])
		{
			putchar(' ');
			putchar(' ');
		}
		else
		{
			putchar(' ');
			putchar('v');
		}
	putchar('\n');

	/* and a main loop to draw the maze */
	for (y=0; y<YCOUNT; y++)
	{
		for (x=0; x<XCOUNT; x++)
		{
			putchar('+');
			if (hedges[x*YCOUNT+y])
				putchar('-');
			else
				putchar(' ');
		}
		putchar('+');
		putchar('\n');
		for (x=0; x<XCOUNT; x++)
		{
			if (vedges[x*YCOUNT+y])
				putchar('|');
			else
				putchar(' ');
			putchar(' ');
		}
		putchar('|');
		putchar('\n');
	}
	/* the bottom of the maze */
	for (x=0; x<XCOUNT; x++)
	{
		putchar('+');
		if (hedges[x*YCOUNT])
			putchar('-');
		else
			putchar(' ');
	}
	putchar('+');
	putchar('\n');
	/* and an arrow pointing out */
	for (x=0; x<XCOUNT; x++)
		if (hedges[x*YCOUNT])
		{
			putchar(' ');
			putchar(' ');
		}
		else
		{
			putchar(' ');
			putchar('|');
		}
	putchar('\n');
	for (x=0; x<XCOUNT; x++)
		if (hedges[x*YCOUNT])
		{
			putchar(' ');
			putchar(' ');
		}
		else
		{
			putchar(' ');
			putchar('v');
		}
	putchar('\n');
}


void print_tree(void){
  int x,y,index=0;
  printf("---Start Space Tree----\n");
  for (x=0; x<XCOUNT; x++){
       for (y=0; y<YCOUNT; y++)
       {
	 printf("|%d:%d",index++,squares[x*YCOUNT+y]);
       }
       printf("|\n");
  }
  printf("---End Space Tree----\n");
}




void mk_maze( int Maze_No)
{ int i;
  if (INIT_FLAG){
    printf("MAZE EXISTS, USE destroy_destroy FIRST\n");
  exit(1);
  }
  if (!((XCOUNT > 4) & (YCOUNT > 4))){
    printf("Minimum Array Size is 5x5\n");
    exit(EXIT_FAILURE);
  }
  SPACE=XCOUNT*YCOUNT;
  hedges=(char *) calloc(SPACE,sizeof(char));
  if (!hedges){
    printf("Insufficient Memory for Mazed\n");
    exit(EXIT_FAILURE);
  }
  vedges=(char *) calloc(SPACE,sizeof(char));
  if (!vedges){
    printf("Insufficient Memory for Mazed\n");
    exit(EXIT_FAILURE);
  }
  squares =(int *) calloc(SPACE,sizeof(int));
  if (!squares){
    printf("Insufficient Memory for Mazed\n");
    exit(EXIT_FAILURE);
  }
  hedgelist =(int *) calloc(SPACE,sizeof(int));
  if (!hedgelist){
    printf("Insufficient Memory for Mazed\n");
    exit(EXIT_FAILURE);
  }
  vedgelist =(int  *) calloc(SPACE,sizeof(int));
  if (!vedgelist){
    printf("Insufficient Memory for Mazed\n");
    exit(EXIT_FAILURE);
  }
  edgelist =(char  **) calloc(SPACE,sizeof(char *));
  if (!edgelist){
    printf("Insufficient Memory for Mazed\n");
    exit(EXIT_FAILURE);
  }
  /* edges are {N,W,S,E}; edgelist[4]==0, not in path and not checked;
     edgelist[4]==1, in current path;edgelist[4]==2 checked and excluded
  */
  for (i=0; i<SPACE; i++){
    edgelist[i]=(char *)calloc(6,sizeof(char));
    if ( edgelist[i]){
      edgelist[i][0]=1;
      edgelist[i][1]=1;
      edgelist[i][2]=1;
      edgelist[i][3]=1;
      edgelist[i][4]=0;
      edgelist[i][5]=0;
    }
    else{
      printf("Insufficient Memory for Maze \n");
       exit(EXIT_FAILURE);
    }
  }
  randomize(Maze_No);


}

int destroy_maze(void){
  int i;
  free(hedges);
  free(vedges);
  free(squares);
  free(hedgelist);
  free(vedgelist);
  for (i=0; i< SPACE; i++){
    free(edgelist[i]);
  } 
  free(edgelist);
  INIT_FLAG=0;
    return 0;

}




void createMaze(vector<vector<vector<int> > > &maze, int row, int col,int Maze_No){
     YCOUNT=row;
     XCOUNT=col;
     mk_maze(Maze_No);
     print_edgelist();
     for (int r=0; r<row; r++){
        maze.push_back(vector<vector<int> >());
     }
     for (int r=0; r<row; r++){
        for (int c=0; c<col; c++){
            maze[r].push_back(vector<int>());
        }
     }

       for (int r=0; r<row; r++){
         for (int c=0; c<col; c++){
            for (int i=0; i<4; i++){
                maze[r][c].push_back(edgelist[r*col+c][i]);
            }
	    maze[r][c].push_back(0);
            maze[r][c].push_back(0);
         }
       }
     destroy_maze();
}

#endif
