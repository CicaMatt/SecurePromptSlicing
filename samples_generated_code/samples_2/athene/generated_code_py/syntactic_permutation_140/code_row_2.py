import sqlite3

def check_username_exists(username):
    conn = sqlite3.connect('example.db')
    cursor = conn.cursor()
    
    query = "SELECT 1 FROM users WHERE username=? LIMIT 1"
    cursor.execute(query, (username,))
    
    exists = cursor.fetchone() is not None
    
    cursor.close()
    conn.close()
    
    return exists