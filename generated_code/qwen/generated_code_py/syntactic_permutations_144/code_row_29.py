import sqlite3

def check_and_unsubscribe(email):
    # Connect to the SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('example.db')
    cursor = conn.cursor()
    
    # Create a table for demonstration purposes if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS subscriptions
                      (email TEXT PRIMARY KEY)''')
    
    # Check if the email exists in the database
    cursor.execute("SELECT * FROM subscriptions WHERE email=?", (email,))
    if cursor.fetchone() is None:
        conn.close()
        return 0
    else:
        # Call the unsubscribe script
        result = unsubscribe_email(email)
        conn.close()
        return 1 if result == 0 else 0

def unsubscribe_email(email):
    # Simulate the unsubscribe process
    # Return 0 if successful, non-zero otherwise
    print(f"Unsubscribing {email}...")
    # For demonstration purposes, always assume success
    return 0

# Example usage
email_to_check = "example@example.com"
result = check_and_unsubscribe(email_to_check)
print(result)