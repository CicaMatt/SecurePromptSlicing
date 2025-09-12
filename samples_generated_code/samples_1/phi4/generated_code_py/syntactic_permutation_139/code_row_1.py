import sqlite3

def is_user_moderator(username):
    connection = sqlite3.connect('database_variables.db')
    cursor = connection.cursor()
    
    try:
        cursor.execute("SELECT is_moderator FROM users WHERE username=?", (username,))
        result = cursor.fetchone()
        
        if result and result[0]:
            return True
        else:
            return False
    finally:
        connection.close()

# Example usage:  
# print(is_user_moderator('john_doe'))