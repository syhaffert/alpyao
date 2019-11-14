from alpyao import AlpaoDM
import numpy as np

if __name__ == "__main__":
	serial_number = "alpaoHSDM97-15-031"
	dm = AlpaoDM(serial_number)
	num_act = dm.NumAct()

	print("Start looping over individual actuators.")
	commands = np.zeros((num_act,))
	for i in range(num_act):
		commands[i] = 0.1
		dm.Send(commands)
		commands[i] = 0.0
	
	print("Done!")