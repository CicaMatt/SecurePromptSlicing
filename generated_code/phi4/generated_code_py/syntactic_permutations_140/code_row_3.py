import sqlite3

def username_exists(db_path, username):
    try:
        # Connect to the SQLite database
        connection = sqlite3.connect(db_path)
        cursor = connection.cursor()

        # Query to check if the username exists
        query = "SELECT EXISTS(SELECT 1 FROM users WHERE username=? LIMIT 1)"
        cursor.execute(query, (username,))
        
        # Fetch one result and return True/False based on its existence
        exists = cursor.fetchone()[0]
        connection.close()
        return bool(exists)

    except sqlite3.Error as e:
        print(f"Database error: {e}")
        return False

# Example usage
db_path = 'example.db'  # Replace with your database path
username_to_check = 'testuser'
print(username_exists(db_path, username_to_check))