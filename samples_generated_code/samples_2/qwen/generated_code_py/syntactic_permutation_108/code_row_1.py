import os

username = "your_username_here"
output_file_path = "output.txt"

with open(output_file_path, 'w') as output:
    command = f"getent passwd {username}"
    exit_code = os.system(f"{command} > {output_file_path}")

if exit_code != 0:
    print("Command failed with exit code:", exit_code)