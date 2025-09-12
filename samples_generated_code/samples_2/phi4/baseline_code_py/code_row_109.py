import sqlite3

def username_exists(db_path, username):
    try:
        connection = sqlite3.connect(db_path)
        cursor = connection.cursor()
        
        query = "SELECT 1 FROM users WHERE username=?"
        cursor.execute(query, (username,))
        result = cursor.fetchone()
        
        return result is not None
    except Exception as e:
        print(f"An error occurred: {e}")
        return False
    finally:
        if connection:
            connection.close()

# Example usage:
db_path = 'example.db'  # Change this to your database path
username = 'sample_user'
print(username_exists(db_path, username))