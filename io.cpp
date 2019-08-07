#include "Header/io.h"

std::string inputmesh_1, prefair_R_1, prefair_L_1, postfair_X_1, hole_R_1, hole_L_1;
std::string inputmesh_2, prefair_R_2, prefair_L_2, postfair_X_2, hole_R_2, hole_L_2;
Eigen::MatrixXd V1, V_prefair_R_1_withhole, V_prefair_L_1_withhole, V_postfair_X_1, V2, V_prefair_R_2_withhole, V_prefair_L_2_withhole, V_postfair_X_2, idx_hole_R_1, idx_hole_L_1, idx_hole_R_2, idx_hole_L_2;
Eigen::MatrixXi F1, F_prefair_R_1, F_prefair_L_1, F2, F_prefair_R_2, F_prefair_L_2;
Eigen::MatrixXd color;
Eigen::MatrixXd vvv,vvv1,vvv2;
Eigen::MatrixXi fff;
Eigen::MatrixXd S;

void load_from_file(std::string &path1, std::string &path2){
	// load mesh 1
	int nPos1 = path1.find("post");
	if (nPos1 != -1) {
		prefair_R_1 = path1.substr(0, nPos1) + "prefair_R.off";
		prefair_L_1 = path1.substr(0, nPos1) + "prefair_L.off";
		postfair_X_1 = path1.substr(0, nPos1) + "postfair_X.dmat";
		hole_R_1 = path1.substr(0, nPos1) + "holeR.dmat";
		hole_L_1 = path1.substr(0, nPos1) + "holeL.dmat";

	}

	igl::readOFF(path1, V1, F1);
	igl::readOFF(prefair_R_1, V_prefair_R_1_withhole, F_prefair_R_1);
	igl::readOFF(prefair_L_1, V_prefair_L_1_withhole, F_prefair_L_1);
	igl::readDMAT(hole_R_1, idx_hole_R_1);
	igl::readDMAT(hole_L_1, idx_hole_L_1);
	igl::readDMAT(postfair_X_1, V_postfair_X_1);


	// load mesh 2
	int nPos2 = path2.find("post");
	if (nPos2 != -1) {
		prefair_R_2 = path2.substr(0, nPos2) + "prefair_R.off";
		prefair_L_2 = path2.substr(0, nPos2) + "prefair_L.off";
		postfair_X_2 = path2.substr(0, nPos2) + "postfair_X.dmat";
		hole_R_2 = path2.substr(0, nPos2) + "holeR.dmat";
		hole_L_2 = path2.substr(0, nPos2) + "holeL.dmat";
	}

	igl::readOFF(path2, V2, F2);
	igl::readOFF(prefair_R_2, V_prefair_R_2_withhole, F_prefair_R_2);
	igl::readOFF(prefair_L_2, V_prefair_L_2_withhole, F_prefair_L_2);
	igl::readDMAT(hole_R_2, idx_hole_R_2);
	igl::readDMAT(hole_L_2, idx_hole_L_2);
	igl::readDMAT(postfair_X_2, V_postfair_X_2);
	

	//color = Eigen::MatrixXd::Constant(V_postfair_X_2.rows(), 3, 1);


}

bool viewer_display() {
	igl::opengl::glfw::Viewer viewer;
	igl::opengl::glfw::imgui::ImGuiMenu menu;
	viewer.plugins.push_back(&menu);
	//viewer.callback_mouse_down = &mouse_down;
	//viewer.callback_key_down = &key_down;
	//viewer.data().add_points(vvv, Eigen::RowVector3d(1,1,1));
	//viewer.data().add_points(vvv, color);

	//viewer.core.align_camera_center(vv);
	//igl::jet(S, true, color);
	//Eigen::VectorXi::Index maxRow, maxCol, minRow, minCol;
	//Eigen::MatrixXd dist;
	//igl::all_pairs_distances(vvv1, vvv2, true, dist);
	//for (int i = 0; i < dist.rows(); i++) {
	//	dist.row(i).minCoeff(&minRow, &minCol);
	//	viewer.data().add_edges(vvv1.row(i),vvv2.row(minCol), Eigen::RowVector3d(0, 1, 0));
	//}
	//dist.rowwise().minCoeff().maxCoeff(&maxRow);
	//dist.colwise().minCoeff().maxCoeff(&maxCol);

	//S.maxCoeff(&maxRow, &maxCol);
	//S.minCoeff(&minRow, &minCol);

	viewer.data().add_points(vvv1, Eigen::RowVector3d(0, 1, 0));
	viewer.data().add_points(vvv2, Eigen::RowVector3d(0, 0, 1));

	viewer.data().set_mesh(vvv, fff);
	//viewer.data().set_colors(color);
	viewer.launch();

	return true;
}