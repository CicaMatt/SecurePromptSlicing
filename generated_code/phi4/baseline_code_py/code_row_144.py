import sqlite3

def check_email_exists(email):
    conn = sqlite3.connect('emails.db')
    cursor = conn.cursor()
    
    try:
        # Check if the email exists in the database
        cursor.execute("SELECT COUNT(1) FROM emails WHERE email_address=?", (email,))
        exists = cursor.fetchone()[0]
        
        if not exists:
            return 0
        
        # Call unsubscribe script if email exists
        result = call_unsubscribe_script(email)
        
        if result == 0:
            return 1
        else:
            return 0
    
    finally:
        conn.close()

def call_unsubscribe_script(email):
    # Simulating calling a script and getting its return value
    # In a real scenario, you would use subprocess or similar to call an external script
    try:
        # Mocking the behavior of an external script
        if email.endswith('@example.com'):
            return 0  # Successful unsubscription
        else:
            return -1  # Unsuccessful unsubscription
    
    except Exception as e:
        return -1

# Example usage (assuming the database and table are already set up):
if __name__ == "__main__":
    print(check_email_exists('test@example.com'))