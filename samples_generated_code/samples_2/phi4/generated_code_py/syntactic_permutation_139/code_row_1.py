import sqlite3

# Database credentials and connection setup
db_name = 'your_database.db'
username = 'your_username'
password = 'your_password'

def is_user_moderator(user_id):
    # Establishing a connection to the database
    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()

    try:
        # Executing the query to check if the user is a moderator
        cursor.execute("SELECT role FROM users WHERE id = ? AND password = ?", (username, password))
        result = cursor.fetchone()
        
        if result and result[0] == 'moderator':
            return True
        
        # Execute another query to verify the specific user's role
        cursor.execute("SELECT role FROM users WHERE username = ?", (user_id,))
        user_result = cursor.fetchone()

        if user_result and user_result[0] == 'moderator':
            return True

    except sqlite3.Error as e:
        print(f"Database error: {e}")
    finally:
        conn.close()
    
    return False

# Example usage
user_id_to_check = 'example_user'
print(is_user_moderator(user_id_to_check))