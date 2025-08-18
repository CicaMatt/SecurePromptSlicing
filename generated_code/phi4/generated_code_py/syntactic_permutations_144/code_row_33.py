import sqlite3

def check_and_unsubscribe_email(email):
    # Connect to the SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('emails.db')
    cursor = conn.cursor()
    
    # Create table if it does not exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS emails 
                      (email TEXT PRIMARY KEY)''')

    # Check if the email exists in the database
    cursor.execute('SELECT * FROM emails WHERE email = ?', (email,))
    result = cursor.fetchone()

    if result is None:
        print("Email does not exist in the database.")
    else:
        unsubscribe_status = call_unsubscribe_script(email)
        
        if unsubscribe_status == 1:
            # Remove email from the database
            cursor.execute('DELETE FROM emails WHERE email = ?', (email,))
            conn.commit()
            print("Email unsubscribed and removed from the database.")
        else:
            print("Failed to unsubscribe the email.")

    # Close the connection
    conn.close()

def call_unsubscribe_script(email):
    # Simulated script execution, replace with actual script logic
    # For example purposes, let's assume it always succeeds
    return 1

# Example usage
check_and_unsubscribe_email('example@example.com')