import subprocess

def run_command(cmd):
    result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    print(result.stdout)

print("ls -la")
run_command("ls -la")