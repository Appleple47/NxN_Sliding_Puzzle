#include <iostream>
#include <vector>
#include <set>
using namespace std;

void show(vector<vector <int> > puzzle, int N);
bool isSolvable(const vector<int> flat, int N, int blank_row);

int main(){
    // Get the size of the puzzle from user input
    int N;
    while(N < 2 || N > 10){
        cout << "Input the size of NxN puzzle. (2 <= N <= 10) "<< endl << "N: ";
        cin >> N;
    }
    vector<vector <int> > puzzle(N, vector<int>(N));

    // Initialize puzzle and goal state (answer), shuffle numbers
    vector<int> numbers(N * N);
    vector<vector <int> > answer(N, vector<int>(N));
    for (int i = 0; i < N * N; ++i) {
        numbers[i] = i + 1;
    }
    srand(time(NULL));
    for (int i = numbers.size() - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(numbers[i], numbers[j]);
    }
    int index = 0, blankX, blankY;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            puzzle[i][j] = numbers[index];
            if(numbers[index] == N * N){
                blankX = i;
                blankY = j;
            }
            answer[i][j] = N * i + j + 1;
            index++;
        }
    }
    if(!isSolvable(numbers, N, blankX) || puzzle == answer){
        cout << "Sorry, you are unlucky to be made unsolvable pazzle. See you!" << endl;
        return 0;
    }

    cout <<"Game Start!" << endl;
    show(puzzle, N);
    int cnt = 0;

    // Main game loop: repeat until puzzle matches the goal state
    while(puzzle != answer){
        cout << "Which number do you want to move?" << endl<< "Choose one of them: ";

        set<int> userschoice;
        int choiceX = blankX, choiceY = blankY;
        if(choiceX + 1 < N){
            userschoice.insert(puzzle[choiceX + 1][choiceY]);
        }
        if(choiceX - 1  >= 0){
            userschoice.insert(puzzle[choiceX - 1][choiceY]);
        }
        if(choiceY + 1 < N){
            userschoice.insert(puzzle[choiceX][choiceY + 1]);
        }
        if(choiceY- 1 >= 0){
            userschoice.insert(puzzle[choiceX][choiceY - 1]);
        }

        int userinput = -1;
        for (auto itr = userschoice.begin(); itr != userschoice.end(); itr++) {
            if(*itr > 0) cout << *itr <<  " ";
        }
        cout << endl;
        while(userschoice.count(userinput) != 1){
            cin >> userinput;
            if(!userschoice.count(userinput)){
                cout << "CHOOSE IN THE RANGE" << endl;
            }
        }

        if(choiceX + 1 < N && puzzle[choiceX + 1][choiceY] == userinput){
            swap(puzzle[choiceX][choiceY], puzzle[choiceX + 1][choiceY]);
            blankX++;
        }
        else if(choiceX - 1  >= 0 && puzzle[choiceX - 1][choiceY] == userinput){
            swap(puzzle[choiceX][choiceY], puzzle[choiceX - 1][choiceY]);
            blankX--;
        }
        else if(choiceY + 1 < N && puzzle[choiceX][choiceY + 1] == userinput){
            swap(puzzle[choiceX][choiceY], puzzle[choiceX][choiceY + 1]);
            blankY++;
        }
        else if(choiceY - 1 >= 0 && puzzle[choiceX][choiceY - 1] == userinput){
            swap(puzzle[choiceX][choiceY], puzzle[choiceX][choiceY - 1]);
            blankY--;
        }
        cout << endl;
        show(puzzle, N);
        cnt++;
    }
    cout << "Clear!!" << endl << "You've cleared in " << cnt << " steps." << endl;
    return 0;
}

// Show the current state of the puzzle
void show(vector<vector <int> > puzzle, int N){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if(0 < puzzle[i][j] && puzzle[i][j] < 10 && puzzle[i][j] < N * N){
                cout << " " << puzzle[i][j] << " ";
            }else if(10 <= puzzle[i][j] && puzzle[i][j] < N * N){
                cout << puzzle[i][j] << " ";
            }else{
                cout << "   ";
            }
        }
        cout << endl;
    }
}

// Determine if the puzzle is solvable based on inversion count and blank row position
bool isSolvable(const vector<int> flat, int N, int blank_row){
    int inversions = 0;
    for (int i = 0; i < flat.size(); ++i) {
        if (flat[i] == N * N) continue;
        for (int j = i + 1; j < flat.size(); ++j) {
            if (flat[j] == N * N) continue;
            if (flat[i] > flat[j]) inversions++;
        }
    }

    if (N % 2 == 1) {
        return inversions % 2 == 0;
    } else {
        return (inversions + blank_row) % 2 == 1;
    }
}