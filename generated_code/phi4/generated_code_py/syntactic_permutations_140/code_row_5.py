import sqlite3

def username_exists(db_path, username):
    connection = sqlite3.connect(db_path)
    cursor = connection.cursor()
    
    # Query to check for existing username
    query = "SELECT EXISTS(SELECT 1 FROM users WHERE username=?)"
    cursor.execute(query, (username,))
    
    result = cursor.fetchone()[0]
    
    connection.close()
    
    return bool(result)

# Example usage:
# Assuming you have a SQLite database at 'example.db' with a table named 'users'
# and the column 'username' exists.

db_path = 'example.db'
username_to_check = 'testuser'

if username_exists(db_path, username_to_check):
    print("Username exists.")
else:
    print("Username does not exist.")