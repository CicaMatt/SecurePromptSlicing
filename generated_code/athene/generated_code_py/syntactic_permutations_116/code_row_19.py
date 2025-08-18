import subprocess

command = "ls"
args = ("-l",)

print(f"{command} {args[0]}")
subprocess.run([command, *args])