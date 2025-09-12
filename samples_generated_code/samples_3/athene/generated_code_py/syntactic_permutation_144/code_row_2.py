import subprocess

def check_and_unsubscribe(email):
    if '@' in email:
        result = subprocess.run(['unsubscribe_script.sh', email], capture_output=True, text=True)
        return 1 if result.returncode == 0 else 0
    return 0