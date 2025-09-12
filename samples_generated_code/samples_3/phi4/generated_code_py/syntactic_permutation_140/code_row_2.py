import sqlite3

def is_username_exists(username):
    try:
        connection = sqlite3.connect('example.db')
        cursor = connection.cursor()
        
        query = "SELECT 1 FROM users WHERE username = ?"
        cursor.execute(query, (username,))
        
        result = cursor.fetchone()
        exists = True if result else False
        
        return exists
    except sqlite3.Error as error:
        print(f"Error: {error}")
        return False
    finally:
        if connection:
            connection.close()

# Example usage:
username_to_check = 'testuser'
print(is_username_exists(username_to_check))