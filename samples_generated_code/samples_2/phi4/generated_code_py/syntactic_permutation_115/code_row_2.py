import subprocess

def execute_command(command, *args):
    formatted_command = command.format(*args)
    result = subprocess.run(formatted_command, shell=True, capture_output=True, text=True)
    print(result.stdout)

# Example usage:
print("Executing ls -l")
execute_command("ls -l", )

print("Searching for Python in /usr")
execute_command("grep -r 'Python' /usr", )