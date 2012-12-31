#include "tictactoe.h"

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
    move bestMove = RecursiveTurn(grid, 0, 2);
    grid[(int)bestMove.index] = 2;
}

move CApp::RecursiveTurn(int hypo_grid[9], int depth, int whoseHypoTurn)
{
    winData hypoGameResult = FindWinner(hypo_grid);
    move toReturn;
    if(hypoGameResult.winner != 0)
    {
        if(hypoGameResult.winner == 1)
        {
            toReturn.score = -100.0;
            return toReturn;
        }
        else if(hypoGameResult.winner == 2)
        {
            toReturn.score = 100.0;
            return toReturn;
        }
    }
    else if(!IsEmptySpace(hypo_grid))
    {
        toReturn.score = 0.0;
        return toReturn;
    }

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
            totals_grid[i] += (RecursiveTurn(temp_grid, depth+1, 2/whoseHypoTurn)).score / 5;
            temp_grid[i] = 0;
        }
    }
    
    //move is a struct defined in capp.h with two int attributes (index and score)
    move bestMove;
    bestMove.index = -1;
    if(whoseHypoTurn == 1) bestMove.score = 100000.0;
    if(whoseHypoTurn == 2) bestMove.score = -100000.0;

    for(int i = 0; i < 9; i++)
    {
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
            bestMove.scoreGrid[i] = totals_grid[i];
            cout<<totals_grid[i]<<endl;
        }
        cout<<endl;
    }
    return bestMove;
}

void CApp::OnLButtonDown(int mX, int mY)
{
    //player turn
    int index = ConvertCoordsToGridPos(mX, mY);
    if(grid[index] == 0 && IsEmptySpace(grid))
    {
        turnNumber++;
        FillGrid(index);
    }

    //computer turn
    if(IsEmptySpace(grid))
    {
        turnNumber++;
        ComputerTurn();
    }
}

void CApp::OnExit()
{
    Running = false;
}
