#include "capp.h"
#include "CSurface.h"

bool CApp::OnInit()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    if((Surf_Display = SDL_SetVideoMode(600, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
    {
        return false;
    }

    if((Surf_Grid = CSurface::OnLoad((char *)"images/grid.bmp")) == NULL)
    {
        cout<<"nope1";
        return false;
    }

    if((Surf_X = CSurface::OnLoad((char *)"images/x.bmp")) == NULL)
    {
        cout<<"nope2";
        return false;
    }

    if((Surf_O = CSurface::OnLoad((char *)"images/o.bmp")) == NULL)
    {
        cout<<"nope3";
        return false;
    }

    CSurface::Transparent(Surf_X, 255, 0, 255);
    CSurface::Transparent(Surf_O, 255, 0, 255);

    return true;
}
