#ifndef CAFFE_SIMILARITY2_LOSS_LAYER_HPP_
#define CAFFE_SIMILARITY2_LOSS_LAYER_HPP_

#include <vector>
#include <stdlib.h>

#include "caffe/blob.hpp"
#include "caffe/layer.hpp"
#include "caffe/proto/caffe.pb.h"

#include "caffe/layers/loss_layer.hpp"

namespace caffe
{
	/*
	Compute loss and gradient by similarity in image pairs.
	loss = 1/n *
		\sum_n ( sim(A, A-) + max(0, alpha - sim(A, A+)) )
	parameter: alpha
	*/
	template <typename Dtype>
	class Similarity2LossLayer : public LossLayer<Dtype>
	{
	public:
		explicit Similarity2LossLayer(const LayerParameter& param) : LossLayer<Dtype>(param){}
		virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top);
		virtual inline const char* type() const { return "Similarity2Loss"; }
		virtual void Reshape(const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top);
	protected:
		virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top);
		virtual void Forward_gpu(const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top);
		virtual void Backward_cpu(const vector<Blob<Dtype>*>& top, 
			const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
		virtual void Backward_gpu(const vector<Blob<Dtype>*>& top,
			const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
		virtual inline int ExactNumBottomBlobs() const { return 2; }
		int batch_size_;
		int code_length_;
		Dtype imagenetsim_;
		Dtype alpha_;
		Dtype beta_;
		Dtype cat_per_iter_;
		Blob<Dtype> norm_vec_;
		Blob<Dtype> norm_mat_;
		Blob<Dtype> dot_product_mat_;
		Blob<Dtype> temp_diff_vec_;
		float * sim_mat_;
	};

}  // namespace caffe

#endif  // CAFFE_SIMILARITY2_LOSS_LAYER_HPP_
