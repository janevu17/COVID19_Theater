/*Author: Thao Vu
Date: 04- 13 - 2020
Description: Option #2 – Covid19 Theatre Seats
This option is to develop an algorithm that would find an optimal pattern to seat guests 
in a theatre where n is the number of rows and m is the number of seats.  
Like a "knights tour"
*/
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

// check if the seat is empty and in the theater space
bool isEmpty(int** map, int x, int y, int row, int col){
    return (((x >= 0 && y>= 0) && ( x < row && y < col)) && map[x][y] == 0);
}

// print theater's map
void printMap(int** map, int row, int column){
    for (int x = 0; x < row; x++){
        for (int y = 0; y < column; y++){
            cout << map[x][y];
        }
        cout << endl;
    }
}

//recursive method which starts from the first seat and keep finding eligible seat in 4 directions in order of
//west, south, east, north. Each eligible seat is marked with number 1. The method stops if there is no more
//eligible seats.
int solveSeat(int x, int y, int** map, int xMove[], int yMove[], int row, int col){
    int k, nextX, nextY,stop;
    stop = 1;

    for (int k = 0; k < 4; k++){
        nextX = x + xMove[k];
        nextY = y + yMove[k];
        if (isEmpty(map, nextX, nextY, row, col) == true){
            stop = 0;
            map[nextX][nextY] = 1;
            if (solveSeat(nextX,nextY,map, xMove, yMove, row, col) == 1) {
                return 1;
            }
        }      
    }
    if (stop == 1){
        return 1;
    }
    return 0;
}

// since we always start finding seat from the east, this method is used to filled in the eligible seats left 
// in the front row. The method is also recursive and it will stop if there is no more eligible seats 
int filledFirstRow(int y, int** map, int row, int col, int seatDistance){
    int nextY = y + ceil(72/seatDistance);
    if (isEmpty(map, 0, nextY, row, col) == true){
        map[0][nextY] = 1;
        if (filledFirstRow(nextY, map,row, col, seatDistance) == 1) {
            return 1;
        }
    }
    return 1;
}

//combined the two recursive methods then test out different map seats from different first row's seats 
//and print out the most optimized seating map for social distancing. 
void OptimizedMap(int rowDist, int seatDist, int row, int column, int** map){
    int OptFirst = 0;
    int countedSeats = 0;
    int xMove[4] = {0, ceil(72/rowDist), 0, -ceil(72/rowDist)};
    int yMove[4] = {-ceil(72/seatDist), 0, ceil(72/seatDist), 0};

    for (int y = 0; y < column; y++){
        int counted = 0;
        map[0][y] = 1;
        filledFirstRow(y, map, row, column, seatDist);
        solveSeat(0,y,map,xMove, yMove, row, column);
        
        for (int x = 0; x < row; x++){
            for (int y = 0; y < column; y++){
                if (map[x][y] == 1){
                    counted++;
                }
            }
        }
        if (counted > countedSeats){
            countedSeats = counted;
            OptFirst = y;
        }
        for (int x = 0; x < row; x++){
            for (int y = 0; y < column; y++){
                map[x][y] = 0;
            }
        }

    }
    map[0][OptFirst] = 1;
    filledFirstRow(OptFirst, map, row, column, seatDist);
    solveSeat(0, OptFirst, map, xMove, yMove, row, column);
    printMap(map, row, column);
    cout << "Available optimized seats: " << countedSeats << endl;

}

//prompt the row, seats, and distance between rows and seats from the user, then run the opmtimized program
// base on the given infomation. 
int main(int argc, char** argv){
    int** seatingMap;
    int seatDistance;
    int rowDistance;
    int seatRow;
    int seatColumn;

    cout << "Enter number of rows in theater: ";
    cin >> seatRow;
    while (seatRow <= 0){
        cout << "Invalid. Have your input be positive" << endl;
        cout << "Enter number of rows in theater: ";
        cin >> seatRow;
    }

    cout << "Enter number of seats per row: ";
    cin >> seatColumn;
    while (seatColumn <= 0){
        cout << "Invalid. Have your input be positive" << endl;
        cout << "Enter number of seats per row: ";
        cin >> seatColumn;
    }

    cout << "Enter distance between two continuous seats (in inches): ";
    cin >> seatDistance;
    while (seatDistance <= 0){
        cout << "Invalid. Have your input be positive" << endl;
        cout << "Enter distance between two continuous seats (in inches): ";
        cin >> seatDistance;
    }
    cout << "Enter distance between two continuous rows (in inches): ";
    cin >> rowDistance;
    while (seatDistance <= 0){
        cout << "Invalid. Have your input be positive" << endl;
        cout << "Enter distance between two continuous rows (in inches): ";
        cin >> seatDistance;
    }

    seatingMap = new int*[seatRow];
    for (int x = 0; x < seatRow; x++){
        seatingMap[x] = new int[seatColumn];
    }
    

    for (int x = 0; x < seatRow; x++){
        for (int y = 0; y < seatColumn; y++){
            seatingMap[x][y] = 0;
        }
    }
    cout << "The optimized seating map is:" << endl;
    OptimizedMap(rowDistance, seatDistance, seatRow, seatColumn, seatingMap);

    return 0;
}