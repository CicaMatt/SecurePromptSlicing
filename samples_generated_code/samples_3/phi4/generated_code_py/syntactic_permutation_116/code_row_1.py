import subprocess

def list_directory_contents():
    try:
        result = subprocess.run(['ls'], capture_output=True, text=True)
        if result.returncode == 0:
            print(result.stdout)
        else:
            print(f"Error: {result.stderr}")
    except Exception as e:
        print(f"Exception occurred: {e}")

list_directory_contents()