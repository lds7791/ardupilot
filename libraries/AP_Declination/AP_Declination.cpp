/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-
#include "AP_Declination.h"

/*
 *	Adam M Rivera
 *	With direction from: Andrew Tridgell, Jason Short, Justin Beech
 *
 *	Adapted from: http://www.societyofrobots.com/robotforum/index.php?topic=11855.0
 *	Scott Ferguson
 *	scottfromscott@gmail.com
 *
*/

static const int8_t dec_tbl[25][73] PROGMEM = {46,46,45,44,44,43,42,42,41,41,40,39,38,37,36,35,33,31,28,26,23,20,16,13,10,7,4,1,-1,-3,-5,-7,-9,-12,-14,-16,-19,-22,-26,-29,-33,-36,-40,-44,-48,-51,-55,-58,-61,-64,-66,-68,-71,-72,-74,-74,-75,-74,-72,-68,-61,-48,-25,2,22,33,40,43,45,46,47,46,46,36,36,36,36,36,35,35,35,35,34,34,34,34,33,32,31,30,28,26,23,20,17,14,10,6,3,0,-2,-4,-7,-9,-10,-12,-14,-15,-17,-20,-23,-26,-29,-32,-36,-40,-43,-47,-50,-53,-56,-58,-60,-62,-63,-64,-64,-63,-62,-59,-55,-49,-41,-30,-17,-4,6,15,22,27,31,33,34,35,36,36,30,30,30,30,30,30,30,29,29,29,29,29,29,29,29,28,27,26,24,21,18,15,11,7,3,0,-3,-6,-9,-11,-12,-14,-15,-16,-17,-19,-21,-23,-26,-29,-32,-35,-39,-42,-45,-48,-51,-53,-55,-56,-57,-57,-56,-55,-53,-49,-44,-38,-31,-23,-14,-6,0,7,13,17,21,24,26,27,29,29,30,25,25,26,26,26,25,25,25,25,25,25,25,25,26,25,25,24,23,21,19,16,12,8,4,0,-3,-7,-10,-13,-15,-16,-17,-18,-19,-20,-21,-22,-23,-25,-28,-31,-34,-37,-40,-43,-46,-48,-49,-50,-51,-51,-50,-48,-45,-42,-37,-32,-26,-19,-13,-7,-1,3,7,11,14,17,19,21,23,24,25,25,21,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,21,20,18,16,13,9,5,1,-3,-7,-11,-14,-17,-18,-20,-21,-21,-22,-22,-22,-23,-23,-25,-27,-29,-32,-35,-37,-40,-42,-44,-45,-45,-45,-44,-42,-40,-36,-32,-27,-22,-17,-12,-7,-3,0,3,7,9,12,14,16,18,19,20,21,21,18,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,18,17,16,14,10,7,2,-1,-6,-10,-14,-17,-19,-21,-22,-23,-24,-24,-24,-24,-23,-23,-23,-24,-26,-28,-30,-33,-35,-37,-38,-39,-39,-38,-36,-34,-31,-28,-24,-19,-15,-10,-6,-3,0,1,4,6,8,10,12,14,15,16,17,18,18,16,16,17,17,17,17,17,17,17,17,17,16,16,16,16,16,16,15,13,11,8,4,0,-4,-9,-13,-16,-19,-21,-23,-24,-25,-25,-25,-25,-24,-23,-21,-20,-20,-21,-22,-24,-26,-28,-30,-31,-32,-31,-30,-29,-27,-24,-21,-17,-13,-9,-6,-3,-1,0,2,4,5,7,9,10,12,13,14,15,16,16,14,14,14,15,15,15,15,15,15,15,14,14,14,14,14,14,13,12,11,9,5,2,-2,-6,-11,-15,-18,-21,-23,-24,-25,-25,-25,-25,-24,-22,-21,-18,-16,-15,-15,-15,-17,-19,-21,-22,-24,-24,-24,-23,-22,-20,-18,-15,-12,-9,-5,-3,-1,0,1,2,4,5,6,8,9,10,11,12,13,14,14,12,13,13,13,13,13,13,13,13,13,13,13,12,12,12,12,11,10,9,6,3,0,-4,-8,-12,-16,-19,-21,-23,-24,-24,-24,-24,-23,-22,-20,-17,-15,-12,-10,-9,-9,-10,-12,-13,-15,-17,-17,-18,-17,-16,-15,-13,-11,-8,-5,-3,-1,0,1,1,2,3,4,6,7,8,9,10,11,12,12,12,11,11,11,11,11,12,12,12,12,12,11,11,11,11,11,10,10,9,7,5,2,-1,-5,-9,-13,-17,-20,-22,-23,-23,-23,-23,-22,-20,-18,-16,-14,-11,-9,-6,-5,-4,-5,-6,-8,-9,-11,-12,-12,-12,-12,-11,-9,-8,-6,-3,-1,0,0,1,1,2,3,4,5,6,7,8,9,10,11,11,11,10,10,10,10,10,10,10,10,10,10,10,10,10,10,9,9,9,7,6,3,0,-3,-6,-10,-14,-17,-20,-21,-22,-22,-22,-21,-19,-17,-15,-13,-10,-8,-6,-4,-2,-2,-2,-2,-4,-5,-7,-8,-8,-9,-8,-8,-7,-5,-4,-2,0,0,1,1,1,2,2,3,4,5,6,7,8,9,10,10,10,9,9,9,9,9,9,9,10,10,9,9,9,9,9,9,8,8,6,5,2,0,-4,-7,-11,-15,-17,-19,-21,-21,-21,-20,-18,-16,-14,-12,-10,-8,-6,-4,-2,-1,0,0,0,-1,-2,-4,-5,-5,-6,-6,-5,-5,-4,-3,-1,0,0,1,1,1,1,2,3,3,5,6,7,8,8,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,8,8,8,8,7,5,4,1,-1,-5,-8,-12,-15,-17,-19,-20,-20,-19,-18,-16,-14,-11,-9,-7,-5,-4,-2,-1,0,0,1,1,0,0,-2,-3,-3,-4,-4,-4,-3,-3,-2,-1,0,0,0,0,0,1,1,2,3,4,5,6,7,8,8,9,9,9,9,9,8,8,8,9,9,9,9,9,8,8,8,8,7,6,5,3,0,-2,-5,-9,-12,-15,-17,-18,-19,-19,-18,-16,-14,-12,-9,-7,-5,-4,-2,-1,0,0,1,1,1,1,0,0,-1,-2,-2,-3,-3,-2,-2,-1,-1,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,8,9,8,8,8,8,8,8,9,9,9,9,9,9,8,8,8,7,6,4,2,0,-3,-6,-9,-12,-15,-17,-18,-18,-17,-16,-14,-12,-10,-8,-6,-4,-2,-1,0,0,1,2,2,2,2,1,0,0,-1,-1,-1,-2,-2,-1,-1,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,8,8,8,8,8,9,9,9,9,9,9,9,9,9,8,8,7,5,3,1,-1,-4,-7,-10,-13,-15,-16,-17,-17,-16,-15,-13,-11,-9,-6,-5,-3,-2,0,0,0,1,2,2,2,2,1,1,0,0,0,-1,-1,-1,-1,-1,0,0,0,0,-1,-1,-1,-1,-1,0,0,1,3,4,5,7,7,8,8,8,9,9,9,9,10,10,10,10,10,10,10,9,8,7,5,3,0,-2,-5,-8,-11,-13,-15,-16,-16,-16,-15,-13,-12,-10,-8,-6,-4,-2,-1,0,0,1,2,2,3,3,2,2,1,0,0,0,0,0,0,0,0,0,0,-1,-1,-2,-2,-2,-2,-2,-1,0,0,1,3,4,6,7,8,7,8,9,9,9,10,10,11,11,11,11,11,10,10,9,7,5,3,0,-2,-6,-9,-11,-13,-15,-16,-16,-15,-14,-13,-11,-9,-7,-5,-3,-2,0,0,1,1,2,3,3,3,3,2,2,1,1,0,0,0,0,0,0,0,-1,-1,-2,-3,-3,-4,-4,-4,-3,-2,-1,0,1,3,5,6,7,6,8,9,9,10,11,11,12,12,12,12,12,11,11,9,7,5,2,0,-3,-7,-10,-12,-14,-15,-16,-15,-15,-13,-12,-10,-8,-7,-5,-3,-1,0,0,1,2,2,3,3,4,3,3,3,2,2,1,1,1,0,0,0,0,-1,-2,-3,-4,-4,-5,-5,-5,-5,-4,-2,-1,0,2,3,5,6,6,7,8,10,11,12,12,13,13,14,14,13,13,11,10,8,5,2,0,-4,-8,-11,-13,-15,-16,-16,-16,-15,-13,-12,-10,-8,-6,-5,-3,-1,0,0,1,2,3,3,4,4,4,4,4,3,3,3,2,2,1,1,0,0,-1,-2,-3,-5,-6,-7,-7,-7,-6,-5,-4,-3,-1,0,2,4,6,5,7,8,10,11,12,13,14,15,15,15,14,14,12,11,8,5,2,-1,-5,-9,-12,-14,-16,-17,-17,-16,-15,-14,-12,-11,-9,-7,-5,-3,-1,0,0,1,2,3,4,4,5,5,5,5,5,5,4,4,3,3,2,1,0,-1,-2,-4,-6,-7,-8,-8,-8,-8,-7,-6,-4,-2,0,1,3,5,4,6,8,10,12,13,14,15,16,16,16,16,15,13,11,9,5,2,-2,-6,-10,-13,-16,-17,-18,-18,-17,-16,-15,-13,-11,-9,-7,-5,-4,-2,0,0,1,3,3,4,5,6,6,7,7,7,7,7,6,5,4,3,2,0,-1,-3,-5,-7,-8,-9,-10,-10,-10,-9,-7,-5,-4,-1,0,2,4,4,6,8,10,12,14,15,16,17,18,18,17,16,15,12,9,5,1,-3,-8,-12,-15,-18,-19,-20,-20,-19,-18,-16,-15,-13,-11,-8,-6,-4,-2,-1,0,1,3,4,5,6,7,8,9,9,9,9,9,9,8,7,5,3,1,-1,-3,-6,-8,-10,-11,-12,-12,-11,-10,-9,-7,-5,-2,0,1,4,4,6,8,11,13,15,16,18,19,19,19,19,18,16,13,10,5,0,-5,-10,-15,-18,-21,-22,-23,-22,-22,-20,-18,-17,-14,-12,-10,-8,-5,-3,-1,0,1,3,5,6,8,9,10,11,12,12,13,12,12,11,9,7,5,2,0,-3,-6,-9,-11,-12,-13,-13,-12,-11,-10,-8,-6,-3,-1,1,4,3,6,9,11,14,16,17,19,20,21,21,21,19,17,14,10,4,-1,-8,-14,-19,-22,-25,-26,-26,-26,-25,-23,-21,-19,-17,-14,-12,-9,-7,-4,-2,0,1,3,5,7,9,11,13,14,15,16,16,16,16,15,13,10,7,4,0,-3,-7,-10,-12,-14,-15,-14,-14,-12,-11,-9,-6,-4,-1,1,3,};

