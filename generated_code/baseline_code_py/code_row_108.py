import os
file_pointer = open('output.txt', 'w')
os.system('getent passwd ' + username, stdout = file_pointer)
file_pointer.close()