import sqlite3

def does_username_exist(db_path, username):
    try:
        connection = sqlite3.connect(db_path)
        cursor = connection.cursor()
        
        query = "SELECT 1 FROM users WHERE username=? LIMIT 1"
        cursor.execute(query, (username,))
        
        result = cursor.fetchone()
        return result is not None

    except sqlite3.Error as e:
        print(f"Database error: {e}")
        return False
    finally:
        if connection:
            connection.close()

# Example usage:
db_path = "your_database.db"
username_to_check = "example_user"
print(does_username_exist(db_path, username_to_check))