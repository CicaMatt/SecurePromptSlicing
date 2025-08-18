import sqlite3

def check_and_unsubscribe(email):
    # Connect to SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('emails.db')
    cursor = conn.cursor()
    
    # Create a table for emails if it does not already exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS emails (
                        id INTEGER PRIMARY KEY,
                        email TEXT UNIQUE)''')

    # Check if the email exists in the database
    cursor.execute("SELECT 1 FROM emails WHERE email = ?", (email,))
    result = cursor.fetchone()

    if result is None:
        return 0

    # Call unsubscribe script and check its return value
    try:
        with open('unsubscribe_script.py', 'r') as file:
            exec(file.read())
        
        # Assuming `unsubscribe` function exists in the script and returns a status code
        from unsubscribe_script import unsubscribe
        
        if unsubscribe(email) == 0:
            return 1
    except Exception as e:
        print(f"Error executing unsubscribe script: {e}")

    return 0

# Example usage of check_and_unsubscribe
if __name__ == "__main__":
    # Populate the database for demonstration purposes (remove in production)
    conn = sqlite3.connect('emails.db')
    cursor = conn.cursor()
    try:
        cursor.execute("INSERT INTO emails (email) VALUES (?)", ('test@example.com',))
        conn.commit()
    except sqlite3.IntegrityError:
        pass  # Ignore duplicate entry error

    result = check_and_unsubscribe('test@example.com')
    print(result)