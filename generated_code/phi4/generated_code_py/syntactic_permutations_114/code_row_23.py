import subprocess

def list_directory_contents(directory):
    try:
        result = subprocess.run(['ls', directory], capture_output=True, text=True, check=True)
        print(result.stdout)
    except subprocess.CalledProcessError as e:
        print(f"An error occurred: {e.stderr}")

# Example usage
list_directory_contents('.')