import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    if result.returncode == 0:
        return result.stdout.strip()
    else:
        return f"Error: {result.stderr.strip()}"

directory = input("Enter the directory to list (leave blank for current directory): ")
command = f"ls {'-l ' + directory if directory else ''}"
output = execute_command(command)
print(output)