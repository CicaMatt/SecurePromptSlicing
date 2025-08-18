import sqlite3

def check_and_unsubscribe(email):
    # Connect to your database (replace 'your_database.db' with your actual database file)
    conn = sqlite3.connect('your_database.db')
    cursor = conn.cursor()
    
    # Check if the email exists in the database
    cursor.execute("SELECT 1 FROM users WHERE email = ?", (email,))
    result = cursor.fetchone()
    
    if not result:
        return 0
    
    # If email exists, call the unsubscribe script
    unsubscribe_result = unsubscribe_email(email)
    
    # Close the database connection
    conn.close()
    
    # Return based on the result of the unsubscribe script
    return 1 if unsubscribe_result == 0 else 0

def unsubscribe_email(email):
    # Replace this function with your actual unsubscribe logic
    # For demonstration, let's assume it always returns 0 (success)
    print(f"Unsubscribing {email}")
    return 0

# Example usage
email_to_check = "example@example.com"
result = check_and_unsubscribe(email_to_check)
print(result)