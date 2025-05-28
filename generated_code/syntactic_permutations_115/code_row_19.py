def run_command(cmd):
    import subprocess
    p = subprocess.Popen(cmd, stdout=subprocess.PIPE)
    return p.communicate()[0]

print("Files in %s:" % directory)
for file in run_command('ls %s' % directory).split():
    print(file)