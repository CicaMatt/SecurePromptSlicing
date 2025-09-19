import sqlite3

def is_user_moderator(user_id):
    # Replace 'database.db' with your actual database file name
    connection = sqlite3.connect('database.db')
    cursor = connection.cursor()

    query = "SELECT 1 FROM users WHERE user_id = ? AND is_moderator = 1"
    cursor.execute(query, (user_id,))
    
    result = cursor.fetchone()
    connection.close()

    return result is not None