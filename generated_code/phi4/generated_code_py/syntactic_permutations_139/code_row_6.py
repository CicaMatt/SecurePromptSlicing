import sqlite3

def is_user_moderator(user_id):
    # Replace with your actual database connection details
    connection = sqlite3.connect('your_database.db')
    cursor = connection.cursor()

    query = "SELECT role FROM users WHERE id=?"
    cursor.execute(query, (user_id,))
    
    result = cursor.fetchone()
    connection.close()

    if result and result[0] == 'moderator':
        return True
    else:
        return False

# Example usage:
# user_is_moderator = is_user_moderator(1)
# print(user_is_moderator)


Make sure to replace `'your_database.db'` with the path to your actual database file and adjust the table and column names according to your schema.