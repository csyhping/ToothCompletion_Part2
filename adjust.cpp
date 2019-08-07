#include "Header/adjust.h"
#include "Header/io.h"

Eigen::MatrixXd v_postfair_R_1, v_postfair_L_2, v_prefair_R_1, v_prefair_L_2;
Eigen::VectorXd wind_num1, wind_num2;
Eigen::RowVectorXi pos1, pos2, pos1_back, pos2_back; // mark which point is inside the other mesh
Eigen::MatrixXd v_valid_1, v_valid_2;
Eigen::MatrixXi f_valid_1, f_valid_2;

bool detect_intersection() {

	// for first mesh, check Right & mesh2
	// for second mesh, check left & mesh1
	v_postfair_R_1.resize(V_prefair_R_1_withhole.rows()-idx_hole_R_1.cols(), 3);
	v_postfair_L_2.resize(V_prefair_L_2_withhole.rows()-idx_hole_L_2.cols(), 3);	
	v_prefair_R_1.resize(v_postfair_R_1.rows(), 3);
	v_prefair_L_2.resize(v_postfair_L_2.rows(), 3);

	v_prefair_R_1 = V_prefair_R_1_withhole.bottomRows(v_prefair_R_1.rows());
	v_prefair_L_2 = V_prefair_L_2_withhole.bottomRows(v_prefair_L_2.rows());
	v_postfair_R_1 = V_postfair_X_1.topRows(v_postfair_R_1.rows());
	v_postfair_L_2 = V_postfair_X_2.bottomRows(v_postfair_L_2.rows());

	//vvv1.resize(v_prefair_R_1.rows(), 3);
	//vvv2.resize(v_postfair_R_1.rows(), 3);
	//vvv1 = v_prefair_R_1;
	//vvv2 = v_postfair_R_1;

	std::cout << "pre r 1 = " << v_postfair_R_1.rows() << std::endl;
	std::cout << "pre l 2 = " << v_postfair_L_2.rows() << std::endl;
	std::cout << "post r 1 = " << v_postfair_R_1.rows() << std::endl;
	std::cout << "post l 2 = " << v_postfair_L_2.rows() << std::endl;

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
		pos1.setConstant(-1);
		pos2.setConstant(-1);
		int posmark = 0; // for adjust vertex idx
		
		// mark valid vertex 
		for (int i = 0; i < wind_num1.rows(); i++) {
			if (wind_num1(i) >= 0.5) {
				pos1(i) = posmark;
				pos1_back.conservativeResize(posmark + 1);
				pos1_back(posmark) = i;
				v_valid_1.conservativeResize(posmark + 1, 3);
				v_valid_1.row(posmark) = v_postfair_R_1.row(i);
				posmark += 1;
			}
		}

		posmark = 0;
		for (int i = 0; i < wind_num2.rows(); i++) {
			if (wind_num2(i) >= 0.5) {
				pos2(i) = posmark;
				pos2_back.conservativeResize(posmark + 1);
				pos2_back(posmark) = i;
				v_valid_2.conservativeResize(posmark + 1, 3);
				v_valid_2.row(posmark) = v_postfair_L_2.row(i);
				posmark += 1;
			}
		}

		// adjust face idx
		posmark = 0;
		Eigen::MatrixXi tmp_f;
		tmp_f.resize(F_prefair_R_1.rows(), 3);
		tmp_f.setConstant(idx_hole_R_1.cols());
		tmp_f = F_prefair_R_1 - tmp_f;

		for (int i = 0; i < tmp_f.rows(); i++) {
			if (tmp_f.row(i).minCoeff() < 0) {
				// no need to use hole vertex
				continue;
			}
			else {
				if (pos1(tmp_f(i, 0)) == -1 || pos1(tmp_f(i, 1)) == -1 || pos1(tmp_f(i, 2)) == -1) {
					// if the vertex is outside the other mesh, no need either
					continue;
				}
				else {
					f_valid_1.conservativeResize(posmark + 1, 3);
					f_valid_1(posmark, 0) = pos1(tmp_f(i, 0));
					f_valid_1(posmark, 1) = pos1(tmp_f(i, 1));
					f_valid_1(posmark, 2) = pos1(tmp_f(i, 2));
					posmark += 1;
				}
			}
		}

		posmark = 0;
		tmp_f.resize(F_prefair_L_2.rows(), 3);
		tmp_f.setConstant(idx_hole_L_2.cols());
		tmp_f = F_prefair_L_2 - tmp_f;

		for (int i = 0; i < tmp_f.rows(); i++) {
			if (tmp_f.row(i).minCoeff() < 0) {
				// no need to use hole vertex
				continue;
			}
			else {
				if (pos2(tmp_f(i, 0)) == -1 || pos2(tmp_f(i, 1)) == -1 || pos2(tmp_f(i, 2)) == -1) {
					// if the vertex is outside the other mesh, no need either
					continue;
				}
				else {
					f_valid_2.conservativeResize(posmark + 1, 3);
					f_valid_2(posmark, 0) = pos2(tmp_f(i, 0));
					f_valid_2(posmark, 1) = pos2(tmp_f(i, 1));
					f_valid_2(posmark, 2) = pos2(tmp_f(i, 2));
					posmark += 1;
				}
			}
		}
		std::cout << "valid v1 = " << v_valid_1.rows() << " f1 = " << f_valid_1.rows() << std::endl;
		std::cout << "valid v2 = " << v_valid_2.rows() << " f2 = " << f_valid_2.rows() << std::endl;
	}
	return true;
}

