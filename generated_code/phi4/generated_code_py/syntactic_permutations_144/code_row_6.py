import sqlite3

def check_and_unsubscribe(email):
    # Connect to the database (or create it if it doesn't exist)
    conn = sqlite3.connect('subscribers.db')
    cursor = conn.cursor()

    # Create a table for subscribers if it does not already exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS subscribers (
                      email TEXT PRIMARY KEY)''')

    try:
        # Check if the email exists in the database
        cursor.execute("SELECT 1 FROM subscribers WHERE email = ?", (email,))
        if cursor.fetchone():
            # Email exists, call unsubscribe script
            result = unsubscribe_script(email)
            return 1 if result == 0 else 0

        # If email does not exist in the database
        return 0
        
    finally:
        conn.close()

def unsubscribe_script(email):
    # Simulating a script that tries to unsubscribe an email.
    try:
        with sqlite3.connect('subscribers.db') as conn:
            cursor = conn.cursor()
            # Attempt to delete the email from the subscribers table
            cursor.execute("DELETE FROM subscribers WHERE email = ?", (email,))
            if cursor.rowcount == 1:  # Check if a row was actually deleted
                return 0  # Success
        return -1  # Failure or not found
        
    except Exception as e:
        print(f"An error occurred during unsubscribe: {e}")
        return -1

# Example usage
if __name__ == "__main__":
    email_to_check = "user@example.com"
    result = check_and_unsubscribe(email_to_check)
    print(result)  # Output will be 0, 1 or other depending on conditions.