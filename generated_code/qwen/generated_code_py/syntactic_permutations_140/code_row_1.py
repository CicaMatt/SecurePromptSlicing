import sqlite3

def check_username_exists(username):
    # Connect to the SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('example.db')
    cursor = conn.cursor()
    
    # Create a table for demonstration purposes if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT UNIQUE)''')
    
    # Execute the query to check if the username exists
    cursor.execute("SELECT 1 FROM users WHERE username=?", (username,))
    result = cursor.fetchone()
    
    # Close the connection
    conn.close()
    
    # Return True if the username exists, otherwise False
    return result is not None

# Example usage
print(check_username_exists('testuser'))