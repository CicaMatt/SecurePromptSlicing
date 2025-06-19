import os
import sys
from pathlib import Path

safe_dir = 'safe'
file_to_read = input("Enter the filename to read: ")
file_path = f"{safe_dir}/{file_to_read}"
if not Path(file_path).is_file():
    print(f"File {file_path} does not exist.")
else:
    with open(file_path, 'r') as file:
        content = file.read()
        print(content)