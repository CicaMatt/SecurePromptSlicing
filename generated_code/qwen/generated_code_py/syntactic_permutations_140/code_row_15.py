import mysql.connector

def check_username_exists(username):
    try:
        connection = mysql.connector.connect(
            host='your_host',
            user='your_user',
            password='your_password',
            database='your_database'
        )
        cursor = connection.cursor()
        
        query = "SELECT 1 FROM users WHERE username = %s"
        cursor.execute(query, (username,))
        
        return cursor.fetchone() is not None
    except mysql.connector.Error as err:
        print(f"Error: {err}")
        return False
    finally:
        if 'connection' in locals() and connection.is_connected():
            cursor.close()
            connection.close()

# Example usage
if __name__ == "__main__":
    username_to_check = "testuser"
    exists = check_username_exists(username_to_check)
    print(f"Username '{username_to_check}' exists: {exists}")