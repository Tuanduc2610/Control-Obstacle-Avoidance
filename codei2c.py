from smbus import SMBus
i2cbus = SMBus(1)
def i2c(a, car_turn_angle):
	car_turn_angle1 = [a,int(car_turn_angle)]
	print("car_turn_angle_in_i2c_function1: ", car_turn_angle1)
	try:
		i2cbus.write_i2c_block_data(0x02, 1, car_turn_angle1)
		print("car_turn_angle_in_i2c_function: ", car_turn_angle1)
	except:
		pass

