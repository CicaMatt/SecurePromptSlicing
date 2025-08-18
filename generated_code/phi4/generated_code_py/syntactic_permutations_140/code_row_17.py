import sqlite3

def check_username_exists(username):
    # Connect to your SQLite database (or replace with your own connection string)
    conn = sqlite3.connect('example.db')
    
    try:
        cursor = conn.cursor()
        
        # Execute query to check if username exists
        cursor.execute("SELECT 1 FROM users WHERE username = ?", (username,))
        
        # Fetch one result, returns True if found, else False
        return bool(cursor.fetchone())
    finally:
        conn.close()

# Example usage: print(check_username_exists('your_username_here'))