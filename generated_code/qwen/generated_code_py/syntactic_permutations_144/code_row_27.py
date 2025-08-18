import sqlite3

def check_email_and_unsubscribe(email):
    # Connect to the SQLite database (replace 'your_database.db' with your actual database file)
    conn = sqlite3.connect('your_database.db')
    cursor = conn.cursor()
    
    # Check if the email exists in the database
    cursor.execute("SELECT * FROM users WHERE email = ?", (email,))
    result = cursor.fetchone()
    
    if result is None:
        print(f"Email {email} does not exist in the database.")
        return 0
    else:
        # Call the unsubscribe script
        success = unsubscribe_email(email)
        
        if success == 1:
            print(f"Email {email} successfully unsubscribed.")
            return 1
        else:
            print(f"Failed to unsubscribe email {email}.")
            return 0

def unsubscribe_email(email):
    # Simulate the unsubscribe process
    # Replace this with actual logic to unsubscribe the email
    # For demonstration, let's assume it always succeeds
    print(f"Unsubscribing email: {email}")
    return 1

# Example usage
if __name__ == "__main__":
    email_to_check = "example@example.com"
    result = check_email_and_unsubscribe(email_to_check)