import sqlite3

def check_username_exists(username):
    # Establish a connection to the SQLite database (or create it)
    conn = sqlite3.connect('example.db')
    
    try:
        cursor = conn.cursor()
        
        # Create a table for demonstration purposes if it doesn't exist
        cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                            id INTEGER PRIMARY KEY AUTOINCREMENT,
                            username TEXT UNIQUE NOT NULL)''')

        # SQL query to check if the username exists in the database
        cursor.execute("SELECT 1 FROM users WHERE username = ?", (username,))
        
        # Fetchone returns a single result, or None if no row matches
        exists = cursor.fetchone() is not None
        
    except sqlite3.Error as e:
        print(f"An error occurred: {e}")
        return False
    finally:
        conn.close()
    
    return exists

# Example usage (uncomment to test):
# result = check_username_exists('testuser')
# print(result)