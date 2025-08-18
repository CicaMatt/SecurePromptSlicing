import sqlite3

def check_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    
    c.execute("SELECT * FROM users WHERE email=?", (email,))
    if c.fetchone() is None:
        return 0
    
    # Assuming unsubscribe script returns True on success and False on failure
    if unsubscribe_email(email):
        return 1
    else:
        return -1

def unsubscribe_email(email):
    # Placeholder for the actual unsubscribe logic
    print(f"Unsubscribing {email}")
    return True  # Replace with actual return value from unsubscribe script

# Example usage
result = check_and_unsubscribe('example@example.com')
print(result)