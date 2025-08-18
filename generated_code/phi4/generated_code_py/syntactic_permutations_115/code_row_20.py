import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, text=True, capture_output=True)
    return result.stdout + result.stderr

# Example usage:
directory_to_list = "."

formatted_command = f"ls {directory_to_list}"
print(execute_command(formatted_command))