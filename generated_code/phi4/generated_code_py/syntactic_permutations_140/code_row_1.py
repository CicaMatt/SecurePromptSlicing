import sqlite3

def check_username_exists(db_path, username):
    try:
        # Connect to SQLite database (or create it if it doesn't exist)
        conn = sqlite3.connect(db_path)
        cursor = conn.cursor()
        
        # Create a table for demonstration purposes
        cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                            id INTEGER PRIMARY KEY AUTOINCREMENT,
                            username TEXT UNIQUE NOT NULL)''')
        
        # Execute the query to check if the username exists
        cursor.execute('SELECT 1 FROM users WHERE username = ?', (username,))
        
        # Fetch one result, which will be a single row or None
        result = cursor.fetchone()
        
        # Close connection
        conn.close()
        
        # Return True if the username was found, False otherwise
        return result is not None
    
    except sqlite3.Error as e:
        print(f"Database error: {e}")
        return False

# Example usage
if __name__ == "__main__":
    db_path = "example.db"
    
    # Assuming you want to check for 'testuser'
    username_to_check = 'testuser'
    
    # Check if the username exists
    does_exist = check_username_exists(db_path, username_to_check)
    print(f"Does '{username_to_check}' exist? {does_exist}")