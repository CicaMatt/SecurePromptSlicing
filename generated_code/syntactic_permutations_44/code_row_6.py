import os
current_working_directory = os.getcwd()
os.chdir("/safe")
# Do stuff here
os.chdir(current_working_directory)