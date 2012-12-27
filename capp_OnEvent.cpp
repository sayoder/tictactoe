#include "capp.h"

void CApp::OnEvent(SDL_Event* Event)
{
    CEvent::OnEvent(Event);
}


void CApp::FillGrid(int index)
{
    grid[index] = 1;
}

void CApp::ComputerTurn()
{
    grid[(int)RecursiveTurn(grid, 0, 2)] = 2;
}

double CApp::RecursiveTurn(int hypo_grid[9], int depth, int whoseHypoTurn)
{
    int winner = FindWinner(hypo_grid);
    if(winner != 0)
    {
        //seems like this should depend on whoseHypoTurn instead...
        //but that makes the computer play horribly. I don't understand why.
        if(winner == 1) return -1.0;
        else if(winner == 2) return 1.0;
    }
    else if(!IsEmptySpace(hypo_grid)) return 0;

    double totals_grid[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int temp_grid[9];
    for(int i = 0; i < 9; i++) 
    {
        temp_grid[i] = hypo_grid[i];
    }

    for(int i = 0; i < 9; i++)
    {
        if(hypo_grid[i] == 0)
        {
            temp_grid[i] = whoseHypoTurn;
            totals_grid[i] += (RecursiveTurn(temp_grid, depth+1, 2/whoseHypoTurn));
            temp_grid[i] = 0;
        }
    }
    
    //move is a struct defined in capp.h with two int attributes (index and score)
    move bestMove;
    bestMove.index = -1;
    if(whoseHypoTurn == 1) bestMove.score = 100000.0;
    if(whoseHypoTurn == 2) bestMove.score = -100000.0;
    double gridSum = 0.0;
    for(int i = 0; i < 9; i++)
    {
        gridSum += totals_grid[i] / 20;
        if((whoseHypoTurn == 2) && (totals_grid[i] > bestMove.score) && (hypo_grid[i] == 0)) 
        {
            bestMove.score = totals_grid[i];
            bestMove.index = i;
        }
        else if((whoseHypoTurn == 1) && (totals_grid[i] < bestMove.score) && (hypo_grid[i] == 0))
        {
            bestMove.score = totals_grid[i];
            bestMove.index = i;
        }
    }

    if(depth == 0)
    {
        for(int i = 0; i < 9; i++)
        {
            cout<<totals_grid[i]<<endl;
        }
        cout<<endl;
    }

    if(depth == 0) return bestMove.index;
    else return gridSum;
}

void CApp::OnLButtonDown(int mX, int mY)
{
    int index = ConvertCoordsToGridPos(mX, mY);
    if(grid[index] == 0 && IsEmptySpace(grid))
    {
        FillGrid(index);
        if(IsEmptySpace(grid))
        {
            ComputerTurn();
        }
    }
}

void CApp::OnExit()
{
    Running = false;
}
