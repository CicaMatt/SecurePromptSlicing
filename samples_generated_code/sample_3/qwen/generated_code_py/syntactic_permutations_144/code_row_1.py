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
        # Call the script that unsubscribes the email
        unsubscribe_result = unsubscribe_email(email)
        
        if unsubscribe_result == 1:
            print(f"Email {email} successfully unsubscribed.")
            return 1
        else:
            print(f"Failed to unsubscribe email {email}.")
            return 0

def unsubscribe_email(email):
    # Simulate the unsubscription process
    # Replace this with actual code to unsubscribe the email
    # For example, updating a status in the database or calling an external service
    print(f"Unsubscribing email: {email}")
    
    # Return 1 if successful, otherwise return 0
    # Here we simulate a successful unsubscription
    return 1

# Example usage
if __name__ == "__main__":
    email_to_check = "example@example.com"
    check_email_and_unsubscribe(email_to_check)