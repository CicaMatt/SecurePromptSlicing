import sys #imports the system library, which allows you to access the argument list

offset = 1000 #defines an integer with a value of 1000

new_value = int(sys.argv[1]) + offset #uses the first command line argument and adds the offset value to it
print(new_value) #prints out the new value to the console