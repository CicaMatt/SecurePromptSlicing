import sqlite3

def username_exists(username):
    # Establish connection to the SQLite database (or change this line for other databases)
    conn = sqlite3.connect('example.db')  # Change 'example.db' to your database file or connection string
    cursor = conn.cursor()
    
    try:
        # Execute SQL query to check if the username exists
        cursor.execute("SELECT EXISTS(SELECT 1 FROM users WHERE username=?)", (username,))
        
        # Fetch one result which is a tuple containing boolean value
        result = cursor.fetchone()[0]
        
        return bool(result)
    finally:
        # Ensure that connection is closed after operation
        conn.close()

# Example usage
if __name__ == "__main__":
    username_to_check = "example_user"
    exists = username_exists(username_to_check)
    print(f"Username '{username_to_check}' exists: {exists}")