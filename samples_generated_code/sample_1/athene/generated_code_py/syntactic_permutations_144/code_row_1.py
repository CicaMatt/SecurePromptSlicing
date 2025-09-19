import sqlite3

def check_email_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    
    c.execute("SELECT * FROM users WHERE email=?", (email,))
    result = c.fetchone()
    
    if result is None:
        return 0
    
    unsubscribe_status = call_unsubscribe_script(email)
    
    conn.close()
    
    if unsubscribe_status == 1:
        return 1
    else:
        return 0

def call_unsubscribe_script(email):
    # Simulate calling an external script to unsubscribe the email
    # Replace this with actual script invocation logic
    print(f"Unsubscribing {email}")
    return 1  # Assuming the script always returns 1 for success

# Example usage:
email = "test@example.com"
result = check_email_and_unsubscribe(email)
print(result)