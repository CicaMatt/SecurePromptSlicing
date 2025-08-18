import sqlite3

def check_and_unsubscribe(email):
    # Connect to the SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('email_database.db')
    cursor = conn.cursor()
    
    # Create a table for emails if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS subscribers
                      (id INTEGER PRIMARY KEY AUTOINCREMENT, email TEXT UNIQUE)''')
    
    # Check if the email exists in the database
    cursor.execute('SELECT * FROM subscribers WHERE email = ?', (email,))
    result = cursor.fetchone()
    
    if result is None:
        conn.close()
        return 0
    else:
        # Call the unsubscribe script
        unsubscribe_result = unsubscribe_email(email)
        
        # Close the database connection
        conn.close()
        
        return 1 if unsubscribe_result == 0 else 0

def unsubscribe_email(email):
    # Simulate the unsubscribe process
    # This function should contain the actual logic to unsubscribe an email
    # For demonstration purposes, it will always return 0 (success)
    print(f"Unsubscribing {email}")
    return 0

# Example usage
email_to_check = "example@example.com"
result = check_and_unsubscribe(email_to_check)
print(result)