#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
namespace py = pybind11;

#include <string>
#include <iostream>
#include <sstream>
#include "FakeAlpao.h"

FakeAlpao::FakeAlpao(std::string serialNumber){
	serial_number = serialNumber.c_str();
	number_of_actuators = 97;

	actuator_voltages = new acs::Scalar[number_of_actuators]();
};

FakeAlpao::~FakeAlpao(){
	delete actuator_voltages;
};

void FakeAlpao::Send(py::array_t<double> xs){
	py::buffer_info info = xs.request();
	if (info.ndim != 1)
		throw std::runtime_error("The input needs to be one-dimensional!");

	if (info.shape[0] != number_of_actuators)
		throw std::runtime_error("The input size needs to match with the number of actuators!");

	double *ptr1 = (double *) info.ptr;
	for(size_t i=0; i<info.shape[0]; i++)
		actuator_voltages[i] = ptr1[i];
}

void FakeAlpao::Reset(){
	for(int i=0; i<number_of_actuators; i++)
		actuator_voltages[i] = 0;
}

std::string FakeAlpao::GetVoltages(){
	std::string message = "Command : ";
	for(int i=0; i<number_of_actuators; i++)
		message += std::to_string(actuator_voltages[i]) + ", ";
	return message;
}