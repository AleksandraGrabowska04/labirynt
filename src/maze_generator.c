#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//Program used for generation of the maze (numerically/in raw data) using the dfs algoritm.
//Jakub Malinowski

//Self-defined char as BOOL macro with customily 1 interpreted as TRUE and 0 as FALSE to 
//make things look clearer.
#define BOOL char
#define TRUE 1
#define FALSE 0

//There are four (4) possible directions (as we define at the beginning of this
//project/program), as there is only way for us to move horizontally or vertically
//(not at the same time though/not diagonally).

//Generally speaking whole program uses notation/convention in which: direction starts from UP 
//to LEFT (which logically means) rotating direction clockwise by 90 degress for each of the
//given directions (as seen below):
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
//We try to stick to this convention as well (i.e: in this order) when we
//write program's code (e.g: particular "if's" or switches) for redability/clarity.
//maybe replace this with enum instead later (?).

//Throughout this program we will use/interpret "x" as the "row number":
#define X curr_maze_cell_x
#define MAZE_HEIGHT 5

//and "y" as the "column number":
#define Y curr_maze_cell_y
#define MAZE_WIDTH 5

//(x = row, y = column - as in the standard mathematical m x n (rows x columns) notation).

//Described in greater detail in comments of the "translate_cell" function.
#define TRANSL_CELL_HGHT 3 //(we expand this macro name's abbreviation to: TRANSLATED_CELL_HEIGHT)
#define TRANSL_CELL_WDTH 3 //(TRANSLATED_CELL_WIDTH)

struct cell{ //maze cell
    int x, y;
    int last_step;
    BOOL is_wall_up, is_wall_right, is_wall_down, is_wall_left;
    BOOL was_visited;
};

struct node{ //data type used for the stack (additionally with storage of cell's ("element") data).
    struct cell *cell;
    struct node *prev_elem; //pointer to the "previous" element (cell) on the stack (bottom element to the one we are pointing at currently). 
};

struct node *stack_push(struct node *node, struct cell *pushed_cell){

    struct node *new = malloc(sizeof(struct node));
    new->cell = pushed_cell;
    new->prev_elem = node;
    return new; //returns pointer to the new top (element) of the stack.
}

void stack_free_elem(struct node **top /*points to the top of the stack*/){ //free's/removes the "uppermost" element on the stack (top) and makes "top" pointer point to the element "below" it.

    if(*top == NULL){ //stack is already empty.

        return;

    } else {

        struct node *temp;
        temp = (*top)->prev_elem;
        free(*top);
        *top = temp;
        return;

    }
}

//translates (returns translated) maze cell to 3x3 (3 by 3) matrix of zero's (0's) and one's (1's) (to make
//it easier/more compatible with other maze solving algoritmsv and its graphical representation).
char** translate_cells(struct cell maze[MAZE_HEIGHT][MAZE_WIDTH], int curr_maze_cell_x, int curr_maze_cell_y){
   
    //error/bug check:

    if(TRANSL_CELL_HGHT != 3 || TRANSL_CELL_WDTH != 3){
        printf("[Error]: Default translated cell's matrix dimension lengths has been changed!");
        printf("Please change it back to 3x3 dimension (height x width) lengths (They should be defined as TRANSL_CELL_HGHT and TRANSL_CELL_WDTH) or make edits/changes in the program's code.\n");
    }

    //memory allocation for cell's 3x3 matrix ("char[3][3]" array):
    //that's a pretty complicated piece of code (to grasp/understand) for non-C user - can change this to make it more/simple readable if need (change of macro usage just to "3" magic number (as the 3 by 3 (3x3) cell's matrix dimensions) instead).

    char** translated_form; //cell in translated form.
    translated_form = malloc(sizeof(char*) * TRANSL_CELL_HGHT); //"(malloc(sizeof(char*)*3);" before (*was more readable, but the current solution is more error proof (error proof of changing the macros values in the program definition)*)).
    for (int i = 0; i < TRANSL_CELL_HGHT; i++){

        *(translated_form + i) = malloc(sizeof(char) * TRANSL_CELL_WDTH);

        for (int j = 0; j < TRANSL_CELL_WDTH; j++)
        {
            translated_form[i][j] = 0;
        }
        
    }

    //cell's translation/conversion to 3x3 numeric matrix representation:

    //describing all of the wall placement possibilities:
    if(maze[X][Y].x == 0 || maze[X][Y].is_wall_up){ //upper wall.
        translated_form[0][0] = 1;
        translated_form[0][1] = 1;
        translated_form[0][2] = 1;
    }

    if(maze[X][Y].y == MAZE_WIDTH-1 || maze[X][Y].is_wall_right){ //right wall.
        translated_form[0][2] = 1;
        translated_form[1][2] = 1;
        translated_form[2][2] = 1;
    }

    if(maze[X][Y].x == MAZE_HEIGHT-1 || maze[X][Y].is_wall_down){ //bottom wall.
        translated_form[2][0] = 1;
        translated_form[2][1] = 1;
        translated_form[2][2] = 1;
    }

    if(maze[X][Y].y == 0 || maze[X][Y].is_wall_left){ //left wall.
        translated_form[0][0] = 1;
        translated_form[1][0] = 1;
        translated_form[2][0] = 1;
    }

    //"Corners":
    if(X > 0 && Y < MAZE_WIDTH-1) //constraints to make sure we don't "jump out" of the bonds.
        if(maze[X-1][Y].is_wall_right && maze[X][Y+1].is_wall_up){//upper right corner (we need to check walls of the surrondning cells)
            translated_form[0][2] = 1; //of cell[X][Y]
        }

    if(X < MAZE_HEIGHT-1 && Y < MAZE_WIDTH-1)
        if(maze[X][Y+1].is_wall_down && maze[X+1][Y].is_wall_right){//bottom (lower) right corner
            translated_form[2][2] = 1;
        }

    if(X < MAZE_HEIGHT-1 && Y > 0)
        if(maze[X+1][Y].is_wall_left && maze[X][Y-1].is_wall_down){//bottom left corner
            translated_form[2][0] = 1;
        }

    if(X > 0 && Y > 0)
        if(maze[X][Y-1].is_wall_up && maze[X-1][Y].is_wall_left){//upper left corner
            translated_form[0][0] = 1;
        }

    return translated_form; //translated cell form
    
}

