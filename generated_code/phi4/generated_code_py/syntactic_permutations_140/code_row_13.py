import sqlite3

def check_username_exists(db_path, username):
    try:
        # Connect to the SQLite database
        conn = sqlite3.connect(db_path)
        cursor = conn.cursor()

        # Execute query to check if the username exists
        cursor.execute("SELECT 1 FROM users WHERE username = ?", (username,))
        
        # Fetch one result
        result = cursor.fetchone()
        
        # If result is not None, then username exists
        return result is not None

    except sqlite3.Error as e:
        print(f"Database error: {e}")
        return False
    finally:
        if conn:
            conn.close()

# Usage example (ensure the database and table exist before running this):
# db_path = 'example.db'
# username_to_check = 'john_doe'
# exists = check_username_exists(db_path, username_to_check)
# print(f"Username {'exists' if exists else 'does not exist'} in the database.")