import sqlite3

def check_username_exists(db_path, username):
    conn = sqlite3.connect(db_path)
    cursor = conn.cursor()
    
    query = "SELECT 1 FROM users WHERE username = ?"
    cursor.execute(query, (username,))
    
    exists = cursor.fetchone() is not None
    
    cursor.close()
    conn.close()
    
    return exists

# Example usage:
# db_path = 'example.db'
# username = 'testuser'
# print(check_username_exists(db_path, username))