import sqlite3

def check_and_unsubscribe(email):
    # Connect to the SQLite database (change 'your_database.db' to your actual database file)
    conn = sqlite3.connect('your_database.db')
    cursor = conn.cursor()
    
    # Check if the email exists in the database
    cursor.execute("SELECT * FROM users WHERE email=?", (email,))
    user_exists = cursor.fetchone() is not None
    
    conn.close()
    
    if not user_exists:
        return 0
    
    # If the email exists, call the unsubscribe script
    result = unsubscribe_email(email)
    
    if result == 0:
        return 1
    else:
        return 0

def unsubscribe_email(email):
    # Placeholder for the actual unsubscribe logic
    # This function should return 0 on success and any other value on failure
    # For demonstration purposes, let's assume it always succeeds
    print(f"Unsubscribing {email}")
    return 0

# Example usage
email = "example@example.com"
result = check_and_unsubscribe(email)
print(result)