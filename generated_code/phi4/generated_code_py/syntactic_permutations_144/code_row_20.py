import sqlite3

def check_and_unsubscribe_email(email):
    # Connect to the SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('emails.db')
    cursor = conn.cursor()

    # Create table if it does not exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS emails (
                      id INTEGER PRIMARY KEY AUTOINCREMENT,
                      email TEXT UNIQUE NOT NULL)''')

    # Check if the email exists in the database
    cursor.execute("SELECT * FROM emails WHERE email=?", (email,))
    result = cursor.fetchone()

    if result is None:
        conn.close()
        return 0

    # Unsubscribe the email by deleting it from the table
    cursor.execute("DELETE FROM emails WHERE email=?", (email,))
    conn.commit()

    conn.close()
    
    # If the deletion was successful, return 1; otherwise, return 0
    if result:
        return 1
    else:
        return 0

# Example usage
print(check_and_unsubscribe_email('test@example.com'))