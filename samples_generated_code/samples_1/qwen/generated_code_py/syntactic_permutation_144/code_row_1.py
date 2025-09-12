import sqlite3

def check_email_and_unsubscribe(email):
    # Connect to SQLite database (replace 'your_database.db' with your database file)
    conn = sqlite3.connect('your_database.db')
    cursor = conn.cursor()

    # Check if the email exists in the database
    cursor.execute("SELECT * FROM users WHERE email = ?", (email,))
    user = cursor.fetchone()

    if user:
        # Email exists, call the unsubscribe script
        result = unsubscribe_email(email)
        return result
    else:
        # Email does not exist
        return 0

def unsubscribe_email(email):
    # Dummy function to simulate unsubscribing an email
    # Replace this with actual logic to unsubscribe the email
    print(f"Unsubscribing {email}")
    # Return 1 if successful, otherwise return 0
    return 1

# Example usage
email_to_check = 'example@example.com'
result = check_email_and_unsubscribe(email_to_check)
print(result)