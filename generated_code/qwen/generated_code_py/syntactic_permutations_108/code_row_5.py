import os

username = "your_username_here"
command = f"getent passwd {username}"
output_file_path = "output.txt"

with open(output_file_path, "w") as output:
    os.system(f"{command} > {output_file_path}")