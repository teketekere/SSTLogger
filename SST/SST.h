#pragma once
#include <vector>

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
	float GetFormerScore(int step);

private:
	int width;
	int n;
	int k;
	int lag;
	int r;
	int m;
	int minlength;
	std::vector<float> datalist;

	void NormalizeDatalist();
	MatrixXf GetTrajectoryMatrix(int step);
	MatrixXf GetTestMatrix(int step);

};

