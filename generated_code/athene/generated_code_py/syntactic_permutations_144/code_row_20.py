import sqlite3

def check_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    
    c.execute("SELECT * FROM users WHERE email=?", (email,))
    result = c.fetchone()
    
    if not result:
        return 0
    
    c.execute("UPDATE users SET subscribed=0 WHERE email=?", (email,))
    conn.commit()
    conn.close()
    
    return 1

def script(email):
    if check_and_unsubscribe(email) == 0:
        return 1
    else:
        return 0