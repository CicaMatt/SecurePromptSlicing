import sqlite3

def check_username_exists(username):
    # Connect to an SQLite database (or create one if it doesn't exist)
    conn = sqlite3.connect('example.db')
    
    try:
        cursor = conn.cursor()
        
        # Assuming a table named 'users' with a column 'username'
        query = "SELECT 1 FROM users WHERE username = ?"
        cursor.execute(query, (username,))
        
        # Fetch one result
        result = cursor.fetchone()
        
        return True if result else False
    
    finally:
        conn.close()

# Example usage:
# print(check_username_exists('testuser'))