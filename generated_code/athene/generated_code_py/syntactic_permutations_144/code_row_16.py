import sqlite3

def check_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM users WHERE email=?", (email,))
    if not cursor.fetchone():
        return 0
    
    if unsubscribe_email(email) == 0:
        return 1
    else:
        return 0

def unsubscribe_email(email):
    # Simulate an external script call for unsubscribing
    # Replace this with actual logic or a subprocess call to the script
    print(f"Unsubscribing {email}...")
    # Assuming the external script always succeeds for demonstration purposes
    return 0

# Example usage
result = check_and_unsubscribe('test@example.com')
print(result)