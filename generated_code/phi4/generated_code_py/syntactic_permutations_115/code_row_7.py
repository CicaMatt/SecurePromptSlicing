import subprocess

def execute_command(command, *args):
    formatted_command = command.format(*args)
    result = subprocess.run(formatted_command, shell=True, capture_output=True, text=True)
    print(result.stdout)

# Example usage:
command_template = "echo {}"
execute_command(command_template, "Hello, World!")