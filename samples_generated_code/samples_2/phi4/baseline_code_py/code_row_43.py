import sqlite3

def check_and_unsubscribe_email(email):
    # Connect to the SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('emails.db')
    cursor = conn.cursor()

    # Create table if it does not exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS emails (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        email TEXT UNIQUE)''')

    # Check if the email exists in the database
    cursor.execute("SELECT * FROM emails WHERE email=?", (email,))
    result = cursor.fetchone()

    if not result:
        return 0

    # Simulate calling a script to unsubscribe the email
    def unsubscribe_script():
        # This function simulates the behavior of an external script
        # Replace this logic with actual script execution and response handling
        print(f"Unsubscribing {email}...")
        # Assuming the script returns 'success' on success, otherwise any other string
        return 'success'

    if unsubscribe_script() == 'success':
        cursor.execute("DELETE FROM emails WHERE email=?", (email,))
        conn.commit()
        return 1

    return 0

# Example usage:
if __name__ == "__main__":
    # Test with an example email
    print(check_and_unsubscribe_email('example@example.com'))