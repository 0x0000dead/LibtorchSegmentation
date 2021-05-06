#pragma once
#include"../utils/util.h"
#include"../utils/InterFace.h"
//��Ӧpytorch�е�make_features����������CNN���壬��������һ��torch::nn::Sequential����
torch::nn::Sequential make_features(std::vector<int> &cfg, bool batch_norm);

//VGG���������������ʼ����ǰ�򴫲�
class VGGImpl : public Backbone
{
private:
	torch::nn::Sequential features_{ nullptr };
	torch::nn::AdaptiveAvgPool2d avgpool{ nullptr };
	torch::nn::Sequential classifier;
	std::vector<int> cfg = {};
	bool batch_norm;

public:
	VGGImpl(std::vector<int> cfg, int num_classes = 1000, bool batch_norm = false);
	torch::Tensor forward(torch::Tensor x);

	std::vector<torch::Tensor> features(torch::Tensor x, int encoder_depth = 5) override;
	torch::Tensor features_at(torch::Tensor x, int stage_num) override;
	void make_dilated(std::vector<int> stage_list, std::vector<int> dilation_list) override;
	void load_pretrained(std::string pretrained_path) override;
};
TORCH_MODULE(VGG);
