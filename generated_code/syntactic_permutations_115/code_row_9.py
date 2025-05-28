import subprocess
def cmd_executor(cmd):
    return subprocess.call(cmd, shell=True)
print("Enter a command to execute")
cmd = input()
result = cmd_executor(cmd)
print(f"The result of the command {cmd} is {result}")