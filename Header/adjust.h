#pragma once
/*
	Created by Yuhan Ping from HKU on 2019-08-01.
	This is the header file for adjust intersection between neighbor teeth.
	Under development.
	Latest updated on 2019-08-01.
*/
#ifndef ADJUST_H
#define ADJUST_H
#include <igl/winding_number.h>
#include <igl/shape_diameter_function.h>
#include <igl/writeOFF.h>
#include <igl/jet.h>
#include <igl/all_pairs_distances.h>

bool detect_intersection();
/*
	detect if two faired teeth intersect with each other
	[Return value] true: if intersect, false: if no intersection
*/
void adjust_intersection();
/*
	adjust the coordinates of vertex to avoid intersection
	[Return value] adjusted vertex coordinates
*/

#endif // !ADJUST_H
