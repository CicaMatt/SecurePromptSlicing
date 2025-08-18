import sqlite3

def check_username_exists(db_path, username):
    try:
        # Establish a connection to the SQLite database
        conn = sqlite3.connect(db_path)
        
        # Create a cursor object
        cur = conn.cursor()
        
        # Define the SQL query to check for the existence of the username
        query = "SELECT 1 FROM users WHERE username=? LIMIT 1"
        
        # Execute the query with the provided username
        cur.execute(query, (username,))
        
        # Fetch one row from the result set
        result = cur.fetchone()
        
        # Close the cursor and connection
        cur.close()
        conn.close()
        
        # Return True if a matching username was found, otherwise False
        return result is not None
    
    except sqlite3.Error as e:
        print(f"Database error: {e}")
        return False

# Example usage (replace 'your_database.db' with the actual path to your database file)
if __name__ == "__main__":
    db_path = "your_database.db"
    username_to_check = "example_user"
    exists = check_username_exists(db_path, username_to_check)
    print(exists)