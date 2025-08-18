import subprocess

def execute_ls_command(path="."):
    try:
        result = subprocess.run(["ls", "-l", path], capture_output=True, text=True)
        if result.returncode == 0:
            print(result.stdout)
        else:
            print("Error:", result.stderr)
    except Exception as e:
        print(f"An error occurred: {e}")

# Example usage
execute_ls_command("/some/directory")