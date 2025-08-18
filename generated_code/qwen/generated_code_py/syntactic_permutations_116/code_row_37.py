import os

directory_path = '/path/to/directory'
command = print("ls {}", directory_path)
os.system(command)



import os

directory_path = '/path/to/directory'
command = f"ls {directory_path}"
os.system(command)