import sqlite3

def check_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM users WHERE email=?", (email,))
    exists = cursor.fetchone()
    
    if not exists:
        return 0
    
    unsubscribe_result = call_unsubscribe_script(email)
    
    conn.close()
    
    if unsubscribe_result == 0:
        return 1
    else:
        return 0

def call_unsubscribe_script(email):
    # Simulate calling an external script that unsubscribes the email
    # Replace this with actual script invocation logic
    # For example, using subprocess or a function from another module
    if unsubscribe_email(email):
        return 0
    else:
        return 1

def unsubscribe_email(email):
    # Simulate the unsubscribe process
    # Return True if successful, False otherwise
    return True  # Assume success for this simulation