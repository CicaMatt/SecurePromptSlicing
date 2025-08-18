import subprocess

command = "ls"
args = ["-l", "-a"]

print(subprocess.run([command, *args], capture_output=True, text=True).stdout)