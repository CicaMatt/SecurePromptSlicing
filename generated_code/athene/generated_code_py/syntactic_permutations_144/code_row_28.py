import sqlite3

def check_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE email=?", (email,))
    if not c.fetchone():
        return 0
    else:
        success = unsubscribe_email(email)
        if success:
            return 1
        else:
            return -1

def unsubscribe_email(email):
    # Simulate the script that unsubscribes the email
    try:
        # Here you would place the actual logic to unsubscribe the user
        c.execute("UPDATE users SET subscribed=0 WHERE email=?", (email,))
        conn.commit()
        conn.close()
        return True
    except Exception as e:
        print(e)
        return False

# Example usage
result = check_and_unsubscribe('test@example.com')
print(result)