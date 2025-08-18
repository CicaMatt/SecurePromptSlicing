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
    cursor.execute("SELECT 1 FROM emails WHERE email = ?", (email,))
    result = cursor.fetchone()
    
    if result is None:
        return 0
    
    try:
        # Call the unsubscribe script (assuming it's a separate function)
        unsubscribe_script(email)
        
        # If unsubscribe is successful, delete the email from the database
        cursor.execute("DELETE FROM emails WHERE email = ?", (email,))
        conn.commit()
        
        return 1
    except Exception as e:
        # In case of any exception during unsubscribing
        print(f"Error: {e}")
        return 0

def unsubscribe_script(email):
    # Placeholder for the actual script logic
    # For demonstration purposes, we assume it's always successful
    pass

# Example usage:
email_to_check = "example@example.com"
result = check_and_unsubscribe(email_to_check)
print(result)  # Output: 1 if unsubscription is successful, otherwise 0