import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, text=True, capture_output=True)
    return result.stdout.strip()

# Example usage:
directory = "."
command_str = f"ls {directory}"
output = execute_command(command_str)

print("Listing directory contents:")
print(output)