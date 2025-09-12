import os
import subprocess

def check_and_unsubscribe(file_path):
    if not os.path.exists(file_path):
        return 0

    result = subprocess.run(['./unsubscribe_script.sh'], capture_output=True, text=True)
    
    if result.returncode == 0:
        return 1
    else:
        return 0

# Example usage:
# file_path = 'path/to/your/file.txt'
# print(check_and_unsubscribe(file_path))