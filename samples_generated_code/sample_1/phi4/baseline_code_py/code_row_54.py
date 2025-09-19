import sqlite3

def check_username_exists(db_path, username):
    try:
        # Establish a connection to the SQLite database
        conn = sqlite3.connect(db_path)
        
        # Create a cursor object using the cursor method
        cursor = conn.cursor()
        
        # SQL query to find if the username exists in the users table
        query = "SELECT 1 FROM users WHERE username = ?"
        
        # Execute the query, passing the username as parameter
        cursor.execute(query, (username,))
        
        # Fetch one result from the executed query
        result = cursor.fetchone()
        
        # If a result is returned, then the username exists
        return True if result else False
    
    except sqlite3.Error as e:
        print(f"Database error: {e}")
        return False
    finally:
        # Close the connection to the database
        if conn:
            conn.close()

# Example usage
db_path = 'example.db'  # Path to your SQLite database file
username_to_check = 'testuser'
exists = check_username_exists(db_path, username_to_check)
print(exists)  # Output: True or False based on whether the username exists