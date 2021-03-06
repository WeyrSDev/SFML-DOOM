#include <ctype.h>

#include "doomdef.hpp"

#include "v_video.hpp"


#include "i_system.hpp"

#include "w_wad.hpp"

#include "st_stuff.hpp"
#include "st_lib.hpp"
#include "r_local.hpp"


// in AM_map.c
extern bool		automapactive; 




//
// Hack display negative frags.
//  Loads and store the stminus lump.
//
patch_t*		sttminus;

void STlib_init(void)
{
    sttminus = (patch_t *) WadManager::getLump("STTMINUS");
}


// ?
void
STlib_initNum
( st_number_t*		n,
  int			x,
  int			y,
  patch_t**		pl,
  int*			num,
  bool*		on,
  int			width )
{
    n->x	= x;
    n->y	= y;
    n->oldnum	= 0;
    n->width	= width;
    n->num	= num;
    n->on	= on;
    n->p	= pl;
}


// 
// A fairly efficient way to draw a number
//  based on differences from the old number.
// Note: worth the trouble?
//
void
STlib_drawNum
( st_number_t*	n,
  bool	refresh )
{
	//JONNY// Could we do something with sf::Font for this?
	// Might need to create/find a matching font though

    int		numdigits = n->width;
    int		num = *n->num;
    
    int		w = n->p[0]->width;
    int		h = n->p[0]->height;
    int		x = n->x;
    
    int		neg;

    n->oldnum = *n->num;

    neg = num < 0;

    if (neg)
    {
	if (numdigits == 2 && num < -9)
	    num = -9;
	else if (numdigits == 3 && num < -99)
	    num = -99;
	
	num = -num;
    }

    // clear the area
    x = n->x - numdigits*w;

    if (n->y - ST_Y < 0)
	I_Error("drawNum: n->y - ST_Y < 0");

    V_CopyRect(x, n->y - ST_Y, BG, w*numdigits, h, x, n->y, FG);

    // if non-number, do not draw it
    if (num == 1994)
	return;

    x = n->x;

    // in the special case of 0, you draw 0
    if (!num)
	V_DrawPatch(x - w, n->y, FG, n->p[ 0 ]);

    // draw the new number
    while (num && numdigits--)
    {
	x -= w;
	V_DrawPatch(x, n->y, FG, n->p[ num % 10 ]);
	num /= 10;
    }

    // draw a minus sign if necessary
    if (neg)
	V_DrawPatch(x - 8, n->y, FG, sttminus);
}


//
void
STlib_updateNum
( st_number_t*		n,
  bool		refresh )
{
    if (*n->on) STlib_drawNum(n, refresh);
}


//
void
STlib_initPercent
( st_percent_t*		p,
  int			x,
  int			y,
  patch_t**		pl,
  int*			num,
  bool*		on,
  patch_t*		percent )
{
    STlib_initNum(&p->n, x, y, pl, num, on, 3);
    p->p = percent;
}




void
STlib_updatePercent
( st_percent_t*		per,
  bool			refresh )
{
    if (refresh && *per->n.on)
	V_DrawPatch(per->n.x, per->n.y, FG, per->p);
    
    STlib_updateNum(&per->n, refresh);
}



void
STlib_initMultIcon
( st_multicon_t*	i,
  int			x,
  int			y,
  patch_t**		il,
  int*			inum,
  bool*		on )
{
    i->x	= x;
    i->y	= y;
    i->oldinum 	= -1;
    i->inum	= inum;
    i->on	= on;
    i->p	= il;
}



void
STlib_updateMultIcon
( st_multicon_t*	mi,
  bool		refresh )
{
    int			w;
    int			h;
    int			x;
    int			y;

    if (mi->on
	&& (mi->oldinum != *mi->inum || refresh)
	&& (*mi->inum!=-1))
    {
	if (mi->oldinum != -1)
	{
	    x = mi->x - mi->p[mi->oldinum]->leftoffset;
        y = mi->y - mi->p[mi->oldinum]->topoffset;
	    w = mi->p[mi->oldinum]->width;
	    h = mi->p[mi->oldinum]->height;

	    if (y - ST_Y < 0)
		I_Error("updateMultIcon: y - ST_Y < 0");

	    V_CopyRect(x, y-ST_Y, BG, w, h, x, y, FG);
	}
	V_DrawPatch(mi->x, mi->y, FG, mi->p[*mi->inum]);
	mi->oldinum = *mi->inum;
    }
}



void
STlib_initBinIcon
( st_binicon_t*		b,
  int			x,
  int			y,
  patch_t*		i,
  bool*		val,
  bool*		on )
{
    b->x	= x;
    b->y	= y;
    b->oldval	= 0;
    b->val	= val;
    b->on	= on;
    b->p	= i;
}



void
STlib_updateBinIcon
( st_binicon_t*		bi,
  bool		refresh )
{
    int			x;
    int			y;
    int			w;
    int			h;

    if (*bi->on
	&& ((bi->oldval==1) != *bi->val || refresh))
    {
	x = bi->x - bi->p->leftoffset;
	y = bi->y - bi->p->topoffset;
	w = bi->p->width;
	h = bi->p->height;

	if (y - ST_Y < 0)
	    I_Error("updateBinIcon: y - ST_Y < 0");

	if (*bi->val)
	    V_DrawPatch(bi->x, bi->y, FG, bi->p);
	else
	    V_CopyRect(x, y-ST_Y, BG, w, h, x, y, FG);

	bi->oldval = *bi->val;
    }

}

