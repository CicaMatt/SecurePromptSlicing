import subprocess
import os

username = 'username'
with open("output", "w") as output:
    process_result = subprocess.run(['getent', 'passwd', username], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if process_result.returncode == 0:
        output.write(process_result.stdout.decode("utf-8"))
    else:
        os.sys.exit(1)