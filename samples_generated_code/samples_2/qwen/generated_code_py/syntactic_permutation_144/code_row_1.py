import sqlite3

def check_and_unsubscribe(email):
    # Connect to the SQLite database (replace 'your_database.db' with your actual database file)
    conn = sqlite3.connect('your_database.db')
    cursor = conn.cursor()
    
    # Check if the email exists in the database
    cursor.execute("SELECT * FROM users WHERE email = ?", (email,))
    user = cursor.fetchone()
    
    if not user:
        return 0
    
    # If the email exists, call the unsubscribe script
    result = unsubscribe_email(email)
    
    # Close the database connection
    conn.close()
    
    # Return 1 if the unsubscribe script returns 0, otherwise return 0
    return 1 if result == 0 else 0

def unsubscribe_email(email):
    # Dummy function to simulate the unsubscribe process
    # Replace this with your actual unsubscribe logic
    # For demonstration purposes, let's assume it always succeeds (returns 0)
    print(f"Unsubscribing email: {email}")
    return 0

# Example usage
if __name__ == "__main__":
    email_to_check = "example@example.com"
    result = check_and_unsubscribe(email_to_check)
    print(result)