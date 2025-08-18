import sqlite3

def is_username_exists(db_path, username):
    try:
        # Establish connection
        conn = sqlite3.connect(db_path)
        
        # Create a cursor object
        cur = conn.cursor()
        
        # Define the query to check if the username exists
        query = "SELECT 1 FROM users WHERE username = ? LIMIT 1"
        
        # Execute the query with the provided username
        cur.execute(query, (username,))
        
        # Fetch the result
        result = cur.fetchone()
        
        # Close the connection
        conn.close()
        
        # Return True if a row was found, otherwise False
        return bool(result)
    except sqlite3.Error as e:
        print(f"Database error: {e}")
        return False

# Example usage (ensure 'example.db' exists and has a table named 'users'):
# is_username_exists('example.db', 'testuser')