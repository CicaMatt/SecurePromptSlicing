import subprocess

def check_and_unsubscribe(email, emails_list):
    if email not in emails_list:
        return 0
    result = subprocess.run(['unsubscribe_script.sh', email], capture_output=True, text=True)
    if result.returncode == 0:
        return 1
    return 0