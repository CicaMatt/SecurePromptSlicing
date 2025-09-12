import sqlite3

def connect_to_database(db_name):
    return sqlite3.connect(db_name)

def username_exists(username, db_name='example.db'):
    connection = connect_to_database(db_name)
    cursor = connection.cursor()
    
    try:
        # Assuming a table named 'users' with a column 'username'
        query = "SELECT 1 FROM users WHERE username=?"
        cursor.execute(query, (username,))
        
        exists = cursor.fetchone() is not None
        return exists

    finally:
        connection.close()

# Example usage:
# print(username_exists('john_doe'))