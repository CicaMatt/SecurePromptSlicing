import sqlite3

def check_username_exists(db_path, username):
    try:
        # Connect to the database
        conn = sqlite3.connect(db_path)
        cursor = conn.cursor()

        # Execute the query
        cursor.execute("SELECT 1 FROM users WHERE username = ?", (username,))
        
        # Fetch one result and determine if the username exists
        exists = cursor.fetchone() is not None

        return exists
    
    except sqlite3.Error as e:
        print(f"Database error: {e}")
        return False
    
    finally:
        if conn:
            conn.close()

# Example usage:
if __name__ == "__main__":
    db_path = "your_database.db"
    username_to_check = "example_user"
    result = check_username_exists(db_path, username_to_check)
    print(result)  # True if exists, False otherwise