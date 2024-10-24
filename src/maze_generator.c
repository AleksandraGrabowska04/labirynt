#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define BOOL char
#define TRUE 1
#define FALSE 0

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
//replace this with enum instead later.

#define MAZE_WIDTH 4
#define MAZE_HEIGHT 4

#define X curr_maze_cell_x
#define Y curr_maze_cell_y

//Program used for generation of the maze (numerically/in raw data) using dfs algoritm
//Jakub Malinowski

struct cell{ //maze cell
    int x, y;
    int last_step;
    BOOL is_wall_up, is_wall_right, is_wall_down, is_wall_left;
    BOOL was_visited;
};

//struct stack
struct node{ //applied as stack of cells
    struct cell *cell;
    struct node *prev_elem; //pointer to the "previous" element (cell) on the stack (bottom element). 
};

struct node *stack_push(struct node *node, struct cell *pushed_cell){

    struct node *new = malloc(sizeof(struct node));
    new->cell = pushed_cell;
    new->prev_elem = node;
    return new;//returns pointer to the new top (element) of the stack.
}

void stack_pop(struct node **node /*points to the top of the stack*/){ //free's the uppermost element of the stack (top) and makes "top" pointer point to element below

    if(*node == NULL){ //stack is already empty.

        return;

    } else {

        struct node *temp;
        temp = (*node)->prev_elem;
        free(*node);
        *node = temp;
        return;

    }
}

int main(){

    srand(time(NULL));

    struct cell maze[MAZE_HEIGHT][MAZE_WIDTH];

    for (int i = 0; i < MAZE_HEIGHT; i++)
        for (int j = 0; j < MAZE_WIDTH; j++){
            
            maze[i][j].is_wall_up = maze[i][j].is_wall_right = 
            maze[i][j].is_wall_down = maze[i][j].is_wall_left = 
            maze[i][j].was_visited = FALSE; // setting everything to "zero" i.e: default value (no maze data yet).

            maze[i][j].last_step = -1;
        }
    

    struct node *top = malloc(sizeof(struct node)); //pointer to the top of the stack.
    top->cell = &maze[0][0]; //pol. tutaj byl problem (pierwszy element musi byc "recznie" zdefiniowany, bo wskazuje na NULL (dopiero na nim mozemy budowac reszte elementow/stawiac nastepne elementy (cells) na stack'u)).
    //top->cell->x = top->cell->y = 0;
    top->prev_elem = NULL;
    
    //top = stack_push(top, &maze[0][0]);//pol. problem tutaj? nie powinno byc: malloc cell itd. zamiast tego (zamiast "empty" node)?

    BOOL is_end = FALSE; //is process of generating the maze by dfs complete.
    BOOL was_step_successful; //checks whether the choosing of the next maze cell was successful.
    int direction;
    int last_step = -1; //what was the direction of the last step.
    int curr_maze_cell_x = 0; //current maze cell x location (row).
    int curr_maze_cell_y = 0; //current maze cell y location (column).
    BOOL was_last_move_pop = FALSE; //checks if last iteration of while loop was popping of the cell on the stack (backtracking), to avoid placing walls which close the way to exit.

    while(!is_end){

        top->cell->x = X;
        top->cell->y = Y;

        printf("X: %d Y: %d\n", X, Y);

        was_step_successful = FALSE;

        top->cell->was_visited = TRUE;

        //X (macro) = curr_maze_cell_x,
        //Y (macro) = curr_maze_cell_y.
        //(used to shortcut/don't make the while's condition too long).

        if(!was_last_move_pop){

            if(X-1 > -1 && maze[X-1][Y].was_visited && last_step != DOWN)

                top->cell->is_wall_up = TRUE;

            if(Y+1 < MAZE_WIDTH && maze[X][Y+1].was_visited && last_step != LEFT)

                top->cell->is_wall_right = TRUE;

            if(X+1 < MAZE_HEIGHT && maze[X+1][Y].was_visited && last_step != UP)

                top->cell->is_wall_down = TRUE;

            if(Y-1 > -1 && maze[X][Y-1].was_visited && last_step != RIGHT)
                        
                top->cell->is_wall_left = TRUE;
        }

        if( (X-1 < 0 || maze[X-1][Y].was_visited) && //out of bounds works just like if there was a wall (the frame of the maze).
            (Y+1 > MAZE_WIDTH-1 || maze[X][Y+1].was_visited) && 
            (X+1 > MAZE_HEIGHT-1 || maze[X+1][Y].was_visited) &&
            (Y-1 < 0 || maze[X][Y-1].was_visited))
        {

            printf("jestem tutaj!\n");

            stack_pop(&top); //pol. cofamy sie o jeden element (cell) "do tylu" (zdejmujemy (kolejny) cell z gory stacka).
            if(top == NULL)
                is_end = TRUE; //all cells in the maze were checked, we are at the beginning of the maze again (even without the first element now), we can end the dfs procedure of generating the maze.
            else{
                X = top->cell->x;
                Y = top->cell->y;
                last_step = top->cell->last_step; //pol. musimy pamietac "skad wrocilismy"/backtrack.
            }

            was_last_move_pop = TRUE;
            
        } else {

            while(!was_step_successful){

                direction = rand()%4; //randomzies number from 0 to 3 (up to left (see consant values definition at the beginning of this file)).

                printf("direction: %d\n", direction);
                //najlepiej jeszcze stack status i is_wall_up itd.

                switch (direction){

                    case UP:
                    
                        if(X-1 > -1 && !maze[X-1][Y].was_visited && last_step != DOWN){

                            X--;
                            //now we have our new curr(ent)_cell (which depends on the direction we have taken (successfully randomized in this while's iterations)).   
                            top = stack_push(top, &maze[X][Y]); //we push our current maze cell on the (top of the) stack.

                            was_step_successful = TRUE;
                            top->cell->last_step = last_step = UP;
                        }
                        break;

                    case RIGHT:

                        if(Y+1 < MAZE_WIDTH && !maze[X][Y+1].was_visited && last_step != LEFT){

                            Y++;
                            top = stack_push(top, &maze[X][Y]);

                            was_step_successful = TRUE;
                            top->cell->last_step = last_step = RIGHT;
                        }
                        break;

                    case DOWN:

                        if(X+1 < MAZE_HEIGHT && !maze[X+1][Y].was_visited && last_step != UP){

                            X++;
                            top = stack_push(top, &maze[X][Y]);

                            was_step_successful = TRUE;
                            top->cell->last_step = last_step = DOWN;
                        }
                        break;

                    case LEFT:

                        if(Y-1 > -1 && !maze[X][Y-1].was_visited && last_step != RIGHT){

                            Y--;
                            top = stack_push(top, &maze[X][Y]);

                            was_step_successful = TRUE;
                            top->cell->last_step = last_step = LEFT;
                        }
                        break;
                        
                    default:
                        printf("Invalid direction has been passed!!!\n");
                        return 1;
                }
            }

            was_last_move_pop = FALSE;

        }

    }
    

    return 0;
}