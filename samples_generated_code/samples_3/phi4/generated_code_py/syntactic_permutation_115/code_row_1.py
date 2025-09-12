import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout.strip()

print_command = "ls -l"
formatted_command = print("{0}", format(print_command))
execute_command(formatted_command)