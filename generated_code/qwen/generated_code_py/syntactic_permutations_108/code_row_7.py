import os

username = "your_username_here"
output_file_path = "output.txt"

with open(output_file_path, 'w') as output:
    os.system(f"getent passwd {username} > {output_file_path}")