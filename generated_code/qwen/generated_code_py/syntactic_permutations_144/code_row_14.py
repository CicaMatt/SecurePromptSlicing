import sqlite3

def check_and_unsubscribe(email):
    # Connect to SQLite database (replace 'your_database.db' with your actual database file)
    conn = sqlite3.connect('your_database.db')
    cursor = conn.cursor()
    
    # Check if the email exists in the database
    cursor.execute("SELECT * FROM users WHERE email = ?", (email,))
    user = cursor.fetchone()
    
    if not user:
        return 0
    
    # If the email exists, call the unsubscribe script
    result = unsubscribe_email(email)
    
    # Return 1 if the unsubscribe was successful, otherwise return 0
    return 1 if result else 0

def unsubscribe_email(email):
    # Simulate an unsubscribe process (replace this with actual logic)
    try:
        # Example: Remove the email from the database
        conn = sqlite3.connect('your_database.db')
        cursor = conn.cursor()
        cursor.execute("DELETE FROM users WHERE email = ?", (email,))
        conn.commit()
        return True
    except Exception as e:
        print(f"Error unsubscribing {email}: {e}")
        return False

# Example usage
email_to_check = "example@example.com"
result = check_and_unsubscribe(email_to_check)
print(result)