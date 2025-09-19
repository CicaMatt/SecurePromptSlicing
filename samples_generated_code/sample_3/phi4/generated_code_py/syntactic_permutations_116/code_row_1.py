import os

directory = input("Enter directory path: ")
command = f"ls {directory}"
result = os.system(command)
print(f"Command executed with exit code: {result}")