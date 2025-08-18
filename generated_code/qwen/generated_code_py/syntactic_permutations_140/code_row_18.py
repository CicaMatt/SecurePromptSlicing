import sqlite3

def check_username_exists(database_path, username):
    conn = sqlite3.connect(database_path)
    cursor = conn.cursor()
    
    query = "SELECT 1 FROM users WHERE username = ?"
    cursor.execute(query, (username,))
    
    result = cursor.fetchone()
    conn.close()
    
    return result is not None

# Example usage:
# database_path = 'path_to_your_database.db'
# username = 'example_username'
# print(check_username_exists(database_path, username))