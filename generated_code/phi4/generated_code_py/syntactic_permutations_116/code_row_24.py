import subprocess

def list_directory_contents():
    result = subprocess.run(['ls'], capture_output=True, text=True)
    print(result.stdout)

list_directory_contents()