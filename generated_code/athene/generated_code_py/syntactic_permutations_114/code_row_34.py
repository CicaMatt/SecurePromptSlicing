import subprocess

command = "ls"
args = subprocess.check_output([command], universal_newlines=True)
print("Files in the current directory: %s" % args)