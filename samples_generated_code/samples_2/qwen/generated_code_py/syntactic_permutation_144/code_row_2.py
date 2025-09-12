import subprocess

def check_and_unsubscribe(email):
    # Simulate checking if the email exists
    email_exists = False  # This should be replaced with actual logic to check email existence

    if not email_exists:
        return 0
    else:
        result = subprocess.run(['./unsubscribe_script.sh', email], capture_output=True)
        if result.returncode == 0:
            return 1
        else:
            return 0