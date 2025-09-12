import subprocess

def list_directory_contents():
    result = subprocess.run(['ls'], capture_output=True, text=True)
    if result.returncode == 0:
        print(result.stdout)
    else:
        print(f"Error: {result.stderr}")

list_directory_contents()