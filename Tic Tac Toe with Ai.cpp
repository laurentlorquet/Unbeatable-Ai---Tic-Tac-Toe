#include <iostream>
using namespace std;

const short SIZE = 3;

class Board
{
    private:
        char block[SIZE][SIZE], 
        ai_Mark, user_Mark;
    public:
        Board();
        void show_instructions();
        void show();
        //Gets pre-approved user move.  
        void userMove(short n, short n2)
        {block[n][n2] = user_Mark;}
        bool valid_move(short n, short n2);
        void computerMove(short n);
        bool win();
        bool lose();
        bool full();
        void clear();
};

//Constructor initializes each space (square) to a blank space and the markers to x and o.
Board::Board()
{
    user_Mark = 'x', ai_Mark = 'o';
    for(short i = 0; i < SIZE; i++){
        for(short j = 0; j < SIZE; j++){
            block[i][j] = ' ';
        }
    }
}

//Outlines the basic instructions and coordinate system.
void Board::show_instructions(){
    cout<<"This is a Tic Tac Toe progam. All of the standard rules of Tic Tac Toe apply (i.e. three in a row is a victory).\n"
        <<"A player may make a move by inputting the coordinance of the point they would like "
        <<"to mark (ex. type \"0 0\" for the first space).\nAn outline of the table "
        <<"and coordinacnes are below:\n"
        <<"\n0 0 | 0 1 | 0 2\n"
        <<"----|-----|----\n"
        <<"1 0 | 1 1 | 1 2\n"
        <<"----|-----|----\n"
        <<"2 0 | 2 1 | 2 2\n\n";

    cout<<"Player 1 will make the first move, followed by Player 2, until the game ends. "
        <<"You are the x's, while the computer is the o's.\n";

    cout<<"Press enter when you are ready to continue. ";
    cin.get();
}

//Shows the current state of the board.
void Board::show()
{
    cout<<block[0][0]<<"  | "<<block[0][1]<<" | "<<block[0][2]<<endl
        <<"---|---|---"<<endl
        <<block[1][0]<<"  | "<<block[1][1]<<" | "<<block[1][2]<<endl
        <<"---|---|---"<<endl
        <<block[2][0]<<"  | "<<block[2][1]<<" | "<<block[2][2]<<endl;
}

//Checks to see if either the computer or user is making a valid move
bool Board::valid_move(short n, short n2)
{
    if(block[n][n2] == ai_Mark || block[n][n2] == user_Mark){
        return false;
    } else {
        return true;
    }
}

int main()
{
    Board laul;
    short choice, num, num2, count = 0;
    char choice2;

    //Displays instructions for users (only first time).
    laul.show_instructions();

    do {
        count++;

        cout<<endl<<"Game "<<count<<"\n";
        for(short i = 0; i < 26; i++){
            cout<<"-";
        }
        cout<<endl;

        cout<<"Select Player 1:\n"
            <<"1. User\n2. AI\nEnter choice (ex. 1 or 2): ";
        cin>>choice;
        if (choice != 1 || choice !=2){cin.clear();
            cout<<"ERROR: you have not entered a valid choice.\n";
            cout<<"Select Player 1:\n"
            <<"1. User\n2. AI\nEnter choice (ex. 1 or 2): ";
            cin >> choice;}

        //Determines which code to run based on who is Player 1
        //(i.e. runs case 1 if user is Player 1 and case 2 if AI is Player 1).
        switch(choice){
            //Runs when user is Player 1.
            case 1:
                cout<<"The game has begun. You are now Player 1. ";
                do {
                    cout<<"Enter your move as a coordinance as follows\n"; 
                    cout<<"First Coordinate [Enter], Second Coordinate [Enter]: ";
                    cin>>num>>num2;

                    while(num > 3 || num < 0 || num2 > 3 || num2 < 0 || !laul.valid_move(num, num2)){
                        cout<<"ERROR: you have not entered a valid coordinance.\n";
                        cout<<"Enter your move as a coordinance: ";
                        cin>>num>>num2;
                    }

                    //Executes moves.
                    laul.userMove(num, num2);
                    laul.computerMove(1);
                    laul.show();

                } while(!laul.lose() && !laul.win() && !laul.full());
                break;

            //Runs when AI is Player 1.
            case 2:
                cout<<"The game has begun. The computer is now Player 1.\n";

                //First computer move.
                laul.computerMove(2);
                laul.show();

                do {
                    cout<<"Enter your move as a coordinance: \n"; 
                    cout<<"First Coordinate [Enter], Second Coordinate [Enter]: ";
                    cin>>num>>num2;

                    while(num>3 || num < 0 || num2 > 3 || num2 < 0 || !laul.valid_move(num, num2)){
                        cout<<"ERROR: you have not entered a valid coordinance.\n";
                        cout<<"Enter your move as a coordinance: ";
                        cin>>num>>num2;
                    }

                    //Executes moves.
                    laul.userMove(num, num2);
                    laul.computerMove(2);
                    laul.show();

                } while (!laul.lose() && !laul.win() && !laul.full());
                break;

            default:
                //If user does not enter 1 or 2 runs this code.
                cout<<"You have not entered a valid option.\n";
                break;
        }

        laul.clear();

        cout<<"Would you like to try again? Enter y/n: ";
        cin>>choice2;

    } while (choice2 != 'n' && choice2 != 'N');

    cout<<"Thanks for playing!\n";

    return 0;
}

