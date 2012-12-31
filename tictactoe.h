#ifndef _CAPP_H_
    #define _CAPP_H_
#include <iostream>
#include <SDL/SDL.h>
#include <string>
#include "CSurface.h"
#include "CEvent.h"

using namespace std;

struct SDL_Point
{
    int x;
    int y;
};

struct move
{
    int index;
    double score;
    double scoreGrid[9];
};

struct winData
{
    //1 = human, 2 = computer, 0 = neither
    int winner;
    int winType;
};

class CApp : public CEvent
{
    private:
        bool Running;
        SDL_Surface * Surf_Display;
        SDL_Surface * Surf_Grid;
        SDL_Surface * Surf_X;
        SDL_Surface * Surf_O;
        int grid[9];
        void OnLButtonDown(int mX, int mY);    
        void FillGrid(int index);
        void ComputerTurn();
        move RecursiveTurn(int hypo_grid[9], int depth, int whoseHypoTurn);
        winData FindWinner(int ngrid[9]);
        bool IsEmptySpace(int ngrid[9]);
        int ConvertCoordsToGridPos(int mX, int mY);
        int turnNumber;

    public:
        CApp();
        int OnExecute();
        bool OnInit();
        void OnEvent(SDL_Event* Event);
        void OnExit();
        void OnLoop();
        void OnRender();
        void OnCleanup();
        SDL_Point ConvertGridPosToCoordinates(int pos);
};

#endif
