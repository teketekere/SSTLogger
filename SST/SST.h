#pragma once
#include <vector>

class SST
{
public:
	// constructor, destructor
	SST(int width);
	~SST();

	// dataを追加する
	void AddData(std::vector<float> data);
	
	// 最新の変化度(0~1)を取得. 1に近い程異常
	float GetScore();

	// stepで指定した分だけ前の変化度を取得
	// step=0なら最新, step=1なら1つ前の変化度
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

