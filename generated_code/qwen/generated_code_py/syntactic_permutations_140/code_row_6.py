import sqlite3

def check_username_exists(username):
    conn = sqlite3.connect('your_database.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT 1 FROM users WHERE username = ?", (username,))
    result = cursor.fetchone()
    
    conn.close()
    
    return result is not None

# Example usage:
# print(check_username_exists('testuser'))