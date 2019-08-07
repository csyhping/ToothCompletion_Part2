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
#include <igl/all_pairs_distances.h>

extern std::string inputmesh_1, prefair_R_1, prefair_L_1, postfair_X_1, hole_R_1, hole_L_1;
extern std::string inputmesh_2, prefair_R_2, prefair_L_2, postfair_X_2, hole_R_2, hole_L_2;
extern Eigen::MatrixXd V1, V_prefair_R_1_withhole, V_prefair_L_1_withhole, V_postfair_X_1, V2, V_prefair_R_2_withhole, V_prefair_L_2_withhole, V_postfair_X_2, idx_hole_R_1, idx_hole_L_1, idx_hole_R_2, idx_hole_L_2;
extern Eigen::MatrixXi F1, F_prefair_R_1, F_prefair_L_1, F2, F_prefair_R_2, F_prefair_L_2;
extern Eigen::MatrixXd S; // SDF value

// test for visualization
extern Eigen::MatrixXd color;
extern Eigen::MatrixXd vvv,vvv1,vvv2;
extern Eigen::MatrixXi fff;

void load_from_file(std::string &path1, std::string &path2);
/*
	load relative data from corresponding files
*/

bool viewer_display(); 
/*
	viewer settings
*/


#endif // !IO_H

