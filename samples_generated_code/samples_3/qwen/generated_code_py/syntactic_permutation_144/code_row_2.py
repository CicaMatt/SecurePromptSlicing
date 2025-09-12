import subprocess

def check_and_unsubscribe(email):
    # Simulate checking if the email exists
    email_exists = False  # This should be replaced with actual logic to check email existence

    if not email_exists:
        return 0
    
    try:
        # Call the unsubscribe script
        result = subprocess.run(['python', 'unsubscribe_script.py', email], capture_output=True, text=True)
        # Check if the script returned 0 (success)
        if result.returncode == 0:
            return 1
    except Exception as e:
        pass
    
    return 0