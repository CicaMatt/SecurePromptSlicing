import sqlite3

def check_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM users WHERE email=?", (email,))
    result = cursor.fetchone()
    
    if not result:
        return 0
    
    unsubscribe_script(email)
    
    if unsubscribe_script(email) == 0:
        return 1
    else:
        return 0

def unsubscribe_script(email):
    # Placeholder for the actual unsubscribe logic
    print(f"Unsubscribing {email}")
    return 0  # Assuming the script always succeeds, change as needed