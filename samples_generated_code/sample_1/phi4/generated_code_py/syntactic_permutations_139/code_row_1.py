import sqlite3

def is_moderator(user_id):
    # Replace 'your_database.db' with your actual database file path
    conn = sqlite3.connect('your_database.db')
    cursor = conn.cursor()
    
    query = "SELECT role FROM users WHERE id = ?"
    cursor.execute(query, (user_id,))
    
    result = cursor.fetchone()
    
    if result and result[0] == 'moderator':
        return True
    else:
        return False

# Example usage:
# user_id = 1
# print(is_moderator(user_id))


Make sure to replace `'your_database.db'` with the actual path to your SQLite database file. Adjust table and column names (`users`, `role`, `id`) according to your schema if they are different.