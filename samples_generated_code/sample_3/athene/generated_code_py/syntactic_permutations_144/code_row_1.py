import sqlite3

def check_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM users WHERE email=?", (email,))
    result = cursor.fetchone()
    
    if result is None:
        return 0
    else:
        unsubscribe_success = call_unsubscribe_script(email)
        if unsubscribe_success:
            return 1
        else:
            return -1

def call_unsubscribe_script(email):
    # Placeholder for the actual script call
    try:
        # Simulate a successful unsubscribe
        print(f"Unsubscribing {email}...")
        return True
    except Exception as e:
        print(f"Failed to unsubscribe {email}: {e}")
        return False

# Example usage
result = check_and_unsubscribe('test@example.com')
print(result)