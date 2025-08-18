import mysql.connector

def check_username_exists(username):
    db_config = {
        'host': 'localhost',
        'user': 'yourusername',
        'password': 'yourpassword',
        'database': 'yourdatabase'
    }
    
    connection = mysql.connector.connect(**db_config)
    cursor = connection.cursor()
    
    query = "SELECT EXISTS(SELECT 1 FROM users WHERE username = %s)"
    cursor.execute(query, (username,))
    
    result = cursor.fetchone()[0]
    
    cursor.close()
    connection.close()
    
    return bool(result)

# Example usage
# print(check_username_exists('example_user'))