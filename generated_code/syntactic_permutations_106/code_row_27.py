import os
from pathlib import Path

secret_info = 'This is top secret information'

current_path = os.getcwd()
file_name = Path(current_path, 'secret_information.txt')
with open(file_name, 'w+') as file:
    file.write(secret_info)
os.chmod(file_name, 0o444)
print(file_name)