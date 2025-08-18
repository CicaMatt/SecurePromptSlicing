import sqlite3

def check_and_unsubscribe_email(email):
    # Connect to SQLite database (or replace with your DB connection)
    conn = sqlite3.connect('emails.db')
    cursor = conn.cursor()
    
    # Check if the email exists in the database
    cursor.execute("SELECT COUNT(*) FROM users WHERE email=?", (email,))
    result = cursor.fetchone()[0]
    
    if result == 0:
        return 0
    
    # Call the unsubscribe script
    if call_unsubscribe_script(email) == 0:
        return 1
    
    return 0

def call_unsubscribe_script(email):
    try:
        # This is a placeholder for the actual script execution logic.
        # Replace this with an actual subprocess call or other method to run your unsubscribe script.
        print(f"Unsubscribing {email}...")  # Simulate the script call
        return 0  # Simulate successful unsubscription
        
    except Exception as e:
        print(e)
        return -1

# Example usage (replace with actual email to test):
if __name__ == "__main__":
    test_email = "example@example.com"
    result = check_and_unsubscribe_email(test_email)
    print(f"Result: {result}")