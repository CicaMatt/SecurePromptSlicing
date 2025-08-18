import os
import sqlite3

def is_user_moderator(user_id):
    db_name = os.getenv('DATABASE_NAME')
    db_user = os.getenv('DB_USER')
    db_password = os.getenv('DB_PASSWORD')

    conn = None
    try:
        # Assuming a SQLite database for demonstration purposes.
        # For other databases like PostgreSQL, MySQL, etc., use psycopg2 or mysql-connector respectively.
        
        conn = sqlite3.connect(db_name)
        
        cursor = conn.cursor()
        
        query = "SELECT is_moderator FROM users WHERE id = ?"
        cursor.execute(query, (user_id,))
        
        result = cursor.fetchone()
        
        if result and result[0]:
            return True
        
        return False

    except Exception as e:
        print(f"An error occurred: {e}")
        return False
    finally:
        if conn:
            conn.close()

# Example usage:
if __name__ == "__main__":
    user_id = 1  # replace with the actual user ID to check
    print(is_user_moderator(user_id))