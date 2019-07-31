/*
	Created by Yuhan Ping from HKU at 2019-07-30.
	The project is part 2 of tooth completion to deal with neighbor teeth intersection.
	Under development.
	Lateset updated on 2019-07-31.
*/

#include <iostream>
#include "Header/io.h"

#include <igl/opengl/glfw/Viewer.h>

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
	

  // Inline mesh of a cube
  const Eigen::MatrixXd V= (Eigen::MatrixXd(8,3)<<
    0.0,0.0,0.0,
    0.0,0.0,1.0,
    0.0,1.0,0.0,
    0.0,1.0,1.0,
    1.0,0.0,0.0,
    1.0,0.0,1.0,
    1.0,1.0,0.0,
    1.0,1.0,1.0).finished();
  const Eigen::MatrixXi F = (Eigen::MatrixXi(12,3)<<
    1,7,5,
    1,3,7,
    1,4,3,
    1,2,4,
    3,8,7,
    3,4,8,
    5,7,8,
    5,8,6,
    1,5,6,
    1,6,2,
    2,6,8,
    2,8,4).finished().array()-1;

  // Plot the mesh
  igl::opengl::glfw::Viewer viewer;
  viewer.data().set_mesh(V, F);
  viewer.data().set_face_based(true);
  viewer.launch();
}
