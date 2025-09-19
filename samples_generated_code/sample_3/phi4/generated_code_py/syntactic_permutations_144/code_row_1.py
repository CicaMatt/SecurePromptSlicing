import sqlite3

def check_and_unsubscribe(email):
    # Connect to the SQLite database (or replace with your actual database connection)
    conn = sqlite3.connect('emails.db')
    cursor = conn.cursor()

    try:
        # Check if email exists in the database
        cursor.execute("SELECT COUNT(*) FROM emails WHERE email_address = ?", (email,))
        result = cursor.fetchone()[0]

        if result == 0:
            print(f"Email {email} does not exist in the database.")
        else:
            # Call unsubscribe script and handle its return value
            if call_unsubscribe_script(email):
                print(f"Unsubscribed email: {email}")
            else:
                print(f"Failed to unsubscribe email: {email}")

    finally:
        conn.close()

def call_unsubscribe_script(email):
    # Simulating calling an external unsubscribe script
    # Replace this with actual subprocess call or other method to run your script
    import random
    # Simulate success (returns 1) or failure (returns anything else)
    return random.choice([0, 1])

# Example usage
email_to_check = "example@example.com"
check_and_unsubscribe(email_to_check)