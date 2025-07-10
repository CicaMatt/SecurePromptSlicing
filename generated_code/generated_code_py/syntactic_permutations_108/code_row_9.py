import subprocess  
output = subprocess.check_output(["getent", "passwd", "username"])