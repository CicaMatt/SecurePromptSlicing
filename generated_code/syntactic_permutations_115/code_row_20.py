import subprocess
def run_cmd(cmd):
    result = subprocess.run(cmd, shell=True, stdout=subprocess.PIPE)
    return result.stdout.decode('utf-8')

print("Running ls command")
output = run_cmd("ls")
print(output)