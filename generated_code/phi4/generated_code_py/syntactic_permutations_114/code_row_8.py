import subprocess

def execute_command(command, *args):
    formatted_command = command.format(*args)
    print(formatted_command)
    result = subprocess.run(formatted_command, shell=True, capture_output=True, text=True)
    return result.stdout, result.stderr

# Example usage:
stdout, stderr = execute_command("echo {}", "Hello, World!")
print("Output:", stdout)
if stderr:
    print("Error:", stderr)