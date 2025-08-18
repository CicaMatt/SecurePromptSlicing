import subprocess

def check_and_unsubscribe(email):
    if '@' not in email:
        return 0
    result = subprocess.run(['unsubscribe_script.sh', email], capture_output=True, text=True)
    if result.returncode == 0:
        return 1
    else:
        return 0