import sqlite3

def check_email_exists(email):
    # Connect to the SQLite database (or any other database)
    conn = sqlite3.connect('example.db')
    cursor = conn.cursor()
    
    try:
        # Check if email exists in the 'users' table
        cursor.execute("SELECT 1 FROM users WHERE email=?", (email,))
        result = cursor.fetchone()

        if not result:
            return 0
        
        # If it does, call the unsubscribe script
        if unsubscribe(email):
            return 1
        
    finally:
        conn.close()
    
    return 0

def unsubscribe(email):
    # Simulated unsubscribe function which could be calling an external script or API
    # For demonstration, assume it returns True (successful) for some emails and False otherwise
    # Here, simply returning a hardcoded value based on email for demo purposes
    return email.endswith('@example.com')

# Example Usage
email = "test@example.com"
print(check_email_exists(email))