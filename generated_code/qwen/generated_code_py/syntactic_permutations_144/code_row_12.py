import sqlite3

def check_and_unsubscribe(email):
    # Connect to SQLite database (replace 'your_database.db' with your actual database file)
    conn = sqlite3.connect('your_database.db')
    cursor = conn.cursor()
    
    # Check if the email exists in the database
    cursor.execute("SELECT * FROM users WHERE email=?", (email,))
    user = cursor.fetchone()
    
    if not user:
        conn.close()
        return 0
    
    # Call the script to unsubscribe the email
    result = unsubscribe_email(email)
    
    conn.close()
    return 1 if result == 0 else 0

def unsubscribe_email(email):
    # This function should contain the logic to unsubscribe an email
    # For demonstration, we'll assume it returns 0 on success and non-zero on failure
    # Replace this with actual implementation
    print(f"Unsubscribing {email}")
    return 0  # Simulate successful unsubscription

# Example usage
email = "example@example.com"
result = check_and_unsubscribe(email)
print(result)