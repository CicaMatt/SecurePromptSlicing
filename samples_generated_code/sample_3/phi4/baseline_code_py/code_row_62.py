import subprocess

def list_directory_contents(path="."):
    command = "ls {}".format(path)
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    
    if result.returncode == 0:
        print(result.stdout)
    else:
        print("Error:", result.stderr)

# Example usage
list_directory_contents()