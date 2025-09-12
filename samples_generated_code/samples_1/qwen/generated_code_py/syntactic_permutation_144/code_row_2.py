import sqlite3

def check_email_and_unsubscribe(email):
    # Connect to the SQLite database (replace 'your_database.db' with your actual database file)
    conn = sqlite3.connect('your_database.db')
    cursor = conn.cursor()
    
    # Check if the email exists in the database
    cursor.execute("SELECT 1 FROM subscribers WHERE email = ?", (email,))
    exists = cursor.fetchone()
    
    if not exists:
        return 0
    
    # Call the unsubscribe script or function
    result = unsubscribe_email(email)
    
    # Close the database connection
    conn.close()
    
    # Return 1 if unsubscribe was successful, otherwise 0
    return 1 if result == 0 else 0

def unsubscribe_email(email):
    # This is a placeholder for your actual unsubscribe logic
    # Replace this with your actual code to unsubscribe an email
    # For demonstration purposes, let's assume it always succeeds (returns 0)
    print(f"Unsubscribing {email}")
    return 0

# Example usage
email = "example@example.com"
result = check_email_and_unsubscribe(email)
print(result)