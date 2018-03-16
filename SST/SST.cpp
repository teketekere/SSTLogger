// Eigen�ɂ��Ă͈ȉ����Q��
// http://dronevisionml.blogspot.jp/2015/05/eigenvisual-studio-2015.html
// https://qiita.com/vs4sh/items/7e8bc95250db8d88bc41
// Eigen�̃C���X�g�[�����Ȃ��ƃr���h�Ƃ��ł��Ȃ�

#define EIGEN_NO_DEBUG // �R�[�h����assert�𖳌����D
#define EIGEN_DONT_VECTORIZE // SIMD�𖳌����D
#define EIGEN_DONT_PARALLELIZE // ����𖳌����D
#define EIGEN_MPL2_ONLY // LGPL���C�Z���X�̃R�[�h���g��Ȃ��D

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
	// �f�[�^��ǉ�����
	for (auto d : data)
	{
		this->datalist.push_back(d);
	}

	// �f�[�^��������𒴂��Ă���ꍇ�͍폜
	this->NormalizeDatalist();
}

float SST::GetScore()
{
	float score = this->GetFormerScore(0);
	return score;
}

float SST::GetFormerScore(int step)
{
	// �ω��x���v�Z. step=0�ōŐV, step=i��i�O�̕ω��l
	return 0.0f;
}

#pragma endregion

#pragma region Private

void SST::NormalizeDatalist()
{
	// maxItemnum�ȏ�f�[�^������ꍇ�͍폜����
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
	// return type��void����K�؂Ȍ^�ɕς���
}

void SST::GetTestMatrix()
{
	// Todo
	// return type��void����K�؂Ȍ^�ɕς���
}

#pragma endregion



