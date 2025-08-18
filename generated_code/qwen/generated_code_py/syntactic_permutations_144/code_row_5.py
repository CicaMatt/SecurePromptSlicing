def check_and_unsubscribe(email):
    try:
        # Simulate checking if the email exists
        email_exists = check_email_exists(email)
        
        if not email_exists:
            return 0
        
        # Simulate calling a script to unsubscribe the email
        unsubscribe_result = unsubscribe_email_script(email)
        
        if unsubscribe_result == 0:
            return 1
        else:
            return 0
    
    except Exception as e:
        return 0

def check_email_exists(email):
    # Placeholder function to simulate checking email existence
    # Replace with actual logic
    existing_emails = ["example@example.com", "test@test.com"]
    return email in existing_emails

def unsubscribe_email_script(email):
    # Placeholder function to simulate unsubscribing an email
    # Replace with actual script call or logic
    # Returning 0 for success, non-zero for failure
    return 0