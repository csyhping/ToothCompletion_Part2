#include "Header/adjust.h"
#include "Header/io.h"

Eigen::MatrixXd v_postfair_R_1, v_postfair_L_2;
Eigen::VectorXd wind_num1, wind_num2;
Eigen::RowVectorXi pos1, pos2; // mark which point is inside the other mesh

bool detect_intersection() {

	// for first mesh, check Right & mesh2
	// for second mesh, check left & mesh1
	v_postfair_R_1.resize(V_prefair_R_1.rows(), 3);
	v_postfair_L_2.resize(V_prefair_L_2.rows(), 3);
	v_postfair_R_1 = V_postfair_X_1.topRows(v_postfair_R_1.rows());
	v_postfair_L_2 = V_postfair_X_2.bottomRows(v_postfair_L_2.rows());

	// calc winding num
	igl::winding_number(V2, F2, v_postfair_R_1, wind_num1);
	igl::winding_number(V1, F1, v_postfair_L_2, wind_num2);

	if (wind_num1.maxCoeff() < 0.5) {
		// if winding num < 0,5, the point is not inside the other mesh
		return false;
	}
	else {
		// mark the point which is inside the other mesh
		pos1.resize(v_postfair_R_1.rows());
		pos2.resize(v_postfair_L_2.rows());
		pos1.setZero();
		pos2.setZero();

		for (int i = 0; i < wind_num1.rows(); i++) {
			if (wind_num1(i) >= 0.5) {
				pos1(i) = 1;
			}
		}

		for (int i = 0; i < wind_num2.rows(); i++) {
			if (wind_num2(i) >= 0.5) {
				pos2(i) = 1;
			}
		}
	}
	return true;
}

void adjust_intersection() {

}
