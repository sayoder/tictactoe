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
    double index;
    double score;
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
        double RecursiveTurn(int hypo_grid[9], int depth, int whoseHypoTurn);
        int FindWinner(int ngrid[9]);
        bool IsEmptySpace(int ngrid[9]);
        int ConvertCoordsToGridPos(int mX, int mY);

    public:
        CApp();
        int OnExecute();
        bool OnInit();
        void OnEvent(SDL_Event* Event);
        void OnExit();
        void OnLoop();
        void OnRender();
        void OnCleanup();
        SDL_Point ConvertGridPos(int pos);
};

#endif
