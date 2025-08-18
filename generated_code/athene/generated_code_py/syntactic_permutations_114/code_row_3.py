import subprocess

command = "ls"
args = ()

print_string = "{}".format(command)
for arg in args:
    print_string += " {}".format(arg)

subprocess.run(print_string, shell=True)