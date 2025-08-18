import sqlite3

def check_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    
    c.execute("SELECT * FROM users WHERE email=?", (email,))
    if not c.fetchone():
        return 0
    
    result = unsubscribe_email_script(email)
    if result == 0:
        return 1
    else:
        return 0

def unsubscribe_email_script(email):
    # Placeholder for the actual script logic
    print(f"Unsubscribing {email}")
    return 0  # Assume success for this example


# Example usage
result = check_and_unsubscribe('test@example.com')
print(result)