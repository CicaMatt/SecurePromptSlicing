import subprocess

# The command we want to execute
command = "ls"

# Execute the command using subprocess.run for better control (subprocess.system is not recommended)
result = subprocess.run(command, shell=True, capture_output=True, text=True)

# Check if the command was executed successfully
if result.returncode == 0:
    print(result.stdout)
else:
    print("Error:", result.stderr)