// Eigenについては以下を参照
// http://dronevisionml.blogspot.jp/2015/05/eigenvisual-studio-2015.html
// https://qiita.com/vs4sh/items/7e8bc95250db8d88bc41
// Eigenのインストールしないとビルドとかできない

#define EIGEN_NO_DEBUG // コード内のassertを無効化．
#define EIGEN_DONT_VECTORIZE // SIMDを無効化．
#define EIGEN_DONT_PARALLELIZE // 並列を無効化．
#define EIGEN_MPL2_ONLY // LGPLライセンスのコードを使わない．

#include <Eigen/Core>
#include "SST.h"
#include <iostream>

#pragma region Constructor and Destructor

SST::SST(int width = 20)
{
	this->width = width;
	this->n = this->width / 2;
	this->k = this->width / 2;
	this->lag = this->k / 2;
	this->r = 3;
	this->m = 2;
	this->minlength = this->lag + this->n + this->width - 1;

	// debug
	Eigen::MatrixXd A(9, 9);
	std::cout << A;
}

SST::~SST()
{
	this->datalist.clear();
}

#pragma endregion

#pragma region Public

void SST::AddData(std::vector<float> data)
{
	// データを追加する
	for (auto d : data)
	{
		this->datalist.push_back(d);
	}

	// データ個数が上限を超えている場合は削除
	this->NormalizeDatalist();
}

float SST::GetScore()
{
	float score = this->GetFormerScore(0);
	return score;
}

float SST::GetFormerScore(int step)
{
	// 変化度を計算. step=0で最新, step=iでi個前の変化値
	return 0.0f;
}

#pragma endregion

#pragma region Private

void SST::NormalizeDatalist()
{
	// maxItemnum個以上データがある場合は削除する
	const int maxItemnum = 2000;
	int reduce = int(this->datalist.size()) - maxItemnum;
	if (reduce > 0)
	{
		this->datalist.erase(this->datalist.begin(), this->datalist.begin() + reduce);
	}
}

void SST::GetTrajectoryMatrix()
{
	// Todo
	// return typeをvoidから適切な型に変える
}

void SST::GetTestMatrix()
{
	// Todo
	// return typeをvoidから適切な型に変える
}

#pragma endregion




