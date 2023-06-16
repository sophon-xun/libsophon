#ifndef CPU_ADAPTIVE_AVERAGE_POOLING3D_H
#define CPU_ADAPTIVE_AVERAGE_POOLING3D_H

#include "cpu_layer.h"

/*
 *  there are two tensor，tensor[0] is input tensor, tensor[1] is output tensor size.
 *  there are no params.
 */
namespace bmcpu {

class cpu_adaptive_average_pooling3dlayer : public cpu_layer {
  public:
    explicit cpu_adaptive_average_pooling3dlayer() {}
    virtual ~cpu_adaptive_average_pooling3dlayer() {}

    int process(void* param, int param_size);
    inline float begin_index(int out_index, int out_size, int in_size);
    template <typename T>
    void adaptive_average_pooling(const T *input,
                                  const vector<int> &in_shape,
                                  const int *out_shape,
                                  const vector<int> &strides,
                                  T *output);

    int reshape(
        void* param, int param_size,
        const vector<vector<int>>& input_shapes,
        vector<vector<int>>& output_shapes) {
        // Use input shape as the max shape
        // Because output shape varies with input_tensors_[1]
        output_shapes[0] = input_shapes[0];
        if(input_shapes.size() == 1){
            BMCPU_DECLARE_AND_UNPACK_PARAM(cpu_adaptive_pool_param_t, layer_param, param, param_size);
            output_shapes[0][2] = layer_param->output_shape[0];
            output_shapes[0][3] = layer_param->output_shape[1];
            output_shapes[0][4] = layer_param->output_shape[2];
        }
        return 0;
    }
    int dtype(const void *param, size_t param_size, const vector<int> &input_dtypes, vector<int> &output_dtypes);
};

}
#endif /* CPU_ADAPTIVE_AVERAGE_POOLING3D_H */