void adjust_intersection() {


	Eigen::MatrixXd dist;
	Eigen::VectorXi::Index maxRow, maxCol, minRow, minCol;
	double max_distance, v1_distance, v2_distance;
	double lamda1, lamda2; // V_final = (1-lambda) * V_prefair + lambda * V_postfair
	

	// calc min-max distance
	igl::all_pairs_distances(v_valid_1, v_valid_2, true, dist);
	dist.rowwise().minCoeff().maxCoeff(&maxRow);
	dist.colwise().minCoeff().maxCoeff(&maxCol);
	std::cout << "maxrow at # " << maxRow << " corresponding to orginal # " << pos1_back(maxRow) << std::endl;
	std::cout << "maxcol at # " << maxCol << " corresponding to orginal # " << pos2_back(maxRow) << std::endl;

	max_distance = dist(maxRow, maxCol);
	std::cout << "max distance = " << max_distance << std::endl;

	// for each of max vertex, calc its [prefair coordinates, postfair coordinates]
	v1_distance = sqrt(
		(v_prefair_R_1(pos1_back(maxRow), 0) - v_postfair_R_1(pos1_back(maxRow), 0))*(v_prefair_R_1(pos1_back(maxRow), 0) - v_postfair_R_1(pos1_back(maxRow), 0)) +
		(v_prefair_R_1(pos1_back(maxRow), 1) - v_postfair_R_1(pos1_back(maxRow), 1))*(v_prefair_R_1(pos1_back(maxRow), 1) - v_postfair_R_1(pos1_back(maxRow), 1)) +
		(v_prefair_R_1(pos1_back(maxRow), 2) - v_postfair_R_1(pos1_back(maxRow), 2))*(v_prefair_R_1(pos1_back(maxRow), 2) - v_postfair_R_1(pos1_back(maxRow), 2))
	);
	v2_distance = sqrt(
		(v_prefair_L_2(pos2_back(maxRow), 0) - v_postfair_L_2(pos2_back(maxRow), 0))*(v_prefair_L_2(pos2_back(maxRow), 0) - v_postfair_L_2(pos2_back(maxRow), 0)) +
		(v_prefair_L_2(pos2_back(maxRow), 1) - v_postfair_L_2(pos2_back(maxRow), 1))*(v_prefair_L_2(pos2_back(maxRow), 1) - v_postfair_L_2(pos2_back(maxRow), 1)) +
		(v_prefair_L_2(pos2_back(maxRow), 2) - v_postfair_L_2(pos2_back(maxRow), 2))*(v_prefair_L_2(pos2_back(maxRow), 2) - v_postfair_L_2(pos2_back(maxRow), 2))
	);
	//std::cout << "v pre x,y,z = " << v_prefair_L_2(pos2_back(maxRow), 0) << " " << v_prefair_L_2(pos2_back(maxRow), 1) << " " << v_prefair_L_2(pos2_back(maxRow), 2) << std::endl;
	//std::cout << "v pre x,y,z = " << v_postfair_L_2(pos2_back(maxRow), 0) << " " << v_postfair_L_2(pos2_back(maxRow), 1) << " " << v_postfair_L_2(pos2_back(maxRow), 2) << std::endl;
	std::cout << "v1 distance = " << v1_distance << std::endl;
	std::cout << "v2 distance = " << v2_distance << std::endl;

	// calc lambda
	lamda1 = 1 - 0.5*max_distance / v1_distance;
	lamda2 = 1 - 0.5*max_distance / v2_distance;

	std::cout << "lambda1 = " << lamda1 << std::endl;
	std::cout << "lambda2 = " << lamda2 << std::endl;


	// for visualization
	vvv1.resize(1, 3);
	vvv2.resize(1, 3);
	vvv1 = v_prefair_L_2.row(pos2_back(maxCol));
	vvv2 = v_postfair_L_2.row(pos2_back(maxCol));

	Eigen::MatrixXd V_combine;
	Eigen::MatrixXi F_combine, tmp_f;

	V_combine.resize(v_valid_1.rows() + v_valid_2.rows(), 3);
	F_combine.resize(f_valid_1.rows() + f_valid_2.rows(), 3);

	tmp_f.resize(f_valid_2.rows(), 3);
	tmp_f.setConstant(v_valid_1.rows());


	std::cout << "v # = " << V_combine.rows() << std::endl;
	std::cout << "f # = " << F_combine.rows() << std::endl;
	


	V_combine <<
		v_valid_1,
		v_valid_2;

	F_combine <<
		f_valid_1,
		f_valid_2 + tmp_f;
	
	vvv.resize(V_combine.rows(), 3);
	fff.resize(F_combine.rows(), 3);
	vvv = V_combine;
	fff = F_combine;
}
