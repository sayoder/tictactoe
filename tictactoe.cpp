#include "tictactoe.h"


CApp::CApp()
{
    Surf_Display = NULL;
    Surf_Grid = NULL;
    Surf_X = NULL;
    Surf_O = NULL;
    Running = true;

    for(int i = 0; i < 9; i++)
    {
        grid[i] = 0;
    }

    turnNumber = 0;
}

bool CApp::IsEmptySpace(int ngrid[9])
{
    bool FoundEmpty = false;
    for(int i = 0; i < 9; i++)
    {
        if (ngrid[i] == 0)
        {
            FoundEmpty = true;
        }
    }

    return FoundEmpty; 
}

winData CApp::FindWinner(int ngrid[9])
{
    int possibleWins[8][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {0, 3, 6},
        {1, 4, 7}, 
        {2, 5, 8},
        {0, 4, 8},
        {6, 4, 2}};

    int i = 0;
    int winner = 0;
    int winType = 0;
    while(i < 8 && winner == 0)
    {
        for(int j = 1; j < 3; j++)
        {
            if(ngrid[possibleWins[i][0]] == j &&
                ngrid[possibleWins[i][1]] == j &&
                ngrid[possibleWins[i][2]] == j)
            {
                winner = j;
                winType = i;
                break;
            }
        }
        i++;
    }
    
    winData gameResult;
    gameResult.winner = winner;
    gameResult.winType = winType;
    return gameResult;
}

int CApp::OnExecute()
{
    if(OnInit() == false)
    {
        return -1;
    }

    SDL_Event Event;

    while(Running)
    {
        SDL_Delay(5);
        while(SDL_PollEvent(&Event))
        {
            OnEvent(&Event);
        }
        OnLoop();
        OnRender();
    }

    OnCleanup();

    return 0;
}

int CApp::ConvertCoordsToGridPos(int mX, int mY)
{
    return (mX / 200) + (3 * (mY / 200));
}

SDL_Point CApp::ConvertGridPosToCoordinates(int pos)
{
    SDL_Point toReturn;
    int x, y;
    x = (pos % 3) * 200;
    y = (pos / 3) * 200; 
    toReturn.x = x;
    toReturn.y = y;
    return toReturn;
}

int main(int arc, char* argv[])
{
    CApp theApp;

    return theApp.OnExecute();
}