float
AP_Declination::get_declination(float lat, float lon)
{
	float decSW, decSE, decNW, decNE, decmin, decmax;
	float lonmin,latmin;
	uint8_t latmin_index,lonmin_index;
	/* set base point (latmin, lonmin) of grid */

	/* no limits test on lon */
	if (lon == 180) lonmin = 175;
	else lonmin = floor(lon/5)*5;

	/* supported lat's -60..60, so range check... */
	if (lat >= 60) latmin = 55;
	else if (lat < -60) latmin = -60;
	else latmin = floor(lat/5)*5;

	/* array index = (degrees+[60|180])/5 */
	latmin_index= (60+latmin)/5;
	lonmin_index= (180+lonmin)/5;


	decSW = (int8_t)pgm_read_byte_far(&dec_tbl[latmin_index][lonmin_index]);
	decSE = (int8_t)pgm_read_byte_far(&dec_tbl[latmin_index][lonmin_index+1]);
	decNE = (int8_t)pgm_read_byte_far(&dec_tbl[latmin_index+1][lonmin_index+1]);
	decNW = (int8_t)pgm_read_byte_far(&dec_tbl[latmin_index+1][lonmin_index]);

	/* approximate declination within the grid using bilinear interpolation */

	decmin = (lon - lonmin) / 5 * (decSE - decSW) + decSW;
	decmax = (lon - lonmin) / 5 * (decNE - decNW) + decNW;
	return   (lat - latmin) / 5 * (decmax - decmin) + decmin;
}