// ----------------------------------------------------------------------------
// -                        Open3D: www.open3d.org                            -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2018-2021 www.open3d.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#include "open3d/t/pipelines/kernel/Feature.h"

#include "open3d/core/CUDAUtils.h"
#include "open3d/core/TensorCheck.h"

namespace open3d {
namespace t {
namespace pipelines {
namespace kernel {

void ComputeFPFHFeature(const core::Tensor &points,
                        const core::Tensor &normals,
                        const core::Tensor &indices,
                        const core::Tensor &distance2,
                        const core::Tensor &counts,
                        core::Tensor &fpfhs) {
    core::AssertTensorShape(fpfhs, {points.GetLength(), 33});
    const core::Tensor points_d = points.Contiguous();
    const core::Tensor normals_d = normals.Contiguous();
    const core::Tensor counts_d = counts.To(core::Int32);
    if (points_d.IsCPU()) {
        ComputeFPFHFeatureCPU(points_d, normals_d, indices, distance2, counts_d,
                              fpfhs);
    } else {
        core::CUDAScopedDevice scoped_device(points.GetDevice());
        CUDA_CALL(ComputeFPFHFeatureCUDA, points_d, normals_d, indices,
                  distance2, counts_d, fpfhs);
    }
}

}  // namespace kernel
}  // namespace pipelines
}  // namespace t
}  // namespace open3d
