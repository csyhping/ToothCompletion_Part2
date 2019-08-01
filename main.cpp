/*
	Created by Yuhan Ping from HKU at 2019-07-30.
	The project is part 2 of tooth completion to deal with neighbor teeth intersection.
	Under development.
	Lateset updated on 2019-07-31.
*/

#include <iostream>
#include "Header/io.h"
#include "Header/adjust.h"
#include <igl/winding_number.h>


using namespace std;
using namespace Eigen;



int main(int argc, char *argv[])
{
	if (argc != 3) {
		cout << "[Usage] ToothCompletionPart2 [path1] [path2] " << endl;
		exit(-1);
	}

	// setup path
	inputmesh_1 = argv[1];
	inputmesh_2 = argv[2];

	// load data
	load_from_file(inputmesh_1, inputmesh_2);

	// detect intersection
	if (!detect_intersection()) {
		cout << "[INFO] No intersection detected !" << endl;
		exit(-1);
	}

	// adjust intersection
	adjust_intersection();
	
	// use viewer to visualize
	viewer_display();
	
	// test winding number
//	MatrixXd p = (MatrixXd(3, 3) <<
//
//		-1, 0.5, 0.5,
//		0.9, 0.5, 0.5,
//		2, 0.5, 0.5).finished();
//	MatrixXd wn;
//
//	// Inline mesh of a cube
//	const Eigen::MatrixXd V = (Eigen::MatrixXd(8, 3) <<
//		0.0, 0.0, 0.0,
//		0.0, 0.0, 1.0,
//		0.0, 1.0, 0.0,
//		0.0, 1.0, 1.0,
//		1.0, 0.0, 0.0,
//		1.0, 0.0, 1.0,
//		1.0, 1.0, 0.0,
//		1.0, 1.0, 1.0).finished();
//	const Eigen::MatrixXi F = (Eigen::MatrixXi(6, 3) <<
//		1, 4, 3,
//		1, 2, 4,
//		3, 8, 7,
//		3, 4, 8,
//		5, 7, 8,
//		5, 8, 6
//).finished().array() - 1;
//
//	igl::winding_number(V, F, p, wn);
//	cout << "winding num = " << wn << endl;
//
//	// Plot the mesh
//	igl::opengl::glfw::Viewer viewer;
//	igl::opengl::glfw::imgui::ImGuiMenu menu;
//	viewer.plugins.push_back(&menu);
//	viewer.data().set_mesh(V, F);
//	viewer.data().add_points(p, RowVector3d(1, 1, 0));
//	viewer.data().set_face_based(true);
//	viewer.launch();
}
