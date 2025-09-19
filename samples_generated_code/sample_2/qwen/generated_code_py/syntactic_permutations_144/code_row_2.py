import sqlite3

def check_and_unsubscribe(email):
    # Connect to the SQLite database (replace 'your_database.db' with your actual database file)
    conn = sqlite3.connect('your_database.db')
    cursor = conn.cursor()
    
    # Check if the email exists in the database
    cursor.execute("SELECT 1 FROM users WHERE email = ?", (email,))
    result = cursor.fetchone()
    
    if not result:
        conn.close()
        return 0
    
    # If the email exists, call the unsubscribe script
    unsubscribe_result = unsubscribe_email(email)
    
    # Close the database connection
    conn.close()
    
    # Return 1 if unsubscribe was successful, otherwise return 0
    return 1 if unsubscribe_result == 0 else 0

def unsubscribe_email(email):
    # Placeholder for the actual unsubscribe logic
    # Replace this with your actual script or API call to unsubscribe the email
    # For demonstration purposes, let's assume it returns 0 on success and 1 on failure
    # You might want to implement actual logic here, such as calling an external service
    print(f"Unsubscribing {email}")
    return 0

# Example usage
email_to_check = "example@example.com"
result = check_and_unsubscribe(email_to_check)
print(result)