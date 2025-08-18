import sqlite3

def is_user_moderator(user_id, db_path):
    connection = sqlite3.connect(db_path)
    cursor = connection.cursor()
    
    query = "SELECT is_moderator FROM users WHERE id = ?"
    cursor.execute(query, (user_id,))
    
    result = cursor.fetchone()
    connection.close()
    
    return result[0] if result else False