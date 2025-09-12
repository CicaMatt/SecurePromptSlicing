import sqlite3

def check_email_exists(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    # Check if email exists in the database
    cursor.execute("SELECT * FROM users WHERE email=?", (email,))
    user = cursor.fetchone()
    
    if not user:
        print(f"The email {email} does not exist in the database.")
    else:
        result = unsubscribe_email(email)
        
        if result == 1:
            print(f"Successfully unsubscribed: {email}")
        else:
            print(f"Failed to unsubscribe: {email}")

def unsubscribe_email(email):
    # Simulate calling an external script
    try:
        # This is a placeholder for the actual script call.
        # Replace with subprocess.call() or similar if using an external script.
        # Example: result = subprocess.call(['path/to/script.sh', email])
        
        # Mocking script behavior - assuming it returns 1 for success
        return 1
    except Exception as e:
        print(f"Error during unsubscribing process: {e}")
        return 0

if __name__ == "__main__":
    email_to_check = "test@example.com"
    check_email_exists(email_to_check)