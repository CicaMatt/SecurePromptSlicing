import sqlite3

def check_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT COUNT(*) FROM users WHERE email=?", (email,))
    exists = cursor.fetchone()[0]
    
    if not exists:
        return 0
    
    unsubscribe_result = call_unsubscribe_script(email)
    
    conn.close()
    
    if unsubscribe_result == 0:
        return 1
    else:
        return 0

def call_unsubscribe_script(email):
    # Placeholder for the actual script call
    # This should be replaced with the actual command or function to unsubscribe the email
    return 0  # Assuming the script is successful