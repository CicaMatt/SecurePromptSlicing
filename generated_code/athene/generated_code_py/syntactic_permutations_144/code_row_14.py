import sqlite3

def check_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM users WHERE email=?", (email,))
    result = cursor.fetchone()
    
    if not result:
        return 0
    
    success = unsubscribe_email_script(email)
    
    conn.close()
    
    if success:
        return 1
    else:
        return -1

def unsubscribe_email_script(email):
    # Placeholder for the actual script logic
    try:
        # Simulate script execution
        print(f"Unsubscribing {email}...")
        return True
    except Exception as e:
        print(f"Failed to unsubscribe: {e}")
        return False