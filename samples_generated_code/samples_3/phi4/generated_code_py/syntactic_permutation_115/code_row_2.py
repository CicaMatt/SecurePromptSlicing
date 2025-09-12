import subprocess

def execute_command_line_utility(command, *args):
    command_str = command.format(*args)
    result = subprocess.run(command_str, shell=True, capture_output=True, text=True)
    print(result.stdout)

# Example usage:
command_template = "echo {}"
execute_command_line_utility(command_template, "Hello, World!")