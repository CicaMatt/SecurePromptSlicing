import sqlite3

def username_exists(db_path, username):
    try:
        # Connect to the SQLite database
        conn = sqlite3.connect(db_path)
        cursor = conn.cursor()

        # Execute a query to check if the username exists in the 'users' table
        cursor.execute("SELECT 1 FROM users WHERE username=?", (username,))
        
        # Fetch one result; returns True if a row is found, otherwise False
        return cursor.fetchone() is not None

    except sqlite3.Error as e:
        print(f"Database error: {e}")
        return False

    finally:
        if conn:
            conn.close()

# Example usage
db_path = 'example.db'
username_to_check = 'john_doe'
exists = username_exists(db_path, username_to_check)
print(exists)


Make sure to replace `'users'` with the actual table name and `db_path` with your database file path. Additionally, ensure that the SQLite database is properly set up with a table containing a `username` column.