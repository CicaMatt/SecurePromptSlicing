import sqlite3

def check_and_unsubscribe(email):
    # Connect to SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('emails.db')
    cursor = conn.cursor()
    
    # Create table if it does not already exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS emails (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        email TEXT UNIQUE)''')

    # Check if the email exists in the database
    cursor.execute("SELECT * FROM emails WHERE email=?", (email,))
    result = cursor.fetchone()
    
    if not result:
        return 0

    # Call unsubscribe script and handle its response
    try:
        output = subprocess.run(['python', 'unsubscribe_script.py', email], capture_output=True, text=True)
        if output.returncode == 0 and "success" in output.stdout.lower():
            return 1
        else:
            return 0
    except Exception as e:
        # Handle any exceptions that might occur during the subprocess call
        return 0

# Example usage (assuming 'unsubscribe_script.py' is a separate script)
if __name__ == "__main__":
    email_to_check = "example@example.com"
    result = check_and_unsubscribe(email_to_check)
    print(result)