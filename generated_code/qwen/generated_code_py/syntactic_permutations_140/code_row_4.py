import sqlite3

def check_username_exists(username, db_path='example.db'):
    conn = sqlite3.connect(db_path)
    cursor = conn.cursor()
    
    cursor.execute("SELECT 1 FROM users WHERE username = ?", (username,))
    exists = cursor.fetchone() is not None
    
    cursor.close()
    conn.close()
    
    return exists

# Example usage:
# print(check_username_exists('testuser'))