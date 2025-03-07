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

#include "open3d/core/Device.h"

#include "pybind/core/core.h"
#include "pybind/docstring.h"
#include "pybind/open3d_pybind.h"

namespace open3d {
namespace core {

void pybind_core_device(py::module &m) {
    py::class_<Device> device(
            m, "Device",
            "Device context specifying device type and device id.");
    device.def(py::init<>());
    device.def(py::init<Device::DeviceType, int>());
    device.def(py::init<const std::string &, int>());
    device.def(py::init<const std::string &>());
    device.def("__eq__", &Device::operator==);
    device.def("__ene__", &Device::operator!=);
    device.def("__repr__", &Device::ToString);
    device.def("__str__", &Device::ToString);
    device.def("get_type", &Device::GetType);
    device.def("get_id", &Device::GetID);
    device.def(py::pickle(
            [](const Device &d) {
                return py::make_tuple(d.GetType(), d.GetID());
            },
            [](py::tuple t) {
                if (t.size() != 2) {
                    utility::LogError(
                            "Cannot unpickle Device! Expecting a tuple of size "
                            "2.");
                }
                return Device(t[0].cast<Device::DeviceType>(),
                              t[1].cast<int>());
            }));

    py::enum_<Device::DeviceType>(device, "DeviceType")
            .value("CPU", Device::DeviceType::CPU)
            .value("CUDA", Device::DeviceType::CUDA)
            .export_values();
}

}  // namespace core
}  // namespace open3d
