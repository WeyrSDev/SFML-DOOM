#pragma once

// We are referring to patches.
#include "r_defs.hpp"


//
// Background and foreground screen numbers
//
#define BG 4
#define FG 0



//
// Typedefs of widgets
//

// Number widget

typedef struct
{
    // upper right-hand corner
    //  of the number (right-justified)
    int		x;
    int		y;

    // max # of digits in number
    int width;    

    // last number value
    int		oldnum;
    
    // pointer to current value
    int*	num;

    // pointer to bool stating
    //  whether to update number
    bool*	on;

    // list of patches for 0-9
    patch_t**	p;

    // user data
    int data;
    
} st_number_t;



// Percent widget ("child" of number widget,
//  or, more precisely, contains a number widget.)
typedef struct
{
    // number information
    st_number_t		n;

    // percent sign graphic
    patch_t*		p;
    
} st_percent_t;



// Multiple Icon widget
typedef struct
{
     // center-justified location of icons
    int			x;
    int			y;

    // last icon number
    int			oldinum;

    // pointer to current icon
    int*		inum;

    // pointer to bool stating
    //  whether to update icon
    bool		on;

    // list of icons
    patch_t**		p;
    
    // user data
    int			data;
    
} st_multicon_t;




// Binary Icon widget

typedef struct
{
    // center-justified location of icon
    int			x;
    int			y;

    // last icon value
    int			oldval;

    // pointer to current icon status
    bool*		val;

    // pointer to bool
    //  stating whether to update icon
    bool*		on;  


    patch_t*		p;	// icon
    int			data;   // user data
    
} st_binicon_t;



//
// Widget creation, access, and update routines
//

// Initializes widget library.
// More precisely, initialize STMINUS,
//  everything else is done somewhere else.
//
void STlib_init(void);



// Number widget routines
void
STlib_initNum
( st_number_t*		n,
  int			x,
  int			y,
  patch_t**		pl,
  int*			num,
  bool*		on,
  int			width );

void
STlib_updateNum
( st_number_t*		n,
  bool		refresh );


// Percent widget routines
void
STlib_initPercent
( st_percent_t*		p,
  int			x,
  int			y,
  patch_t**		pl,
  int*			num,
  bool*		on,
  patch_t*		percent );


void
STlib_updatePercent
( st_percent_t*		per,
  bool			refresh );


// Multiple Icon widget routines
void
STlib_initMultIcon
( st_multicon_t*	mi,
  int			x,
  int			y,
  patch_t**		il,
  int*			inum,
  bool*		on );


void
STlib_updateMultIcon
( st_multicon_t*	mi,
  bool		refresh );

// Binary Icon widget routines

void
STlib_initBinIcon
( st_binicon_t*		b,
  int			x,
  int			y,
  patch_t*		i,
  bool*		val,
  bool*		on );

void
STlib_updateBinIcon
( st_binicon_t*		bi,
  bool		refresh );