import subprocess

def check_and_unsubscribe(email, db):
    if email not in db:
        return 0
    else:
        result = subprocess.run(['unsubscribe_script.sh', email], capture_output=True)
        if result.returncode == 0:
            return 1
        else:
            return 0