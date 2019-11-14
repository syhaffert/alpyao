#include "AlpaoDM.h"

AlpaoDM::AlpaoDM(std::string serialNumber){
	serial_number = serialNumber.c_str();
	
	real_dm = new acs::DM( serial_number );
    if ( !real_dm->Check() )
        throw std::runtime_error("The DM has not initialized correctly!");
    
	// Get the number of actuators
    number_of_actuators = (acs::UInt) real_dm->Get( "NbOfActuator" );
	real_dm->Set("daqFreq", 2e6);

	// Initialize the actuator voltages to 0.0
	actuator_voltages = new acs::Scalar[number_of_actuators]();
}

AlpaoDM::~AlpaoDM(){
	delete actuator_voltages;
	delete real_dm;
}

void AlpaoDM::Send(py::array_t<double> xs){
	py::buffer_info info = xs.request();
	if (info.ndim != 1)
		throw std::runtime_error("The input needs to be one-dimensional!");

	if (info.shape[0] != number_of_actuators)
		throw std::runtime_error("The input size needs to match with the number of actuators!");

	double *ptr1 = (double *) info.ptr;
	for(size_t i=0; i<info.shape[0]; i++){
		
		// Add software safety to DM voltage commands
		if(ptr1[i] < 1 && ptr1[i] > -1){
			actuator_voltages[i] = ptr1[i];
		}else{
			if(ptr1[i]>1){
				actuator_voltages[i] = 1;
			}else{
				actuator_voltages[i] = -1;
			}
		}

	}

	real_dm->Send( actuator_voltages );
	
	if ( !real_dm->Check() )
        throw std::runtime_error("The command was not send succesfully!");
}

void AlpaoDM::Reset(){
	for(int i=0; i<number_of_actuators; i++)
		actuator_voltages[i] = 0;
	
	real_dm->Send( actuator_voltages );
	
	if ( !real_dm->Check() )
        throw std::runtime_error("The reset was not send succesfully!");
}

std::string AlpaoDM::GetVoltages(){
	std::string message = "Command : ";
	for(int i=0; i<number_of_actuators; i++)
		message += std::to_string(actuator_voltages[i]) + ", ";
	return message;
}