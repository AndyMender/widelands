/*
 * Copyright (C) 2002 by The Widelands Development Team
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include "widelands.h"
#include "interactive_base.h"
#include "map.h"
#include "options.h"
#include "mapview.h"
#include "minimap.h"

/*
==============================================================================

Interactive_Base IMPLEMENTATION

==============================================================================
*/

/*
===============
Interactive_Base::Interactive_Base
 
Initialize
===============
*/
Interactive_Base::Interactive_Base(Editor_Game_Base* g) :
  Panel(0, 0, 0, get_xres(), get_yres())
{
	// Switch to the new graphics system now, if necessary
   Section *s = g_options.pull_section("global");
	
	Sys_InitGraphics(GFXSYS_SW16, get_xres(), get_yres(), s->get_bool("fullscreen", false));

   memset(&m_maprenderinfo, 0, sizeof(m_maprenderinfo));   

   m_fieldsel_freeze = false;
   m_egbase=g;

   m_minimapview=0;
   m_mapview=0;
	
   
   set_fieldsel_radius(0);
}

/*
===============
Interactive_Base::~Interactive_Base

cleanups
===============
*/
Interactive_Base::~Interactive_Base(void)
{
	if (m_maprenderinfo.overlay_basic)
		free(m_maprenderinfo.overlay_basic);
	if (m_maprenderinfo.overlay_roads)
		free(m_maprenderinfo.overlay_roads);
}


/*
===============
Interactive_Base::set_fieldsel

Change the field selection. Does not honour the freeze!
===============
*/
void Interactive_Base::set_fieldsel(Coords c)
{
	m_maprenderinfo.fieldsel = c;
}


/*
===============
Interactive_Base::set_fieldsel_freeze

Field selection is frozen while the field action dialog is visible
===============
*/
void Interactive_Base::set_fieldsel_freeze(bool yes)
{
	m_fieldsel_freeze = yes;
}


/*
===============
Interactive_Base::get_xres [static]
Interactive_Base::get_yres [static]

Retrieve in-game resolution from g_options.
===============
*/
int Interactive_Base::get_xres()
{
	return g_options.pull_section("global")->get_int("xres", 640);
}

int Interactive_Base::get_yres()
{
	return g_options.pull_section("global")->get_int("yres", 480);
}


/*
===============
Interactive_Base::think

Called once per frame by the UI code
===============
*/
void Interactive_Base::think()
{
	// Call game logic here
   // The game advances
	m_egbase->think();
 
	// The entire screen needs to be redrawn (unit movement, tile animation, etc...)
	g_gr->update_fullscreen();
	
	// some of the UI windows need to think()
	Panel::think();
}


/** Interactive_Base::mainview_move(int x, int y)
 *
 * Signal handler for the main view's warpview updates the mini map's
 * viewpos marker position
 */
void Interactive_Base::mainview_move(int x, int y)
{
	if (get_minimapview()) {
		int maxx = MULTIPLY_WITH_FIELD_WIDTH(m_egbase->get_map()->get_width());
		int maxy = MULTIPLY_WITH_HALF_FIELD_HEIGHT(m_egbase->get_map()->get_height());

		x += get_mapview()->get_w()>>1;
		if (x >= maxx) x -= maxx;
		y += get_mapview()->get_h()>>1;
		if (y >= maxy) y -= maxy;

		get_minimapview()->set_view_pos(x, y);
	}
}

/** Interactive_Base::minimap_warp(int x, int y)
 *
 * Called whenever the player clicks on a location on the minimap.
 * Warps the main mapview position to the clicked location.
 */
void Interactive_Base::minimap_warp(int x, int y)
{
	x -= get_mapview()->get_w()>>1;
	if (x < 0) x += MULTIPLY_WITH_FIELD_WIDTH(m_egbase->get_map()->get_width());
	y -= get_mapview()->get_h()>>1;
	if (y < 0) y += MULTIPLY_WITH_HALF_FIELD_HEIGHT(m_egbase->get_map()->get_height());
	get_mapview()->set_viewpoint(x, y);
}


/** Interactive_Base::move_view_to(int fx, int fy)
 *
 * Move the mainview to the given position (in field coordinates)
 */
void Interactive_Base::move_view_to(int fx, int fy)
{
	int x = MULTIPLY_WITH_FIELD_WIDTH(fx);
	int y = MULTIPLY_WITH_HALF_FIELD_HEIGHT(fy);

	if (get_minimapview())
		get_minimapview()->set_view_pos(x, y);
	
	x -= get_mapview()->get_w()>>1;
	if (x < 0) x += MULTIPLY_WITH_FIELD_WIDTH(m_egbase->get_map()->get_width());
	y -= get_mapview()->get_h()>>1;
	if (y < 0) y += MULTIPLY_WITH_HALF_FIELD_HEIGHT(m_egbase->get_map()->get_height());
	get_mapview()->set_viewpoint(x, y);
}


/*
===============
Interactive_Base::warp_mouse_to_field

Move the mouse so that it's directly above the given field
===============
*/
void Interactive_Base::warp_mouse_to_field(Coords c)
{
	get_mapview()->warp_mouse_to_field(c);
}


