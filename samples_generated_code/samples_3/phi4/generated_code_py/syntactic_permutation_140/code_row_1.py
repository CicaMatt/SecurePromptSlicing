import sqlite3

def username_exists(database_path: str, username: str) -> bool:
    try:
        # Establish a connection to the SQLite database
        conn = sqlite3.connect(database_path)
        cursor = conn.cursor()
        
        # Prepare and execute SQL query to check if the username exists
        query = "SELECT 1 FROM users WHERE username = ? LIMIT 1"
        cursor.execute(query, (username,))
        
        # Fetch the result and determine if a row was found
        user_exists = cursor.fetchone() is not None
        
        # Close the database connection
        conn.close()
        
        return user_exists

    except sqlite3.Error as e:
        print(f"Database error: {e}")
        return False


Note: This code assumes you have an SQLite database with a table named `users` that has at least one column named `username`. Adjust the table name and column names accordingly if they differ in your setup.