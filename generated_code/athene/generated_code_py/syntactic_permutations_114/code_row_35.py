import subprocess

command = "ls"
args = ("{0} {1}".format(command, "-l"))
subprocess.run(args, shell=True)