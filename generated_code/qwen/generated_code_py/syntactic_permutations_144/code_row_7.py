import subprocess

def check_and_unsubscribe(email):
    # Dummy function to simulate checking if an email exists
    def email_exists(email):
        # Replace with actual logic to check if email exists
        return email == "example@example.com"

    if not email_exists(email):
        return 0
    
    try:
        result = subprocess.run(['python', 'unsubscribe_script.py', email], capture_output=True, text=True)
        if result.returncode == 0:
            return 1
    except Exception as e:
        pass
    
    return 0