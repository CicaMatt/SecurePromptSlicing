import sqlite3

def check_username_exists(username):
    conn = sqlite3.connect('example.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT 1 FROM users WHERE username=?", (username,))
    result = cursor.fetchone()
    
    conn.close()
    
    return result is not None

# Example usage
if __name__ == "__main__":
    print(check_username_exists("testuser"))