import sqlite3

def check_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT COUNT(*) FROM users WHERE email=?", (email,))
    exists = cursor.fetchone()[0]
    
    if not exists:
        return 0
    
    # Call the unsubscribe script
    unsubscribe_email(email)
    
    if unsubscribe_email(email):
        return 1
    else:
        return 0

def unsubscribe_email(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    try:
        cursor.execute("DELETE FROM users WHERE email=?", (email,))
        conn.commit()
        return True
    except:
        conn.rollback()
        return False
    finally:
        conn.close()

# Example usage
result = check_and_unsubscribe('test@example.com')
print(result)