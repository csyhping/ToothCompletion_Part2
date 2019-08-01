#pragma once
/*
	Created by Yuhan Ping from HKU on 2019-07-31.
	This is the header file for all io-related functions and the viewer settings.
	Under development.
	Latest updated on 2019-07-31.
*/
#ifndef IO_H
#define IO_H

#include <igl/readOFF.h>
#include <igl/readDMAT.h>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/imgui/ImGuiHelpers.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>

extern std::string inputmesh_1, prefair_R_1, prefair_L_1, postfair_X_1;
extern std::string inputmesh_2, prefair_R_2, prefair_L_2, postfair_X_2;
extern Eigen::MatrixXd V1, V_prefair_R_1, V_prefair_L_1, V_postfair_X_1, V2, V_prefair_R_2, V_prefair_L_2, V_postfair_X_2;
extern Eigen::MatrixXi F1, F2;

// test for visualization
extern Eigen::MatrixXd color;

void load_from_file(std::string &path1, std::string &path2);
/*
	load relative data from corresponding files
*/

bool viewer_display(); 
/*
	viewer settings
*/


#endif // !IO_H

