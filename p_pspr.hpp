#pragma once

// Basic data types.
// Needs fixed point, and BAM angles.
#include "m_fixed.hpp"
#include "tables.hpp"


//
// Needs to include the precompiled
//  sprite animation tables.
// Header generated by multigen utility.
// This includes all the data for thing animation,
// i.e. the Thing Atrributes table
// and the Frame Sequence table.
#include "info.hpp"

//
// Frame flags:
// handles maximum brightness (torches, muzzle flare, light sources)
//
#define FF_FULLBRIGHT	0x8000	// flag in thing->frame
#define FF_FRAMEMASK	0x7fff



//
// Overlay psprites are scaled shapes
// drawn directly on the view screen,
// coordinates are given for a 320*200 view screen.
//
typedef enum
{
    ps_weapon,
    ps_flash,
    NUMPSPRITES

} psprnum_t;

typedef struct
{
    state_t*	state;	// a NULL state means not active
    int		tics;
    fixed_t	sx;
    fixed_t	sy;

} pspdef_t;
