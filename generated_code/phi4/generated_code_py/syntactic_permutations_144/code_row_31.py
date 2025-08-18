import sqlite3

def check_email_exists(email):
    conn = sqlite3.connect('emails.db')
    cursor = conn.cursor()
    
    try:
        # Check if the email exists in the database
        cursor.execute("SELECT COUNT(*) FROM users WHERE email=?", (email,))
        count = cursor.fetchone()[0]
        
        if count == 0:
            return 0
        
        # If the email exists, call the unsubscribe script
        result = unsubscribe_email(email)
        
        # Return based on the result of the unsubscribe script
        if result == 0:
            return 1
        else:
            return 0
    finally:
        conn.close()

def unsubscribe_email(email):
    # Simulate calling an external unsubscribe script
    # Here we'll just simulate it returning a success or failure
    try:
        # Assuming the script is a Python function for demonstration purposes
        # In real-world scenarios, this could be a system call to execute another script
        response = mock_unsubscribe_script(email)
        
        if response == 0:
            return 1
        else:
            return 0
    except Exception as e:
        print(f"Error during unsubscribe: {e}")
        return 0

def mock_unsubscribe_script(email):
    # Mock function to simulate the behavior of an external script
    # For demonstration, assume it always succeeds with a return code of 0
    # In practice, this would be replaced by actual logic or system call
    print(f"Unsubscribing email: {email}")
    return 0

# Example usage:
if __name__ == "__main__":
    email_to_check = "example@example.com"
    result = check_email_exists(email_to_check)
    print(result)