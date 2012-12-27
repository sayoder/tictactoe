#include "capp.h"

void CApp::OnRender()
{
    for(int i = 0; i < 9; i++)
    {
        if(grid[i] == 1)
        {
            SDL_Point myPoint = ConvertGridPos(i);
            CSurface::OnDraw(Surf_Grid, Surf_X, myPoint.x, myPoint.y);
        }
        else if(grid[i] == 2)
        {
            SDL_Point myPoint = ConvertGridPos(i);
            CSurface::OnDraw(Surf_Grid, Surf_O, myPoint.x, myPoint.y);
        }
    }
    CSurface::OnDraw(Surf_Display, Surf_Grid, 0, 0);

    SDL_Flip(Surf_Display);
}
