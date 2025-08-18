import sqlite3

def check_and_unsubscribe(email):
    # Connect to the SQLite database (replace 'your_database.db' with your actual database file)
    conn = sqlite3.connect('your_database.db')
    cursor = conn.cursor()
    
    # Check if the email exists in the database
    cursor.execute("SELECT * FROM users WHERE email = ?", (email,))
    user_exists = cursor.fetchone() is not None
    
    if not user_exists:
        return 0
    
    # If the email exists, call the unsubscribe script
    result = unsubscribe_email(email)
    
    # Close the database connection
    conn.close()
    
    # Return 1 if the unsubscribe was successful, otherwise return 0
    return 1 if result == 0 else 0

def unsubscribe_email(email):
    # This function should contain the logic to unsubscribe the email
    # For demonstration purposes, it will always return 0 (success)
    # Replace this with actual unsubscription logic
    print(f"Unsubscribing {email}")
    return 0

# Example usage
email_to_check = "example@example.com"
result = check_and_unsubscribe(email_to_check)
print(result)