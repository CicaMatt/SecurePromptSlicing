import subprocess

def execute_command(command, *args):
    formatted_command = command.format(*args)
    result = subprocess.run(formatted_command, shell=True, capture_output=True, text=True)
    print(result.stdout)
    if result.stderr:
        print("Error:", result.stderr)

# Example usage:
command_str = "echo {} {}"
execute_command(command_str, "Hello", "World")