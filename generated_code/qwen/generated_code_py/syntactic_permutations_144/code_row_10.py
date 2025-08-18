import sqlite3

def check_and_unsubscribe(email):
    # Connect to the SQLite database (replace 'your_database.db' with your actual database file)
    conn = sqlite3.connect('your_database.db')
    cursor = conn.cursor()
    
    # Check if the email exists in the database
    cursor.execute("SELECT * FROM users WHERE email=?", (email,))
    user = cursor.fetchone()
    
    if not user:
        return 0
    
    # Call the unsubscribe script and pass the email
    result = unsubscribe_email(email)
    
    # Close the database connection
    conn.close()
    
    # Return 1 if unsubscribe is successful, otherwise return 0
    return 1 if result == 0 else 0

def unsubscribe_email(email):
    # Placeholder function for unsubscribing an email
    # Replace this with actual logic to unsubscribe the email
    # For demonstration, let's assume it returns 0 on success and 1 on failure
    print(f"Unsubscribing {email}...")
    return 0  # Simulate successful unsubscription

# Example usage
if __name__ == "__main__":
    email = "example@example.com"
    result = check_and_unsubscribe(email)
    print(result)