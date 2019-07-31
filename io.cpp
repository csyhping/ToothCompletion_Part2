#include "Header/io.h"

std::string inputmesh_1, prefair_R_1, prefair_L_1, postfair_X_1;
std::string inputmesh_2, prefair_R_2, prefair_L_2, postfair_X_2;
Eigen::MatrixXd V1, F1, V_prefair_R_1, V_prefair_L_1, V_postfair_X_1, V2, F2, V_prefair_R_2, V_prefair_L_2, V_postfair_X_2;

void load_from_file(std::string &path1, std::string &path2){
	// load mesh 1
	int nPos1 = path1.find(".off");
	if (nPos1 != -1) {
		prefair_R_1 = path1.substr(0, nPos1) + "prefair_R.dmat";
		prefair_L_1 = path1.substr(0, nPos1) + "prefair_L.dmat";
		postfair_X_1 = path1.substr(0, nPos1) + "postfair_X.dmat";
	}

	igl::readOFF(path1, V1, F1);
	igl::readDMAT(prefair_R_1, V_prefair_R_1);
	igl::readDMAT(prefair_L_1, V_prefair_L_1);
	igl::readDMAT(postfair_X_1, V_postfair_X_1);

	// load mesh 2
	int nPos2 = path2.find(".off");
	if (nPos2 != -1) {
		prefair_R_2 = path2.substr(0, nPos2) + "prefair_R.dmat";
		prefair_L_2 = path2.substr(0, nPos2) + "prefair_L.dmat";
		postfair_X_2 = path2.substr(0, nPos2) + "postfair_X.dmat";
	}

	igl::readOFF(path2, V2, F2);
	igl::readDMAT(prefair_R_2, V_prefair_R_2);
	igl::readDMAT(prefair_L_2, V_prefair_L_2);
	igl::readDMAT(postfair_X_2, V_postfair_X_2);

	std::cout << "v1 ============== " << V1.rows() << std::endl;
	std::cout << "prefair = " << V_prefair_R_1.rows() << std::endl;
	std::cout << "prefair l = " << V_prefair_L_1.rows() << std::endl;
	std::cout << "postfaor = " << V_postfair_X_1.rows() << std::endl;
	std::cout << "v2 = " << V2.rows() << std::endl;
	std::cout << "prefair = " << V_prefair_R_2.rows() << std::endl;
	std::cout << "prefair l = " << V_prefair_L_2.rows() << std::endl;
	std::cout << "postfaor = " << V_postfair_X_2.rows() << std::endl;
	std::cout << V_postfair_X_2 << std::endl;
	
}