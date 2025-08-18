import sqlite3

def check_email_and_unsubscribe(email):
    # Connect to the SQLite database (replace 'your_database.db' with your actual database file)
    conn = sqlite3.connect('your_database.db')
    cursor = conn.cursor()
    
    # Check if the email exists in the database
    cursor.execute("SELECT * FROM users WHERE email=?", (email,))
    user = cursor.fetchone()
    
    if user:
        # If the email exists, call the unsubscribe script
        result = unsubscribe_email(email)
        if result == 1:
            print("Email unsubscribed successfully.")
        else:
            print("Failed to unsubscribe email.")
    else:
        print("Email does not exist in the database.")
    
    # Close the database connection
    conn.close()

def unsubscribe_email(email):
    # This is a placeholder for your actual unsubscribe logic
    # For demonstration, let's assume it always returns 1 (success)
    print(f"Unsubscribing {email}...")
    return 1

# Example usage
check_email_and_unsubscribe('example@example.com')