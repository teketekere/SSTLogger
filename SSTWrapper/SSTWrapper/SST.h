#pragma once
#include <vector>
#include <Eigen/Core>
using namespace Eigen;

class SST
{
public:
	// constructor, destructor
	SST(int width);
	~SST();

	// data��ǉ�����
	void AddData(std::vector<float> data);
	
	// �ŐV�̕ω��x(0~1)���擾. 1�ɋ߂����ُ�
	float GetScore();

	// step�Ŏw�肵���������O�̕ω��x���擾
	// step=0�Ȃ�ŐV, step=1�Ȃ�1�O�̕ω��x
	float GetFormerScore(const unsigned int step);

private:
	unsigned int width;
	unsigned int n;
	unsigned int k;
	unsigned int lag;
	unsigned int r;
	unsigned int m;
	unsigned int minlength;
	std::vector<float> datalist;

	void NormalizeDatalist();
	MatrixXf GetTrajectoryMatrix(unsigned int step);
	MatrixXf GetTestMatrix(unsigned int step);
};