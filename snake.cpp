#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>

#define HEIGHT 20
#define WIDTH 60  

int target_x, target_y;
int head_x, head_y;
int score = 0;
int input_availbale();//if any input is there in the position of snake movement or not

enum Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STOP
};
enum Direction dir;

void setup();
void clear_screen();
void draw();
void set_terminal_attributes();
void reset_terminal_attributes();
void game_play();//main logic of the game 
void input();
int input_available();

struct termios old_props; 

int main() {
    srand(time(NULL));
    set_terminal_attributes();
    setup();
   while(1)
   {
    draw();
    input();
    game_play();
    sleep(1);
   }
    return 0;
}

void input()
{
    if(input_available()){
        char ch =getchar();
        switch (ch)
        {
        case 'a' :
        dir=LEFT;
            break;
        case 's':
        dir=DOWN;
            break;
        case 'd' :
        dir=RIGHT;
            break;
        case 'w':
        dir=UP;
            break;
        case 'x':
            exit(0);
            break;
        default:
            break;
        }
    }
}
void game_play() // making the snake move in the direction taken in the input
{
    switch (dir)
    {
    case UP:
    head_y--;
        /* code */
        break;
    
    case DOWN:
    head_y++;
        /* code */
        break;
    case LEFT:
    head_x--;
        /* code */
        break;
    case RIGHT:
    head_x++;
        /* code */
        break;
    case STOP:
        // do nothing
        break;
    }
    if(head_x<0){
        head_x=WIDTH-1;
    }
    else if(head_x>=WIDTH){
        head_x=0;
    }
    if(head_y<0){
        head_y=HEIGHT-1;
    }
    else if(head_y>=HEIGHT){
        head_y=0;
    }
    if(head_x== target_x && head_y == target_y)
    {
        score+=10;
        target_x = rand() % WIDTH;
        target_y = rand() % HEIGHT;
    }
}

int input_available(){
    struct timeval tv ={ 0L, 0L };
    fd_set fds;
    FD_SET(0,&fds);
    return select(1,&fds,NULL,NULL,&tv);  //if input available in keyborad then 1 and if not any input available in keyborad then 0
}

void setup() {
    head_x = HEIGHT / 2;  // Fixed order
    head_y = WIDTH / 2;
    target_x = rand() % WIDTH;
    target_y = rand() % HEIGHT;
    dir =STOP; // initail position of the snake
}

void set_terminal_attributes() {
    tcgetattr(STDIN_FILENO, &old_props);
    atexit(reset_terminal_attributes);
    
    struct termios new_props = old_props;
    new_props.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_props);
}

void reset_terminal_attributes() {  // Removed incorrect semicolon
    tcsetattr(STDIN_FILENO, TCSANOW, &old_props);  // Fixed function name
}

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void draw() {  // Display the game screen
    clear_screen();
    printf("\tWelcome to the World of Snake Game!!!!!!\n");

    for (int i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        printf("#");
        for (int j = 0; j < WIDTH; j++) {
            if (i == head_x && j == head_y) {
                printf("O");
            } else if (i == target_y && j == target_x) {
                printf("T");//
            } else {
                printf(" ");
            }
        }
        printf("#\n");  // Fixed missing border closing
    }

    for (int i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    
    printf("\nScore: %d\n", score);
}
