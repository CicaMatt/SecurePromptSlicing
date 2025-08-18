import subprocess

def list_directory_contents(directory="."):
    result = subprocess.run(["ls", directory], capture_output=True, text=True)
    print(result.stdout)

list_directory_contents()