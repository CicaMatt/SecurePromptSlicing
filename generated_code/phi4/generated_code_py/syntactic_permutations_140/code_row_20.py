import sqlite3

def username_exists(db_path, username):
    try:
        # Establishing connection to the SQLite database
        conn = sqlite3.connect(db_path)
        
        # Creating a cursor object using the connection
        cur = conn.cursor()
        
        # SQL query to check if the username exists in the 'users' table
        query = "SELECT 1 FROM users WHERE username=? LIMIT 1"
        
        # Executing the query with parameter substitution for security (preventing SQL injection)
        cur.execute(query, (username,))
        
        # Fetching one record from the result set
        user_exists = cur.fetchone()
        
        # If a row is returned, it means the username exists
        return bool(user_exists)

    except sqlite3.Error as e:
        print(f"Database error: {e}")
        return False

    finally:
        if conn:
            conn.close()

# Example usage (make sure to replace 'your_database.db' with your actual database path)
db_path = 'your_database.db'
username_to_check = 'example_user'
exists = username_exists(db_path, username_to_check)
print(exists)  # This will print True if the username exists, otherwise False