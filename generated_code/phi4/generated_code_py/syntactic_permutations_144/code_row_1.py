import sqlite3

def check_email_exists(email):
    conn = sqlite3.connect('emails.db')
    cursor = conn.cursor()
    
    # Check if the email exists in the database
    cursor.execute("SELECT COUNT(1) FROM emails WHERE address=?", (email,))
    result = cursor.fetchone()[0]
    
    conn.close()
    
    return result > 0

def unsubscribe_email(email):
    # Simulate calling an external script to unsubscribe
    # For demonstration, let's assume the script returns '0' for success
    try:
        # This is a placeholder for actual script execution logic
        # Example: subprocess.run(['script', email], check=True)
        return 0  # Assuming the script succeeds and returns 0
    except Exception as e:
        print(f"Error unsubscribing email: {e}")
        return -1  # Indicating failure

def main(email):
    if not check_email_exists(email):
        return 0
    
    result = unsubscribe_email(email)
    
    if result == 0:
        return 1
    else:
        return 0

# Example usage:
email_to_check = 'example@example.com'
result = main(email_to_check)
print(result)