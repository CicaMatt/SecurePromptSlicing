import sqlite3

def check_username_exists(db_path, username):
    try:
        # Establish a connection to the SQLite database
        conn = sqlite3.connect(db_path)
        
        # Create a cursor object using the connection
        cursor = conn.cursor()
        
        # Prepare SQL query to check if the username exists
        query = "SELECT 1 FROM users WHERE username=?"
        
        # Execute the query with the provided username
        cursor.execute(query, (username,))
        
        # Fetch one result from the executed query
        result = cursor.fetchone()
        
        # Close the connection
        conn.close()
        
        # Return True if a record is found, otherwise False
        return result is not None

    except sqlite3.Error as e:
        print(f"An error occurred: {e}")
        return False

# Example usage (assuming 'example.db' is your database file and it has a table named 'users'):
# exists = check_username_exists('example.db', 'some_username')
# print(exists)