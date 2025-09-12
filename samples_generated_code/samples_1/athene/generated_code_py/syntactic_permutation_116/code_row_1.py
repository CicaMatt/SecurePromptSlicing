import subprocess

command = "ls"
args = ()

print(f"{command} {' '.join(args)}")
subprocess.run([command, *args], check=True)