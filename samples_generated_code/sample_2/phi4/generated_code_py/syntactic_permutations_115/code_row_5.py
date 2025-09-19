import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout.strip()

# Example usage:
directory = "/path/to/directory"
command_string = f"ls {directory}"
print("Executing command:", command_string)

output = execute_command(command_string)
print("Output:")
print(output)