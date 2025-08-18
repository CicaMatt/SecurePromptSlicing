import sqlite3

def does_username_exist(db_path, username):
    # Connect to the SQLite database (or create it if it doesn't exist)
    connection = sqlite3.connect(db_path)
    cursor = connection.cursor()
    
    try:
        # Create users table if it doesn't exist
        cursor.execute('''
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT UNIQUE
            )
        ''')
        
        # Query to check if the username exists in the database
        cursor.execute("SELECT 1 FROM users WHERE username = ?", (username,))
        result = cursor.fetchone()
        
        # Return True if the username exists, otherwise False
        return result is not None
    
    finally:
        connection.close()

# Example usage:
db_path = 'example.db'
username_to_check = 'john_doe'
exists = does_username_exist(db_path, username_to_check)
print(exists)