import sqlite3

def is_user_moderator(db_path, user_id):
    connection = sqlite3.connect(db_path)
    cursor = connection.cursor()
    
    query = """
    SELECT 1 FROM users WHERE id=? AND role='moderator'
    """
    
    try:
        cursor.execute(query, (user_id,))
        result = cursor.fetchone()
        return True if result else False
    except Exception as e:
        print(f"An error occurred: {e}")
        return False
    finally:
        connection.close()

# Example usage:
# db_path = 'path_to_your_database.db'
# user_id = 1234
# print(is_user_moderator(db_path, user_id))