//A random assignment is made, then based on game type (i.e. if user is Player 1) a
//specialized move is selected, then if any cases of imminent defeat or victory are detected
//it responds accordingly.
void Board::computerMove(short n)
{
    if(win()){
        cout<<"You have won!\n";
        return;
    }

    if(full()){
        cout<<"You have tied the computer!\n";
        return;
    }

    short r, r2, r3;

    double seed;
    seed = time(0);
    srand(seed);
    r = 0 + rand() % 3;
    r2 = 0 + rand() % 3;

    //Starts off with a random move assignment in the event that no cases fit.
    while(!valid_move(r, r2)){
        r = 0 + rand() % 3;
        r2 = 0 + rand() % 3;
    }

    switch(n){
        //This code is employs strategies reserved specifically for when the computer moves second.
        case 1:
            if(valid_move(1,1) && (block[0][0] == user_Mark || block[0][2] == user_Mark || block[2][0] == user_Mark || block[2][2] == user_Mark)){
                //If the user begins in a corner AI moves to the center.
                r = 1, r2 = 1;
            } else if (block[1][1] == ai_Mark){
                //After AI moves to the center AI attempts to occupy an edge.
                if(valid_move(0,1)){
                    r = 0, r2 = 1;
                } else if (valid_move(1,0)){
                    r = 1, r2 = 0;
                } else if (valid_move(1,2)){
                    r = 1, r2 = 2;
                } else if (valid_move(2,1)){
                    r = 2, r2 = 1;
                }
            } else if (block[1][1] == user_Mark){
                //If the user begins in the center the AI moves to a corner.
                if(valid_move(0,0)){
                    r = 0, r2 = 0;
                } else if (valid_move(0,2)){
                    r = 0, r2 = 2;
                } else if (valid_move(2,0)){
                    r = 2, r2 = 0;
                } else if (valid_move(2,2)){
                    r = 2, r2 = 2;
                }
            } else if (block[0][1] == user_Mark || block[1][0] == user_Mark || block[1][2] == user_Mark || block[2][1] == user_Mark){
                //If the user starts on the side the AI moves to the center.
                r=1, r2=1;
            }
            break;

        //This code is employs strategies reserved specifically for when the computer moves first.
        case 2:
            if (valid_move(0,0) && valid_move(0,2) && valid_move(2,0) && valid_move(2,2)){
                //Makes sure that the computer starts in a corner.
                r3 = 0 + rand() % 4;

                if(r3 == 0){
                    r = 0, r2 = 0;
                } else if (r3 == 1){
                    r = 0, r2 = 2;
                } else if (r3 == 2){
                    r = 2, r2 = 0;
                } else if (r3 == 3){
                    r = 2, r2 = 2;
                }
            } else if (block[1][1] == user_Mark){
                //If the user moves to the center AI moves to the opposite corner.
                if(block[0][0] == ai_Mark && valid_move(2,2)){
                    r = 2, r2 = 2;
                } else if (block[0][2] == ai_Mark && valid_move(2,0)){
                    r = 2, r2 = 0;
                } else if (block[2][0] == ai_Mark && valid_move(0,2)){
                    r = 0, r2 = 2;
                } else if (block[2][2] == ai_Mark && valid_move(0,0)){
                    r = 0, r2 = 0;
                }
            } else if (block[1][1] != user_Mark){
                //If the user does not move to the center AI moves to another corner which ensures a win.
                if(valid_move(0,0)){
                    r = 0, r2 = 0;
                } else if (valid_move(0,2)){
                    r = 0, r2 = 2;
                } else if (valid_move(2,0)){
                    r = 2, r2 = 0;
                } else if (valid_move(2,2)){
                    r = 2, r2 = 2;
                }
            }

            break;
    }

    //CODE FOR CHECKING IMMINENT USER VICTORY BEGINS HERE.

    //Checks diagonals.
    if(block[2][0] == user_Mark && block[1][1] == user_Mark && block[0][2] == ' '){
        r = 0, r2 = 2;
    } else if (block[2][0] == ' ' && block[1][1] == user_Mark && block[0][2] == user_Mark){
        r = 2, r2 = 0;
    } else if (block[0][0] == ' ' && block[1][1] == user_Mark && block[2][2] == user_Mark){
        r = 0, r2 = 0;
    } else if (block[0][0] == user_Mark && block[1][1] == user_Mark && block[2][2] == ' '){
        r = 2, r2 = 2;
    } else if (block[0][0] == user_Mark && block[1][1] == ' ' && block[2][2] == user_Mark){
        r = 1, r2 = 1;
    } else if (block[2][0] == user_Mark && block[1][1] == ' ' && block[0][2] == user_Mark){
        r = 1, r2 = 1;
    }

    //Checks all vertical possibilities.
    if(block[0][0] == user_Mark && block[1][0] == user_Mark && block[2][0] == ' '){
        r = 2, r2 = 0;
    } else if (block[0][0] == user_Mark && block[1][0] == ' ' && block[2][0] == user_Mark){
        r = 1, r2 = 0;
    } else if (block[0][0] == ' ' && block[1][0] == user_Mark && block[2][0] == user_Mark){
        r = 0, r2 = 0;
    } else if (block[0][1] == user_Mark && block[1][1] == user_Mark && block[2][1] == ' '){
        r = 2, r2 = 1;
    } else if (block[0][1] == user_Mark && block[1][1] == ' ' && block[2][1] == user_Mark){
        r = 1, r2 = 1;
    } else if (block[0][1] == ' ' && block[1][1] == user_Mark && block[2][1] == user_Mark){
        r = 0, r2 = 1;
    } else if (block[0][2] == user_Mark && block[1][2] == user_Mark && block[2][2] == ' '){
        r = 2, r2 = 2;
    } else if (block[0][2] == user_Mark && block[1][2] == ' ' && block[2][2] == user_Mark){
        r = 1, r2 = 2;
    } else if (block[0][2] == ' ' && block[1][2] == user_Mark && block[2][2] == user_Mark){
        r = 0, r2 = 2;
    }

    //Checks all horizontal possibilities.
    if(block[0][0] == user_Mark && block[0][1] == user_Mark && block[0][2] == ' '){
        r = 0, r2 = 2;
    } else if (block[0][0] == user_Mark && block[0][1] == ' ' && block[0][2] == user_Mark){
        r = 0, r2 = 1;
    } else if (block[0][0] == ' ' && block[0][1] == user_Mark && block[0][2] == user_Mark){
        r = 0, r2 = 0;
    } else if (block[1][0] == user_Mark && block[1][1] == user_Mark && block[1][2] == ' '){
        r = 1, r2 = 2;
    } else if (block[1][0] == user_Mark && block[1][1] == ' ' && block[1][2] == user_Mark){
        r = 1, r2 = 1;
    } else if (block[1][0] == ' ' && block[1][1] == user_Mark && block[1][2] == user_Mark){
        r = 1, r2 = 0;
    } else if (block[2][0] == user_Mark && block[2][1] == user_Mark && block[2][2] == ' '){
        r = 2, r2 = 2;
    } else if (block[2][0] == user_Mark && block[2][1] == ' ' && block[2][2] == user_Mark){
        r = 2, r2 = 1;
    } else if (block[2][0] == ' ' && block[2][1] == user_Mark && block[2][2] == user_Mark){
        r = 2, r2 = 0;
    }

    //CODE FOR CHECKING IMMINENT USER VICTORY ENDS HERE.
    //CODE FOR CHECKING IMMINENT COMPUTER VICTORY BEGINS HERE.

    //Checks diagonals.
    if(block[2][0] == ai_Mark && block[1][1] == ai_Mark && block[0][2] == ' '){
        r = 0, r2 = 2;
    } else if (block[2][0] == ' ' && block[1][1] == ai_Mark && block[0][2] == ai_Mark){
        r = 2, r2 = 0;
    } else if (block[0][0] == ' ' && block[1][1] == ai_Mark && block[2][2] == ai_Mark){
        r = 0, r2 = 0;
    } else if (block[0][0] == ai_Mark && block[1][1] == ai_Mark && block[2][2] == ' '){
        r = 2, r2 = 2;
    } else if (block[0][0] == ai_Mark && block[1][1] == ' ' && block[2][2] == ai_Mark){
        r = 1, r2 = 1;
    } else if (block[2][0] == ai_Mark && block[1][1] == ' ' && block[0][2] == ai_Mark){
        r = 1, r2 = 1;
    }

    //Checks all vertical possibilities.
    if(block[0][0] == ai_Mark && block[1][0] == ai_Mark && block[2][0] == ' '){
        r = 2, r2 = 0;
    } else if (block[0][0] == ai_Mark && block[1][0] == ' ' && block[2][0] == ai_Mark){
        r = 1, r2 = 0;
    } else if (block[0][0] == ' ' && block[1][0] == ai_Mark && block[2][0] == ai_Mark){
        r = 0, r2 = 0;
    } else if (block[0][1] == ai_Mark && block[1][1] == ai_Mark && block[2][1] == ' '){
        r = 2, r2 = 1;
    } else if (block[0][1] == ai_Mark && block[1][1] == ' ' && block[2][1] == ai_Mark){
        r = 1, r2 = 1;
    } else if (block[0][1] == ' ' && block[1][1] == ai_Mark && block[2][1] == ai_Mark){
        r = 0, r2 = 1;
    } else if (block[0][2] == ai_Mark && block[1][2] == ai_Mark && block[2][2] == ' '){
        r = 2, r2 = 2;
    } else if (block[0][2] == ai_Mark && block[1][2] == ' ' && block[2][2] == ai_Mark){
        r = 1, r2 = 2;
    } else if (block[0][2] == ' ' && block[1][2] == ai_Mark && block[2][2] == ai_Mark){
        r = 0, r2 = 2;
    }

    //Checks all horizontal possibilities.
    if(block[0][0] == ai_Mark && block[0][1] == ai_Mark && block[0][2] == ' '){
        r = 0, r2 = 2;
    } else if (block[0][0] == ai_Mark && block[0][1] == ' ' && block[0][2] == ai_Mark){
        r = 0, r2 = 1;
    } else if (block[0][0] == ' ' && block[0][1] == ai_Mark && block[0][2] == ai_Mark){
        r = 0, r2 = 0;
    } else if (block[1][0] == ai_Mark && block[1][1] == ai_Mark && block[1][2] == ' '){
        r = 1, r2 = 2;
    } else if (block[1][0] == ai_Mark && block[1][1] == ' ' && block[1][2] == ai_Mark){
        r = 1, r2 = 1;
    } else if (block[1][0] == ' ' && block[1][1] == ai_Mark && block[1][2] == ai_Mark){
        r = 1, r2 = 0;
    } else if (block[2][0] == ai_Mark && block[2][1] == ai_Mark && block[2][2] == ' '){
        r = 2, r2 = 2;
    } else if (block[2][0] == ai_Mark && block[2][1] == ' ' && block[2][2] == ai_Mark){
        r = 2, r2 = 1;
    } else if (block[2][0] == ' ' && block[2][1] == ai_Mark && block[2][2] == ai_Mark){
        r = 2, r2 = 0;
    }

    //CODE FOR CHECKING IMMINENT COMPUTER VICTORY ENDS HERE.

    block[r][r2] = ai_Mark;

    if(lose()){
        cout<<"You have lost!\n";
        return;
    }

    if(full()){
        cout<<"You have tied the computer!\n";
        return;
    }

    if(!full() && !lose()){
        cout<<"Computer move: "<<r<<" "<<r2<<endl;
    }
}

