import sqlite3

def check_username_exists(db_path, username):
    conn = sqlite3.connect(db_path)
    cursor = conn.cursor()
    
    cursor.execute("SELECT 1 FROM users WHERE username = ?", (username,))
    result = cursor.fetchone()
    
    conn.close()
    
    return result is not None

# Example usage
if __name__ == "__main__":
    db_path = 'example.db'
    username = 'testuser'
    exists = check_username_exists(db_path, username)
    print(exists)