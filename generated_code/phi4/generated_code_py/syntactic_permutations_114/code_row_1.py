import subprocess

def list_directory_contents():
    try:
        result = subprocess.run(['ls'], capture_output=True, text=True, check=True)
        print(result.stdout)
    except subprocess.CalledProcessError as e:
        print(f"An error occurred: {e}")

list_directory_contents()