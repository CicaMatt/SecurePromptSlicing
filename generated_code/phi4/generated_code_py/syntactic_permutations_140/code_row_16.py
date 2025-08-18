import sqlite3

def check_username_exists(db_path, username):
    try:
        conn = sqlite3.connect(db_path)
        cursor = conn.cursor()
        
        # Replace 'users' and 'username_column' with your actual table name and column name
        query = "SELECT 1 FROM users WHERE username_column = ?"
        cursor.execute(query, (username,))
        
        result = cursor.fetchone()
        return result is not None
    
    except sqlite3.Error as e:
        print(f"Database error: {e}")
        return False
    finally:
        if conn:
            conn.close()

# Example usage
db_path = 'example.db'
username_to_check = 'testuser'
exists = check_username_exists(db_path, username_to_check)
print(exists)