#include "Damier.h"
#include <GL/glut.h>
#include "Shapes.h"
#include "Log.h"

Damier::Damier()
{
    reset();
}

void
Damier::clear()
{
    for(int i=0; i<SIZE; i++)
        tab[i] = EMPTY;
}

void
Damier::reset()
{
    clear();
    for(int i=0; i<20; i++)
    {
        tab[i] = WHITE;
        tab[50-i-1] = BLACK;
    }
}

void
Damier::set(Piece p, int i)
{
    if(i < 0 || i > SIZE)
        return;

    tab[i] = p;

}

Damier::Piece
Damier::at(int i)
{
    if(i < 0 || i > SIZE)
        return EMPTY;

    return tab[i];
}

short decrementRight(short x)
{
   if((x/5)==0)
        return(-1);
   else
   {
       switch (x%10)
        {
            case 5: return(x-5);
                    break;
            case 4: return(-1);
                    break;
            case 0 ... 3 : return(x-4);
                            break;
            case 6 ... 9 : return(x-5);
                            break;
        }
   }
   return -1;
}

static short decrementLeft(short x)
{
   if((x/5)==0)
        return(-1);
   else
   {
       switch (x%10)
        {
            case 5: return(-1);
                    break;
            case 4: return(x-5);
                    break;
            case 0 ... 3 : return(x-5);
                            break;
            case 6 ... 9 : return(x-6);
                            break;
        }
   }
   return -1;
}
static short incrementLeft(short x)
{
   if((x/5)==9)
        return(-1);
   else
   {
       switch (x%10)
        {
            case 5: return(-1);
                    break;
            case 4: return(x+5);
                    break;
            case 0 ...3 : return(x+5);
                            break;
            case 6 ... 9 : return(x+4);
                            break;
        }
   }
   return -1;
}
static short incrementRight(short x)
{
   if((x/5)==9)
        return(-1);
   else
   {
       switch (x%10)
        {
            case 5: return(x+5);
                    break;
            case 4: return(-1);
                    break;
            case 0 ... 3 : return(x+6);
                            break;
            case 6 ... 9 : return(x+5);
                            break;
        }
   }
   return(-1);
}
std::vector<short>
Damier::whiteNormalMouvement(short x)
{
    std::vector<short> v;
    short a=decrementLeft(x);
    short b=decrementRight(x);
    if( (a !=(-1)) && tab[a] == EMPTY)
        v.push_back(a);
    if( (b!=(-1)) && tab[a] == EMPTY )
        v.push_back(b);
    return(v);
}
std::vector<short>
Damier::blackNormalMouvement(short x)
{
    std::vector<short> v;
    short a=incrementLeft(x);
    short b=incrementRight(x);
    if( (a !=(-1)) && tab[a] == EMPTY )
        v.push_back(a);
    if( (b!=(-1)) && tab[a] == EMPTY )
        v.push_back(b);
    return(v);
}


void
Damier::draw()
{
    int x = 0, y = 0;
    glPushMatrix();
    glColor3ub(255,255,255);
    drawRectangleFilled(x, y, 1, 1);

    glColor3ub(162,145,107);
    float ox = x - 0.5f;
    float oy = y - 0.5f;
    for(int i = 0; i<10; i++)
    {
        for(int j = 0; j<10; j++)
        {
            if((i+j)%2 == 0)
                drawRectangleFilled(ox+i*0.1f, oy+j*0.1f, 0.1f, 0.1f, false);
        }
    }

    ox += 0.05f;
    oy += 0.05f;
    for(int i = 0; i<10; i++)
    {
        for(int j = 0; j<10; j++)
        {
            if((i+j)%2 == 0)
            {
                switch(tab[(i*10 + j)/2])
                {
                    case WHITE:
                        glColor3ub(255,255,255);
                        drawCircleFilled(ox+j*0.1f,oy+i*0.1f, 0.04f, 15);
                        break;
                    case BLACK:
                        glColor3ub(0,0,0);
                        drawCircleFilled( ox+j*0.1f, oy+i*0.1f, 0.04f, 15);
                        break;
                    case WHITE_KING :
                        glColor3ub(255,255,255);
                        drawCircleFilled(ox+j*0.1f,oy+i*0.1f, 0.04f, 15);
                        glColor3ub(0, 0, 0);
                        drawKing(ox+j*0.1f, oy-0.01+i*0.1f, 0.03f);
                        break;
                    case BLACK_KING :
                        glColor3ub(0,0,0);
                        drawCircleFilled( ox+j*0.1f, oy+i*0.1f, 0.04f, 15);
                        glColor3ub(255, 255, 255);
                        drawKing(ox+j*0.1f, oy-0.01+i*0.1f, 0.03f);
                        break;
                    case EMPTY :
                        break;
                }
            }
        }
    }

    glPopMatrix();
}