import subprocess

def execute_command(format_string, *args):
    command = format_string % args
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    print(result.stdout)

execute_command("echo Hello, %s", "World")