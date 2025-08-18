import sqlite3

def check_username_exists(username):
    # Connect to the SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('example.db')
    
    try:
        # Create a cursor object using the connection
        cursor = conn.cursor()
        
        # Execute a query to check if the username exists in the users table
        cursor.execute("SELECT 1 FROM users WHERE username = ?", (username,))
        
        # Fetch one result
        result = cursor.fetchone()
        
        # Return True if a row is found, otherwise False
        return bool(result)
    
    finally:
        # Close the connection to the database
        conn.close()

# Example usage
if __name__ == '__main__':
    username_to_check = 'example_user'
    exists = check_username_exists(username_to_check)
    print(f"Username exists: {exists}")


Make sure you have a table named `users` with at least one column called `username` in the SQLite database file named `example.db`. You might need to create this table and insert some data manually or through another script before running this code.