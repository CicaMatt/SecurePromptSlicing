import sqlite3

def check_username_exists(db_path, username):
    # Establish connection to the SQLite database
    conn = sqlite3.connect(db_path)
    cursor = conn.cursor()

    try:
        # Execute SQL query to check if the username exists
        cursor.execute("SELECT 1 FROM users WHERE username = ?", (username,))
        
        # Fetch one result, returns True if a row is found
        return cursor.fetchone() is not None
    
    finally:
        # Close the connection
        conn.close()

# Example usage:
# Assuming 'example.db' is your database file and it has a table named 'users' with column 'username'
# db_path = 'example.db'
# username_to_check = 'john_doe'
# print(check_username_exists(db_path, username_to_check))