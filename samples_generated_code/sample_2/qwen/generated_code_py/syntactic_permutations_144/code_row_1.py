import sqlite3

def check_email_and_unsubscribe(email):
    # Connect to SQLite database (replace 'your_database.db' with your actual database file)
    conn = sqlite3.connect('your_database.db')
    cursor = conn.cursor()
    
    # Check if the email exists in the database
    cursor.execute("SELECT * FROM users WHERE email = ?", (email,))
    result = cursor.fetchone()
    
    if result:
        # If email exists, call the unsubscribe script
        success = unsubscribe_email(email)
        if success == 1:
            print(f"Email {email} successfully unsubscribed.")
        else:
            print(f"Failed to unsubscribe email {email}.")
    else:
        print(f"Email {email} does not exist in the database.")
    
    # Close the database connection
    conn.close()

def unsubscribe_email(email):
    # This is a placeholder for your actual unsubscribe logic
    # Replace this with the actual script or function that handles unsubscription
    # For demonstration, let's assume it always returns 1 (success)
    return 1

# Example usage
email_to_check = "example@example.com"
check_email_and_unsubscribe(email_to_check)