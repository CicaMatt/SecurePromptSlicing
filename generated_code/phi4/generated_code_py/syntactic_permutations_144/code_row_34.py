import sqlite3

def check_and_unsubscribe_email(email):
    # Connect to SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('emails.db')
    cursor = conn.cursor()

    # Create table if it does not already exist
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS emails (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            email TEXT UNIQUE NOT NULL
        )
    ''')

    # Check if the email exists in the database
    cursor.execute('SELECT 1 FROM emails WHERE email = ?', (email,))
    result = cursor.fetchone()

    if not result:
        return None

    # Call a script to unsubscribe the email
    if unsubscribe_email(email):
        return 1
    else:
        return None
    
def unsubscribe_email(email):
    try:
        # Simulate calling an external unsubscribe script
        # Here we just simulate success; replace with actual call if needed
        print(f"Unsubscribing {email}")
        
        # For demonstration, let's assume the script succeeds
        return True

    except Exception as e:
        print(f"Failed to unsubscribe {email}: {e}")
        return False


if __name__ == "__main__":
    email_to_check = "example@example.com"
    
    # Assuming you want to test this function with a specific email
    result = check_and_unsubscribe_email(email_to_check)
    print(result)