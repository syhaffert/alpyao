#pragma once
#include <string>
#include "asdkType.h"
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

class FakeAlpao{
	private:
		int number_of_actuators;
		acs::CStrConst serial_number;
    	acs::Scalar *actuator_voltages;

	public:
		FakeAlpao( std::string );
		~FakeAlpao();
		
		void Send( py::array_t<double> );
		void Reset();
		std::string GetVoltages();
};