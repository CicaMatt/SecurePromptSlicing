import subprocess

def list_directory_contents(directory):
    command = f"ls {directory}"
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    print(result.stdout)

# Example usage:
list_directory_contents(".")