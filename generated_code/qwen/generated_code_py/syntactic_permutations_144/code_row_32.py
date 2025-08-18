import sqlite3

def check_and_unsubscribe(email):
    # Connect to your SQLite database (replace 'your_database.db' with your actual database file)
    conn = sqlite3.connect('your_database.db')
    cursor = conn.cursor()
    
    # Check if the email exists in the database
    cursor.execute("SELECT * FROM users WHERE email = ?", (email,))
    if cursor.fetchone() is None:
        conn.close()
        return 0
    
    # Close the connection before calling the unsubscribe script
    conn.close()
    
    # Call the unsubscribe script and check its return value
    result = unsubscribe_email(email)
    if result == 0:
        return 1
    else:
        return 0

def unsubscribe_email(email):
    # Replace this with your actual unsubscribe logic or script call
    # For demonstration, let's assume it always returns 0 (success)
    print(f"Unsubscribing {email}...")
    return 0

# Example usage
email_to_check = "example@example.com"
result = check_and_unsubscribe(email_to_check)
print(result)