//Checks to see if the user has made three moves in a row.
bool Board::win()
{
    if(block[0][0] == user_Mark && block[0][1] == user_Mark && block[0][2] == user_Mark){
        return true;
    } else if (block[1][0] == user_Mark && block[1][1] == user_Mark && block[1][2] == user_Mark){
        return true;
    } else if (block[2][0] == user_Mark && block[2][1] == user_Mark && block[2][2] == user_Mark){
        return true;
    } else if (block[0][0] == user_Mark && block[1][0] == user_Mark && block[2][0] == user_Mark){
        return true;
    } else if (block[0][1] == user_Mark && block[1][1] == user_Mark && block[2][1] == user_Mark){
        return true;
    } else if (block[0][2] == user_Mark && block[1][2] == user_Mark && block[2][2] == user_Mark){
        return true;
    } else if (block[0][0] == user_Mark && block[1][1] == user_Mark && block[2][2] == user_Mark){
        return true;
    } else if (block[0][2] == user_Mark && block[1][1] == user_Mark && block[2][0] == user_Mark){
        return true;
    } else {
        return false;
    }
}

//Checks to see if computer has made three moves in a row.
bool Board::lose()
{
    if(block[0][0] == ai_Mark && block[0][1] == ai_Mark && block[0][2] == ai_Mark){
        return true;
    } else if (block[1][0] == ai_Mark && block[1][1] == ai_Mark && block[1][2] == ai_Mark){
        return true;
    } else if (block[2][0] == ai_Mark && block[2][1] == ai_Mark && block[2][2] == ai_Mark){
        return true;
    } else if (block[0][0] == ai_Mark && block[1][0] == ai_Mark && block[2][0] == ai_Mark){
        return true;
    } else if (block[0][1] == ai_Mark && block[1][1] == ai_Mark && block[2][1] == ai_Mark){
        return true;
    } else if (block[0][2] == ai_Mark && block[1][2] == ai_Mark && block[2][2] == ai_Mark){
        return true;
    } else if (block[0][0] == ai_Mark && block[1][1] == ai_Mark && block[2][2] == ai_Mark){
        return true;
    } else if (block[0][2] == ai_Mark && block[1][1] == ai_Mark && block[2][0] == ai_Mark){
        return true;
    } else {
        return false;
    }
}

//Checks to see if all the squares are full; if they are, it returns false to indicate a tie.
bool Board::full()
{
    short count = 0;
    for(short i = 0; i < SIZE; i++){
        for(short j = 0; j < SIZE; j++){
            if(block[i][j] == ai_Mark || block[i][j] == user_Mark){
                count++;
            } else {
                continue;
            }
        }
    }

    if(count == 9){
        return true;
    } else {
        return false;
    }
}

//Clears board in event that it is not the first game.
void Board::clear()
{
    for(short i = 0; i < SIZE; i++){
        for(short j = 0; j < SIZE; j++){
            block[i][j] = ' ';
        }
    }
}