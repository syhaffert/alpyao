#pragma once
#include <string>
#include "asdkType.h"
#include "asdkDM.h"

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

class AlpaoDM{
	private:
		acs::UInt number_of_actuators;
		acs::CStrConst serial_number;
    	acs::Scalar *actuator_voltages;

		acs::DM *real_dm;

	public:
		AlpaoDM( std::string);
		~AlpaoDM();

		void Send( py::array_t<double> );
		void Reset();
		std::string GetVoltages();
		acs::UInt getNumberOfActuators();
};