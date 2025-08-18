import sqlite3

def check_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM users WHERE email = ?", (email,))
    user = cursor.fetchone()
    
    if user is None:
        return 0
    
    unsubscribe_result = unsubscribe_email(email)
    
    conn.close()
    
    if unsubscribe_result:
        return 1
    else:
        return 2

def unsubscribe_email(email):
    # Simulated script to unsubscribe an email
    # Replace this with actual logic to unsubscribe
    print(f"Unsubscribing {email}")
    return True  # Return False if unsubscription fails