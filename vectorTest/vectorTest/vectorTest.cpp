// vectorTest.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <Eigen/Core>
#include <Eigen/SVD>
#include <vector>
#include <iostream>

using namespace Eigen;

int main()
{
	std::vector<int> vec;

	for (int i = 0; i < 10; i++) {
		vec.push_back(i);
	}

	// vec.erase(vec.end()-3, vec.end() -1);

	for (auto v : vec)
	{
		std::cout << v << std::endl;
	}

	std::cout << "owari" << std::endl;

	for (auto it = vec.end()-5; it != vec.end()-2; ++it)
	{
		std::cout << *it << std::endl;
	}

	std::cout << "owari" << std::endl;

	int array[12];
	for (int i = 0; i < 12; ++i) array[i] = i;
	std::cout << Map<MatrixXi, 0, OuterStride<> >(array, 4, 2, OuterStride<>(1)) << std::endl;
	std::cout << Map<MatrixXi, 0, OuterStride<> >(&vec[vec.size()-7], 3, 3, OuterStride<>(1)) << std::endl;

	MatrixXi mat = Map<MatrixXi, 0, OuterStride<> >(&vec[vec.size() - 9], 3, 3, OuterStride<>(1));

	using namespace std;
	MatrixXf m = MatrixXf::Random(8, 7);
	cout << "Here is the matrix m:" << endl << m << endl;
	JacobiSVD<MatrixXf> svd(m, ComputeThinU | ComputeThinV);
	cout << "Its singular values are:" << endl << svd.singularValues() << endl;
	cout << "Its left singular vectors are the columns of the thin U matrix:" << endl << svd.matrixU() << endl;
	cout << "Its right singular vectors are the columns of the thin V matrix:" << endl << svd.matrixV() << endl;

	while (1);
    return 0;
}