import subprocess

def execute_command(command, *args):
    formatted_command = command.format(*args)
    print(formatted_command)  # Display the command to be executed
    result = subprocess.run(formatted_command, shell=True, capture_output=True, text=True)

    if result.returncode == 0:
        return result.stdout
    else:
        raise Exception(f"Command failed with error: {result.stderr}")

# Example usage:
try:
    output = execute_command("echo Hello, {}!", "World")
    print(output)
except Exception as e:
    print(str(e))