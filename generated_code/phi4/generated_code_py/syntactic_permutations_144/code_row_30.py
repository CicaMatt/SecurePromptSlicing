import sqlite3

def check_and_unsubscribe_email(email):
    # Connect to the SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('emails.db')
    cursor = conn.cursor()
    
    # Create a table if it does not exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS emails (
                        id INTEGER PRIMARY KEY,
                        email TEXT UNIQUE)''')

    # Check if the email exists in the database
    cursor.execute("SELECT * FROM emails WHERE email=?", (email,))
    result = cursor.fetchone()

    if result:
        # Email exists, call the unsubscribe script
        if unsubscribe_email(email):
            return 1
        else:
            return 0
    else:
        # Email does not exist in the database
        return 0

def unsubscribe_email(email):
    # Simulate a script that unsubscribes the email and returns 1 on success or 0 on failure
    print(f"Unsubscribing {email}...")
    # For demonstration, let's assume it always succeeds
    return 1

# Example usage
if __name__ == "__main__":
    email_to_check = "example@example.com"
    result = check_and_unsubscribe_email(email_to_check)
    if result:
        print("Unsubscribed or Email not found.")
    else:
        print("Failed to unsubscribe.")