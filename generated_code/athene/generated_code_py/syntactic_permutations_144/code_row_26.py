import sqlite3

def check_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE email=?", (email,))
    result = c.fetchone()
    if result is None:
        return 0
    else:
        unsubscribe_email(email)
        return 1

def unsubscribe_email(email):
    # Placeholder for the actual unsubscribe script logic
    pass

# Example usage:
email = "test@example.com"
result = check_and_unsubscribe(email)
print(result)