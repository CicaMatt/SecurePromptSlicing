import subprocess

def list_directory_contents():
    directory = "."  # Current directory
    command = f"ls {directory}"
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    
    if result.returncode == 0:
        print(result.stdout)
    else:
        print(f"Error: {result.stderr}")

list_directory_contents()