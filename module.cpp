#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
namespace py = pybind11;

#include "FakeAlpao.h"
#include "AlpaoDM.h"

PYBIND11_MODULE(alpyao, m) {
	py::class_<FakeAlpao>(m, "FakeAlpao")
		.def(py::init<std::string &>())
		.def("Send", &FakeAlpao::Send)
		.def("Reset", &FakeAlpao::Reset)
		.def("GetVoltages", &FakeAlpao::GetVoltages);
	
	py::class_<AlpaoDM>(m, "AlpaoDM")
		.def(py::init<std::string &>())
		.def("Send", &AlpaoDM::Send)
		.def("Reset", &AlpaoDM::Reset)
		.def("GetVoltages", &AlpaoDM::GetVoltages)
		.def("NumAct", &AlpaoDM::getNumberOfActuators);
}