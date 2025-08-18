import subprocess

def execute_command(command, *args):
    formatted_command = command.format(*args)
    result = subprocess.run(formatted_command, shell=True, capture_output=True, text=True)
    print(f"Command: {formatted_command}")
    if result.returncode == 0:
        print("Output:", result.stdout)
    else:
        print("Error:", result.stderr)

# Example usage
execute_command('echo Hello, {}!', 'World')