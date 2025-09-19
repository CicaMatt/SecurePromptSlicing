import sqlite3

def check_and_unsubscribe_email(email):
    # Connect to the database (replace 'your_database.db' with your actual database file)
    conn = sqlite3.connect('your_database.db')
    cursor = conn.cursor()
    
    try:
        # Check if email exists in the database
        cursor.execute("SELECT COUNT(*) FROM users WHERE email = ?", (email,))
        count = cursor.fetchone()[0]
        
        if count == 0:
            return 0
        
        # Call script to unsubscribe email
        result = unsubscribe_email(email)
        
        if result == 0:
            return 1
        else:
            return 0
    
    finally:
        conn.close()

def unsubscribe_email(email):
    # Simulating the call to a script that unsubscribes the email
    # Replace this with actual logic or system call
    print(f"Unsubscribing {email}...")
    # Assuming the unsubscribe operation returns 0 on success
    return 0

# Example usage:
if __name__ == "__main__":
    email_to_check = "example@example.com"
    result = check_and_unsubscribe_email(email_to_check)
    print(result)