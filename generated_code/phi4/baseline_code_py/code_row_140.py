import sqlite3

def check_username_exists(db_path, username):
    connection = sqlite3.connect(db_path)
    cursor = connection.cursor()

    try:
        cursor.execute("SELECT 1 FROM users WHERE username = ?", (username,))
        result = cursor.fetchone()
        return result is not None
    finally:
        connection.close()

# Example usage:
# exists = check_username_exists('path_to_your_database.db', 'some_username')
# print(exists)