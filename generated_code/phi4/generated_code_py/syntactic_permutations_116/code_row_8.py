import subprocess

def execute_command(command, *args):
    formatted_command = command.format(*args)
    print(formatted_command)  # Print the command before execution
    subprocess.run(formatted_command, shell=True)

# Example usage:
execute_command("echo {} {}", "Hello", "World")