//prints a maze in its "translated" (check "translate_cells" function) form.
void print_maze(char** translated_maze[MAZE_HEIGHT][MAZE_WIDTH]){
    //kept this way (in 4-dimensions) because "unfortunately" it's objectively more readable.

    for(int maze_x = 0; maze_x < MAZE_HEIGHT; maze_x++){

        for(int cell_x = 0; cell_x < TRANSL_CELL_HGHT; cell_x++){

            for (int maze_y = 0; maze_y < MAZE_WIDTH; maze_y++)
            {
                for (int cell_y = 0; cell_y < TRANSL_CELL_WDTH; cell_y++)
                {
                    printf("%d", translated_maze[maze_x][maze_y][cell_x][cell_y]); //kept this way (in 4-dimensions) because it's objectively more readable.
                }
            }
            printf("\n");

        }

    }
}

int main(){

    srand(time(NULL));

    struct cell maze[MAZE_HEIGHT][MAZE_WIDTH];

    for (int i = 0; i < MAZE_HEIGHT; i++)
        for (int j = 0; j < MAZE_WIDTH; j++){

            maze[i][j].is_wall_up = maze[i][j].is_wall_right = 
            maze[i][j].is_wall_down = maze[i][j].is_wall_left = 
            maze[i][j].was_visited = FALSE; //setting everything to "zero" i.e: default value (no maze data yet).

            maze[i][j].last_step = -1;
        }
    
    struct node *top = malloc(sizeof(struct node)); //pointer to the top of the stack.
    top->cell = &maze[0][0]; //I decided to do this (manually define first element of the stack) instead of implementing definition of the first (NULL) element on the stack. 
    top->prev_elem = NULL; //There is "nothing" before the first element of the stack (so that's NULL).

    BOOL is_end = FALSE; //informs if the process of generating the maze by dfs is complete.
    BOOL was_step_successful; //checks whether the choosing of the next maze cell was successful.
    int direction; //used in storing randomized value for current direction
    int last_step = -1; //what was the direction of the last step.
    int curr_maze_cell_x = 0; //current maze cell x location (row).
    int curr_maze_cell_y = 0; //current maze cell y location (column).
    BOOL was_last_move_pop = FALSE; //checks if last iteration of while loop was popping of the cell on the stack (backtracking), to avoid placing walls which close the way to exit.

    while(!is_end){

      /*Important:
        X (macro) = curr_maze_cell_x,
        Y (macro) = curr_maze_cell_y.
        (used to shortcut/don't make the while's condition too long).*/

        //Since we have to enter every of the maze cells before the dfs algorithm ends, we take
        //the chance/opportunity to save operation numbers and define each cell's (their own)
        //x and y's to remember their position later for the "translate_cells" function.
        top->cell->x = X;
        top->cell->y = Y;

        was_step_successful = FALSE; //Needed to check whether the randomized step was successful and if we can leave the "while" loop.

        top->cell->was_visited = TRUE;

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

        //out of bounds check:
        if( (X-1 < 0 || maze[X-1][Y].was_visited) && 
            (Y+1 > MAZE_WIDTH-1 || maze[X][Y+1].was_visited) && 
            (X+1 > MAZE_HEIGHT-1 || maze[X+1][Y].was_visited) &&
            (Y-1 < 0 || maze[X][Y-1].was_visited))
        {

            stack_free_elem(&top); //we take out one element (cell) from the bottom of the current(ly pointed) element (cell) on the stack.
            if(top == NULL)
                is_end = TRUE; //all cells in the maze were checked, we are at the beginning of the maze again (even without the first element now), we can end the dfs procedure of generating the maze.
            else{
                X = top->cell->x; //remembering our current "maze cell position". 
                Y = top->cell->y;
                last_step = top->cell->last_step; //we need to store/remember what was the last randomized step's direction made by the dfs algorithm (in order to backtrack where did we come from).
            }

            was_last_move_pop = TRUE;
            
        } else {

            while(!was_step_successful){

                direction = rand()%4; //randomzies number from 0 to 3 (*up* to *left* (see consant (macro) values definition at the beginning of this file)).

                switch (direction){

                    case UP:
                    
                        //(maybe comment/explain this in more detail later...)
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

    //Translating the maze cells:
    char** translated_maze[MAZE_HEIGHT][MAZE_WIDTH];

    for (int i = 0; i < MAZE_HEIGHT; i++)
    {
        for (int j = 0; j < MAZE_WIDTH; j++)
        {
            translated_maze[i][j] = translate_cells(maze, i, j);
        }
        
    }
    
    print_maze(translated_maze);

    return 0;
}