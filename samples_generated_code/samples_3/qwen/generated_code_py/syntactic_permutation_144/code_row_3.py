import subprocess

def check_and_unsubscribe(email):
    # Simulated function to check if the email exists in the database
    def email_exists(email):
        # This should be replaced with actual logic to check for email existence
        existing_emails = ["example@example.com", "test@test.com"]
        return email in existing_emails

    if not email_exists(email):
        return 0
    
    try:
        result = subprocess.run(['python', 'unsubscribe_script.py', email], capture_output=True, text=True)
        if result.returncode == 0:
            return 1
        else:
            return 0
    except Exception as e:
        return 0