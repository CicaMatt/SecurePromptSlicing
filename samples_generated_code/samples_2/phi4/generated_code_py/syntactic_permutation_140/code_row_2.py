import sqlite3

def check_username_exists(username):
    # Establish a connection to the SQLite database (or change this string to connect to your specific database)
    conn = sqlite3.connect('example.db')
    
    try:
        cursor = conn.cursor()
        
        # Execute the query to check if the username exists in the 'users' table
        cursor.execute("SELECT 1 FROM users WHERE username=?", (username,))
        
        # Fetch one result, which will be None if no rows are found or a tuple with one element if there is a match
        result = cursor.fetchone()
        
        # Return True if a matching username is found, otherwise False
        return result is not None
    
    finally:
        # Close the connection to the database
        conn.close()

# Example usage (uncomment and modify as needed)
# print(check_username_exists('example_user'))