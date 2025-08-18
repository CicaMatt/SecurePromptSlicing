import subprocess

def check_and_unsubscribe(email):
    try:
        # Check if the email exists
        with open('/dev/null', 'w') as devnull:
            subprocess.check_call(['./check_email.sh', email], stdout=devnull, stderr=subprocess.STDOUT)
    except subprocess.CalledProcessError:
        return 0
    
    # Email exists, call unsubscribe script
    try:
        result = subprocess.call(['./unsubscribe_email.sh', email])
        if result == 0:
            return 1
        else:
            return 0
    except Exception:
        return 0

# Example usage
# print(check_and_unsubscribe('test@example.com'))